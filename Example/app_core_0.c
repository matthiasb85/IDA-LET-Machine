/**
 * \file app_core_0.c
 * \brief LET application for core 0
 * \ingroup Example
 */

/*
 * app_core_0.c
 *
 *  Created on: 25.07.2017
 *      Author: matthiasb
 */
#include "shared.h"
#include "burn_wcet.h"

/*
 * Core Execution Times (CET) for simulated runnable
 * blocks (e.g. each block is interpreted as an LET task)
 * (times given in micro seconds)
 */
const EE_UINT32 C0_T10_RUNNABLE_CET[C0_T10_RUNNABLE_NUM] =		/**< \brief Runnable sequence table (WCETs) for T10 on C0  */
{
		400,
		200,
		150
};
const EE_UINT32 C0_T20_RUNNABLE_CET[C0_T20_RUNNABLE_NUM] =		/**< \brief Runnable sequence table (WCETs) for T20 on C0  */
{
		800,
		200,
		100,
		500,
		150
};
const EE_UINT32 C0_T100_RUNNABLE_CET[C0_T100_RUNNABLE_NUM] =	/**< \brief Runnable sequence table (WCETs) for T100 on C0 */
{
		100,
		150,
		200,
		400,
};

/*
 * Define Doube Buffer for each runnable block
 * initialized to 0, as we don't have real data
 */
ILM_DATA_OUT_T EE_SHARED_UDATA DB_C0_T10_0	= {.Read.Generic = (void *)0, .Write.Generic =  (void *)0};	/**< \brief Double buffer for runnable 0 of T10 on C0  */
ILM_DATA_OUT_T EE_SHARED_UDATA DB_C0_T10_1	= {.Read.Generic = (void *)0, .Write.Generic =  (void *)0};	/**< \brief Double buffer for runnable 1 of T10 on C0  */
ILM_DATA_OUT_T EE_SHARED_UDATA DB_C0_T10_2	= {.Read.Generic = (void *)0, .Write.Generic =  (void *)0};	/**< \brief Double buffer for runnable 2 of T10 on C0  */
ILM_DATA_OUT_T EE_SHARED_UDATA DB_C0_T20_0	= {.Read.Generic = (void *)0, .Write.Generic =  (void *)0};	/**< \brief Double buffer for runnable 0 of T20 on C0  */
ILM_DATA_OUT_T EE_SHARED_UDATA DB_C0_T20_1	= {.Read.Generic = (void *)0, .Write.Generic =  (void *)0};	/**< \brief Double buffer for runnable 1 of T20 on C0  */
ILM_DATA_OUT_T EE_SHARED_UDATA DB_C0_T20_2	= {.Read.Generic = (void *)0, .Write.Generic =  (void *)0};	/**< \brief Double buffer for runnable 2 of T20 on C0  */
ILM_DATA_OUT_T EE_SHARED_UDATA DB_C0_T20_3	= {.Read.Generic = (void *)0, .Write.Generic =  (void *)0};	/**< \brief Double buffer for runnable 3 of T20 on C0  */
ILM_DATA_OUT_T EE_SHARED_UDATA DB_C0_T20_4	= {.Read.Generic = (void *)0, .Write.Generic =  (void *)0};	/**< \brief Double buffer for runnable 4 of T20 on C0  */
ILM_DATA_OUT_T EE_SHARED_UDATA DB_C0_T100_0	= {.Read.Generic = (void *)0, .Write.Generic =  (void *)0};	/**< \brief Double buffer for runnable 0 of T100 on C0 */
ILM_DATA_OUT_T EE_SHARED_UDATA DB_C0_T100_1	= {.Read.Generic = (void *)0, .Write.Generic =  (void *)0};	/**< \brief Double buffer for runnable 1 of T100 on C0 */
ILM_DATA_OUT_T EE_SHARED_UDATA DB_C0_T100_2	= {.Read.Generic = (void *)0, .Write.Generic =  (void *)0};	/**< \brief Double buffer for runnable 2 of T100 on C0 */
ILM_DATA_OUT_T EE_SHARED_UDATA DB_C0_T100_3	= {.Read.Generic = (void *)0, .Write.Generic =  (void *)0};	/**< \brief Double buffer for runnable 3 of T100 on C0 */

