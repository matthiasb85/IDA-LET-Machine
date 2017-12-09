/**
 * \file burn_wcet.h
 * \brief Macro definition for worst-case execution time simulation
 * \ingroup Example
 */

/*
 * burn_wcet.h
 *
 *  Created on: 15.06.2017
 *      Author: matthiasb
 */

#ifndef BURN_WCET_H_
#define BURN_WCET_H_


#if  (EE_CURRENTCPU == 0)
#define CPU_CYCLE_SCALE			18.21				/**< \brief CPU scaling factor for an TC1.6e AURIX@200MHz  */
#define CPU_OS_TASK_OFFSET		0					/**< \brief CPU overhead offset for an TC1.6e AURIX@200MHz */

#elif (EE_CURRENTCPU == 1) ||  (EE_CURRENTCPU == 2)
#define CPU_CYCLE_SCALE			33.33				/**< \brief CPU scaling factor for an TC1.6p AURIX@200MHz  */
#define CPU_OS_TASK_OFFSET		0					/**< \brief CPU overhead offset for an TC1.6p AURIX@200MHz */
#else
#warning "No scaling for current CPU, modify gt_cfg.h"
#endif

/**
 * \brief Internal function for worst-case execution time simulation
 * \param x Time in microseconds
 * \param y Overhead offset
 * \param z CPU scale
 * \return None
 */
static void __attribute__((optimize("O2"))) __ARCH_AURIX_C(unsigned long x, unsigned long y, float z)
{
	volatile unsigned long __end = (unsigned long)((float)x*z);
    __end = (__end > y) ? __end - y : 0;
    while(__end > 0)__end--;
}


#endif /* BURN_WCET_H_ */
