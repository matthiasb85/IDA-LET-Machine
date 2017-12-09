/**
 * \file slave1.c
 * \brief Main file of ERIKA OS Multicore ILM example for C1
 * \ingroup Example
 */

/*
 * slave1.c
 * ERIKA OS Multicore ILM example
 *
 *  Created on: Jul, 2017
 *      Author: Matthias Beckert
 */
#include "shared.h"


/**
 * \brief C-Entry function on C1
 * \return None
 */
int main(void)
{
	/*
	 * Init ILM framework and enter synchronization barrier
	 */
	ILM_Init((ILM_LET_TABLE_T *)C1_LET_TABLE, C1_LET_TABLE_SIZE, TICKS_PER_MACRO_PERIOD);
	ILM_OS_SyncCores();

	StartOS(DONOTCARE);

	/*
	 * HC SVNT DRACONES
	 */
	return 0;
}
