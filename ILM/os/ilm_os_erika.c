/**
 * \file ilm_os_erika.c
 * \brief Operating system port for ERIKAOS
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
 *  Created on: 09.05.2017
 *      Author: matthiasb
 */

#include "ILM/if/ilm_core.h"
#include "ILM/if/ilm_hw_port.h"
#include "ILM/if/ilm_os_port.h"
#include "ee.h"
#include "ee_internal.h"

#if ILM_USE_HW_SOFT_IRQ == 0
static unit32 _ILM_OS_CORE_TASK_LOOKUP[ILM_NUM_OF_CORES] = {C0_ILM, C1_ILM, C2_ILM}	/**< \brief Task id lookup table for ILM_Handler tasks*/
#endif

#if (EE_CURRENTCPU == 0)  /* EE_MASTER_CPU (EE_CURRENTCPU == 0) */
/*
 * Synchronization barriers get linked to the C0 binary
 */
EE_TYPEBARRIER 	EE_SHARED_UDATA 	_ILM_OS_Barrier;			/**< \brief Synchronization barrier         */
EE_UREG 		EE_SHARED_UDATA 	_ILM_OS_BarrierMask;		/**< \brief Synchronization barrier bitmask */
#else
extern EE_TYPEBARRIER 				_ILM_OS_Barrier;			/**< \brief External reference to synchronization barrier         */
extern EE_UREG 						_ILM_OS_BarrierMask;		/**< \brief External reference to synchronization barrier bitmask */
#endif
#define ILM_OS_SPINLOCK	4										/**< \brief Spinlock ID for synchronization barrier               */

/**
 * \brief Call core handler and sync cores
 * \return None
 */
static void __attribute__((unused)) _ILM_OS_CallHandler(void)
{
	ILM_Handler(0);
	ILM_OS_SyncCores();
}

/**
 * \brief Wait until all necessary cores reached the synchronization barrier, stripped version of EE_hal_sync_barrier
 * \return None
 */
void __attribute__ ((noinline)) ILM_OS_SyncCores(void)
{
#if ILM_USE_OS_MIN_BARRIER > 0
	EE_hal_spin_in(ILM_OS_SPINLOCK);
	/* Set current CPU as entered */
	_ILM_OS_Barrier.value |= ((EE_UINT32)1U << EE_CURRENTCPU);
	EE_hal_spin_out(ILM_OS_SPINLOCK);
	/* Wait for all other cores/CPUs */
	while ( _ILM_OS_Barrier.value != _ILM_OS_BarrierMask );
#else
	EE_hal_sync_barrier(&_ILM_OS_Barrier, &_ILM_OS_BarrierMask);
#endif
}

/**
 * \brief Activate OS task
 * \param TaskId Task identifier
 * \return None
 */
void ILM_OS_ActivateTask(ILM_TASKS_T TaskId)
{
	ActivateTask((TaskType)TaskId);
}

/**
 * \brief Set event for waiting ECC task
 * \param TaskId Task identifier
 * \param pEvent Pointer to event struct/Id
 * \return None
 */
void ILM_OS_SetEvent(ILM_TASKS_T TaskId, void *pEvent)
{
#if ILM_USE_OSEK_ECC > 0
	SetEvent((TaskType)TaskId, (EventMaskType)pEvent);
#else
	(void)TaskId;
	(void)pEvent;
#endif
}

/**
 * \brief Set barrier mask, should only be called from the master core
 * \param CoreMask Bitmask of included cores
 * \return None
 */
void ILM_OS_Set_BarrierMask(ILM_COREMASK_T CoreMask)
{
#if (EE_CURRENTCPU == 0)
	_ILM_OS_Barrier.value = 0;
	_ILM_OS_BarrierMask = (EE_UREG)CoreMask;
#else
	(void)CoreMask;
#endif
}

#if ILM_USE_HOOK_MISS_LET > 0
/**
 * \brief Returns current state of the container task, 1 (running/ready) or 0 (suspended/waiting)
 * \param TaskId Task identifier
 * \return Current state of the container task
 */
uint32 ILM_OS_CheckTaskState(ILM_TASKS_T TaskId)
{
	TaskStateType State = 0;
	StatusType Ret =  GetTaskState((TaskType)TaskId, &State);
	return (Ret == E_OK && (State == RUNNING || State == READY)) ? 1 : 0;
}
#endif

#if ILM_USE_HW_SOFT_IRQ == 0
/**
 * \brief Activate ILM handler (as a task) on a remote core
 * \param CoreMask Bitmask of included cores with remote tasks
 * \return None
 */
void ILM_OS_ActivateILMCoreTasks(ILM_COREMASK_T CoreMask)
{
	uint32 i = 0;
	for(i=0; i < ILM_NUM_OF_CORES; i++)
	{
		if(CoreMask & (1 << i))
			ILM_OS_ActivateTask(_ILM_OS_CORE_TASK_LOOKUP[i]);
	}
}
#endif

/*
 * Define IRQ start hook
 */
#if ILM_USE_HOOK_START_IRQ > 0
#define IRQ_START() ILM_HOOK_START_IRQ()			/**< \brief Macro for IRQ Start Hook          */
#else
#define IRQ_START()									/**< \brief Macro for IRQ Start Hook          */
#endif

/*
 * Define IRQ stop hook
 */
#if ILM_USE_HOOK_STOP_IRQ > 0
#define IRQ_STOP() ILM_HOOK_STOP_IRQ()				/**< \brief Macro for IRQ Stop Hook           */
#else
#define IRQ_STOP()									/**< \brief Macro for IRQ Stop Hook           */
#endif

#if ILM_USE_HW_CCU > 0
#if ILM_USE_HW_SOFT_IRQ > 0
/*
 * Register IRQ handler as ISR2 for a system
 * with remote activation via software IRQs
 */
#if (EE_CURRENTCPU == 0)
ISR2(ILM_OS_Isr) {IRQ_START(); if(ILM_HW_Isr_Master()) _ILM_OS_CallHandler(); IRQ_STOP(); }
#elif (EE_CURRENTCPU == 1)
ISR2(ILM_OS_Isr) {IRQ_START(); ILM_HW_Isr_Slave(EE_CURRENTCPU); _ILM_OS_CallHandler(); IRQ_STOP(); }
#elif (EE_CURRENTCPU == 2)
ISR2(ILM_OS_Isr) {IRQ_START(); ILM_HW_Isr_Slave(EE_CURRENTCPU); _ILM_OS_CallHandler(); IRQ_STOP();}
#endif
#else
/*
 * Register IRQ handler as ISR2 for a system
 * with remote activation via task activate
 * (all ILM_Handler execute in task context)
 */
#if (EE_CURRENTCPU == 0)
ISR1(ILM_OS_Isr) {ILM_HW_Isr();}
TASK(C0_ILM){ _ILM_OS_CallHandler(); TerminateTask();}
#elif (EE_CURRENTCPU == 1)
TASK(C1_ILM){ _ILM_OS_CallHandler(); TerminateTask();}
#elif (EE_CURRENTCPU == 2)
TASK(C2_ILM){ _ILM_OS_CallHandler(); TerminateTask();}
#endif
#endif
#endif
