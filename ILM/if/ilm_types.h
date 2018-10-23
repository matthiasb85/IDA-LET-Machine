/**
 * \file ilm_types.h
 * \brief General include for type definitions
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
 *  Created on: 08.05.2017
 *      Author: matthiasb
 */

#ifndef ILM_TYPES_H_
#define ILM_TYPES_H_
#include "ILM/cfg/ilm_cfg.h"

/*
 * AUTOSAR integer data types
 */
typedef signed char    sint8;														/**< \brief AUTOSAR: signed int 8Bit           -128 .. +127			*/
typedef unsigned char  uint8;														/**< \brief AUTOSAR: unsigned int 8Bit            0 .. 255			*/
typedef signed short   sint16;														/**< \brief AUTOSAR: signed int 16Bit        -32768 .. +32767		*/
typedef unsigned short uint16;														/**< \brief AUTOSAR: unsigned int 16Bit           0 .. 65535		*/
typedef signed long    sint32;														/**< \brief AUTOSAR: signed int 32Bit   -2147483648 .. +2147483647	*/
typedef unsigned long  uint32;														/**< \brief AUTOSAR: unsigned int 32Bit           0 .. 4294967295	*/
typedef float          float32;														/**< \brief AUTOSAR: float 32Bit									*/
typedef double         float64;														/**< \brief AUTOSAR: float 64Bit									*/

typedef unsigned long  uint8_least;         										/**< \brief AUTOSAR: At least 8Bit									*/
typedef unsigned long  uint16_least;        										/**< \brief AUTOSAR: At least 16Bit									*/
typedef unsigned long  uint32_least;        										/**< \brief AUTOSAR: At least 32Bit									*/
typedef signed long    sint8_least;         										/**< \brief AUTOSAR: At least 7Bit + 1Bit sign						*/
typedef signed long    sint16_least;        										/**< \brief AUTOSAR: At least 15Bit + 1Bit sign						*/
typedef signed long    sint32_least;        										/**< \brief AUTOSAR: At least 31Bit + 1Bit sign						*/

typedef unsigned char  boolean;          											/**< \brief AUTOSAR: Boolean for use with TRUE/FALSE        		*/


#define ILM_EVENT_NONE 	(0)															/**< \brief Bitmask for LET event: Do nothing							*/
#define ILM_EVENT_TACT	((1 << 0))													/**< \brief Bitmask for LET event: Task activation						*/
#define ILM_EVENT_PRIOB ((1 << 1))													/**< \brief Bitmask for LET event: Priority boost						*/
#define ILM_EVENT_PSWAP	((1 << 2))													/**< \brief Bitmask for LET event: Pointer swap							*/
#define ILM_EVENT_LETEV	((1 << 3))													/**< \brief Bitmask for LET event: Set event							*/
#define ILM_EVENT_TTERM	((1 << 4))													/**< \brief Bitmask for LET event: Task termination						*/
typedef uint8 ILM_TYPEMASK_T;														/**< \brief Container type for event bitmask							*/

#define ILM_COREMASK_NONE	(0)														/**< \brief Bitmask for core event: No core should react				*/
#define ILM_COREMASK_C0		((1 << 0))												/**< \brief Bitmask for core event: Relevant for C0						*/
#define ILM_COREMASK_C1 	((1 << 1))												/**< \brief Bitmask for core event: Relevant for C1						*/
#define ILM_COREMASK_C2		((1 << 2))												/**< \brief Bitmask for core event: Relevant for C2						*/
#define ILM_COREMASK_ALL	(ILM_COREMASK_C0 | ILM_COREMASK_C1 | ILM_COREMASK_C2)	/**< \brief Bitmask for core event: Relevant for all cores				*/
typedef uint8 ILM_COREMASK_T;														/**< \brief Container type for core event bitmask						*/
#if ILM_NUM_OF_CORES > 3
#error "Not yet supported"
#endif

#ifdef ILM_MAX_LET_OFFSET
#if 	ILM_MAX_LET_OFFSET > 0 && ILM_MAX_LET_OFFSET <= 255
typedef uint8 ILM_OFFSET_T;															/**< \brief Optimized container type for LET offset						*/
#elif 	ILM_MAX_LET_OFFSET > 255 && ILM_MAX_LET_OFFSET <= 65535
typedef uint16 ILM_OFFSET_T;														/**< \brief Optimized container type for LET offset						*/
#elif 	ILM_MAX_LET_OFFSET > 65535 && ILM_MAX_LET_OFFSET <= 4294967295
typedef uint32 ILM_OFFSET_T;														/**< \brief Optimized container type for LET offset						*/
#else
#error "Offset size not supported"
#endif
#else
typedef uint32 ILM_OFFSET_T;														/**< \brief Container type for LET offset								*/
#endif

