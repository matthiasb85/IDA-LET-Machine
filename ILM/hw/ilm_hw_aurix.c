/**
 * \file ilm_hw_aurix.c
 * \brief Capture Compare based hardware port for the AURIX microcontroller family
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
 *  Created on: 23.05.2017
 *      Author: matthiasb
 */

#include "ILM/if/ilm_hw_port.h"
#include "ILM/if/ilm_os_port.h"
#include "Ccu6/Timer/IfxCcu6_Timer.h"
#include "Ccu6/Std/IfxCcu6.h"

#define ILM_TC2YX_SRN_PRIORITY(prio)     	(((uint32)(prio)) & (uint32)0x7FU)			/**< \brief Macro for IRQ priority conf.  */
#define ILM_TC2YX_SRN_ENABLE               	((uint32)1U << 10U)							/**< \brief Macro to enable SRN           */
#define ILM_TC2YX_SRN_TYPE_OF_SERVICE(tos) 	((((uint32)(tos)) & (uint32)0x3U) << 11U)	/**< \brief Macro to set type of service  */
#define ILM_TC2YX_SRN_CLEAR_REQUEST        	((uint32)1U << 25U)							/**< \brief Macro to clear service request*/
#define ILM_TC2YX_SRN_SET_REQUEST          	((uint32)1U << 26U)							/**< \brief Macro to set service request  */

static volatile IfxCcu6_Timer 				_ILM_HW_TIMER;								/**< \brief Local timer handle            */
static volatile ILM_HW_LET_TABLE_T * 		_ILM_HW_Table = (ILM_HW_LET_TABLE_T *)NULL;	/**< \brief Local value for table pointer */
static volatile uint32 						_ILM_HW_TableSize = 0;						/**< \brief Local value for table size    */
static volatile uint16 						_ILM_HW_TableIdx = 0;						/**< \brief Current table index           */
static volatile float32 					_ILM_HW_PeriodScale = 0.0;					/**< \brief Scaling factor for CCU values */

/**
 * \brief Internal helper function for compare value calculation
 * \param NextIdx Next index for compare value
 * \return Scaled value for CCU
 */
static ILM_OFFSET_T _ILM_HW_CalcCompare(uint16 NextIdx)
{
	return (ILM_OFFSET_T)(((float32)_ILM_HW_Table[NextIdx].Offset)*_ILM_HW_PeriodScale);
}

/**
 * \brief Send software IRQ to CoreId
 * \param CoreId Identifier of target core
 * \return None
 */
static void _ILM_HW_SendSoftIrq(uint32 CoreId)
{
	switch(CoreId)
	{
	case 1:
		SRC_GPSR11.U |= ILM_TC2YX_SRN_SET_REQUEST;
		break;
	case 2:
		SRC_GPSR21.U |= ILM_TC2YX_SRN_SET_REQUEST;
		break;
	case 0:
	default:
		break;
	}
}

/**
 * \brief Init function for CCU based IRQ generation
 * \param pTable Pointer to compare table
 * \param TableSize Length of referenced compare table
 * \param Freq Tick frequency(granularity) for compare table entries
 * \param MacroPeriod Macro period of compare table
 * \return None
 */
void __attribute__((unused)) ILM_HW_Init(ILM_HW_LET_TABLE_T * pTable, uint32 TableSize, uint32 Freq, uint32 MacroPeriod)
{

	if(pTable == NULL || Freq == 0 || MacroPeriod == 0)
		return;

	_ILM_HW_Table = pTable;
	_ILM_HW_TableIdx = 0;
	_ILM_HW_TableSize = TableSize;

	/*
	 * Initialize configuration struct
	 */
	IfxCcu6_Timer_Config TimerConfig;
	IfxCcu6_Timer_initModuleConfig(&TimerConfig, &MODULE_CCU60);

	/*
	 * Set "PWM" frequency to (Freq/MacroPeriod)
	 * (Ticks/s) / (Ticks / Period)
	 *
	 */
	TimerConfig.base.t13Frequency = ((float32)Freq)/((float32)MacroPeriod);
	TimerConfig.base.t13Period = MacroPeriod;

	/*
	 * Use T13, without synchronousOperation
	 */
	TimerConfig.timer = IfxCcu6_TimerId_t13;
	TimerConfig.synchronousOperation = FALSE;

	/*
	 * Setup clock source, reset counter value
	 */
	TimerConfig.clock.t13ExtClockEnabled     = FALSE;
	TimerConfig.clock.t13ExtClockInput       = NULL_PTR;
	TimerConfig.clock.t13countingInputMode   = IfxCcu6_CountingInputMode_internal;
	TimerConfig.timer13.counterValue         = 0;

	/*
	 * Setup CCU IRQ
	 */
	TimerConfig.interrupt1.source            = IfxCcu6_InterruptSource_t13CompareMatch;
	TimerConfig.interrupt1.serviceRequest    = IfxCcu6_ServiceRequest_1;
	TimerConfig.interrupt1.priority          = ILM_HW_HARD_IRQ;
	TimerConfig.interrupt1.typeOfService     = (IfxSrc_Tos)IfxCpu_getCoreId();

	/*
	 * Neither input, nor output triggering
	 */
	TimerConfig.pins = NULL_PTR;
	TimerConfig.trigger.t12ExtInputTrigger   = NULL_PTR;
	TimerConfig.trigger.t13ExtInputTrigger   = NULL_PTR;
	TimerConfig.trigger.extInputTriggerMode  = IfxCcu6_ExternalTriggerMode_disable;
	TimerConfig.trigger.t13InSyncWithT12     = FALSE;

	/*
	 * Pass config struct to init function
	 */
	IfxCcu6_Timer_initModule((IfxCcu6_Timer *)&_ILM_HW_TIMER, &TimerConfig);

	/*
	 * Calculate scaling factor based on the internal
	 * clock source.
	 */
	_ILM_HW_PeriodScale =((float32)_ILM_HW_TIMER.ccu6->T13PR.U) / ((float32)MacroPeriod);

#if ILM_USE_HW_SOFT_IRQ > 0
	/*
	 * Setup core-2-core software IRQs
	 */
	SRC_GPSR11.U = ILM_TC2YX_SRN_TYPE_OF_SERVICE(1U) | ILM_TC2YX_SRN_ENABLE | ILM_TC2YX_SRN_PRIORITY(ILM_HW_SOFT_IRQ);
	SRC_GPSR21.U = ILM_TC2YX_SRN_TYPE_OF_SERVICE(2U) | ILM_TC2YX_SRN_ENABLE | ILM_TC2YX_SRN_PRIORITY(ILM_HW_SOFT_IRQ);
#endif

#if defined(ERIKA_OS)
	/*
	 * Not needed, as done by ERIKA
	 */
#else
	/*
	 * Register IRQ handler
	 */
	IfxCpu_Irq_installInterruptHandler(&ILM_HW_Isr_Master, ILM_HW_HARD_IRQ);
	IfxCpu_enableInterrupts();
#endif

}

