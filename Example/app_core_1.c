/**
 * \file app_core_1.c
 * \brief LET application for core 1
 * \ingroup Example
 */

/*
 * app_core_1.c
 *
 *  Created on: 25.07.2017
 *      Author: matthiasb
 */
#include "shared.h"
#include "burn_wcet.h"

/*
 * Worst-case execution Times (WCET) for simulated runnable
 * blocks (e.g. each block is interpreted as an LET task)
 * (times given in micro seconds)
 */
const EE_UINT32 C1_T10_RUNNABLE_WCET[C1_T10_RUNNABLE_NUM] =		/**< \brief Runnable sequence table (WCETs) for T10 on C1  */
{
		150,
		200,
		100,
		150
};
const EE_UINT32 C1_T20_RUNNABLE_WCET[C1_T20_RUNNABLE_NUM] =		/**< \brief Runnable sequence table (WCETs) for T20 on C1  */
{
		300,
		200,
		100
};
const EE_UINT32 C1_T100_RUNNABLE_WCET[C1_T100_RUNNABLE_NUM] =	/**< \brief Runnable sequence table (WCETs) for T100 on C1 */
{
		100,
		150
};

/*
 * Define Doube Buffer for each runnable block
 * initialized to 0, as we don't have real data
 */
ILM_DATA_OUT_T EE_SHARED_UDATA DB_C1_T10_0	= {.Read.Generic = (void *)0, .Write.Generic =  (void *)0};	/**< \brief Double buffer for runnable 0 of T10 on C1  */
ILM_DATA_OUT_T EE_SHARED_UDATA DB_C1_T10_1	= {.Read.Generic = (void *)0, .Write.Generic =  (void *)0};	/**< \brief Double buffer for runnable 1 of T10 on C1  */
ILM_DATA_OUT_T EE_SHARED_UDATA DB_C1_T10_2	= {.Read.Generic = (void *)0, .Write.Generic =  (void *)0};	/**< \brief Double buffer for runnable 2 of T10 on C1  */
ILM_DATA_OUT_T EE_SHARED_UDATA DB_C1_T10_3	= {.Read.Generic = (void *)0, .Write.Generic =  (void *)0};	/**< \brief Double buffer for runnable 3 of T10 on C1  */
ILM_DATA_OUT_T EE_SHARED_UDATA DB_C1_T20_0	= {.Read.Generic = (void *)0, .Write.Generic =  (void *)0};	/**< \brief Double buffer for runnable 0 of T20 on C1  */
ILM_DATA_OUT_T EE_SHARED_UDATA DB_C1_T20_1	= {.Read.Generic = (void *)0, .Write.Generic =  (void *)0};	/**< \brief Double buffer for runnable 1 of T20 on C1  */
ILM_DATA_OUT_T EE_SHARED_UDATA DB_C1_T20_2	= {.Read.Generic = (void *)0, .Write.Generic =  (void *)0};	/**< \brief Double buffer for runnable 2 of T20 on C1  */
ILM_DATA_OUT_T EE_SHARED_UDATA DB_C1_T100_0	= {.Read.Generic = (void *)0, .Write.Generic =  (void *)0};	/**< \brief Double buffer for runnable 0 of T100 on C1 */
ILM_DATA_OUT_T EE_SHARED_UDATA DB_C1_T100_1	= {.Read.Generic = (void *)0, .Write.Generic =  (void *)0};	/**< \brief Double buffer for runnable 1 of T100 on C1 */

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
 * \brief ECC implementation of task T10 on C1
 * \return None
 */
TASK(C1_T10)
{
	const unsigned int myId=C1_T10;
	EventMaskType mask;
	FUNC_CALL(C1_T10_RUNNABLE_WCET[0]);
	WAIT_SP(C1_T10, C1_EV_T10, &mask);
	FUNC_CALL(C1_T10_RUNNABLE_WCET[1]);
	WAIT_SP(C1_T10, C1_EV_T10, &mask);
	FUNC_CALL(C1_T10_RUNNABLE_WCET[2]);
	WAIT_SP(C1_T10, C1_EV_T10, &mask);
	FUNC_CALL(C1_T10_RUNNABLE_WCET[3]);
	TerminateTask();
}

