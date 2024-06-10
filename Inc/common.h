/*
 * common_macros.h
 *
 *  Created on: Jan 30, 2024
 *      Author: sameh
 */

#ifndef COMMON_H_
#define COMMON_H_

#define _SET_BIT(REG,BIT)		(REG |=  (1 << BIT))
#define _CLEAR_BIT(REG,BIT)		(REG &= ~(1 << BIT))
#define _TOGGLE_BIT(REG,BIT)	(REG ^=  (1 << BIT))

typedef enum
{
	E_NOK = 0,
	E_OK
}Std_ReturnStatus;

#endif /* COMMON_H_ */