/*
 * Task bodies for ILM taskset
 * Use ILM_USE_OSEK_ECC in ILM/cfg/ilm_cfg.h
 * to determine the used conformance class
 * Make sure, that ILM_USE_OSEK_ECC with
 * KERNEL_TYPE in conf.oil
 */
#if ILM_USE_OSEK_ECC > 0
/*
 * Use an OSEK/AUTOSAR
 * Extended Conformance Class (ECC)
 * task model
 */

/**
 * \brief ECC implementation of task T10 on C0
 * \return None
 */
TASK(C0_T10)
{
	const unsigned int myId=C0_T10;
	EventMaskType mask;
	FUNC_CALL(C0_T10_RUNNABLE_CET[0]);
	WAIT_SP(C0_T10, C0_EV_T10, &mask);
	FUNC_CALL(C0_T10_RUNNABLE_CET[1]);
	WAIT_SP(C0_T10, C0_EV_T10, &mask);
	FUNC_CALL(C0_T10_RUNNABLE_CET[2]);
	TerminateTask();
}

/**
 * \brief ECC implementation of task T20 on C0
 * \return None
 */
TASK(C0_T20)
{
	const unsigned int myId=C0_T20;
	EventMaskType mask;
	FUNC_CALL(C0_T20_RUNNABLE_CET[0]);
	WAIT_SP(C0_T20, C0_EV_T20, &mask);
	FUNC_CALL(C0_T20_RUNNABLE_CET[1]);
	WAIT_SP(C0_T20, C0_EV_T20, &mask);
	FUNC_CALL(C0_T20_RUNNABLE_CET[2]);
	WAIT_SP(C0_T20, C0_EV_T20, &mask);
	FUNC_CALL(C0_T20_RUNNABLE_CET[3]);
	WAIT_SP(C0_T20, C0_EV_T20, &mask);
	FUNC_CALL(C0_T20_RUNNABLE_CET[4]);
	TerminateTask();
}

/**
 * \brief ECC implementation of task T100 on C0
 * \return None
 */
TASK(C0_T100)
{
	const unsigned int myId=C0_T100;
	EventMaskType mask;
	FUNC_CALL(C0_T100_RUNNABLE_CET[0]);
	WAIT_SP(C0_T100, C0_EV_T100, &mask);
	FUNC_CALL(C0_T100_RUNNABLE_CET[1]);
	WAIT_SP(C0_T100, C0_EV_T100, &mask);
	FUNC_CALL(C0_T100_RUNNABLE_CET[2]);
	WAIT_SP(C0_T100, C0_EV_T100, &mask);
	FUNC_CALL(C0_T100_RUNNABLE_CET[3]);
	TerminateTask();
}
#else
/*
 * Use an OSEK/AUTOSAR
 * Basic Conformance Class (BCC)
 * task model
 */

/**
 * \brief BCC implementation of task T10 on C0
 * \return None
 */
TASK(C0_T10)
{
	const unsigned int myId=C0_T10;
	static unsigned int C0_T10_CNT = 0;

	FUNC_CALL(C0_T10_RUNNABLE_CET[C0_T10_CNT]);
	C0_T10_CNT = (C0_T10_CNT + 1) % C0_T10_RUNNABLE_NUM;
	TerminateTask();
}

/**
 * \brief BCC implementation of task T20 on C0
 * \return None
 */
TASK(C0_T20)
{
	const unsigned int myId=C0_T20;
	static unsigned int C0_T20_CNT = 0;

	FUNC_CALL(C0_T20_RUNNABLE_CET[C0_T20_CNT]);
	C0_T20_CNT = (C0_T20_CNT + 1) % C0_T20_RUNNABLE_NUM;
	TerminateTask();
}

/**
 * \brief BCC implementation of task T100 on C0
 * \return None
 */
TASK(C0_T100)
{
	const unsigned int myId=C0_T100;
	static unsigned int C0_T100_CNT = 0;

	FUNC_CALL(C0_T100_RUNNABLE_CET[C0_T100_CNT]);
	C0_T100_CNT = (C0_T100_CNT + 1) % C0_T100_RUNNABLE_NUM;
	TerminateTask();
}
#endif

/*
 * Configuration table for CCU
 */
