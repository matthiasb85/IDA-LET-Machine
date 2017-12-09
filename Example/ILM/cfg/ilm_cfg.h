/**
 * \file ./master/Example/ILM/cfg/ilm_cfg.h
 * \brief Application specific user defined configuration file
 * \ingroup Example
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

#ifndef ILM_CFG_H_
#define ILM_CFG_H_

#define ILM_USE_HOOK_TACT		1	/**< \brief Use Task Activate Hook 												*/
#define ILM_USE_HOOK_PRIOB		0	/**< \brief Use Priority Boost Hook												*/
#define ILM_USE_HOOK_PSWAP		1	/**< \brief Use Pointer Swap Hook												*/
#define ILM_USE_HOOK_LETEV		1	/**< \brief Use LET Event (SetEvent) Hook										*/
#define ILM_USE_HOOK_TTERM		1	/**< \brief Use Task Terminate Hook												*/
#define ILM_USE_HOOK_START_ILM	0	/**< \brief Use LET Handler Start Hook											*/
#define ILM_USE_HOOK_STOP_ILM	0	/**< \brief Use LET Handler End Hook											*/
#define ILM_USE_HOOK_START_IRQ 	1	/**< \brief Use HW IRQ Start Hook												*/
#define ILM_USE_HOOK_STOP_IRQ 	1	/**< \brief Use HW IRQ Stop Hook												*/
#define ILM_USE_HOOK_START_EXEC	1	/**< \brief Use Task Start Execution Hook										*/
#define ILM_USE_HOOK_STOP_EXEC	1	/**< \brief Use Task Stop Execution Hook										*/

#define ILM_USE_TERM_CTX		0	/**< \brief Use additional SetEvent at Task Termination							*/
#define ILM_USE_OSEK_ECC		0	/**< \brief Use Extended Conformance Class (ECC) Tasks instead of Basic (BCC)	*/
#define ILM_USE_HW_CCU			1	/**< \brief If 0, a software timetick is used									*/
#define ILM_USE_HW_SOFT_IRQ		1	/**< \brief If 0, a tasks are used for the LET scheduler						*/

#define ILM_NUM_OF_CORES		3	/**< \brief Number of Cores														*/
#define ILM_HW_HARD_IRQ			64	/**< \brief Priority for main hardware IRQ										*/
#define ILM_HW_SOFT_IRQ			64	/**< \brief Priority for secondary software IRQs								*/

#endif /* ILM_CFG_H_ */
