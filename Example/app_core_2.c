/**
 * \file app_core_2.c
 * \brief LET application for core 2
 * \ingroup Example
 */

/*
 * app_core_2.c
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
const EE_UINT32 C2_T10_RUNABLE_CET[C2_T10_RUNABLE_NUM] =	/**< \brief Runnable sequence table (WCETs) for T10 on C2  */
{
		100,
		200,
		100,
		150
};
const EE_UINT32 C2_T20_RUNABLE_CET[C2_T20_RUNABLE_NUM] =	/**< \brief Runnable sequence table (WCETs) for T20 on C2  */
{
		400,
		200
};
const EE_UINT32 C2_T100_RUNABLE_CET[C2_T100_RUNABLE_NUM] =	/**< \brief Runnable sequence table (WCETs) for T100 on C2 */
{
		100,
		200,
		300,
		400
};

/*
 * Define Doube Buffer for each runnable block
 * initialized to 0, as we don't have real data
 */
ILM_DATA_OUT_T EE_SHARED_UDATA DB_C2_T10_0	= {.Read.Generic = (void *)0, .Write.Generic =  (void *)0};	/**< \brief Double buffer for runnable 0 of T10 on C2  */
ILM_DATA_OUT_T EE_SHARED_UDATA DB_C2_T10_1	= {.Read.Generic = (void *)0, .Write.Generic =  (void *)0};	/**< \brief Double buffer for runnable 1 of T10 on C2  */
ILM_DATA_OUT_T EE_SHARED_UDATA DB_C2_T10_2	= {.Read.Generic = (void *)0, .Write.Generic =  (void *)0};	/**< \brief Double buffer for runnable 2 of T10 on C2  */
ILM_DATA_OUT_T EE_SHARED_UDATA DB_C2_T10_3	= {.Read.Generic = (void *)0, .Write.Generic =  (void *)0};	/**< \brief Double buffer for runnable 3 of T10 on C2  */
ILM_DATA_OUT_T EE_SHARED_UDATA DB_C2_T20_0	= {.Read.Generic = (void *)0, .Write.Generic =  (void *)0};	/**< \brief Double buffer for runnable 0 of T20 on C2  */
ILM_DATA_OUT_T EE_SHARED_UDATA DB_C2_T20_1	= {.Read.Generic = (void *)0, .Write.Generic =  (void *)0};	/**< \brief Double buffer for runnable 1 of T20 on C2  */
ILM_DATA_OUT_T EE_SHARED_UDATA DB_C2_T100_0	= {.Read.Generic = (void *)0, .Write.Generic =  (void *)0};	/**< \brief Double buffer for runnable 0 of T100 on C2 */
ILM_DATA_OUT_T EE_SHARED_UDATA DB_C2_T100_1	= {.Read.Generic = (void *)0, .Write.Generic =  (void *)0};	/**< \brief Double buffer for runnable 1 of T100 on C2 */
ILM_DATA_OUT_T EE_SHARED_UDATA DB_C2_T100_2	= {.Read.Generic = (void *)0, .Write.Generic =  (void *)0};	/**< \brief Double buffer for runnable 2 of T100 on C2 */
ILM_DATA_OUT_T EE_SHARED_UDATA DB_C2_T100_3	= {.Read.Generic = (void *)0, .Write.Generic =  (void *)0};	/**< \brief Double buffer for runnable 3 of T100 on C2 */

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
 * \brief ECC implementation of task T10 on C2
 * \return None
 */
TASK(C2_T10)
{
	const unsigned int myId=C2_T10;
	EventMaskType mask;
	FUNC_CALL(C2_T10_RUNABLE_CET[0]);
	WAIT_SP(C2_T10, C2_EV_T10, &mask);
	FUNC_CALL(C2_T10_RUNABLE_CET[1]);
	WAIT_SP(C2_T10, C2_EV_T10, &mask);
	FUNC_CALL(C2_T10_RUNABLE_CET[2]);
	WAIT_SP(C2_T10, C2_EV_T10, &mask);
	FUNC_CALL(C2_T10_RUNABLE_CET[3]);
	TerminateTask();
}

/**
 * \brief ECC implementation of task T20 on C2
 * \return None
 */
TASK(C2_T20)
{
	const unsigned int myId=C2_T20;
	EventMaskType mask;
	FUNC_CALL(C2_T20_RUNABLE_CET[0]);
	WAIT_SP(C2_T20, C2_EV_T20, &mask);
	FUNC_CALL(C2_T20_RUNABLE_CET[1]);
	TerminateTask();
}

/**
 * \brief ECC implementation of task T100 on C2
 * \return None
 */
