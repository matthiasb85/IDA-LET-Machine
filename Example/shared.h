/**
 * \file shared.h
 * \brief Include file for common files and defines
 * \ingroup Example
 */


/*
 * shared.h
 *
 *  Created on: 09.08.2016
 *      Author: matthiasb
 */
#ifndef SHARED_H
#define SHARED_H

#include "ee.h"
#include "ee_irq.h"

#include <stdio.h>
#include <string.h>
#include "ILM/if/ilm_core.h"
#include "ILM/if/ilm_os_port.h"
#include "ILM/if/ilm_hw_port.h"

#include "eecfg.h"


#define TICKS_PER_S 			10000	//10kHz
#define TICKS_PER_MACRO_PERIOD 	1000	//10Hz PWM

#define DB_NAME(X,Y)	DB_##X_##Y

#define FUNC_CET(X)		__ARCH_AURIX_C(X,CPU_OS_TASK_OFFSET,CPU_CYCLE_SCALE);
#if ILM_USE_HOOK_START_EXEC > 0 && ILM_USE_HOOK_STOP_EXEC > 0
#define FUNC_CALL(X)	ILM_HOOK_START_EXEC(myId);FUNC_CET(X);ILM_HOOK_STOP_EXEC(myId)
#else
#define FUNC_CALL(X)	FUNC_CET(X)
#endif
#define WAIT_SP(X,Y,Z)	WaitEvent((EventMaskType)(Y));					\
						GetEvent((TaskType)(X), (EventMaskRefType)(Z));	\
						ClearEvent((EventMaskType)(Y));

#define C0_T10_RUNNABLE_NUM		3
#define C0_T20_RUNNABLE_NUM		5
#define C0_T100_RUNNABLE_NUM	4

#define C1_T10_RUNNABLE_NUM		4
#define C1_T20_RUNNABLE_NUM		3
#define C1_T100_RUNNABLE_NUM	2

#define C2_T10_RUNNABLE_NUM		4
#define C2_T20_RUNNABLE_NUM		2
#define C2_T100_RUNNABLE_NUM	4

#if ILM_USE_PRIOB > 0
#define PAYLOAD(V,X,Y,Z)					{(V), (X), (Y), (Z)}
#else
#define PAYLOAD(V,X,Y,Z)					{(X), (Y), (Z)}
#endif

#ifdef EE_MASTER_CPU
extern const ILM_LET_TABLE_T CO_LET_TABLE[];
extern const ILM_HW_LET_TABLE_T C0_HW_Master_Table[];
extern const size_t CO_LET_TABLE_SIZE;
extern const size_t C0_HW_TABLE_SIZE;
#elif (EE_CURRENTCPU == 1)
extern const ILM_LET_TABLE_T C1_LET_TABLE[];
extern const size_t C1_LET_TABLE_SIZE;
#elif (EE_CURRENTCPU == 2)
extern const ILM_LET_TABLE_T C2_LET_TABLE[];
extern const size_t C2_LET_TABLE_SIZE;
#endif

#endif /* SHARED_H */
