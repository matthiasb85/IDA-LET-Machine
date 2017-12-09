/**
 * \file master.c
 * \brief Main file of ERIKA OS Multicore ILM example for C0
 * \ingroup Example
 */

/*
 * master.c
 * ERIKA OS Multicore ILM example
 *
 *  Created on: Jul, 2017
 *      Author: Matthias Beckert
 */
#include "Scu/Std/IfxScuCcu.h"
#include "shared.h"
#include "IO/GPIO/gpio.h"
#include <math.h>
#include "cpu/tricore/inc/ee_tc_multicore.h"

/**
 * \brief Generic trap handler
 * \param tin Trap cause register
 * \param RA Return address
 * \return None
 */
static void _C0_TrapHandler(EE_TIN tin, EE_FADDR RA)
{
	while(1) {
		asm volatile("debug"); /* dummy */
	}
}

/*
 * Trap handler stubs
 */
/**
 * \brief Trap entry for C0_trap_prot
 * \return None
 */
TRAP(EE_CLASS_TRAPPROT, C0_trap_prot)		{ _C0_TrapHandler(EE_tc_get_TIN(),(EE_FADDR)EE_tc_get_RA()); }

/**
 * \brief Trap entry for C0_trap_inst
 * \return None
 */
TRAP(EE_CLASS_TRAPINST, C0_trap_inst)		{ _C0_TrapHandler(EE_tc_get_TIN(),(EE_FADDR)EE_tc_get_RA()); }

/**
 * \brief Trap entry for C0_trap_cont
 * \return None
 */
TRAP(EE_CLASS_TRAPCONT, C0_trap_cont)		{ _C0_TrapHandler(EE_tc_get_TIN(),(EE_FADDR)EE_tc_get_RA()); }

/**
 * \brief Trap entry for C0_trap_bus
 * \return None
 */
TRAP(EE_CLASS_TRAPBUS,  C0_trap_bus)		{ _C0_TrapHandler(EE_tc_get_TIN(),(EE_FADDR)EE_tc_get_RA()); }

/**
 * \brief Trap entry for C0_trap_sys
 * \return None
 */
TRAP(EE_CLASS_TRAPASS,  C0_trap_sys)		{ _C0_TrapHandler(EE_tc_get_TIN(),(EE_FADDR)EE_tc_get_RA()); }

/**
 * \brief Trap entry for C0_trap_nmi
 * \return None
 */
TRAP(EE_CLASS_TRAPSYS,  C0_trap_nmi)		{ _C0_TrapHandler(EE_tc_get_TIN(),(EE_FADDR)EE_tc_get_RA()); }

/**
 * \brief Trap entry for C0_trap_context
 * \return None
 */
TRAP(EE_CLASS_TRAPNMI,  C0_trap_context)	{ _C0_TrapHandler(EE_tc_get_TIN(),(EE_FADDR)EE_tc_get_RA()); }

/**
 * \brief ERIKA OS generic error hook
 * \param Error Passed error argument
 * \return None
 */
void ErrorHook(StatusType Error)
{
	static EE_UINT32 myErrorCounter;
	++myErrorCounter;
}

/**
 * \brief C-Entry function on C0
 * \return None
 */
int main(void)
{
	StatusType status;

	/*
	 * Init clock tree
	 */
	IfxScuCcu_Config ClockConfig;
	IfxScuCcu_initConfig(&ClockConfig);
	IfxScuCcu_init(&ClockConfig);

	GPIO_Init();

	/*
	 * Init LET task
	 */
	ILM_Init((ILM_LET_TABLE_T *)CO_LET_TABLE, CO_LET_TABLE_SIZE, TICKS_PER_MACRO_PERIOD);

	/*
	 * Init CCU
	 */
	ILM_HW_Init((ILM_HW_LET_TABLE_T *)C0_HW_Master_Table, C0_HW_TABLE_SIZE, TICKS_PER_S, TICKS_PER_MACRO_PERIOD);

	/*
	 * Configure synchronization barrier
	 */
	ILM_OS_Set_BarrierMask((ILM_COREMASK_C1 | ILM_COREMASK_C2));

	/*
	 * Start C1 & C2
	 */
	StartCore(OS_CORE_ID_1, &status);
	StartCore(OS_CORE_ID_2, &status);

	/*
	 * Wait until C1 & C2 have been started
	 * and initialized their local ILM framework
	 */
	ILM_OS_SyncCores();

	/*
	 * Fire!
	 */
	ILM_HW_StartTimer();
	StartOS(OSDEFAULTAPPMODE);

	/*
	 * HC SVNT DRACONES
	 */
	return 0;
}