TASK(C2_T100)
{
	const unsigned int myId=C2_T100;
	EventMaskType mask;
	FUNC_CALL(C2_T100_RUNABLE_CET[0]);
	WAIT_SP(C2_T100, C2_EV_T100, &mask);
	FUNC_CALL(C2_T100_RUNABLE_CET[1]);
	WAIT_SP(C2_T100, C2_EV_T100, &mask);
	FUNC_CALL(C2_T100_RUNABLE_CET[2]);
	WAIT_SP(C2_T100, C2_EV_T100, &mask);
	FUNC_CALL(C2_T100_RUNABLE_CET[3]);
	TerminateTask();
}
#else
/*
 * Use an OSEK/AUTOSAR
 * Basic Conformance Class (ECC)
 * task model
 */

/**
 * \brief BCC implementation of task T10 on C2
 * \return None
 */
TASK(C2_T10)
{
	const unsigned int myId=C2_T10;
	static unsigned int C2_T10_CNT = 0;

	FUNC_CALL(C2_T10_RUNABLE_CET[C2_T10_CNT]);
	C2_T10_CNT = (C2_T10_CNT + 1) % C2_T10_RUNABLE_NUM;
	TerminateTask();
}

/**
 * \brief BCC implementation of task T20 on C2
 * \return None
 */
TASK(C2_T20)
{
	const unsigned int myId=C2_T20;
	static unsigned int C2_T20_CNT = 0;

	FUNC_CALL(C2_T20_RUNABLE_CET[C2_T20_CNT]);
	C2_T20_CNT = (C2_T20_CNT + 1) % C2_T20_RUNABLE_NUM;
	TerminateTask();
}

/**
 * \brief BCC implementation of task T100 on C2
 * \return None
 */
TASK(C2_T100)
{
	const unsigned int myId=C2_T100;
	static unsigned int C2_T100_CNT = 0;

	FUNC_CALL(C2_T100_RUNABLE_CET[C2_T100_CNT]);
	C2_T100_CNT = (C2_T100_CNT + 1) % C2_T100_RUNABLE_NUM;
	TerminateTask();
}
#endif

/*
 * Configuration table for ILM Handler
 */
