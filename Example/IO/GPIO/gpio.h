/**
 * \file gpio.h
 * \brief Abstraction layer for GPIO access
 * \ingroup Example
 */

/*
 * gpio.h
 *
 *  Created on: 16.05.2017
 *      Author: matthiasb
 */

#ifndef GPIO_H_
#define GPIO_H_

extern void GPIO_Init(void);
extern void GPIO_On(unsigned int id);
extern void GPIO_Off(unsigned int id);


#endif /* GPIO_H_ */
