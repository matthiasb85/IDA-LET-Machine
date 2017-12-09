/**
 * \file gpio.c
 * \brief Abstraction layer for GPIO access
 * \ingroup Example
 */

/*
 * gpio.c
 *
 *  Created on: 16.05.2017
 *      Author: matthiasb
 */
#include "ee.h"
#include "Port/Io/IfxPort_Io.h"

#if defined(GPIO_SHIELDBUDDY)
#define GPIO_PIN_MAX		27																				/**< \brief Number of GPIOs (ShieldBuddy)           */
static const IfxPort_Pin GPIO_PINS[GPIO_PIN_MAX] =															/**< \brief GPIO pin mapping table (ShieldBuddy)    */
{
	{ (Ifx_P *)&MODULE_P14,	 1 	},	// 0
	{ (Ifx_P *)&MODULE_P00,	 0 	},	// 1
	{ (Ifx_P *)&MODULE_P00,	 1 	},	// 2
	{ (Ifx_P *)&MODULE_P00,	 2 	},	// 3
	{ (Ifx_P *)&MODULE_P00,	 3 	},	// 4
	{ (Ifx_P *)&MODULE_P00,	 4 	},	// 5
	{ (Ifx_P *)&MODULE_P00,	 5 	},	// 6
	{ (Ifx_P *)&MODULE_P00,	 6 	},	// 7
	{ (Ifx_P *)&MODULE_P00,	 7 	},	// 8
	{ (Ifx_P *)&MODULE_P11,	 9 	},	// 9
	{ (Ifx_P *)&MODULE_P11,	 11 },	// 10
	{ (Ifx_P *)&MODULE_P11,	 2 	},	// 11
	{ (Ifx_P *)&MODULE_P11,	 6 	},	// 12
	{ (Ifx_P *)&MODULE_P21,	 0 	},	// 13
	{ (Ifx_P *)&MODULE_P14,	 0 	},	// 14
	{ (Ifx_P *)&MODULE_P15,	 6 	},	// 15
	{ (Ifx_P *)&MODULE_P00,	 8 	},	// 16
	{ (Ifx_P *)&MODULE_P00,	 9 	},	// 17
	{ (Ifx_P *)&MODULE_P00,	 10 },	// 18
	{ (Ifx_P *)&MODULE_P00,	 11 },	// 19
	{ (Ifx_P *)&MODULE_P00,	 12 },	// 20
	{ (Ifx_P *)&MODULE_P33,	 2 	},	// 21
	{ (Ifx_P *)&MODULE_P33,	 1 	},	// 22
	{ (Ifx_P *)&MODULE_P33,	 0 	},	// 23
	{ (Ifx_P *)&MODULE_P11,	 10 },	// 24
	{ (Ifx_P *)&MODULE_P33,	 3 	},	// 25
	{ (Ifx_P *)&MODULE_P11,	 3 	}	// 26
};