const ILM_LET_TABLE_T C2_LET_TABLE[] =											/**< \brief LET event table for C2 */
{
	{	6,		C2_T10,		(ILM_EVENT_TACT),						PAYLOAD(0, (void *)0, 0, 0)							},
	{	8,		C2_T10,		(ILM_EVENT_PSWAP),						PAYLOAD(0, (void *)0, 0, &DB_C2_T10_0)				},
	{	11,		C2_T10,		(ILM_EVENT_LETEV),						PAYLOAD(0, (void *)C2_EV_T10, 0, 0)					},
	{	15,		C2_T10,		(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C2_EV_T10, 0, &DB_C2_T10_1)		},
	{	17,		C2_T10,		(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C2_EV_T10, 0, &DB_C2_T10_2)		},
	{	19,		C2_T10,		(ILM_EVENT_PSWAP | ILM_EVENT_TTERM),	PAYLOAD(0, (void *)0, 0, &DB_C2_T10_3)				},
	{	35,		C2_T20,		(ILM_EVENT_TACT),						PAYLOAD(0, (void *)0, 0, 0)							},
	{	41,		C2_T20,		(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C2_EV_T20, 0, &DB_C2_T20_0)		},
	{	48,		C2_T20,		(ILM_EVENT_PSWAP | ILM_EVENT_TTERM),	PAYLOAD(0, (void *)C2_EV_T20, 0, &DB_C2_T20_1)		},
	{	52,		C2_T100,	(ILM_EVENT_TACT),						PAYLOAD(0, (void *)0, 0, 0)							},
	{	54,		C2_T100,	(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C2_EV_T100, 0, &DB_C2_T100_0)	},
	{	57,		C2_T100,	(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C2_EV_T100, 0, &DB_C2_T100_1)	},
	{	61,		C2_T100,	(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C2_EV_T100, 0, &DB_C2_T100_2)	},
	{	67,		C2_T100,	(ILM_EVENT_PSWAP | ILM_EVENT_TTERM),	PAYLOAD(0, (void *)C2_EV_T100, 0, &DB_C2_T100_3)	},
	{	106,	C2_T10,		(ILM_EVENT_TACT),						PAYLOAD(0, (void *)0, 0, 0)							},
	{	108,	C2_T10,		(ILM_EVENT_PSWAP),						PAYLOAD(0, (void *)0, 0, &DB_C2_T10_0)				},
	{	111,	C2_T10,		(ILM_EVENT_LETEV),						PAYLOAD(0, (void *)C2_EV_T10, 0, 0)					},
	{	115,	C2_T10,		(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C2_EV_T10, 0, &DB_C2_T10_1)		},
	{	117,	C2_T10,		(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C2_EV_T10, 0, &DB_C2_T10_2)		},
	{	119,	C2_T10,		(ILM_EVENT_PSWAP | ILM_EVENT_TTERM),	PAYLOAD(0, (void *)0, 0, &DB_C2_T10_3)				},
	{	206,	C2_T10,		(ILM_EVENT_TACT),						PAYLOAD(0, (void *)0, 0, 0)							},
	{	208,	C2_T10,		(ILM_EVENT_PSWAP),						PAYLOAD(0, (void *)0, 0, &DB_C2_T10_0)				},
	{	211,	C2_T10,		(ILM_EVENT_LETEV),						PAYLOAD(0, (void *)C2_EV_T10, 0, 0)					},
	{	215,	C2_T10,		(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C2_EV_T10, 0, &DB_C2_T10_1)		},
	{	217,	C2_T10,		(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C2_EV_T10, 0, &DB_C2_T10_2)		},
	{	219,	C2_T10,		(ILM_EVENT_PSWAP | ILM_EVENT_TTERM),	PAYLOAD(0, (void *)0, 0, &DB_C2_T10_3)				},
	{	235,	C2_T20,		(ILM_EVENT_TACT),						PAYLOAD(0, (void *)0, 0, 0)							},
	{	241,	C2_T20,		(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C2_EV_T20, 0, &DB_C2_T20_0)		},
	{	248,	C2_T20,		(ILM_EVENT_PSWAP | ILM_EVENT_TTERM),	PAYLOAD(0, (void *)C2_EV_T20, 0, &DB_C2_T20_1)		},
	{	306,	C2_T10,		(ILM_EVENT_TACT),						PAYLOAD(0, (void *)0, 0, 0)							},
	{	308,	C2_T10,		(ILM_EVENT_PSWAP),						PAYLOAD(0, (void *)0, 0, &DB_C2_T10_0)				},
	{	311,	C2_T10,		(ILM_EVENT_LETEV),						PAYLOAD(0, (void *)C2_EV_T10, 0, 0)					},
	{	315,	C2_T10,		(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C2_EV_T10, 0, &DB_C2_T10_1)		},
	{	317,	C2_T10,		(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C2_EV_T10, 0, &DB_C2_T10_2)		},
	{	319,	C2_T10,		(ILM_EVENT_PSWAP | ILM_EVENT_TTERM),	PAYLOAD(0, (void *)0, 0, &DB_C2_T10_3)				},
	{	406,	C2_T10,		(ILM_EVENT_TACT),						PAYLOAD(0, (void *)0, 0, 0)							},
	{	408,	C2_T10,		(ILM_EVENT_PSWAP),						PAYLOAD(0, (void *)0, 0, &DB_C2_T10_0)				},
	{	411,	C2_T10,		(ILM_EVENT_LETEV),						PAYLOAD(0, (void *)C2_EV_T10, 0, 0)					},
	{	415,	C2_T10,		(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C2_EV_T10, 0, &DB_C2_T10_1)		},
	{	417,	C2_T10,		(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C2_EV_T10, 0, &DB_C2_T10_2)		},
	{	419,	C2_T10,		(ILM_EVENT_PSWAP | ILM_EVENT_TTERM),	PAYLOAD(0, (void *)0, 0, &DB_C2_T10_3)				},
	{	435,	C2_T20,		(ILM_EVENT_TACT),						PAYLOAD(0, (void *)0, 0, 0)							},
	{	441,	C2_T20,		(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C2_EV_T20, 0, &DB_C2_T20_0)		},
	{	448,	C2_T20,		(ILM_EVENT_PSWAP | ILM_EVENT_TTERM),	PAYLOAD(0, (void *)C2_EV_T20, 0, &DB_C2_T20_1)		},
	{	506,	C2_T10,		(ILM_EVENT_TACT),						PAYLOAD(0, (void *)0, 0, 0)							},
	{	508,	C2_T10,		(ILM_EVENT_PSWAP),						PAYLOAD(0, (void *)0, 0, &DB_C2_T10_0)				},
	{	511,	C2_T10,		(ILM_EVENT_LETEV),						PAYLOAD(0, (void *)C2_EV_T10, 0, 0)					},
	{	515,	C2_T10,		(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C2_EV_T10, 0, &DB_C2_T10_1)		},
	{	517,	C2_T10,		(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C2_EV_T10, 0, &DB_C2_T10_2)		},
	{	519,	C2_T10,		(ILM_EVENT_PSWAP | ILM_EVENT_TTERM),	PAYLOAD(0, (void *)0, 0, &DB_C2_T10_3)				},
	{	606,	C2_T10,		(ILM_EVENT_TACT),						PAYLOAD(0, (void *)0, 0, 0)							},
	{	608,	C2_T10,		(ILM_EVENT_PSWAP),						PAYLOAD(0, (void *)0, 0, &DB_C2_T10_0)				},
	{	611,	C2_T10,		(ILM_EVENT_LETEV),						PAYLOAD(0, (void *)C2_EV_T10, 0, 0)					},
	{	615,	C2_T10,		(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C2_EV_T10, 0, &DB_C2_T10_1)		},
	{	617,	C2_T10,		(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C2_EV_T10, 0, &DB_C2_T10_2)		},
	{	619,	C2_T10,		(ILM_EVENT_PSWAP | ILM_EVENT_TTERM),	PAYLOAD(0, (void *)0, 0, &DB_C2_T10_3)				},
	{	635,	C2_T20,		(ILM_EVENT_TACT),						PAYLOAD(0, (void *)0, 0, 0)							},
	{	641,	C2_T20,		(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C2_EV_T20, 0, &DB_C2_T20_0)		},
	{	648,	C2_T20,		(ILM_EVENT_PSWAP | ILM_EVENT_TTERM),	PAYLOAD(0, (void *)C2_EV_T20, 0, &DB_C2_T20_1)		},
	{	706,	C2_T10,		(ILM_EVENT_TACT),						PAYLOAD(0, (void *)0, 0, 0)							},
	{	708,	C2_T10,		(ILM_EVENT_PSWAP),						PAYLOAD(0, (void *)0, 0, &DB_C2_T10_0)				},
	{	711,	C2_T10,		(ILM_EVENT_LETEV),						PAYLOAD(0, (void *)C2_EV_T10, 0, 0)					},
	{	715,	C2_T10,		(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C2_EV_T10, 0, &DB_C2_T10_1)		},
	{	717,	C2_T10,		(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C2_EV_T10, 0, &DB_C2_T10_2)		},
	{	719,	C2_T10,		(ILM_EVENT_PSWAP | ILM_EVENT_TTERM),	PAYLOAD(0, (void *)0, 0, &DB_C2_T10_3)				},
	{	806,	C2_T10,		(ILM_EVENT_TACT),						PAYLOAD(0, (void *)0, 0, 0)							},
	{	808,	C2_T10,		(ILM_EVENT_PSWAP),						PAYLOAD(0, (void *)0, 0, &DB_C2_T10_0)				},
	{	811,	C2_T10,		(ILM_EVENT_LETEV),						PAYLOAD(0, (void *)C2_EV_T10, 0, 0)					},
	{	815,	C2_T10,		(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C2_EV_T10, 0, &DB_C2_T10_1)		},
	{	817,	C2_T10,		(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C2_EV_T10, 0, &DB_C2_T10_2)		},
	{	819,	C2_T10,		(ILM_EVENT_PSWAP | ILM_EVENT_TTERM),	PAYLOAD(0, (void *)0, 0, &DB_C2_T10_3)				},
	{	835,	C2_T20,		(ILM_EVENT_TACT),						PAYLOAD(0, (void *)0, 0, 0)							},
	{	841,	C2_T20,		(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C2_EV_T20, 0, &DB_C2_T20_0)		},
	{	848,	C2_T20,		(ILM_EVENT_PSWAP | ILM_EVENT_TTERM),	PAYLOAD(0, (void *)C2_EV_T20, 0, &DB_C2_T20_1)		},
	{	906,	C2_T10,		(ILM_EVENT_TACT),						PAYLOAD(0, (void *)0, 0, 0)							},
	{	908,	C2_T10,		(ILM_EVENT_PSWAP),						PAYLOAD(0, (void *)C2_EV_T10, 0, &DB_C2_T10_0)		},
	{	911,	C2_T10,		(ILM_EVENT_LETEV),						PAYLOAD(0, (void *)C2_EV_T10, 0, 0)					},
	{	915,	C2_T10,		(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C2_EV_T10, 0, &DB_C2_T10_1)		},
	{	917,	C2_T10,		(ILM_EVENT_PSWAP | ILM_EVENT_LETEV),	PAYLOAD(0, (void *)C2_EV_T10, 0, &DB_C2_T10_2)		},
	{	919,	C2_T10,		(ILM_EVENT_PSWAP | ILM_EVENT_TTERM),	PAYLOAD(0, (void *)0, 0, &DB_C2_T10_3)				}
};

const size_t C2_LET_TABLE_SIZE = sizeof(C2_LET_TABLE) / sizeof(ILM_LET_TABLE_T);			/**< \brief Number of LET event entries on C2 */