#ifdef ILM_MAX_OS_TASKS
#if 	ILM_MAX_OS_TASKS > 0 && ILM_MAX_OS_TASKS <= 255
typedef uint8 ILM_TASKS_T;															/**< \brief Optimized container type for OS task identifier				*/
#elif 	ILM_MAX_OS_TASKS > 255 && ILM_MAX_OS_TASKS <= 65535
typedef uint16 ILM_TASKS_T;															/**< \brief Optimized container type for OS task identifier				*/
#elif 	ILM_MAX_OS_TASKS > 65535 && ILM_MAX_OS_TASKS <= 4294967295
typedef uint32 ILM_TASKS_T;															/**< \brief Optimized container type for OS task identifier				*/
#else
#error "Offset size not supported"
#endif
#else
typedef uint32 ILM_TASKS_T;															/**< \brief Optimized container type for OS task identifier				*/
#endif


/**
 * \brief Double buffer struct
 */
typedef struct
{
	union
	{
		void	*Generic;															/**< \brief Generic pointer for fast access during pointer swap			*/
		sint8 	*S08;																/**< \brief Pointer for signed int 8 bit derefrencing during read 		*/
		uint8 	*U08;																/**< \brief Pointer for unsigned int 8 bit derefrencing during read 	*/
		sint16 	*S16;																/**< \brief Pointer for signed int 16 bit derefrencing during read 		*/
		uint16 	*U16;																/**< \brief Pointer for unsigned int 16 bit derefrencing during read	*/
		sint32 	*S32;																/**< \brief Pointer for signed int 32 bit derefrencing during read	 	*/
		uint32 	*U32;																/**< \brief Pointer for unsigned int 32 bit derefrencing during read 	*/
		float32	*F32;																/**< \brief Pointer for float 32 bit derefrencing during read 			*/
		float64	*F64;																/**< \brief Pointer for float 64 bit derefrencing during read			*/
	}Read;																			/**< \brief Pointer set for fast read access							*/
	union
	{
		void	*Generic;															/**< \brief Generic pointer for fast access during pointer swap			*/
		sint8 	*S08;																/**< \brief Pointer for signed int 8 bit derefrencing during write 		*/
		uint8 	*U08;																/**< \brief Pointer for unsigned int 8 bit derefrencing during write 	*/
		sint16 	*S16;																/**< \brief Pointer for signed int 16 bit derefrencing during write 	*/
		uint16 	*U16;																/**< \brief Pointer for unsigned int 16 bit derefrencing during write	*/
		sint32 	*S32;																/**< \brief Pointer for signed int 32 bit derefrencing during write 	*/
		uint32 	*U32;																/**< \brief Pointer for unsigned int 32 bit derefrencing during write 	*/
		float32	*F32;																/**< \brief Pointer for float 32 bit derefrencing during write 			*/
		float64	*F64;																/**< \brief Pointer for float 64 bit derefrencing during write			*/
	}Write;																			/**< \brief Pointer set for fast write access							*/
}ILM_DATA_OUT_T;

/**
 * \brief Struct for input backup during task activation
 */
typedef struct
{
	ILM_DATA_OUT_T	*pInput;														/**< \brief Pointer to double buffer struct, used as input				*/
	void 			**pLocalCopy;													/**< \brief Pointer to local backup pointer								*/
}ILM_DATA_IN_T;

/**
 * \brief Struct for LET table entry
 */
typedef struct
{
	ILM_OFFSET_T	Offset;															/**< \brief Relativ offset inside a macro period for LET event			*/
	ILM_TASKS_T		TaskId;															/**< \brief Task identifier												*/
	ILM_TYPEMASK_T	Type;															/**< \brief Type of LET event											*/
	struct
	{
#if ILM_USE_PRIOB > 0
		sint32			PrioBoost;													/**< \brief Priority boost level										*/
#endif
		void 			*pSchedEvent;												/**< \brief Pointer to event struct/id									*/
		ILM_DATA_IN_T	*pDataIn;													/**< \brief Pointer to input backup struct								*/
		ILM_DATA_OUT_T	*pDataOut;													/**< \brief Pointer to double buffer struct								*/
	}Payload;																		/**< \brief Payload struct for different event actions					*/

}ILM_LET_TABLE_T;

/**
 * \brief Struct for HW capture compare values
 */
typedef struct
{
	ILM_OFFSET_T	Offset;															/**< \brief Offset for capture compare IRQ in range of 0..MacroPeriod		*/
	ILM_COREMASK_T	CoreMask;														/**< \brief Bitmask to identify relevant cores for the event at this offset */
}ILM_HW_LET_TABLE_T;

#endif /* ILM_TYPES_H_ */