const ILM_HW_LET_TABLE_T C0_HW_Master_Table[] = 								/**< \brief HW table for IRQ generation */
{
	{	0,		(ILM_COREMASK_C0)											},
	{	6,		(ILM_COREMASK_C0 | ILM_COREMASK_C1 | ILM_COREMASK_C2)		},
	{	8,		(ILM_COREMASK_C1 | ILM_COREMASK_C2)							},
	{	11,		(ILM_COREMASK_C0 | ILM_COREMASK_C1 | ILM_COREMASK_C2)		},
	{	15,		(ILM_COREMASK_C0 | ILM_COREMASK_C1 | ILM_COREMASK_C2)		},
	{	17,		(ILM_COREMASK_C1 | ILM_COREMASK_C2)							},
	{	19,		(ILM_COREMASK_C0 | ILM_COREMASK_C2)							},
	{	21,		(ILM_COREMASK_C0)											},
	{	31,		(ILM_COREMASK_C0 | ILM_COREMASK_C1)							},
	{	35,		(ILM_COREMASK_C0 | ILM_COREMASK_C1 | ILM_COREMASK_C2)		},
	{	41,		(ILM_COREMASK_C0 | ILM_COREMASK_C1 | ILM_COREMASK_C2)		},
	{	48,		(ILM_COREMASK_C0 | ILM_COREMASK_C1 | ILM_COREMASK_C2)		},
	{	50,		(ILM_COREMASK_C0)											},
	{	52,		(ILM_COREMASK_C0 | ILM_COREMASK_C2)							},
	{	54,		(ILM_COREMASK_C0 | ILM_COREMASK_C2)							},
	{	57,		(ILM_COREMASK_C0 | ILM_COREMASK_C1 | ILM_COREMASK_C2)		},
	{	61,		(ILM_COREMASK_C0 | ILM_COREMASK_C1 | ILM_COREMASK_C2)		},
	{	67,		(ILM_COREMASK_C0 | ILM_COREMASK_C1 | ILM_COREMASK_C2)		},
	{	73,		(ILM_COREMASK_C0)											},
	{	100,	(ILM_COREMASK_C0)											},
	{	106,	(ILM_COREMASK_C0 | ILM_COREMASK_C1 | ILM_COREMASK_C2)		},
	{	108,	(ILM_COREMASK_C1 | ILM_COREMASK_C2)							},
	{	111,	(ILM_COREMASK_C0 | ILM_COREMASK_C1 | ILM_COREMASK_C2)		},
	{	115,	(ILM_COREMASK_C0 | ILM_COREMASK_C1 | ILM_COREMASK_C2)		},
	{	117,	(ILM_COREMASK_C1 | ILM_COREMASK_C2)							},
	{	119,	(ILM_COREMASK_C0 | ILM_COREMASK_C2)							},
	{	121,	(ILM_COREMASK_C0)											},
	{	200,	(ILM_COREMASK_C0)											},
	{	206,	(ILM_COREMASK_C0 | ILM_COREMASK_C1 | ILM_COREMASK_C2)		},
	{	208,	(ILM_COREMASK_C1 | ILM_COREMASK_C2)							},
	{	211,	(ILM_COREMASK_C0 | ILM_COREMASK_C1 | ILM_COREMASK_C2)		},
	{	215,	(ILM_COREMASK_C0 | ILM_COREMASK_C1 | ILM_COREMASK_C2)		},
	{	217,	(ILM_COREMASK_C1 | ILM_COREMASK_C2)							},
	{	219,	(ILM_COREMASK_C0 | ILM_COREMASK_C2)							},
	{	221,	(ILM_COREMASK_C0)											},
	{	231,	(ILM_COREMASK_C0 | ILM_COREMASK_C1)							},
	{	235,	(ILM_COREMASK_C0 | ILM_COREMASK_C1 | ILM_COREMASK_C2)		},
	{	241,	(ILM_COREMASK_C0 | ILM_COREMASK_C1 | ILM_COREMASK_C2)		},
	{	248,	(ILM_COREMASK_C0 | ILM_COREMASK_C1 | ILM_COREMASK_C2)		},
	{	250,	(ILM_COREMASK_C0)											},
	{	300,	(ILM_COREMASK_C0)											},
	{	306,	(ILM_COREMASK_C0 | ILM_COREMASK_C1 | ILM_COREMASK_C2)		},
	{	308,	(ILM_COREMASK_C1 | ILM_COREMASK_C2)							},
	{	311,	(ILM_COREMASK_C0 | ILM_COREMASK_C1 | ILM_COREMASK_C2)		},
	{	315,	(ILM_COREMASK_C0 | ILM_COREMASK_C1 | ILM_COREMASK_C2)		},
	{	317,	(ILM_COREMASK_C1 | ILM_COREMASK_C2)							},
	{	319,	(ILM_COREMASK_C0 | ILM_COREMASK_C2)							},
	{	321,	(ILM_COREMASK_C0)											},
	{	400,	(ILM_COREMASK_C0)											},
	{	406,	(ILM_COREMASK_C0 | ILM_COREMASK_C1 | ILM_COREMASK_C2)		},
	{	408,	(ILM_COREMASK_C1 | ILM_COREMASK_C2)							},
	{	411,	(ILM_COREMASK_C0 | ILM_COREMASK_C1 | ILM_COREMASK_C2)		},
	{	415,	(ILM_COREMASK_C0 | ILM_COREMASK_C1 | ILM_COREMASK_C2)		},
	{	417,	(ILM_COREMASK_C1 | ILM_COREMASK_C2)							},
	{	419,	(ILM_COREMASK_C0 | ILM_COREMASK_C2)							},
	{	421,	(ILM_COREMASK_C0)											},
	{	431,	(ILM_COREMASK_C0 | ILM_COREMASK_C1)							},
	{	435,	(ILM_COREMASK_C0 | ILM_COREMASK_C1 | ILM_COREMASK_C2)		},
	{	441,	(ILM_COREMASK_C0 | ILM_COREMASK_C1 | ILM_COREMASK_C2)		},
	{	448,	(ILM_COREMASK_C0 | ILM_COREMASK_C1 | ILM_COREMASK_C2)		},
	{	450,	(ILM_COREMASK_C0)											},
	{	500,	(ILM_COREMASK_C0)											},
	{	506,	(ILM_COREMASK_C0 | ILM_COREMASK_C1 | ILM_COREMASK_C2)		},
	{	508,	(ILM_COREMASK_C1 | ILM_COREMASK_C2)							},
	{	511,	(ILM_COREMASK_C0 | ILM_COREMASK_C1 | ILM_COREMASK_C2)		},
	{	515,	(ILM_COREMASK_C0 | ILM_COREMASK_C1 | ILM_COREMASK_C2)		},
	{	517,	(ILM_COREMASK_C1 | ILM_COREMASK_C2)							},
	{	519,	(ILM_COREMASK_C0 | ILM_COREMASK_C2)							},
	{	521,	(ILM_COREMASK_C0)											},
	{	600,	(ILM_COREMASK_C0)											},
	{	606,	(ILM_COREMASK_C0 | ILM_COREMASK_C1 | ILM_COREMASK_C2)		},
	{	608,	(ILM_COREMASK_C1 | ILM_COREMASK_C2)							},
	{	611,	(ILM_COREMASK_C0 | ILM_COREMASK_C1 | ILM_COREMASK_C2)		},
	{	615,	(ILM_COREMASK_C0 | ILM_COREMASK_C1 | ILM_COREMASK_C2)		},
	{	617,	(ILM_COREMASK_C1 | ILM_COREMASK_C2)							},
	{	619,	(ILM_COREMASK_C0 | ILM_COREMASK_C2)							},
	{	621,	(ILM_COREMASK_C0)											},
	{	631,	(ILM_COREMASK_C0 | ILM_COREMASK_C1)							},
	{	635,	(ILM_COREMASK_C0 | ILM_COREMASK_C1 | ILM_COREMASK_C2)		},
	{	641,	(ILM_COREMASK_C0 | ILM_COREMASK_C1 | ILM_COREMASK_C2)		},
	{	648,	(ILM_COREMASK_C0 | ILM_COREMASK_C1 | ILM_COREMASK_C2)		},
	{	650,	(ILM_COREMASK_C0)											},
	{	700,	(ILM_COREMASK_C0)											},
	{	706,	(ILM_COREMASK_C0 | ILM_COREMASK_C1 | ILM_COREMASK_C2)		},
	{	708,	(ILM_COREMASK_C1 | ILM_COREMASK_C2)							},
	{	711,	(ILM_COREMASK_C0 | ILM_COREMASK_C1 | ILM_COREMASK_C2)		},
	{	715,	(ILM_COREMASK_C0 | ILM_COREMASK_C1 | ILM_COREMASK_C2)		},
	{	717,	(ILM_COREMASK_C1 | ILM_COREMASK_C2)							},
	{	719,	(ILM_COREMASK_C0 | ILM_COREMASK_C2)							},
	{	721,	(ILM_COREMASK_C0)											},
	{	800,	(ILM_COREMASK_C0)											},
	{	806,	(ILM_COREMASK_C0 | ILM_COREMASK_C1 | ILM_COREMASK_C2)		},
	{	808,	(ILM_COREMASK_C1 | ILM_COREMASK_C2)							},
	{	811,	(ILM_COREMASK_C0 | ILM_COREMASK_C1 | ILM_COREMASK_C2)		},
	{	815,	(ILM_COREMASK_C0 | ILM_COREMASK_C1 | ILM_COREMASK_C2)		},
	{	817,	(ILM_COREMASK_C1 | ILM_COREMASK_C2)							},
	{	819,	(ILM_COREMASK_C0 | ILM_COREMASK_C2)							},
	{	821,	(ILM_COREMASK_C0)											},
	{	831,	(ILM_COREMASK_C0 | ILM_COREMASK_C1)							},
	{	835,	(ILM_COREMASK_C0 | ILM_COREMASK_C1 | ILM_COREMASK_C2)		},
	{	841,	(ILM_COREMASK_C0 | ILM_COREMASK_C1 | ILM_COREMASK_C2)		},
	{	848,	(ILM_COREMASK_C0 | ILM_COREMASK_C1 | ILM_COREMASK_C2)		},
	{	850,	(ILM_COREMASK_C0)											},
	{	900,	(ILM_COREMASK_C0)											},
	{	906,	(ILM_COREMASK_C0 | ILM_COREMASK_C1 | ILM_COREMASK_C2)		},
	{	908,	(ILM_COREMASK_C1 | ILM_COREMASK_C2)							},
	{	911,	(ILM_COREMASK_C0 | ILM_COREMASK_C1 | ILM_COREMASK_C2)		},
	{	915,	(ILM_COREMASK_C0 | ILM_COREMASK_C1 | ILM_COREMASK_C2)		},
	{	917,	(ILM_COREMASK_C1 | ILM_COREMASK_C2)							},
	{	919,	(ILM_COREMASK_C0 | ILM_COREMASK_C2)							},
	{	921,	(ILM_COREMASK_C0)											}
};

