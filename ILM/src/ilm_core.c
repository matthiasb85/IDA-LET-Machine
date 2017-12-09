/**
 * \file ilm_core.c
 * \brief Core module of the IDA-LET-Machine
 * \ingroup ILM
 */

/*
 * This file is part of The ILM, The IDA-LET-Machine.
 *
 * Copyright (c) 2017 Matthias Beckert <beckert@ida.ing.tu-bs.de>
 *
 * The ILM is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Linking this code statically or dynamically with other modules is
 * making a combined work based on this code.  Thus, the terms and
 * conditions of the GNU General Public License cover the whole
 * combination.
 *
 * As a special exception, the copyright holders of this library give you
 * permission to link this code with independent modules to produce an
 * executable, regardless of the license terms of these independent
 * modules, and to copy and distribute the resulting executable under
 * terms of your choice, provided that you also meet, for each linked
 * independent module, the terms and conditions of the license of that
 * module.  An independent module is a module which is not derived from
 * or based on this library.  If you modify this code, you may extend
 * this exception to your version of the code, but you are not
 * obligated to do so.  If you do not wish to do so, delete this
 * exception statement from your version.
 *
 * The ILM is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * ILM - The IDA-LET-Machine
 *
 *  Created on: 08.05.2017
 *      Author: matthiasb
 */

#include "ILM/if/ilm_core.h"
#include "ILM/if/ilm_os_port.h"
#include "ILM/if/ilm_hooks.h"

static ILM_LET_TABLE_T * 	_ILM_Table 			= (void *)0;	/**< \brief Local value for table pointer */
static uint32 				_ILM_TableSize 		= 0;			/**< \brief Local value for table size    */
static uint32 				_ILM_MacroPeriod 	= 0;			/**< \brief Local value for macro period  */
static uint32				_ILM_TableIdx		= 0;			/**< \brief Current table index           */
static uint8				_ILM_SystemReady	= 0;			/**< \brief Current system state          */

#if ILM_USE_HW_CCU == 0
static uint32				_ILM_LastStart		= 0;			/**< \brief Only needed for software emulated CCU */
#endif

/**
 * \brief Internal function for read pointer backup
 * \param pData Pointer to data struct
 * \return None
 */
static void _ILM_BackupReadPointer(ILM_DATA_IN_T *pData)
{
	/*
	 * Backup Input Data
	 * "Zero-Time" Communication
	 *  -> Enforce "Delayed Read"
	 */
	if(pData)
	{
		while(pData->pInput)
		{
			pData->pLocalCopy = pData->pInput->Read.Generic;
			pData++;
		}
	}
}

/**
 * \brief Internal function for event table processing
 * \param pEntry Current table entry
 * \return None
 */