/**
 * \brief Start hardware timer
 * \return None
 */
void ILM_HW_StartTimer(void)
{
	IfxCcu6_setT13CaptureCompareState(_ILM_HW_TIMER.ccu6, IfxCcu6_CaptureCompareState_clear);
    IfxCcu6_setT13CounterValue(_ILM_HW_TIMER.ccu6, _ILM_HW_CalcCompare(0) + 2);
	IfxCcu6_Timer_start((IfxCcu6_Timer *)&_ILM_HW_TIMER);
	_ILM_HW_TIMER.ccu6->CC63SR.B.CCS = _ILM_HW_CalcCompare(0);
}

/**
 * \brief IRQ handler for master core C0, called from OS implementation
 * \return State for local ILM_Handler (1 execute, 0 skip)
 */
uint32 __attribute__((unused)) ILM_HW_Isr_Master(void)
{
	uint32 ret = 0;
	uint32 CoreMask = _ILM_HW_Table[_ILM_HW_TableIdx].CoreMask;
	uint16 NextIdx = (_ILM_HW_TableIdx + 1) % _ILM_HW_TableSize;

	/*
	 * Handle CCU IRQ,
	 * set core sync barrier,
	 * set new reload value and
	 * restart the timer
	 */
	IfxCcu6_Timer_stop((IfxCcu6_Timer *)&_ILM_HW_TIMER);
	ILM_OS_Set_BarrierMask(CoreMask);
	IfxCcu6_setT13CaptureCompareState(_ILM_HW_TIMER.ccu6, IfxCcu6_CaptureCompareState_clear);
	_ILM_HW_TIMER.ccu6->CC63SR.B.CCS = _ILM_HW_CalcCompare(NextIdx);
	IfxCcu6_Timer_start((IfxCcu6_Timer *)&_ILM_HW_TIMER);

	/*
	 * Redirect IRQ to other cores
	 */
#if ILM_USE_HW_SOFT_IRQ == 0
	ILM_OS_ActivateILMCoreTasks(CoreMask);
#else
	uint32 i = 0;
	for(i=1; i < ILM_NUM_OF_CORES; i++)
	{
		if(CoreMask & (1 << i))
			_ILM_HW_SendSoftIrq(i);
	}
	/*
	 * Check if this core should also
	 * call the ILM_Handler
	 */
	ret = CoreMask & (ILM_COREMASK_C0);
#endif
	_ILM_HW_TableIdx = NextIdx;

	return ret;
}

#if ILM_USE_HW_SOFT_IRQ > 0
/**
 * \brief IRQ handler for software IRQ on C1 or C2, called from OS implementation
 * \param CoreId Identifier for current core
 */
void __attribute__((unused)) ILM_HW_Isr_Slave(uint32 CoreId)
{
	/*
	 * Generic ack. mechanism for soft IRQ on slave cores
	 */
	switch(CoreId)
	{
	case 1:
		SRC_GPSR11.U |= ILM_TC2YX_SRN_CLEAR_REQUEST;
		break;
	case 2:
		SRC_GPSR21.U |= ILM_TC2YX_SRN_CLEAR_REQUEST;
		break;
	case 0:
	default:
		break;
	}
}
#endif
