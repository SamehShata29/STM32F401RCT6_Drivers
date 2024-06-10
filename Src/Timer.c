/*
 * Timer.c
 *
 *  Created on: Feb 5, 2024
 *      Author: sameh
 */


#include "Timer.h"

uint32_t delay_flag = 0;


/*
 * @brief Generate the required PWM according to the inputs.
 * @param TIMER     : a pointer to TIM_TypeDef which contains
 * 		  the registers the required timer.
 * @param cfg       : a pointer to PWM_config which contains
 * 		  the configurations of the required output signal.
 * @param timer_clk : the running timer frequency.
 * @ret   return error status according to the function
 * 		  behavior.
 * 		  E_OK -> everything is OK.
 * 		  E_NOK-> something wrong happened.
 */
Std_ReturnStatus PWM_GEN(TIM_TypeDef *TIMER,PWM_config* PWM_cfg ,uint32_t timer_clk)
{
	if((NULL == TIMER) || (NULL == PWM_cfg))
	{
		return E_NOK;
	}
	else
	{
		//Disable TIMER (CEN = 0)
		TIMER->CR1 &= ~(1 << 0);
		/*
		 ***************************************************************************
		 *   Calculate the prescaler and auto reload value depending on user input *
		 *					    Fpwm = (Fclk)/((ARR+1)*(PSC+1))  				   *
		 *                   so (ARR+1) = (Fclk)/((Fpwm)*(PSC+1))				   *
		 *   we will iterate over this equation to get the values of ARR and PSC   *
		 ***************************************************************************
		 */
		uint32_t temp_ARR = 0;
		uint32_t temp_PSC = 1;
		while(1)
		{
			temp_ARR = timer_clk/(PWM_cfg->freq * temp_PSC);
			if(temp_ARR >= 35000)
			{
				temp_PSC += 2;
			}
			else
			{
				break;
			}
		}
		//Configurations of timer depending on which one is chosen.
		if(TIMER == TIM1)
		{
			//Enable Timer1 RCC clock and GPIOA clock
			TIM1_ENABLE();
			GPIOA_ENABLE();
			//configure the timer according to the chosen channel.
			if(PWM_cfg->ch == CH1)
			{
				//Configure the channel pin and initialize it.
				Pin_cfg TIM1_CH1 ={.Gpio = GPIOA, .mode = AltFunction, .altFunc = AF1,
								   .pin_no = 8, .outSpeed = HighSpeed};
				GPIO_Init(&TIM1_CH1);
				/*******************************************
				 *                                         *
				 * Start of timer registers configurations *
				 *                                         *
				 *******************************************
				 */
				//Choose PWM mode 1.
				TIMER->CCMR1 |= (0b110 << 4);
				//Output compare preload enable.
				TIMER->CCMR1 |= (1 << 3);
				//Capture/Compare 1 output enable.
				TIMER->CCER  |= (1 << 0);
				//active high is the default in (Bit CC1P: Capture/Compare 1 output polarity).
				//Main output enable
				TIMER->BDTR  |= (1 << 15);
				//Edge align mode is the default in TIMx_CR1 register [CMS].
				//Update interrupt enable [UIE].
				TIMER->DIER  |= (1 << 0);
				//Capture/Compare 1 interrupt enable [CC1E]
				TIMER->DIER  |= (1 << 1);
				//Put the capture value [CCR1].
				TIMER->CCR1   = temp_ARR * PWM_cfg->duty_cycle / 1000;
			}
			else if(PWM_cfg->ch == CH2)
			{
				//Configure the channel pin and initialize it.
				Pin_cfg TIM1_CH2 ={.Gpio = GPIOA, .mode = AltFunction, .altFunc = AF1,
								   .pin_no = 9, .outSpeed = HighSpeed};
				GPIO_Init(&TIM1_CH2);
				/*******************************************
				 *                                         *
				 * Start of timer registers configurations *
				 *                                         *
				 *******************************************
				 */
				//Choose PWM mode 1.
				TIMER->CCMR1 |= (0b110 << 12);
				//Output compare preload enable.
				TIMER->CCMR1 |= (1 << 11);
				//Capture/Compare 2 output enable.
				TIMER->CCER  |= (1 << 4);
				//active high is the default in (Bit CC2P: Capture/Compare 1 output polarity).
				//Main output enable
				TIMER->BDTR  |= (1 << 15);
				//Edge align mode is the default in TIMx_CR1 register [CMS].
				//Update interrupt enable [UIE].
				TIMER->DIER  |= (1 << 0);
				//Capture/Compare 2 interrupt enable [CC2E]
				TIMER->DIER  |= (1 << 2);
				//Put the capture value [CCR2].
				TIMER->CCR2   = temp_ARR * PWM_cfg->duty_cycle / 1000;
			}
			else if(PWM_cfg->ch == CH3)
			{
				//Configure the channel pin and initialize it.
				Pin_cfg TIM1_CH3 ={.Gpio = GPIOA, .mode = AltFunction, .altFunc = AF1,
								   .pin_no = 10, .outSpeed = HighSpeed};
				GPIO_Init(&TIM1_CH3);
				/*******************************************
				 *                                         *
				 * Start of timer registers configurations *
				 *                                         *
				 *******************************************
				 */
				//Choose PWM mode 1.
				TIMER->CCMR2 |= (0b110 << 4);
				//Output compare preload enable.
				TIMER->CCMR2 |= (1 << 3);
				//Capture/Compare 3 output enable.
				TIMER->CCER  |= (1 << 8);
				//active high is the default in (Bit CC3P: Capture/Compare 1 output polarity).
				//Main output enable
				TIMER->BDTR  |= (1 << 15);
				//Edge align mode is the default in TIMx_CR1 register [CMS].
				//Update interrupt enable [UIE].
				TIMER->DIER  |= (1 << 0);
				//Capture/Compare 1 interrupt enable [CC3E]
				TIMER->DIER  |= (1 << 3);
				//Put the capture value [CCR3].
				TIMER->CCR3   = temp_ARR * PWM_cfg->duty_cycle / 1000;
			}
			else if(PWM_cfg->ch == CH4)
			{
				//Configure the channel pin and initialize it.
				Pin_cfg TIM1_CH4 ={.Gpio = GPIOA, .mode = AltFunction, .altFunc = AF1,
								   .pin_no = 11, .outSpeed = HighSpeed};
				GPIO_Init(&TIM1_CH4);
				/*******************************************
				 *                                         *
				 * Start of timer registers configurations *
				 *                                         *
				 *******************************************
				 */
				//Choose PWM mode 1.
				TIMER->CCMR2 |= (0b110 << 12);
				//Output compare preload enable.
				TIMER->CCMR2 |= (1 << 11);
				//Capture/Compare 4 output enable.
				TIMER->CCER  |= (1 << 12);
				//active high is the default in (Bit 1 CC4P: Capture/Compare 1 output polarity).
				//Main output enable
				TIMER->BDTR  |= (1 << 15);
				//Edge align mode is the default in TIMx_CR1 register [CMS].
				//Update interrupt enable [UIE].
				TIMER->DIER  |= (1 << 0);
				//Capture/Compare 2 interrupt enable [CC4E]
				TIMER->DIER  |= (1 << 4);
				//Put the capture value [CCR4].
				TIMER->CCR4   = temp_ARR * PWM_cfg->duty_cycle / 1000;
			}
			else{return E_NOK;}
		}
		else if(TIMER == TIM2)
		{
			//Enable Timer1 RCC clock and GPIOA clock
			TIM2_ENABLE();
			GPIOA_ENABLE();
			//configure the timer according to the chosen channel.
			if(PWM_cfg->ch == CH1)
			{
				//Configure the channel pin and initialize it.
				Pin_cfg TIM2_CH1 ={.Gpio = GPIOA, .mode = AltFunction, .altFunc = AF1,
								   .pin_no = 0, .outSpeed = HighSpeed};
				GPIO_Init(&TIM2_CH1);
				/*******************************************
				 *                                         *
				 * Start of timer registers configurations *
				 *                                         *
				 *******************************************
				 */
				//Choose PWM mode 1.
				TIMER->CCMR1 |= (0b110 << 4);
				//Output compare preload enable.
				TIMER->CCMR1 |= (1 << 3);
				//Capture/Compare 1 output enable.
				TIMER->CCER  |= (1 << 0);
				//active high is the default in (Bit CC1P: Capture/Compare 1 output polarity).
				//Edge align mode is the default in TIMx_CR1 register [CMS].
				//Update interrupt enable [UIE].
				TIMER->DIER  |= (1 << 0);
				//Capture/Compare 1 interrupt enable [CC1E]
				TIMER->DIER  |= (1 << 1);
				//Put the capture value [CCR1].
				TIMER->CCR1   = temp_ARR * PWM_cfg->duty_cycle / 1000;
			}
			else if(PWM_cfg->ch == CH2)
			{
				//Configure the channel pin and initialize it.
				Pin_cfg TIM2_CH2 ={.Gpio = GPIOA, .mode = AltFunction, .altFunc = AF1,
								   .pin_no = 1, .outSpeed = HighSpeed};
				GPIO_Init(&TIM2_CH2);
				/*******************************************
				 *                                         *
				 * Start of timer registers configurations *
				 *                                         *
				 *******************************************
				 */
				//Choose PWM mode 1.
				TIMER->CCMR1 |= (0b110 << 12);
				//Output compare preload enable.
				TIMER->CCMR1 |= (1 << 11);
				//Capture/Compare 2 output enable.
				TIMER->CCER  |= (1 << 4);
				//active high is the default in (Bit CC2P: Capture/Compare 1 output polarity).
				//Edge align mode is the default in TIMx_CR1 register [CMS].
				//Update interrupt enable [UIE].
				TIMER->DIER  |= (1 << 0);
				//Capture/Compare 2 interrupt enable [CC2E]
				TIMER->DIER  |= (1 << 2);
				//Put the capture value [CCR2].
				TIMER->CCR2   = temp_ARR * PWM_cfg->duty_cycle / 1000;
			}
			else if(PWM_cfg->ch == CH3)
			{
				//Configure the channel pin and initialize it.
				Pin_cfg TIM2_CH3 ={.Gpio = GPIOA, .mode = AltFunction, .altFunc = AF1,
								   .pin_no = 2, .outSpeed = HighSpeed};
				GPIO_Init(&TIM2_CH3);
				/*******************************************
				 *                                         *
				 * Start of timer registers configurations *
				 *                                         *
				 *******************************************
				 */
				//Choose PWM mode 1.
				TIMER->CCMR2 |= (0b110 << 4);
				//Output compare preload enable.
				TIMER->CCMR2 |= (1 << 3);
				//Capture/Compare 3 output enable.
				TIMER->CCER  |= (1 << 8);
				//active high is the default in (Bit CC3P: Capture/Compare 1 output polarity).
				//Edge align mode is the default in TIMx_CR1 register [CMS].
				//Update interrupt enable [UIE].
				TIMER->DIER  |= (1 << 0);
				//Capture/Compare 1 interrupt enable [CC3E]
				TIMER->DIER  |= (1 << 3);
				//Put the capture value [CCR3].
				TIMER->CCR3   = temp_ARR * PWM_cfg->duty_cycle / 1000;
			}
			else if(PWM_cfg->ch == CH4)
			{
				//Configure the channel pin and initialize it.
				Pin_cfg TIM2_CH4 ={.Gpio = GPIOA, .mode = AltFunction, .altFunc = AF1,
								   .pin_no = 3, .outSpeed = HighSpeed};
				GPIO_Init(&TIM2_CH4);
				/*******************************************
				 *                                         *
				 * Start of timer registers configurations *
				 *                                         *
				 *******************************************
				 */
				//Choose PWM mode 1.
				TIMER->CCMR2 |= (0b110 << 12);
				//Output compare preload enable.
				TIMER->CCMR2 |= (1 << 11);
				//Capture/Compare 4 output enable.
				TIMER->CCER  |= (1 << 12);
				//active high is the default in (Bit 1 CC4P: Capture/Compare 1 output polarity).
				//Edge align mode is the default in TIMx_CR1 register [CMS].
				//Update interrupt enable [UIE].
				TIMER->DIER  |= (1 << 0);
				//Capture/Compare 2 interrupt enable [CC4E]
				TIMER->DIER  |= (1 << 4);
				//Put the capture value [CCR4].
				TIMER->CCR4   = temp_ARR * PWM_cfg->duty_cycle / 1000;
			}
			else{return E_NOK;}
		}
		else if(TIMER == TIM3)
		{
			//Enable Timer1 RCC clock and GPIOA clock
			TIM3_ENABLE();
			GPIOB_ENABLE();
			//configure the timer according to the chosen channel.
			if(PWM_cfg->ch == CH1)
			{
				//Configure the channel pin and initialize it.
				Pin_cfg TIM3_CH1 ={.Gpio = GPIOB, .mode = AltFunction, .altFunc = AF2,
								   .pin_no = 4, .outSpeed = HighSpeed};
				GPIO_Init(&TIM3_CH1);
				/*******************************************
				 *                                         *
				 * Start of timer registers configurations *
				 *                                         *
				 *******************************************
				 */
				//Choose PWM mode 1.
				TIMER->CCMR1 |= (0b110 << 4);
				//Output compare preload enable.
				TIMER->CCMR1 |= (1 << 3);
				//Capture/Compare 1 output enable.
				TIMER->CCER  |= (1 << 0);
				//active high is the default in (Bit CC1P: Capture/Compare 1 output polarity).
				//Edge align mode is the default in TIMx_CR1 register [CMS].
				//Update interrupt enable [UIE].
				TIMER->DIER  |= (1 << 0);
				//Capture/Compare 1 interrupt enable [CC1E]
				TIMER->DIER  |= (1 << 1);
				//Put the capture value [CCR1].
				TIMER->CCR1   = temp_ARR * PWM_cfg->duty_cycle / 1000;
			}
			else if(PWM_cfg->ch == CH2)
			{
				//Configure the channel pin and initialize it.
				Pin_cfg TIM3_CH2 ={.Gpio = GPIOB, .mode = AltFunction, .altFunc = AF2,
								   .pin_no = 5, .outSpeed = HighSpeed};
				GPIO_Init(&TIM3_CH2);
				/*******************************************
				 *                                         *
				 * Start of timer registers configurations *
				 *                                         *
				 *******************************************
				 */
				//Choose PWM mode 1.
				TIMER->CCMR1 |= (0b110 << 12);
				//Output compare preload enable.
				TIMER->CCMR1 |= (1 << 11);
				//Capture/Compare 2 output enable.
				TIMER->CCER  |= (1 << 4);
				//active high is the default in (Bit CC2P: Capture/Compare 1 output polarity).
				//Edge align mode is the default in TIMx_CR1 register [CMS].
				//Update interrupt enable [UIE].
				TIMER->DIER  |= (1 << 0);
				//Capture/Compare 2 interrupt enable [CC2E]
				TIMER->DIER  |= (1 << 2);
				//Put the capture value [CCR2].
				TIMER->CCR2   = temp_ARR * PWM_cfg->duty_cycle / 1000;
			}
			else if(PWM_cfg->ch == CH3)
			{
				//Configure the channel pin and initialize it.
				Pin_cfg TIM3_CH3 ={.Gpio = GPIOB, .mode = AltFunction, .altFunc = AF2,
								   .pin_no = 0, .outSpeed = HighSpeed};
				GPIO_Init(&TIM3_CH3);
				/*******************************************
				 *                                         *
				 * Start of timer registers configurations *
				 *                                         *
				 *******************************************
				 */
				//Choose PWM mode 1.
				TIMER->CCMR2 |= (0b110 << 4);
				//Output compare preload enable.
				TIMER->CCMR2 |= (1 << 3);
				//Capture/Compare 3 output enable.
				TIMER->CCER  |= (1 << 8);
				//active high is the default in (Bit CC3P: Capture/Compare 1 output polarity).
				//Edge align mode is the default in TIMx_CR1 register [CMS].
				//Update interrupt enable [UIE].
				TIMER->DIER  |= (1 << 0);
				//Capture/Compare 1 interrupt enable [CC3E]
				TIMER->DIER  |= (1 << 3);
				//Put the capture value [CCR3].
				TIMER->CCR3   = temp_ARR * PWM_cfg->duty_cycle / 1000;
			}
			else if(PWM_cfg->ch == CH4)
			{
				//Configure the channel pin and initialize it.
				Pin_cfg TIM3_CH4 ={.Gpio = GPIOB, .mode = AltFunction, .altFunc = AF2,
								   .pin_no = 1, .outSpeed = HighSpeed};
				GPIO_Init(&TIM3_CH4);
				/*******************************************
				 *                                         *
				 * Start of timer registers configurations *
				 *                                         *
				 *******************************************
				 */
				//Choose PWM mode 1.
				TIMER->CCMR2 |= (0b110 << 12);
				//Output compare preload enable.
				TIMER->CCMR2 |= (1 << 11);
				//Capture/Compare 4 output enable.
				TIMER->CCER  |= (1 << 12);
				//active high is the default in (Bit 1 CC4P: Capture/Compare 1 output polarity).
				//Edge align mode is the default in TIMx_CR1 register [CMS].
				//Update interrupt enable [UIE].
				TIMER->DIER  |= (1 << 0);
				//Capture/Compare 2 interrupt enable [CC4E]
				TIMER->DIER  |= (1 << 4);
				//Put the capture value [CCR4].
				TIMER->CCR4   = temp_ARR * PWM_cfg->duty_cycle / 1000;
			}
			else{return E_NOK;}
		}
		else if(TIMER == TIM4)
		{
			//Enable Timer1 RCC clock and GPIOA clock
			TIM4_ENABLE();
			GPIOB_ENABLE();
			//configure the timer according to the chosen channel.
			if(PWM_cfg->ch == CH1)
			{
				//Configure the channel pin and initialize it.
				Pin_cfg TIM4_CH1 ={.Gpio = GPIOB, .mode = AltFunction, .altFunc = AF2,
								   .pin_no = 6, .outSpeed = HighSpeed};
				GPIO_Init(&TIM4_CH1);
				/*******************************************
				 *                                         *
				 * Start of timer registers configurations *
				 *                                         *
				 *******************************************
				 */
				//Choose PWM mode 1.
				TIMER->CCMR1 |= (0b110 << 4);
				//Output compare preload enable.
				TIMER->CCMR1 |= (1 << 3);
				//Capture/Compare 1 output enable.
				TIMER->CCER  |= (1 << 0);
				//active high is the default in (Bit CC1P: Capture/Compare 1 output polarity).
				//Edge align mode is the default in TIMx_CR1 register [CMS].
				//Update interrupt enable [UIE].
				TIMER->DIER  |= (1 << 0);
				//Capture/Compare 1 interrupt enable [CC1E]
				TIMER->DIER  |= (1 << 1);
				//Put the capture value [CCR1].
				TIMER->CCR1   = temp_ARR * PWM_cfg->duty_cycle / 1000;
			}
			else if(PWM_cfg->ch == CH2)
			{
				//Configure the channel pin and initialize it.
				Pin_cfg TIM4_CH2 ={.Gpio = GPIOB, .mode = AltFunction, .altFunc = AF2,
								   .pin_no = 7, .outSpeed = HighSpeed};
				GPIO_Init(&TIM4_CH2);
				/*******************************************
				 *                                         *
				 * Start of timer registers configurations *
				 *                                         *
				 *******************************************
				 */
				//Choose PWM mode 1.
				TIMER->CCMR1 |= (0b110 << 12);
				//Output compare preload enable.
				TIMER->CCMR1 |= (1 << 11);
				//Capture/Compare 2 output enable.
				TIMER->CCER  |= (1 << 4);
				//active high is the default in (Bit CC2P: Capture/Compare 1 output polarity).
				//Edge align mode is the default in TIMx_CR1 register [CMS].
				//Update interrupt enable [UIE].
				TIMER->DIER  |= (1 << 0);
				//Capture/Compare 2 interrupt enable [CC2E]
				TIMER->DIER  |= (1 << 2);
				//Put the capture value [CCR2].
				TIMER->CCR2   = temp_ARR * PWM_cfg->duty_cycle / 1000;
			}
			else if(PWM_cfg->ch == CH3)
			{
				//Configure the channel pin and initialize it.
				Pin_cfg TIM4_CH3 ={.Gpio = GPIOB, .mode = AltFunction, .altFunc = AF2,
								   .pin_no = 8, .outSpeed = HighSpeed};
				GPIO_Init(&TIM4_CH3);
				/*******************************************
				 *                                         *
				 * Start of timer registers configurations *
				 *                                         *
				 *******************************************
				 */
				//Choose PWM mode 1.
				TIMER->CCMR2 |= (0b110 << 4);
				//Output compare preload enable.
				TIMER->CCMR2 |= (1 << 3);
				//Capture/Compare 3 output enable.
				TIMER->CCER  |= (1 << 8);
				//active high is the default in (Bit CC3P: Capture/Compare 1 output polarity).
				//Edge align mode is the default in TIMx_CR1 register [CMS].
				//Update interrupt enable [UIE].
				TIMER->DIER  |= (1 << 0);
				//Capture/Compare 1 interrupt enable [CC3E]
				TIMER->DIER  |= (1 << 3);
				//Put the capture value [CCR3].
				TIMER->CCR3   = temp_ARR * PWM_cfg->duty_cycle / 1000;
			}
			else if(PWM_cfg->ch == CH4)
			{
				//Configure the channel pin and initialize it.
				Pin_cfg TIM4_CH4 ={.Gpio = GPIOB, .mode = AltFunction, .altFunc = AF2,
								   .pin_no = 9, .outSpeed = HighSpeed};
				GPIO_Init(&TIM4_CH4);
				/*******************************************
				 *                                         *
				 * Start of timer registers configurations *
				 *                                         *
				 *******************************************
				 */
				//Choose PWM mode 1.
				TIMER->CCMR2 |= (0b110 << 12);
				//Output compare preload enable.
				TIMER->CCMR2 |= (1 << 11);
				//Capture/Compare 4 output enable.
				TIMER->CCER  |= (1 << 12);
				//active high is the default in (Bit 1 CC4P: Capture/Compare 1 output polarity).
				//Edge align mode is the default in TIMx_CR1 register [CMS].
				//Update interrupt enable [UIE].
				TIMER->DIER  |= (1 << 0);
				//Capture/Compare 2 interrupt enable [CC4E]
				TIMER->DIER  |= (1 << 4);
				//Put the capture value [CCR4].
				TIMER->CCR4   = temp_ARR * PWM_cfg->duty_cycle / 1000;
			}
			else{return E_NOK;}
		}

		//Enable Auto reload pre-load.
		TIMER->CR1 |= (1 << 7);
		//ARR value.
		TIMER->ARR  = temp_ARR - 1;
		//PSC value.
		TIMER->PSC  = temp_PSC - 1;
		//Update generation
		TIMER->EGR |= TIM_EGR_UG;
		//Enable the timer (CEN = 0).
		TIMER->CR1 |= (1 << 0);

		return E_OK;
	}
}