static IfxPort_Io_ConfigPin GPIO_OUTPUTS[GPIO_PIN_MAX] =													/**< \brief GPIO configuration table (ShieldBuddy) */
{
	{ &GPIO_PINS[0],	IfxPort_Mode_outputPushPullGeneral, 	IfxPort_PadDriver_cmosAutomotiveSpeed1 },
	{ &GPIO_PINS[1],	IfxPort_Mode_outputPushPullGeneral, 	IfxPort_PadDriver_cmosAutomotiveSpeed1 },
	{ &GPIO_PINS[2],	IfxPort_Mode_outputPushPullGeneral, 	IfxPort_PadDriver_cmosAutomotiveSpeed1 },
	{ &GPIO_PINS[3],	IfxPort_Mode_outputPushPullGeneral, 	IfxPort_PadDriver_cmosAutomotiveSpeed1 },
	{ &GPIO_PINS[4],	IfxPort_Mode_outputPushPullGeneral, 	IfxPort_PadDriver_cmosAutomotiveSpeed1 },
	{ &GPIO_PINS[5],	IfxPort_Mode_outputPushPullGeneral, 	IfxPort_PadDriver_cmosAutomotiveSpeed1 },
	{ &GPIO_PINS[6],	IfxPort_Mode_outputPushPullGeneral, 	IfxPort_PadDriver_cmosAutomotiveSpeed1 },
	{ &GPIO_PINS[7],	IfxPort_Mode_outputPushPullGeneral, 	IfxPort_PadDriver_cmosAutomotiveSpeed1 },
	{ &GPIO_PINS[8],	IfxPort_Mode_outputPushPullGeneral, 	IfxPort_PadDriver_cmosAutomotiveSpeed1 },
	{ &GPIO_PINS[9],	IfxPort_Mode_outputPushPullGeneral, 	IfxPort_PadDriver_cmosAutomotiveSpeed1 },
	{ &GPIO_PINS[10],	IfxPort_Mode_outputPushPullGeneral, 	IfxPort_PadDriver_cmosAutomotiveSpeed1 },
	{ &GPIO_PINS[11],	IfxPort_Mode_outputPushPullGeneral, 	IfxPort_PadDriver_cmosAutomotiveSpeed1 },
	{ &GPIO_PINS[12],	IfxPort_Mode_outputPushPullGeneral, 	IfxPort_PadDriver_cmosAutomotiveSpeed1 },
	{ &GPIO_PINS[13],	IfxPort_Mode_outputPushPullGeneral, 	IfxPort_PadDriver_cmosAutomotiveSpeed1 },
	{ &GPIO_PINS[14],	IfxPort_Mode_outputPushPullGeneral, 	IfxPort_PadDriver_cmosAutomotiveSpeed1 },
	{ &GPIO_PINS[15],	IfxPort_Mode_outputPushPullGeneral, 	IfxPort_PadDriver_cmosAutomotiveSpeed1 },
	{ &GPIO_PINS[16],	IfxPort_Mode_outputPushPullGeneral, 	IfxPort_PadDriver_cmosAutomotiveSpeed1 },
	{ &GPIO_PINS[17],	IfxPort_Mode_outputPushPullGeneral, 	IfxPort_PadDriver_cmosAutomotiveSpeed1 },
	{ &GPIO_PINS[18],	IfxPort_Mode_outputPushPullGeneral, 	IfxPort_PadDriver_cmosAutomotiveSpeed1 },
	{ &GPIO_PINS[19],	IfxPort_Mode_outputPushPullGeneral, 	IfxPort_PadDriver_cmosAutomotiveSpeed1 },
	{ &GPIO_PINS[20],	IfxPort_Mode_outputPushPullGeneral, 	IfxPort_PadDriver_cmosAutomotiveSpeed1 },
	{ &GPIO_PINS[21],	IfxPort_Mode_outputPushPullGeneral, 	IfxPort_PadDriver_cmosAutomotiveSpeed1 },
	{ &GPIO_PINS[22],	IfxPort_Mode_outputPushPullGeneral, 	IfxPort_PadDriver_cmosAutomotiveSpeed1 },
	{ &GPIO_PINS[23],	IfxPort_Mode_outputPushPullGeneral, 	IfxPort_PadDriver_cmosAutomotiveSpeed1 },
	{ &GPIO_PINS[24],	IfxPort_Mode_outputPushPullGeneral, 	IfxPort_PadDriver_cmosAutomotiveSpeed1 },
	{ &GPIO_PINS[25],	IfxPort_Mode_outputPushPullGeneral, 	IfxPort_PadDriver_cmosAutomotiveSpeed1 },
	{ &GPIO_PINS[26],	IfxPort_Mode_outputPushPullGeneral, 	IfxPort_PadDriver_cmosAutomotiveSpeed1 }
};
#elif defined(GPIO_TRIBOARD_TC275C)
#define GPIO_PIN_MAX		23																				/**< \brief Number of GPIOs (Triboard TC275)        */
static const IfxPort_Pin GPIO_PINS[GPIO_PIN_MAX] =															/**< \brief GPIO pin mapping table (Triboard TC275) */
{
	{ (Ifx_P *)&MODULE_P14,	 7 	},	// 0
	{ (Ifx_P *)&MODULE_P14,	 8 	},	// 1
	{ (Ifx_P *)&MODULE_P14,	 9 	},	// 2
	{ (Ifx_P *)&MODULE_P14,	 10 },	// 3
	{ (Ifx_P *)&MODULE_P15,	 6 	},	// 4
	{ (Ifx_P *)&MODULE_P15,	 7 	},	// 5
	{ (Ifx_P *)&MODULE_P20,	 1 	},	// 6
	{ (Ifx_P *)&MODULE_P10,	 1 	},	// 7
	{ (Ifx_P *)&MODULE_P10,	 0 	},	// 8
	{ (Ifx_P *)&MODULE_P33,	 6 	},	// 9
	{ (Ifx_P *)&MODULE_P33,	 0 	},	// 10
	{ (Ifx_P *)&MODULE_P33,	 4  },	// 11
	{ (Ifx_P *)&MODULE_P00,	 6	},	// 12
	{ (Ifx_P *)&MODULE_P00,	 7	},	// 13
	{ (Ifx_P *)&MODULE_P00,	 8 	},	// 14
	{ (Ifx_P *)&MODULE_P33,	 12 },	// 15
	{ (Ifx_P *)&MODULE_P33,	 11 },	// 16
	{ (Ifx_P *)&MODULE_P02,	 8	},	// 17
	{ (Ifx_P *)&MODULE_P02,	 7	},	// 18
	{ (Ifx_P *)&MODULE_P02,	 6 	},	// 19
	{ (Ifx_P *)&MODULE_P33,	 1 	},	// 20
	{ (Ifx_P *)&MODULE_P33,	 2 	},	// 21
	{ (Ifx_P *)&MODULE_P33,	 3  }	// 22

};


