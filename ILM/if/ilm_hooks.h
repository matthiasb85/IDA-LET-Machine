/**
 * \file ilm_hooks.h
 * \brief API definition for hook functions
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
 *  Created on: 10.05.2017
 *      Author: matthiasb
 */

#ifndef ILM_HOOKS_H_
#define ILM_HOOKS_H_
#include "ILM/cfg/ilm_cfg.h"
#include "ILM/if/ilm_types.h"

/**
 * \brief Task Activation Hook
 * \param pEntry Pointer to current LET table entry
 * \return None
 */
extern void ILM_HOOK_TACT(ILM_LET_TABLE_T *pEntry);

/**
 * \brief Priority Boosting Hook
 * \param pEntry Pointer to current LET table entry
 * \return None
 */
extern void ILM_HOOK_PRIOB(ILM_LET_TABLE_T *pEntry);

/**
 * \brief Pointer Swap Hook
 * \param pEntry Pointer to current LET table entry
 * \return None
 */
extern void ILM_HOOK_PSWAP(ILM_LET_TABLE_T *pEntry);

/**
 * \brief Set Event Hook
 * \param pEntry Pointer to current LET table entry
 * \return None
 */
extern void ILM_HOOK_LETEV(ILM_LET_TABLE_T *pEntry);

/**
 * \brief Task Termination Hook
 * \param pEntry Pointer to current LET table entry
 * \return None
 */
extern void ILM_HOOK_TTERM(ILM_LET_TABLE_T *pEntry);

/**
 * \brief Task Activation Hook
 * \return None
 */
extern void ILM_HOOK_START_ILM_HANDLER(void);

/**
 * \brief ILM_Hanlder  Hook
 * \return None
 */
extern void ILM_HOOK_STOP_ILM_HANDLER(void);

/**
 * \brief IRQ Start Hook
 * \return None
 */
extern void ILM_HOOK_START_IRQ(void);

/**
 * \brief IRQ Stop Hook
 * \return None
 */
extern void ILM_HOOK_STOP_IRQ(void);

/**
 * \brief Task Start Execution Hook
 * \param id Task identifier
 * \return None
 */
extern void ILM_HOOK_START_EXEC(const unsigned int id);

/**
 * \brief Task Stop Execution Hook
 * \param id Task identifier
 * \return None
 */
extern void ILM_HOOK_STOP_EXEC(const unsigned int id);

/**
 * \brief LET Miss Hook
 * \param pEntry Pointer to current LET table entry
 * \return None
 */
extern void ILM_HOOK_MISS_LET(ILM_LET_TABLE_T *pEntry);

#endif /* ILM_HOOKS_H_ */