/*
 * Configuration table for ILM Handler
 */
const ILM_LET_TABLE_T CO_LET_TABLE[] =											/**< \brief LET event table for C0 */
{
	{	0,		C0_T10,		(ILM_EVENT_TACT),						PAYLOAD(0, (void *)0, 0, 0)							},
	{	6,		C0_T10,		(ILM_EVENT_PSWAP),						PAYLOAD(0, (void *)0, 0, &DB_C0_T10_0)				},
	{	11,		C0_T10,		(ILM_EVENT_LETEV),						PAYLOAD(0, (void *)C0_EV_T10, 0, 0)					},
	{	15,		C0_T10,		(ILM_EVENT_PSWAP),						PAYLOAD(0, (void *)0, 0, &DB_C0_T10_1)				},
	{	19,		C0_T10,		(ILM_EVENT_LETEV),						PAYLOAD(0, (void *)C0_EV_T10, 0, 0)					},
	{	21,		C0_T10,		(ILM_EVENT_PSWAP | ILM_EVENT_TTERM),	PAYLOAD(0, (void *)0, 0, &DB_C0_T10_2)				},
	{	21,		C0_T20,		(ILM_EVENT_TACT),						PAYLOAD(0, (void *)0, 0, 0)							},
	{	31,		C0_T20,		(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C0_EV_T20, 0, &DB_C0_T20_0)		},
	{	35,		C0_T20,		(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C0_EV_T20, 0, &DB_C0_T20_1)		},
	{	41,		C0_T20,		(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C0_EV_T20, 0, &DB_C0_T20_2)		},
	{	48,		C0_T20,		(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C0_EV_T20, 0, &DB_C0_T20_3)		},
	{	50,		C0_T20,		(ILM_EVENT_PSWAP | ILM_EVENT_TTERM),	PAYLOAD(0, (void *)0, 0, &DB_C0_T20_4)				},
	{	50,		C0_T100,	(ILM_EVENT_TACT),						PAYLOAD(0, (void *)0, 0, 0)							},
	{	52,		C0_T100,	(ILM_EVENT_PSWAP),						PAYLOAD(0, (void *)0, 0, &DB_C0_T100_0)				},
	{	54,		C0_T100,	(ILM_EVENT_LETEV),						PAYLOAD(0, (void *)C0_EV_T100, 0, 0)				},
	{	57,		C0_T100,	(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C0_EV_T100, 0, &DB_C0_T100_1)	},
	{	61,		C0_T100,	(ILM_EVENT_PSWAP),						PAYLOAD(0, (void *)0, 0, &DB_C0_T100_2)				},
	{	67,		C0_T100,	(ILM_EVENT_LETEV),						PAYLOAD(0, (void *)C0_EV_T100, 0, 0)				},
	{	73,		C0_T100,	(ILM_EVENT_PSWAP | ILM_EVENT_TTERM),	PAYLOAD(0, (void *)0, 0, &DB_C0_T100_3)				},
	{	100,	C0_T10,		(ILM_EVENT_TACT),						PAYLOAD(0, (void *)0, 0, 0)							},
	{	106,	C0_T10,		(ILM_EVENT_PSWAP),						PAYLOAD(0, (void *)0, 0, &DB_C0_T10_0)				},
	{	111,	C0_T10,		(ILM_EVENT_LETEV),						PAYLOAD(0, (void *)C0_EV_T10, 0, 0)					},
	{	115,	C0_T10,		(ILM_EVENT_PSWAP),						PAYLOAD(0, (void *)0, 0, &DB_C0_T10_1)				},
	{	119,	C0_T10,		(ILM_EVENT_LETEV),						PAYLOAD(0, (void *)C0_EV_T10, 0, 0)					},
	{	121,	C0_T10,		(ILM_EVENT_PSWAP | ILM_EVENT_TTERM),	PAYLOAD(0, (void *)0, 0, &DB_C0_T10_2)				},
	{	200,	C0_T10,		(ILM_EVENT_TACT),						PAYLOAD(0, (void *)0, 0, 0)							},
	{	206,	C0_T10,		(ILM_EVENT_PSWAP),						PAYLOAD(0, (void *)0, 0, &DB_C0_T10_0)				},
	{	211,	C0_T10,		(ILM_EVENT_LETEV),						PAYLOAD(0, (void *)C0_EV_T10, 0, 0)					},
	{	215,	C0_T10,		(ILM_EVENT_PSWAP),						PAYLOAD(0, (void *)0, 0, &DB_C0_T10_1)				},
	{	219,	C0_T10,		(ILM_EVENT_LETEV),						PAYLOAD(0, (void *)C0_EV_T10, 0, 0)					},
	{	221,	C0_T10,		(ILM_EVENT_PSWAP | ILM_EVENT_TTERM),	PAYLOAD(0, (void *)0, 0, &DB_C0_T10_2)				},
	{	221,	C0_T20,		(ILM_EVENT_TACT),						PAYLOAD(0, (void *)0, 0, 0)							},
	{	231,	C0_T20,		(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C0_EV_T20, 0, &DB_C0_T20_0)		},
	{	235,	C0_T20,		(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C0_EV_T20, 0, &DB_C0_T20_1)		},
	{	241,	C0_T20,		(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C0_EV_T20, 0, &DB_C0_T20_2)		},
	{	248,	C0_T20,		(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C0_EV_T20, 0, &DB_C0_T20_3)		},
	{	250,	C0_T20,		(ILM_EVENT_PSWAP | ILM_EVENT_TTERM),	PAYLOAD(0, (void *)0, 0, &DB_C0_T20_4)				},
	{	300,	C0_T10,		(ILM_EVENT_TACT),						PAYLOAD(0, (void *)0, 0, 0)							},
	{	306,	C0_T10,		(ILM_EVENT_PSWAP),						PAYLOAD(0, (void *)0, 0, &DB_C0_T10_0)				},
	{	311,	C0_T10,		(ILM_EVENT_LETEV),						PAYLOAD(0, (void *)C0_EV_T10, 0, 0)					},
	{	315,	C0_T10,		(ILM_EVENT_PSWAP),						PAYLOAD(0, (void *)0, 0, &DB_C0_T10_1)				},
	{	319,	C0_T10,		(ILM_EVENT_LETEV),						PAYLOAD(0, (void *)C0_EV_T10, 0, 0)					},
	{	321,	C0_T10,		(ILM_EVENT_PSWAP | ILM_EVENT_TTERM),	PAYLOAD(0, (void *)0, 0, &DB_C0_T10_2)				},
	{	400,	C0_T10,		(ILM_EVENT_TACT),						PAYLOAD(0, (void *)0, 0, 0)							},
	{	406,	C0_T10,		(ILM_EVENT_PSWAP),						PAYLOAD(0, (void *)0, 0, &DB_C0_T10_0)				},
	{	411,	C0_T10,		(ILM_EVENT_LETEV),						PAYLOAD(0, (void *)C0_EV_T10, 0, 0)					},
	{	415,	C0_T10,		(ILM_EVENT_PSWAP),						PAYLOAD(0, (void *)0, 0, &DB_C0_T10_1)				},
	{	419,	C0_T10,		(ILM_EVENT_LETEV),						PAYLOAD(0, (void *)C0_EV_T10, 0, 0)					},
	{	421,	C0_T10,		(ILM_EVENT_PSWAP | ILM_EVENT_TTERM),	PAYLOAD(0, (void *)0, 0, &DB_C0_T10_2)				},
	{	421,	C0_T20,		(ILM_EVENT_TACT),						PAYLOAD(0, (void *)0, 0, 0)							},
	{	431,	C0_T20,		(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C0_EV_T20, 0, &DB_C0_T20_0)		},
	{	435,	C0_T20,		(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C0_EV_T20, 0, &DB_C0_T20_1)		},
	{	441,	C0_T20,		(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C0_EV_T20, 0, &DB_C0_T20_2)		},
	{	448,	C0_T20,		(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C0_EV_T20, 0, &DB_C0_T20_3)		},
	{	450,	C0_T20,		(ILM_EVENT_PSWAP | ILM_EVENT_TTERM),	PAYLOAD(0, (void *)0, 0, &DB_C0_T20_4)				},
	{	500,	C0_T10,		(ILM_EVENT_TACT),						PAYLOAD(0, (void *)0, 0, 0)							},
	{	506,	C0_T10,		(ILM_EVENT_PSWAP),						PAYLOAD(0, (void *)0, 0, &DB_C0_T10_0)				},
	{	511,	C0_T10,		(ILM_EVENT_LETEV),						PAYLOAD(0, (void *)C0_EV_T10, 0, 0)					},
	{	515,	C0_T10,		(ILM_EVENT_PSWAP),						PAYLOAD(0, (void *)0, 0, &DB_C0_T10_1)				},
	{	519,	C0_T10,		(ILM_EVENT_LETEV),						PAYLOAD(0, (void *)C0_EV_T10, 0, 0)					},
	{	521,	C0_T10,		(ILM_EVENT_PSWAP | ILM_EVENT_TTERM),	PAYLOAD(0, (void *)0, 0, &DB_C0_T10_2)				},
	{	600,	C0_T10,		(ILM_EVENT_TACT),						PAYLOAD(0, (void *)0, 0, 0)							},
	{	606,	C0_T10,		(ILM_EVENT_PSWAP),						PAYLOAD(0, (void *)0, 0, &DB_C0_T10_0)				},
	{	611,	C0_T10,		(ILM_EVENT_LETEV),						PAYLOAD(0, (void *)C0_EV_T10, 0, 0)					},
	{	615,	C0_T10,		(ILM_EVENT_PSWAP),						PAYLOAD(0, (void *)0, 0, &DB_C0_T10_1)				},
	{	619,	C0_T10,		(ILM_EVENT_LETEV),						PAYLOAD(0, (void *)C0_EV_T10, 0, 0)					},
	{	621,	C0_T10,		(ILM_EVENT_PSWAP | ILM_EVENT_TTERM),	PAYLOAD(0, (void *)0, 0, &DB_C0_T10_2)				},
	{	621,	C0_T20,		(ILM_EVENT_TACT),						PAYLOAD(0, (void *)0, 0, 0)							},
	{	631,	C0_T20,		(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C0_EV_T20, 0, &DB_C0_T20_0)		},
	{	635,	C0_T20,		(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C0_EV_T20, 0, &DB_C0_T20_1)		},
	{	641,	C0_T20,		(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C0_EV_T20, 0, &DB_C0_T20_2)		},
	{	648,	C0_T20,		(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C0_EV_T20, 0, &DB_C0_T20_3)		},
	{	650,	C0_T20,		(ILM_EVENT_PSWAP | ILM_EVENT_TTERM),	PAYLOAD(0, (void *)0, 0, &DB_C0_T20_4)				},
	{	700,	C0_T10,		(ILM_EVENT_TACT),						PAYLOAD(0, (void *)0, 0, 0)							},
	{	706,	C0_T10,		(ILM_EVENT_PSWAP),						PAYLOAD(0, (void *)0, 0, &DB_C0_T10_0)				},
	{	711,	C0_T10,		(ILM_EVENT_LETEV),						PAYLOAD(0, (void *)C0_EV_T10, 0, 0)					},
	{	715,	C0_T10,		(ILM_EVENT_PSWAP),						PAYLOAD(0, (void *)0, 0, &DB_C0_T10_1)				},
	{	719,	C0_T10,		(ILM_EVENT_LETEV),						PAYLOAD(0, (void *)C0_EV_T10, 0, 0)					},
	{	721,	C0_T10,		(ILM_EVENT_PSWAP | ILM_EVENT_TTERM),	PAYLOAD(0, (void *)0, 0, &DB_C0_T10_2)				},
	{	800,	C0_T10,		(ILM_EVENT_TACT),						PAYLOAD(0, (void *)0, 0, 0)							},
	{	806,	C0_T10,		(ILM_EVENT_PSWAP),						PAYLOAD(0, (void *)0, 0, &DB_C0_T10_0)				},
	{	811,	C0_T10,		(ILM_EVENT_LETEV),						PAYLOAD(0, (void *)C0_EV_T10, 0, 0)					},
	{	815,	C0_T10,		(ILM_EVENT_PSWAP),						PAYLOAD(0, (void *)0, 0, &DB_C0_T10_1)				},
	{	819,	C0_T10,		(ILM_EVENT_LETEV),						PAYLOAD(0, (void *)C0_EV_T10, 0, 0)					},
	{	821,	C0_T10,		(ILM_EVENT_PSWAP | ILM_EVENT_TTERM),	PAYLOAD(0, (void *)0, 0, &DB_C0_T10_2)				},
	{	821,	C0_T20,		(ILM_EVENT_TACT),						PAYLOAD(0, (void *)0, 0, 0)							},
	{	831,	C0_T20,		(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C0_EV_T20, 0, &DB_C0_T20_0)		},
	{	835,	C0_T20,		(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C0_EV_T20, 0, &DB_C0_T20_1)		},
	{	841,	C0_T20,		(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C0_EV_T20, 0, &DB_C0_T20_2)		},
	{	848,	C0_T20,		(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C0_EV_T20, 0, &DB_C0_T20_3)		},
	{	850,	C0_T20,		(ILM_EVENT_PSWAP | ILM_EVENT_TTERM),	PAYLOAD(0, (void *)0, 0, &DB_C0_T20_4)				},
	{	900,	C0_T10,		(ILM_EVENT_TACT),						PAYLOAD(0, (void *)0, 0, 0)							},
	{	906,	C0_T10,		(ILM_EVENT_PSWAP),						PAYLOAD(0, (void *)0, 0, &DB_C0_T10_0)				},
	{	911,	C0_T10,		(ILM_EVENT_LETEV),						PAYLOAD(0, (void *)C0_EV_T10, 0, 0)					},
	{	915,	C0_T10,		(ILM_EVENT_PSWAP),						PAYLOAD(0, (void *)0, 0, &DB_C0_T10_1)				},
	{	919,	C0_T10,		(ILM_EVENT_LETEV),						PAYLOAD(0, (void *)C0_EV_T10, 0, 0)					},
	{	921,	C0_T10,		(ILM_EVENT_PSWAP | ILM_EVENT_TTERM),	PAYLOAD(0, (void *)0, 0, &DB_C0_T10_2)				}
};

const size_t CO_LET_TABLE_SIZE = sizeof(CO_LET_TABLE) / sizeof(ILM_LET_TABLE_T);			/**< \brief Number of LET event entries on C0 */
const size_t C0_HW_TABLE_SIZE = sizeof(C0_HW_Master_Table) / sizeof(ILM_HW_LET_TABLE_T);	/**< \brief Number of LET IRQ entries         */
