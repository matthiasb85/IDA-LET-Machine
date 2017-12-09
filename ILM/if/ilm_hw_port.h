/**
 * \file ilm_hw_port.h
 * \brief API definition for hardware port
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

#ifndef ILM_HW_PORT_H_
#define ILM_HW_PORT_H_

#include "ILM/if/ilm_core.h"

/**
 * \brief IRQ handler for master core C0, called from OS implementation
 * \return State for local ILM_Handler (1 execute, 0 skip)
 */
extern uint32 ILM_HW_Isr_Master(void);

/**
 * \brief IRQ handler for software IRQ on C1 or C2, called from OS implementation
 * \param CoreId Identifier for current core
 */
extern void ILM_HW_Isr_Slave(uint32 CoreId);

/**
 * \brief Init function for CCU based IRQ generation
 * \param pTable Pointer to compare table
 * \param TableSize Length of referenced compare table
 * \param Freq Tick frequency(granularity) for compare table entries
 * \param MacroPeriod Macro period of compare table
 * \return None
 */
extern void ILM_HW_Init(ILM_HW_LET_TABLE_T * pTable, uint32 TableSize, uint32 Freq, uint32 MacroPeriod);

/**
 * \brief Start hardware timer
 * \return None
 */
extern void ILM_HW_StartTimer(void);

#endif /* ILM_HW_PORT_H_ */