/**
 * \brief ECC implementation of task T20 on C1
 * \return None
 */
TASK(C1_T20)
{
	const unsigned int myId=C1_T20;
	EventMaskType mask;
	FUNC_CALL(C1_T20_RUNNABLE_WCET[0]);
	WAIT_SP(C1_T20, C1_EV_T20, &mask);
	FUNC_CALL(C1_T20_RUNNABLE_WCET[1]);
	WAIT_SP(C1_T20, C1_EV_T20, &mask);
	FUNC_CALL(C1_T20_RUNNABLE_WCET[2]);
	TerminateTask();
}

/**
 * \brief ECC implementation of task T100 on C1
 * \return None
 */
TASK(C1_T100)
{
	const unsigned int myId=C1_T100;
	EventMaskType mask;
	FUNC_CALL(C1_T100_RUNNABLE_WCET[0]);
	WAIT_SP(C1_T100, C1_EV_T100, &mask);
	FUNC_CALL(C1_T100_RUNNABLE_WCET[1]);
	TerminateTask();
}
#else
/*
 * Use an OSEK/AUTOSAR
 * Basic Conformance Class (ECC)
 * task model
 */

/**
 * \brief BCC implementation of task T10 on C1
 * \return None
 */
TASK(C1_T10)
{
	const unsigned int myId=C1_T10;
	static unsigned int C1_T10_CNT = 0;

	FUNC_CALL(C1_T10_RUNNABLE_WCET[C1_T10_CNT]);
	C1_T10_CNT = (C1_T10_CNT + 1) % C1_T10_RUNNABLE_NUM;
	TerminateTask();
}

/**
 * \brief BCC implementation of task T20 on C1
 * \return None
 */
TASK(C1_T20)
{
	const unsigned int myId=C1_T20;
	static unsigned int C1_T20_CNT = 0;

	FUNC_CALL(C1_T20_RUNNABLE_WCET[C1_T20_CNT]);
	C1_T20_CNT = (C1_T20_CNT + 1) % C1_T20_RUNNABLE_NUM;
	TerminateTask();
}

/**
 * \brief BCC implementation of task T100 on C1
 * \return None
 */
TASK(C1_T100)
{
	const unsigned int myId=C1_T100;
	static unsigned int C1_T100_CNT = 0;

	FUNC_CALL(C1_T100_RUNNABLE_WCET[C1_T100_CNT]);
	C1_T100_CNT = (C1_T100_CNT + 1) % C1_T100_RUNNABLE_NUM;
	TerminateTask();
}
#endif

/*
 * Configuration table for ILM Handler
 */