static IfxPort_Io_ConfigPin GPIO_OUTPUTS[GPIO_PIN_MAX] =													/**< \brief GPIO configuration table (Triboard TC275) */
{
	{ &GPIO_PINS[0],	IfxPort_Mode_outputPushPullGeneral, 	IfxPort_PadDriver_cmosAutomotiveSpeed1 },
	{ &GPIO_PINS[1],	IfxPort_Mode_outputPushPullGeneral, 	IfxPort_PadDriver_cmosAutomotiveSpeed1 },
	{ &GPIO_PINS[2],	IfxPort_Mode_outputPushPullGeneral, 	IfxPort_PadDriver_cmosAutomotiveSpeed1 },
	{ &GPIO_PINS[3],	IfxPort_Mode_outputPushPullGeneral, 	IfxPort_PadDriver_cmosAutomotiveSpeed1 },
	{ &GPIO_PINS[4],	IfxPort_Mode_outputPushPullGeneral, 	IfxPort_PadDriver_cmosAutomotiveSpeed1 },
	{ &GPIO_PINS[5],	IfxPort_Mode_outputPushPullGeneral, 	IfxPort_PadDriver_cmosAutomotiveSpeed1 },
	{ &GPIO_PINS[6],	IfxPort_Mode_outputPushPullGeneral, 	IfxPort_PadDriver_cmosAutomotiveSpeed1 },
	{ &GPIO_PINS[7],	IfxPort_Mode_outputPushPullGeneral, 	IfxPort_PadDriver_cmosAutomotiveSpeed1 },
	{ &GPIO_PINS[8],	IfxPort_Mode_outputPushPullGeneral, 	IfxPort_PadDriver_cmosAutomotiveSpeed1 },
	{ &GPIO_PINS[9],	IfxPort_Mode_outputPushPullGeneral, 	IfxPort_PadDriver_cmosAutomotiveSpeed1 },
	{ &GPIO_PINS[10],	IfxPort_Mode_outputPushPullGeneral, 	IfxPort_PadDriver_cmosAutomotiveSpeed1 },
	{ &GPIO_PINS[11],	IfxPort_Mode_outputPushPullGeneral, 	IfxPort_PadDriver_cmosAutomotiveSpeed1 },
	{ &GPIO_PINS[12],	IfxPort_Mode_outputPushPullGeneral, 	IfxPort_PadDriver_cmosAutomotiveSpeed1 },
	{ &GPIO_PINS[13],	IfxPort_Mode_outputPushPullGeneral, 	IfxPort_PadDriver_cmosAutomotiveSpeed1 },
	{ &GPIO_PINS[14],	IfxPort_Mode_outputPushPullGeneral, 	IfxPort_PadDriver_cmosAutomotiveSpeed1 },
	{ &GPIO_PINS[15],	IfxPort_Mode_outputPushPullGeneral, 	IfxPort_PadDriver_cmosAutomotiveSpeed1 },
	{ &GPIO_PINS[16],	IfxPort_Mode_outputPushPullGeneral, 	IfxPort_PadDriver_cmosAutomotiveSpeed1 },
	{ &GPIO_PINS[17],	IfxPort_Mode_outputPushPullGeneral, 	IfxPort_PadDriver_cmosAutomotiveSpeed1 },
	{ &GPIO_PINS[18],	IfxPort_Mode_outputPushPullGeneral, 	IfxPort_PadDriver_cmosAutomotiveSpeed1 },
	{ &GPIO_PINS[19],	IfxPort_Mode_outputPushPullGeneral, 	IfxPort_PadDriver_cmosAutomotiveSpeed1 },
	{ &GPIO_PINS[20],	IfxPort_Mode_outputPushPullGeneral, 	IfxPort_PadDriver_cmosAutomotiveSpeed1 },
	{ &GPIO_PINS[21],	IfxPort_Mode_outputPushPullGeneral, 	IfxPort_PadDriver_cmosAutomotiveSpeed1 },
	{ &GPIO_PINS[22],	IfxPort_Mode_outputPushPullGeneral, 	IfxPort_PadDriver_cmosAutomotiveSpeed1 },
};
#endif

static const IfxPort_Io_Config GPIO_Config = { .size = GPIO_PIN_MAX, .pinTable = GPIO_OUTPUTS };			/**< \brief GPIO configuration struct  */

/**
 * \brief Sets GPIO [id] to high
 * \param id Generic pin identifier
 * \return None
 */
void GPIO_On(unsigned int id)
{
	unsigned int idx = id;
	IfxPort_setPinHigh(GPIO_PINS[idx].port, GPIO_PINS[idx].pinIndex);
}

/**
 * \brief Sets GPIO [id] to low
 * \param id Generic pin identifier
 * \return None
 */
void GPIO_Off(unsigned int id)
{
	unsigned int idx = id;
	IfxPort_setPinLow(GPIO_PINS[idx].port, GPIO_PINS[idx].pinIndex);
}

/**
 * \brief GPIO init call
 * \return None
 */
void GPIO_Init(void)
{
    unsigned int index;

    IfxPort_Io_initModule(&GPIO_Config);

    /* Switch GPIOs OFF */
    for( index = 0; index < GPIO_PIN_MAX; ++index )
    {
    	GPIO_Off( index );
    }

    return;
}