/*
 * @brief Generate interrupt after the required time.
 * @param TIMER     : a pointer to TIM_TypeDef which contains
 * 		  the registers the required timer.
 * @param t_ms      : time in milli-seconds.
 * @param timer_clk : the running timer frequency.
 * @ret   return error status according to the function
 * 		  behavior.
 * 		  E_OK -> everything is OK.
 * 		  E_NOK-> something wrong happened.
 */
Std_ReturnStatus INT_GEN_ms(TIM_TypeDef *TIMER,uint32_t t_ms ,uint32_t timer_clk)
{
	if(NULL == TIMER)
	{
		return E_NOK;
	}
	else
	{
		//Enable timer clock and interrupt
		if(TIMER == TIM1){TIM1_ENABLE();}
		else if(TIMER == TIM2){TIM2_ENABLE();}
		else if(TIMER == TIM3){TIM3_ENABLE();}
		else if(TIMER == TIM4){TIM4_ENABLE();}
		else if(TIMER == TIM9){TIM9_ENABLE();}
		//Disable TIMER (CEN = 0)
		TIMER->CR1 &= ~TIM_CR1_CEN;
		/*
		 ***************************************************************************
		 *   Calculate the prescaler and auto reload value depending on user input *
		 *					    Tout = ((ARR+1)*(PSC+1))/(Fclk) 				   *
		 *                   so (ARR+1) = Tout*Fclk / (PSC+1)				   	   *
		 *   we will iterate over this equation to get the values of ARR and PSC   *
		 ***************************************************************************
		 */
		uint32_t temp_ARR = 0;
		uint32_t temp_PSC = 1;
		while(1)
		{
			temp_ARR = ((timer_clk)/(temp_PSC*1000)) * t_ms;
			if(temp_ARR >= 35000)
			{
				temp_PSC += 2;
			}
			else
			{
				break;
			}
		}
		//Timer configuration to generate the interrupt after t_ms.
		//Enable Auto reload pre-load.
		TIMER->CR1 |= TIM_CR1_ARPE;
		//Select up counting.
		TIMER->CR1 &= ~TIM_CR1_DIR;
		//prescaler value
		TIMER->PSC = temp_PSC-1;
		//auto reload value
		TIMER->ARR = temp_ARR-1;
		//Generate an update event to synchronize
		TIMER->EGR |= TIM_EGR_UG;
		//enable update interrupt
		TIMER->DIER |= TIM_DIER_UIE;
		//Enable Timer counter
		TIMER->CR1 |= TIM_CR1_CEN;
		//Enable interrupt
		if(TIMER == TIM1){NVIC_EnableIRQ(TIM1_CC_IRQn);}
		else if(TIMER == TIM2){NVIC_EnableIRQ(TIM2_IRQn);}
		else if(TIMER == TIM3){NVIC_EnableIRQ(TIM3_IRQn);}
		else if(TIMER == TIM4){NVIC_EnableIRQ(TIM4_IRQn);}
		else if(TIMER == TIM9){NVIC_EnableIRQ(TIM1_BRK_TIM9_IRQn);}

		return E_OK;
	}
}