const ILM_LET_TABLE_T C1_LET_TABLE[] =											/**< \brief LET event table for C1 */
{
	{	6,		C1_T10,		(ILM_EVENT_TACT),						PAYLOAD(0, (void *)0, 0, 0)						},
	{	8,		C1_T10,		(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C1_EV_T10, 0, &DB_C1_T10_0)	},
	{	11,		C1_T10,		(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C1_EV_T10, 0, &DB_C1_T10_1)	},
	{	15,		C1_T10,		(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C1_EV_T10, 0, &DB_C1_T10_2)	},
	{	17,		C1_T10,		(ILM_EVENT_PSWAP | ILM_EVENT_TTERM),	PAYLOAD(0, (void *)0, 0, &DB_C1_T10_3)			},
	{	31,		C1_T20,		(ILM_EVENT_TACT),						PAYLOAD(0, (void *)0, 0, 0)						},
	{	35,		C1_T20,		(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C1_EV_T20, 0, &DB_C1_T20_0)	},
	{	41,		C1_T20,		(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C1_EV_T20, 0, &DB_C1_T20_1)	},
	{	48,		C1_T20,		(ILM_EVENT_PSWAP | ILM_EVENT_TTERM),	PAYLOAD(0, (void *)0, 0, &DB_C1_T20_2)			},
	{	57,		C1_T100,	(ILM_EVENT_TACT),						PAYLOAD(0, (void *)0, 0, 0)						},
	{	61,		C1_T100,	(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C1_EV_T100, 0, &DB_C1_T100_0)},
	{	67,		C1_T100,	(ILM_EVENT_PSWAP | ILM_EVENT_TTERM),	PAYLOAD(0, (void *)0, 0, &DB_C1_T100_1)			},
	{	106,	C1_T10,		(ILM_EVENT_TACT),						PAYLOAD(0, (void *)0, 0, 0)						},
	{	108,	C1_T10,		(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C1_EV_T10, 0, &DB_C1_T10_0)	},
	{	111,	C1_T10,		(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C1_EV_T10, 0, &DB_C1_T10_1)	},
	{	115,	C1_T10,		(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C1_EV_T10, 0, &DB_C1_T10_2)	},
	{	117,	C1_T10,		(ILM_EVENT_PSWAP | ILM_EVENT_TTERM),	PAYLOAD(0, (void *)0, 0, &DB_C1_T10_3)			},
	{	206,	C1_T10,		(ILM_EVENT_TACT),						PAYLOAD(0, (void *)0, 0, 0)						},
	{	208,	C1_T10,		(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C1_EV_T10, 0, &DB_C1_T10_0)	},
	{	211,	C1_T10,		(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C1_EV_T10, 0, &DB_C1_T10_1)	},
	{	215,	C1_T10,		(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C1_EV_T10, 0, &DB_C1_T10_2)	},
	{	217,	C1_T10,		(ILM_EVENT_PSWAP | ILM_EVENT_TTERM),	PAYLOAD(0, (void *)0, 0, &DB_C1_T10_3)			},
	{	231,	C1_T20,		(ILM_EVENT_TACT),						PAYLOAD(0, (void *)0, 0, 0)						},
	{	235,	C1_T20,		(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C1_EV_T20, 0, &DB_C1_T20_0)	},
	{	241,	C1_T20,		(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C1_EV_T20, 0, &DB_C1_T20_1)	},
	{	248,	C1_T20,		(ILM_EVENT_PSWAP | ILM_EVENT_TTERM),	PAYLOAD(0, (void *)0, 0, &DB_C1_T20_2)			},
	{	306,	C1_T10,		(ILM_EVENT_TACT),						PAYLOAD(0, (void *)0, 0, 0)						},
	{	308,	C1_T10,		(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C1_EV_T10, 0, &DB_C1_T10_0)	},
	{	311,	C1_T10,		(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C1_EV_T10, 0, &DB_C1_T10_1)	},
	{	315,	C1_T10,		(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C1_EV_T10, 0, &DB_C1_T10_2)	},
	{	317,	C1_T10,		(ILM_EVENT_PSWAP | ILM_EVENT_TTERM),	PAYLOAD(0, (void *)0, 0, &DB_C1_T10_3)			},
	{	406,	C1_T10,		(ILM_EVENT_TACT),						PAYLOAD(0, (void *)0, 0, 0)						},
	{	408,	C1_T10,		(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C1_EV_T10, 0, &DB_C1_T10_0)	},
	{	411,	C1_T10,		(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C1_EV_T10, 0, &DB_C1_T10_1)	},
	{	415,	C1_T10,		(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C1_EV_T10, 0, &DB_C1_T10_2)	},
	{	417,	C1_T10,		(ILM_EVENT_PSWAP | ILM_EVENT_TTERM),	PAYLOAD(0, (void *)0, 0, &DB_C1_T10_3)			},
	{	431,	C1_T20,		(ILM_EVENT_TACT),						PAYLOAD(0, (void *)0, 0, 0)						},
	{	435,	C1_T20,		(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C1_EV_T20, 0, &DB_C1_T20_0)	},
	{	441,	C1_T20,		(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C1_EV_T20, 0, &DB_C1_T20_1)	},
	{	448,	C1_T20,		(ILM_EVENT_PSWAP | ILM_EVENT_TTERM),	PAYLOAD(0, (void *)0, 0, &DB_C1_T20_2)			},
	{	506,	C1_T10,		(ILM_EVENT_TACT),						PAYLOAD(0, (void *)0, 0, 0)						},
	{	508,	C1_T10,		(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C1_EV_T10, 0, &DB_C1_T10_0)	},
	{	511,	C1_T10,		(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C1_EV_T10, 0, &DB_C1_T10_1)	},
	{	515,	C1_T10,		(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C1_EV_T10, 0, &DB_C1_T10_2)	},
	{	517,	C1_T10,		(ILM_EVENT_PSWAP | ILM_EVENT_TTERM),	PAYLOAD(0, (void *)0, 0, &DB_C1_T10_3)			},
	{	606,	C1_T10,		(ILM_EVENT_TACT),						PAYLOAD(0, (void *)0, 0, 0)						},
	{	608,	C1_T10,		(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C1_EV_T10, 0, &DB_C1_T10_0)	},
	{	611,	C1_T10,		(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C1_EV_T10, 0, &DB_C1_T10_1)	},
	{	615,	C1_T10,		(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C1_EV_T10, 0, &DB_C1_T10_2)	},
	{	617,	C1_T10,		(ILM_EVENT_PSWAP | ILM_EVENT_TTERM),	PAYLOAD(0, (void *)0, 0, &DB_C1_T10_3)			},
	{	631,	C1_T20,		(ILM_EVENT_TACT),						PAYLOAD(0, (void *)0, 0, 0)						},
	{	635,	C1_T20,		(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C1_EV_T20, 0, &DB_C1_T20_0)	},
	{	641,	C1_T20,		(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C1_EV_T20, 0, &DB_C1_T20_1)	},
	{	648,	C1_T20,		(ILM_EVENT_PSWAP | ILM_EVENT_TTERM),	PAYLOAD(0, (void *)0, 0, &DB_C1_T20_2)			},
	{	706,	C1_T10,		(ILM_EVENT_TACT),						PAYLOAD(0, (void *)0, 0, 0)						},
	{	708,	C1_T10,		(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C1_EV_T10, 0, &DB_C1_T10_0)	},
	{	711,	C1_T10,		(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C1_EV_T10, 0, &DB_C1_T10_1)	},
	{	715,	C1_T10,		(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C1_EV_T10, 0, &DB_C1_T10_2)	},
	{	717,	C1_T10,		(ILM_EVENT_PSWAP | ILM_EVENT_TTERM),	PAYLOAD(0, (void *)0, 0, &DB_C1_T10_3)			},
	{	806,	C1_T10,		(ILM_EVENT_TACT),						PAYLOAD(0, (void *)0, 0, 0)						},
	{	808,	C1_T10,		(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C1_EV_T10, 0, &DB_C1_T10_0)	},
	{	811,	C1_T10,		(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C1_EV_T10, 0, &DB_C1_T10_1)	},
	{	815,	C1_T10,		(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C1_EV_T10, 0, &DB_C1_T10_2)	},
	{	817,	C1_T10,		(ILM_EVENT_PSWAP | ILM_EVENT_TTERM),	PAYLOAD(0, (void *)0, 0, &DB_C1_T10_3)			},
	{	831,	C1_T20,		(ILM_EVENT_TACT),						PAYLOAD(0, (void *)0, 0, 0)						},
	{	835,	C1_T20,		(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C1_EV_T20, 0, &DB_C1_T20_0)	},
	{	841,	C1_T20,		(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C1_EV_T20, 0, &DB_C1_T20_1)	},
	{	848,	C1_T20,		(ILM_EVENT_PSWAP | ILM_EVENT_TTERM),	PAYLOAD(0, (void *)0, 0, &DB_C1_T20_2)			},
	{	906,	C1_T10,		(ILM_EVENT_TACT),						PAYLOAD(0, (void *)0, 0, 0)						},
	{	908,	C1_T10,		(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C1_EV_T10, 0, &DB_C1_T10_0)	},
	{	911,	C1_T10,		(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C1_EV_T10, 0, &DB_C1_T10_1)	},
	{	915,	C1_T10,		(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C1_EV_T10, 0, &DB_C1_T10_2)	},
	{	917,	C1_T10,		(ILM_EVENT_PSWAP | ILM_EVENT_TTERM),	PAYLOAD(0, (void *)0, 0, &DB_C1_T10_3)			}
};

const size_t C1_LET_TABLE_SIZE = sizeof(C1_LET_TABLE) / sizeof(ILM_LET_TABLE_T);			/**< \brief Number of LET event entries on C1 */

