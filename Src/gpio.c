/*
 * gpio.c
 *
 *  Created on: Jan 31, 2024
 *      Author: sameh
 */


#include "gpio.h"

/*
 * @brief initialization of GPIO configurations.
 * @param Gpio : a pointer to Pin_cfg which contains
 * 		  the configuration of the required gpio.
 * @ret   return error status according to the function
 * 		  behavior.
 * 		  E_OK -> everything is OK.
 * 		  E_NOK-> something wrong happened.
 */
Std_ReturnStatus GPIO_Init(Pin_cfg *pin)
{
	if((NULL == pin) || (pin->pin_no < 0))
	{
		return E_NOK;
	}
	else
	{
		//Clear existing configuration.
		pin->Gpio->MODER &= ~(0x3 << (pin->pin_no * 2));
		//Set the new configuration
		pin->Gpio->MODER |= (pin->mode << (pin->pin_no * 2));
		if((pin->mode == Output) || (pin->mode == AltFunction))
		{
			if(pin->outType == PushPull)
			{
				pin->Gpio->OTYPER &= ~(1 << pin->pin_no);
			}
			else if(pin->outType == OpenDrain)
			{
				pin->Gpio->OTYPER |=  (1 << pin->pin_no);
			}
			//Clear existing output speed configurations.
			pin->Gpio->OSPEEDR &= ~(0x3 << (pin->pin_no * 2));
			//Set new output speed configurations.
			pin->Gpio->OSPEEDR |= (pin->outSpeed << (pin->pin_no * 2));
		}
		if(pin->mode != Analog)
		{
			//Clear existing Pull configurations.
			pin->Gpio->PUPDR &= ~(0x3 << (pin->pin_no * 2));
			//Set new Pull configurations.
			pin->Gpio->PUPDR |= (pin->pull << (pin->pin_no * 2));
		}
		if(pin->mode == AltFunction)
		{
			if(pin->pin_no <= 7)
			{
				//Clear existing alternate function configuration.
				pin->Gpio->AFR[0] &= ~(0xF << (pin->pin_no * 4));
				//Set new alternate function configuration.
				pin->Gpio->AFR[0] |= (pin->altFunc << (pin->pin_no * 4));
			}
			else
			{
				//Clear existing alternate function configuration.
				pin->Gpio->AFR[1] &= ~(0xF << ((8 - pin->pin_no) * 4));
				//Set new alternate function configuration.
				pin->Gpio->AFR[1] |= (pin->altFunc << ((8 - pin->pin_no) * 4));
			}
		}
		return E_OK;
	}
}
/*
 * @brief Sets (1) or Resets (0) the pin output.
 * @param Gpio  : a pointer to GPIO_TypeDef which contains
 * 		  the required registers for the chosen GPIO port.
 * @param pin   : the pin number.
 * @parm  logic : the required output (0 or 1);
 * @ret   return error status according to the function
 * 		  behavior.
 * 		  E_OK -> everything is OK.
 * 		  E_NOK-> something wrong happened.
 */
Std_ReturnStatus GPIO_Write_Pin(GPIO_TypeDef *Gpio,uint16_t pin, Logic_t logic)
{
	if((NULL == Gpio) || (pin < 0))
	{
		return E_NOK;
	}
	else
	{
		if(logic == GPIO_HIGH)
		{
			Gpio->BSRR |= (1 << pin);
		}
		else
		{
			Gpio->BSRR |= (1 << pin << 16);
		}
		return E_OK;
	}
}
/*
 * @brief Toggles the pin output (0 -> 1), (1 -> 0).
 * @param Gpio : a pointer to GPIO_TypeDef which contains
 * 		  the required registers for the chosen GPIO port.
 * @param pin  : the pin number.
 * @ret   return error status according to the function
 * 		  behavior.
 * 		  E_OK -> everything is OK.
 * 		  E_NOK-> something wrong happened.
 */