/*
 * @brief Generate time delay in milli-seconds using Timer9.
 * @param t_ms      : time in milli-seconds.
 * @param timer_clk : the running timer frequency.
 * @ret   void
 */
void tdelay_ms(uint32_t t_ms ,uint32_t timer_clk)
{
	INT_GEN_ms(TIM9, t_ms, timer_clk);
	delay_flag = 1;
	while(delay_flag)
	{
		/*Nothing, just wait the delay time*/
	}
}

/*
 * @brief configure the timer to operate on external clock mode.
 * @param TIMER   : a pointer to TIM_TypeDef which contains.
 * 		  the registers the required timer.
 * @param ARR_val : value of auto reload value.
 * @ret   void
 */
void timer_ext_clk(TIM_TypeDef *TIMER, uint32_t ARR_val)
{

}

void encoder_mode(void)
{
	//Disable TIMER (CEN = 0)
	TIM4->CR1 &= ~(1 << 0);
	//Enable Timer1 RCC clock and GPIOA clock
	TIM4_ENABLE();
	GPIOB_ENABLE();
	//Configure the channel pin and initialize it.
	Pin_cfg TIM4_CH1 ={.Gpio = GPIOB, .mode = AltFunction, .altFunc = AF2,
			.pin_no = 6, .outSpeed = HighSpeed};
	GPIO_Init(&TIM4_CH1);
	//Configure the channel pin and initialize it.
	Pin_cfg TIM4_CH2 ={.Gpio = GPIOB, .mode = AltFunction, .altFunc = AF2,
			.pin_no = 7, .outSpeed = HighSpeed};
	GPIO_Init(&TIM4_CH2);

	//Encoder mode 3
	TIM4->SMCR |= TIM_SMCR_SMS_0;
	TIM4->SMCR |= TIM_SMCR_SMS_1;
	//Input selection
	TIM4->CCMR1 |= TIM_CCMR1_CC1S_0;
	TIM4->CCMR1 |= TIM_CCMR1_CC2S_0;
	//Update interrupt enable [UIE].
	TIM4->DIER  |= (1 << 0);
	//Enable Auto reload pre-load.
	TIM4->CR1 |= (1 << 7);
	//ARR value.
	TIM4->ARR  = 0xffff;
	//Enable the timer (CEN = 0).
	TIM4->CR1 |= (1 << 0);

	NVIC_EnableIRQ(TIM4_IRQn);
}
