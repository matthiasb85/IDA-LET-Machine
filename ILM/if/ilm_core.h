/**
 * \file ilm_core.h
 * \brief Toplevel include for core module API
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
 *  Created on: 08.05.2017
 *      Author: matthiasb
 */

#ifndef ILM_CORE_H_
#define ILM_CORE_H_
#include "ILM/cfg/ilm_cfg.h"
#include "ILM/if/ilm_types.h"
#include "ILM/if/ilm_hooks.h"

/**
 * \brief Handler function for IRQ or time tick based LET event processing\n
 * If ILM_USE_HW_CCU == 0 the function should be called within the time tick\n
 * for software based CCU emulation
 * \param CurTick Current time tick value, only needed if ILM_Hander is called\n
 * from a task context
 * \return None
 */
extern void ILM_Handler(uint32 CurTick);

/**
 * \brief Init function for ILM core module
 * \param pTable Pointer to LET table
 * \param TableSize Length of the table located at pTable
 * \param MacroPeriod Macro period of the provided LET table
 * \return None
 */
extern void ILM_Init(ILM_LET_TABLE_T *pTable, uint32 TableSize, uint32 MacroPeriod);

#endif /* ILM_CORE_H_ */
