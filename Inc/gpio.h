/*
 * gpio.h
 *
 *  Created on: Jan 31, 2024
 *      Author: sameh
 */

#ifndef GPIO_H_
#define GPIO_H_

/*================= includes =================*/
#include "RCC.h"

/*================= Macros =================*/


/*================= User defined data types =================*/
typedef enum
{
	GPIO_LOW = 0,
	GPIO_HIGH
}Logic_t;

typedef enum
{
	Input = 0,
	Output,
	AltFunction,
	Analog
}GPIO_mode;

typedef enum
{
	PushPull = 0,
	OpenDrain
}OUT_type;

typedef enum
{
	LowSpeed = 0,
	MedSpeed,
	HighSpeed,
	VeryHighSpeed
}OUT_speed;

typedef enum
{
	None = 0,
	PullUp,
	PullDown
}PULL_type;

typedef enum
{
	AF0 = 0,
	AF1,
	AF2,
	AF3,
	AF4,
	AF5,
	AF6,
	AF7,
	AF8,
	AF9,
	AF10,
	AF11,
	AF12,
	AF13,
	AF14,
	AF15,
}ALT_num;

typedef struct
{
	GPIO_TypeDef *Gpio;
	uint32_t pin_no;
	uint32_t mode;
	uint32_t outType;
	uint32_t outSpeed;
	uint32_t pull;
	uint32_t altFunc;
}Pin_cfg;

typedef enum
{
	RISING = 0,
	FALLING,
	RISING_FALLING

}edge_detect;
/*================= Software interfaces =================*/
Std_ReturnStatus GPIO_Init(Pin_cfg *pin);
Std_ReturnStatus GPIO_Write_Pin(GPIO_TypeDef *Gpio,uint16_t pin, Logic_t logic);
Std_ReturnStatus GPIO_Toggle_Pin(GPIO_TypeDef *Gpio,uint16_t pin);
Logic_t GPIO_Read_Pin(GPIO_TypeDef *Gpio,uint16_t pin);
Std_ReturnStatus GPIO_Set_EXTI(GPIO_TypeDef *Gpio,uint16_t pin,edge_detect edge);

#endif /* GPIO_H_ */
