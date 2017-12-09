/**
 * \file ./master/ILM/cfg/ilm_hooks.c
 * \brief User defined hook implementation (default template)
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
#include "ee.h"
#include "IO/GPIO/gpio.h"
#include "ILM/if/ilm_hooks.h"

/*
 * User defined hook implementation
 * Those hooks can be used, for pin toggeling,
 * software tracing, measurements etc.
 */

#ifdef LET_MAPPING_1
#undef GPIO_COREOFFSET
#undef GPIO_MISS
#if  (EE_CURRENTCPU == 0)
#define GPIO_COREOFFSET 0
#define GPIO_MISS		14
#elif  (EE_CURRENTCPU == 1)
#define GPIO_COREOFFSET 7
#define GPIO_MISS		15
#elif  (EE_CURRENTCPU == 2)
#define GPIO_COREOFFSET 16
#else
#error "not supported for this core at the moment"
#endif
#endif
#ifdef LET_MAPPING_2
#undef GPIO_COREOFFSET
#if  (EE_CURRENTCPU == 0)
#define GPIO_COREOFFSET 0
#elif  (EE_CURRENTCPU == 1)
#define GPIO_COREOFFSET 1
#define GPIO_MISS		15
#elif  (EE_CURRENTCPU == 2)
#define GPIO_COREOFFSET 8
#define GPIO_MISS		16
#else
#error "not supported for this core at the moment"
#endif
#endif




#if ILM_USE_HOOK_TACT	> 0
void ILM_HOOK_TACT(ILM_LET_TABLE_T *pEntry)
{
	GPIO_On(pEntry->TaskId*2 + GPIO_COREOFFSET + 1);
}
#endif

#if ILM_USE_HOOK_PRIOB	> 0
void ILM_HOOK_PRIOB(ILM_LET_TABLE_T *pEntry)
{
	;
}
#endif

#if ILM_USE_HOOK_PSWAP	> 0
void ILM_HOOK_PSWAP(ILM_LET_TABLE_T *pEntry)
{
	GPIO_Off(pEntry->TaskId*2 + GPIO_COREOFFSET + 1);
}
#endif

#if ILM_USE_HOOK_LETEV	> 0
void ILM_HOOK_LETEV(ILM_LET_TABLE_T *pEntry)
{
	GPIO_On(pEntry->TaskId*2 + GPIO_COREOFFSET + 1);
}
#endif

#if ILM_USE_HOOK_TTERM	> 0
void ILM_HOOK_TTERM(ILM_LET_TABLE_T *pEntry)
{
	GPIO_Off(pEntry->TaskId*2 + GPIO_COREOFFSET + 1);
}
#endif

#if ILM_USE_HOOK_START_ILM	> 0
void ILM_HOOK_START_ILM_HANDLER(void)
{
#if  (EE_CURRENTCPU == 0)
	GPIO_On(12 + GPIO_COREOFFSET);
#endif
}
#endif
#if ILM_USE_HOOK_STOP_ILM > 0
void ILM_HOOK_STOP_ILM_HANDLER(void)
{
#if  (EE_CURRENTCPU == 0)
	GPIO_Off(12 + GPIO_COREOFFSET);
#endif
}
#endif

#if ILM_USE_HOOK_START_IRQ	> 0
void ILM_HOOK_START_IRQ(void)
{
	GPIO_On(GPIO_COREOFFSET);
}
#endif
#if ILM_USE_HOOK_STOP_IRQ	> 0
void ILM_HOOK_STOP_IRQ(void)
{
	GPIO_Off(GPIO_COREOFFSET);
}
#endif

#if ILM_USE_HOOK_START_EXEC	> 0
void ILM_HOOK_START_EXEC(const unsigned int id)
{
	GPIO_On(id*2 + GPIO_COREOFFSET + 2);
}
#endif
#if ILM_USE_HOOK_STOP_EXEC	> 0
void ILM_HOOK_STOP_EXEC(const unsigned int id)
{
	GPIO_Off(id*2 + GPIO_COREOFFSET + 2);
}
#endif

#if ILM_USE_HOOK_MISS_LET	> 0
void ILM_HOOK_MISS_LET(ILM_LET_TABLE_T *pEntry)
{
	(void)pEntry;
#ifdef GPIO_MISS
	GPIO_On(GPIO_MISS);
	GPIO_Off(GPIO_MISS);
#endif
}
#endif
