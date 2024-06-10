/*
 * interrupt.c
 *
 *  Created on: Feb 2, 2024
 *      Author: sameh
 */

#include "interrupt.h"

/*================= Processor exceptions' Handlers =================*/

/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{

}

/*================= Peripherals Interrupt Handlers =================*/

/**
  * @brief  This function handles EXTI0 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI0_IRQHandler(void)
{
	//Clear pending to prevent infinite loop of handler.
	EXTI->PR |= EXTI_PR_PR0;
	//Interrupt handler code.
}

/**
  * @brief  This function handles EXTI1 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI1_IRQHandler(void)
{
	//Clear pending to prevent infinite loop of handler.
	EXTI->PR |= EXTI_PR_PR1;
	//Interrupt handler code.
}

/**
  * @brief  This function handles EXTI2 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI2_IRQHandler(void)
{
	//Clear pending to prevent infinite loop of handler.
	EXTI->PR |= EXTI_PR_PR2;
	//Interrupt handler code.
}

/**
  * @brief  This function handles EXTI3 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI3_IRQHandler(void)
{
	//Clear pending to prevent infinite loop of handler.
	EXTI->PR |= EXTI_PR_PR3;
	//Interrupt handler code.

}

/**
  * @brief  This function handles EXTI4 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI4_IRQHandler(void)
{
	//Clear pending to prevent infinite loop of handler.
	EXTI->PR |= EXTI_PR_PR4;
	//Interrupt handler code.

}

/**
  * @brief  This function handles EXTI5:EXTI9 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI9_5_IRQHandler(void)
{
	//Check if the interrupt is coming from line 5
	if(EXTI->PR & (1 << 5))
	{
		//Clear pending to prevent infinite loop of handler.
		EXTI->PR |= EXTI_PR_PR5;
		//Interrupt handler code.
	}
	//Check if the interrupt is coming from line 6
	if(EXTI->PR & (1 << 6))
	{
		//Clear pending to prevent infinite loop of handler.
		EXTI->PR |= EXTI_PR_PR6;
		//Interrupt handler code.
	}
	//Check if the interrupt is coming from line 7
	if(EXTI->PR & (1 << 7))
	{
		//Clear pending to prevent infinite loop of handler.
		EXTI->PR |= EXTI_PR_PR7;
		//Interrupt handler code.
	}
	//Check if the interrupt is coming from line 8
	if(EXTI->PR & (1 << 8))
	{
		//Clear pending to prevent infinite loop of handler.
		EXTI->PR |= EXTI_PR_PR8;
		//Interrupt handler code.
		if(GPIO_Read_Pin(GPIOB, 9) == 0)
		{
			position1++;
		}
		else if(GPIO_Read_Pin(GPIOB, 9) == 1)
		{
			position1--;
		}
		speed1 = 1000.0/(c_millis - prev_t1);
		prev_t1 = c_millis;

	}
	//Check if the interrupt is coming from line 9
	if(EXTI->PR & (1 << 9))
	{
		//Clear pending to prevent infinite loop of handler.
		EXTI->PR |= EXTI_PR_PR9;
		//Interrupt handler code.
		GPIO_Toggle_Pin(GPIOA, 8);
	}
}

/**
  * @brief  This function handles EXTI10:EXTI15 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI15_10_IRQHandler(void)
{
	//Check if the interrupt is coming from line 10
	if(EXTI->PR & (1 << 10))
	{
		//Clear pending to prevent infinite loop of handler.
		EXTI->PR |= EXTI_PR_PR10;
		//Interrupt handler code.
		if(GPIO_Read_Pin(GPIOB, 0) == 0)
		{
			position3++;
		}
		else if(GPIO_Read_Pin(GPIOB, 0) == 1)
		{
			position3--;
		}
		speed3 = 1000.0/(c_millis - prev_t3);
		prev_t3 = c_millis;
	}
	//Check if the interrupt is coming from line 11
	if(EXTI->PR & (1 << 11))
	{
		//Clear pending to prevent infinite loop of handler.
		EXTI->PR |= EXTI_PR_PR11;
		//Interrupt handler code.
		if(GPIO_Read_Pin(GPIOA, 12) == 0)
				{
					position2++;
				}
				else if(GPIO_Read_Pin(GPIOA, 12) == 1)
				{
					position2--;
				}
		speed2 = 1000.0/(c_millis - prev_t2);
		prev_t2 = c_millis;
	}
	//Check if the interrupt is coming from line 12
	if(EXTI->PR & (1 << 12))
	{
		//Clear pending to prevent infinite loop of handler.
		EXTI->PR |= EXTI_PR_PR12;
		//Interrupt handler code.


	}
	//Check if the interrupt is coming from line 13
	if(EXTI->PR & (1 << 13))
	{
		//Clear pending to prevent infinite loop of handler.
		EXTI->PR |= EXTI_PR_PR13;
		//Interrupt handler code.
		if(GPIO_Read_Pin(GPIOB, 14) == 0)
		{
			position4++;
		}
		else if(GPIO_Read_Pin(GPIOB, 14) == 1)
		{
			position4--;
		}
		speed4 = 1000.0/(c_millis - prev_t4);
		prev_t4 = c_millis;
	}
	//Check if the interrupt is coming from line 14
	if(EXTI->PR & (1 << 14))
	{
		//Clear pending to prevent infinite loop of handler.
		EXTI->PR |= EXTI_PR_PR14;
		//Interrupt handler code.
	}
	//Check if the interrupt is coming from line 15
	if(EXTI->PR & (1 << 15))
	{
		//Clear pending to prevent infinite loop of handler.
		EXTI->PR |= EXTI_PR_PR15;
		//Interrupt handler code.
	}
}
/**
  * @brief  This function handles Timer2 global interrupt request.
  * @param  None
  * @retval None
  */