Std_ReturnStatus GPIO_Toggle_Pin(GPIO_TypeDef *Gpio,uint16_t pin)
{
	if((NULL == Gpio) || (pin < 0))
	{
		return E_NOK;
	}
	else
	{
		Gpio->ODR ^= (1 << pin);
		return E_OK;
	}
}
/*
 * @brief Read the pin status (Input pin).
 * @param Gpio : a pointer to GPIO_TypeDef which contains
 * 		  the required registers for the chosen GPIO port.
 * @param pin : the pin number.
 * @ret   return pin status:
 * 		  GPIO_HIGH -> 1
 * 		  GPIO_LOW  -> 0
 */
Logic_t GPIO_Read_Pin(GPIO_TypeDef *Gpio,uint16_t pin)
{
	if((Gpio->IDR & (1 << pin)) == (1 << pin))
	{
		return GPIO_HIGH;
	}
	else
	{
		return GPIO_LOW;
	}
}

/*
 * @brief Sets the required pin as an external interrupt source.
 * @param Gpio : a pointer to GPIO_TypeDef which contains
 * 		  the required registers for the chosen GPIO port.
 * @param pin : the pin number.
 * @ret   return error status according to the function
 * 		  behavior.
 * 		  E_OK -> everything is OK.
 * 		  E_NOK-> something wrong happened.
 */
Std_ReturnStatus GPIO_Set_EXTI(GPIO_TypeDef *Gpio,uint16_t pin,edge_detect edge)
{
	if((NULL == Gpio) || (pin < 0))
	{
		return E_NOK;
	}
	else
	{
		Pin_cfg EXTI_pin =
		{
				.Gpio = Gpio,
				.pin_no = pin,
				.pull = PullUp,
				.mode = Input
		};
		//Initialize the pin as input, pull down.
		GPIO_Init(&EXTI_pin);
		SYSCFG_ENABLE();
		if(pin <= 4)
		{
			/*
			 * Enable Interrupt request for the specific line
			 * EXTI0_IRQn                  = 6,      < EXTI Line6 Interrupt>
			 * EXTI1_IRQn                  = 7,      < EXTI Line7 Interrupt>
			 * EXTI2_IRQn                  = 8,      < EXTI Line8 Interrupt>
			 * EXTI3_IRQn                  = 9,      < EXTI Line9 Interrupt>
			 * EXTI4_IRQn                  = 10,     < EXTI Line10 Interrupt>
			 */
			NVIC_EnableIRQ(pin + 6);
		}
		else if(pin >= 5 && pin <= 9)
		{
			NVIC_EnableIRQ(EXTI9_5_IRQn);
		}
		else if(pin >= 10 && pin <= 15)
		{
			NVIC_EnableIRQ(EXTI15_10_IRQn);
		}
		uint32_t GPIO_Index = 0;
		if(Gpio == GPIOA)     {GPIO_Index = 0;}
		else if(Gpio == GPIOB){GPIO_Index = 1;}
		else if(Gpio == GPIOC){GPIO_Index = 2;}
		else if(Gpio == GPIOD){GPIO_Index = 3;}
		else if(Gpio == GPIOE){GPIO_Index = 4;}
		else if(Gpio == GPIOH){GPIO_Index = 7;}
		else{return E_NOK;}
		//select the source input for the external interrupt.
		//Clear previous configurations to prevent conflict.
		SYSCFG->EXTICR[pin >> 2] &= ~(0xF << (4 * (pin & 0x3)));
		//Set new configurations.
		SYSCFG->EXTICR[pin >> 2] |= (GPIO_Index << (4 * (pin & 0x3)));
		//Clear rising and falling edge configurations for the pin.
		EXTI->RTSR &= ~(1 << pin);
		EXTI->FTSR &= ~(1 << pin);
		//Set edge detection according to required.
		if(edge == RISING)
		{
			EXTI->RTSR |= (1 << pin);
		}
		else if(edge == FALLING)
		{
			EXTI->FTSR |= (1 << pin);
		}
		else if(edge == RISING_FALLING)
		{
			EXTI->RTSR |= (1 << pin);
			EXTI->FTSR |= (1 << pin);
		}
		else{return E_NOK;}
		//Un-mask the interrupt line.
		EXTI->IMR  |=  (1 << pin);

		return E_OK;
	}
}