static void _ILM_EventHandling(ILM_LET_TABLE_T * pEntry)
{
	uint16 OldOffset = pEntry->Offset;
	/*
	 * Process all entries with the same offset
	 */
	while(pEntry->Offset == OldOffset )
	{
		if((pEntry->Type & ILM_EVENT_TACT) == ILM_EVENT_TACT)
		{
			/*
			 * Backup read pointer first if needed
			 */
			_ILM_BackupReadPointer(pEntry->Payload.pDataIn);
			/*
			 * Activate task
			 */
			ILM_OS_ActivateTask(pEntry->TaskId);
#if ILM_USE_HOOK_TACT	> 0
			ILM_HOOK_TACT(pEntry);
#endif
		}
		else
		{
#if ILM_USE_PRIOB	> 0
			if((pEntry->Type & ILM_EVENT_PRIOB) == ILM_EVENT_PRIOB)
			{
				/* not implmented yet*/
#if ILM_USE_HOOK_PRIOB	> 0
				ILM_HOOK_PRIOB(pEntry);
#endif
			}
#endif
			if((pEntry->Type & ILM_EVENT_PSWAP) == ILM_EVENT_PSWAP)
			{
				/*
				 * Simple pointer swap
				 * "Zero-Time" Communication
				 *  -> Enforce "Early Write"
				 *  -> Marks end of LET
				 */
#if ILM_USE_HOOK_MISS_LET > 0
				if(ILM_OS_CheckTaskState(pEntry->TaskId) == 1)
					ILM_HOOK_MISS_LET(pEntry);
#endif
				ILM_DATA_OUT_T * pData = pEntry->Payload.pDataOut;
				void * Backup = pData->Read.Generic;
				pData->Read.Generic = pData->Write.Generic;
				pData->Write.Generic = Backup;
#if ILM_USE_HOOK_PSWAP	> 0
				ILM_HOOK_PSWAP(pEntry);
#endif
			}
			if((pEntry->Type & ILM_EVENT_LETEV) == ILM_EVENT_LETEV)
			{
				/*
				 * Backup read pointer first if needed
				 */
				_ILM_BackupReadPointer(pEntry->Payload.pDataIn);
#if ILM_USE_OSEK_ECC > 0
				/*
				 * Use set event if ECC tasks are used
				 */
				ILM_OS_SetEvent(pEntry->TaskId, pEntry->Payload.pSchedEvent);
#else
				/*
				 * Use task activate if BCC tasks are used
				 */
				ILM_OS_ActivateTask(pEntry->TaskId);
#endif
#if ILM_USE_HOOK_LETEV	> 0
				ILM_HOOK_LETEV(pEntry);
#endif
			}
			if((pEntry->Type & ILM_EVENT_TTERM) == ILM_EVENT_TTERM)
			{
#if ILM_USE_TERM_CTX > 0
				/*
				 * Set event for task termination
				 */
				ILM_OS_SetEvent(pEntry->TaskId, pEntry->Payload.pSchedEvent);
#endif
#if ILM_USE_HOOK_TTERM	> 0
				ILM_HOOK_TTERM(pEntry);
#endif
			}
		}
		_ILM_TableIdx = (_ILM_TableIdx + 1) % _ILM_TableSize;
		OldOffset = pEntry->Offset;
		pEntry = &_ILM_Table[_ILM_TableIdx];

	}

}

/**
 * \brief Handler function for IRQ or time tick based LET event processing\n
 * If ILM_USE_HW_CCU == 0 the function should be called within the time tick\n
 * for software based CCU emulation
 * \param CurTick Current time tick value, only needed if ILM_Hander is called\n
 * from a task context
 * \return None
 */
void __attribute__((unused)) ILM_Handler(uint32 CurTick)
{
#if ILM_USE_HOOK_START_ILM	> 0
	ILM_HOOK_START_ILM_HANDLER();
#endif
	if(!_ILM_Table)
		return;
#if ILM_USE_HW_CCU > 0
	(void)CurTick;
#endif
#if ILM_USE_HW_CCU == 0
	if(_ILM_SystemReady > 0)
	{
		if(_ILM_SystemReady == 1)
		{
			_ILM_LastStart = CurTick;
			_ILM_SystemReady = 2;
		}
#endif
		ILM_LET_TABLE_T * pEntry = &_ILM_Table[_ILM_TableIdx];
#if ILM_USE_HW_CCU == 0
		if(_ILM_LastStart + pEntry->Offset == CurTick )
		{
#endif
			/*
			 * Call LET event handler
			 */
			_ILM_EventHandling(pEntry);
#if ILM_USE_HW_CCU == 0
			if(_ILM_TableIdx == 0)
				_ILM_LastStart = _ILM_LastStart + _ILM_MacroPeriod;
		}
	}
#endif
#if ILM_USE_HOOK_STOP_ILM > 0
	ILM_HOOK_STOP_ILM_HANDLER();
#endif
}


/**
 * \brief Init function for ILM core module
 * \param pTable Pointer to LET table
 * \param TableSize Length of the table located at pTable
 * \param MacroPeriod Macro period of the provided LET table
 * \return None
 */
void __attribute__((unused)) ILM_Init(ILM_LET_TABLE_T *pTable, uint32 TableSize, uint32 MacroPeriod)
{
	if(pTable == (ILM_LET_TABLE_T *)0)
		return;
	if(TableSize == 0)
		return;
	if(MacroPeriod == 0)
		return;

	_ILM_SystemReady = 0;
	_ILM_Table = pTable;
	_ILM_TableSize = TableSize;
	_ILM_MacroPeriod = MacroPeriod;
	_ILM_TableIdx = 0;
	_ILM_SystemReady = 1;
}