void TIM2_IRQHandler(void)
{
	if(stepper_f)
	{
		TIM2->SR &= ~TIM_SR_UIF;
		if(steps)
		{
			steps--;
		}
		else
		{
			stepper_f = 0;
			TIM2->CR1 &= ~TIM_CR1_CEN;
		}
	}
//	TIM2->SR &= ~TIM_SR_UIF;
//	GPIO_Toggle_Pin(GPIOA, 11);
}

/**
  * @brief  This function handles Timer3 global interrupt request.
  * @param  None
  * @retval None
  */
void TIM3_IRQHandler(void)
{
	if(stepper_f)
	{
		TIM3->SR &= ~TIM_SR_UIF;
		if(steps)
		{
			steps--;
		}
		else
		{
			stepper_f = 0;
			TIM3->CR1 &= ~TIM_CR1_CEN;
		}
	}
//	TIM3->SR &= ~TIM_SR_UIF;
//	GPIO_Toggle_Pin(GPIOA, 11);
}

/**
  * @brief  This function handles Timer4 global interrupt request.
  * @param  None
  * @retval None
  */
void TIM4_IRQHandler(void)
{
	TIM4->SR &= ~TIM_SR_UIF;
	c_millis++;
}

void TIM1_CC_IRQHandler(void)
{

}
/**
  * @brief  This function handles Timer9 global interrupt request and Timer 1 break interrupt.
  * @param  None
  * @retval None
  */
void TIM1_BRK_TIM9_IRQHandler(void)
{
	TIM9->SR &= ~TIM_SR_UIF;
	if(delay_flag)
	{
		delay_flag = 0;
		//Disable TIMER (CEN = 0)
		TIM9->CR1 &= ~TIM_CR1_CEN;
	}
}

void USART1_IRQHandler(void)
{
	if(USART1->SR & USART_SR_RXNE)
	{
		data_read = USART1->DR;
	}
	if(USART1->SR & USART_SR_TXE)
	{

	}
}
void USART2_IRQHandler(void)
{
	if(USART2->SR & USART_SR_RXNE)
	{
		data_read = USART1->DR;
	}
	if(USART2->SR & USART_SR_TXE)
	{

	}
}
void USART6_IRQHandler(void)
{
	if(USART6->SR & USART_SR_RXNE)
	{
		data_read = USART1->DR;
	}
	if(USART6->SR & USART_SR_TXE)
	{

	}
}
