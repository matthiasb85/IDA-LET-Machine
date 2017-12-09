/**
 * \file ilm_os_port.h
 * \brief API definition for operating system port
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

#ifndef ILM_OS_PORT_H_
#define ILM_OS_PORT_H_

/**
 * \brief Activate OS task
 * \param TaskId Task identifier
 * \return None
 */
extern void ILM_OS_ActivateTask(ILM_TASKS_T TaskId);

/**
 * \brief Set event for waiting ECC task
 * \param TaskId Task identifier
 * \param pEvent Pointer to event struct/Id
 * \return None
 */
extern void ILM_OS_SetEvent(ILM_TASKS_T TaskId, void *pEvent);

/**
 * \brief Wait until all necessary cores reached the synchronization barrier
 * \return None
 */
extern void ILM_OS_SyncCores(void);

/**
 * \brief Set barrier mask, should only be called from the master core
 * \param CoreMask Bitmask of included cores
 * \return None
 */
extern void ILM_OS_Set_BarrierMask(ILM_COREMASK_T CoreMask);

/**
 * \brief Returns current state of the container task, 1 (running/ready) or 0 (suspended/waiting)
 * \param TaskId Task identifier
 * \return Current state of the container task
 */
extern uint32 ILM_OS_CheckTaskState(ILM_TASKS_T TaskId);

/**
 * \brief Activate ILM handler (as a task) on a remote core
 * \param CoreMask Bitmask of included cores with remote tasks
 * \return None
 */
extern void ILM_OS_ActivateILMCoreTasks(ILM_COREMASK_T CoreMask);

#endif /* ILM_OS_PORT_H_ */
