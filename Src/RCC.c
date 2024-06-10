/*
 * RCC.c
 *
 *  Created on: Jan 30, 2024
 *      Author: sameh
 */

#include "RCC.h"

/*================= Clock speed and source section. =================*/

/*
 * @brief initialization of oscillators configurations.
 * @param OSC : a pointer to OSC_CFG_type which contains
 * 		  the configuration of the required oscillator.
 * @ret   return error status according to the function
 * 		  behavior.
 * 		  E_OK -> everything is OK.
 * 		  E_NOK-> something wrong happened.
 */
Std_ReturnStatus OSC_CFG_init(OSC_CFG_type* OSC)
{
	if(NULL == OSC)
	{
		return E_NOK;
	}
	else
	{
		//HSI selection
		if(OSC->OSC_type == RCC_OSC_HSI)
		{
			if(OSC->HSI_state == HSI_OSC_ON)
			{
				//Enable HSI.
				RCC->CR |= RCC_CR_HSION;
				//Wait for HSI to be ready.
				while((RCC->CR & RCC_CR_HSIRDY) == 0);
				return E_OK;
			}
			else if(OSC->HSI_state == HSI_OSC_OFF)
			{
				//Disable HSI
				RCC->CR &= ~RCC_CR_HSION;
				return E_OK;
			}
			else{return E_NOK;}

		}
		//HSE selection
		else if(OSC->OSC_type == RCC_OSC_HSE)
		{
			if(OSC->HSE_state == HSE_OSC_ON)
			{
				//Enable HSE.
				RCC->CR |= RCC_CR_HSEON;
				//wait for HSE to be ready.
				while((RCC->CR & RCC_CR_HSERDY) == 0);
				return E_OK;
			}
			else if(OSC->HSE_state == HSE_OSC_OFF)
			{
				//Disable HSE.
				RCC->CR &= ~RCC_CR_HSEON;
				return E_OK;
			}
			else{return E_NOK;}
		}
		else{return E_NOK;}

	}
}

/*
 * @brief initialization of System clock configurations.
 * @param CLK : a pointer to CLK_CFG_type which contains
 * 		  the configuration of the System clock.
 * @ret   return error status according to the function
 * 		  behavior.
 * 		  E_OK -> everything is OK.
 * 		  E_NOK-> something wrong happened.
 */
Std_ReturnStatus CLK_CFG_init(CLK_CFG_type* CLK)
{
	if(NULL == CLK)
	{
		return E_NOK;
	}
	else
	{
		if(CLK->SYSCLK_SRC == CLKSRC_HSI)
		{
			//set HSI as system clock source.
			RCC->CFGR &= ~RCC_CFGR_SW;
			RCC->CFGR |=  RCC_CFGR_SW_HSI;
			//wait for HSI to be ready as system clock.
			while((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSI);
		}
		else if(CLK->SYSCLK_SRC == CLKSRC_HSE)
		{
			//set HSE as system clock source.
			RCC->CFGR &= ~RCC_CFGR_SW;
			RCC->CFGR |=  RCC_CFGR_SW_HSE;
			//wait for HSE to be ready as system clock.
			while((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSE);
		}
		else if(CLK->SYSCLK_SRC == CLKSRC_PLL)
		{
			//Flash latency
			FLASH->ACR &= ~FLASH_ACR_LATENCY;
			FLASH->ACR |= 2;
			//set PLL as system clock source.
			RCC->CFGR &= ~RCC_CFGR_SW;
			RCC->CFGR |= RCC_CFGR_SW_PLL;
			//wait for PLL to be ready as system clock.
			while((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);
		}
		else{return E_NOK;}
		//set AHB prescaler HPRE[4:7].
		RCC->CFGR |= CLK->AHB_prescaler;
		//set APB Low speed prescaler (APB1) PPRE1[10:12].
		RCC->CFGR |= CLK->APB1_prescaler;
		//set APB high-speed prescaler (APB2 PREE2[13:15].
		RCC->CFGR |= CLK->APB2_prescaler;

		return E_OK;
	}
}

/*
 * @brief initialization of PLL configurations.
 * @param PLL : a pointer to PLL_CFG_type which contains
 * 		  the configuration of the clock system.
 * @ret   return error status according to the function
 * 		  behavior.
 * 		  E_OK -> everything is OK.
 * 		  E_NOK-> something wrong happened.
 */
Std_ReturnStatus PLL_CFG_init(PLL_CFG_type* PLL)
{
	if(NULL == PLL)
	{
		return E_NOK;
	}
	else
	{
		if(PLL->PLL_state == PLL_OFF)
		{
			//Disable PLLON.
			RCC->CR &= ~ RCC_CR_PLLON;
			//wait until it's disabled.
			while((RCC->CR & RCC_CR_PLLRDY) == 1);
		}
		else if(PLL->PLL_state == PLL_ON)
		{
			//Disable PLLON First.
			RCC->CR &= ~ RCC_CR_PLLON;
			//wait until it's disabled.
			while((RCC->CR & RCC_CR_PLLRDY) == 1);
			//setting the configurations for PLL
			//Setting PLL parameters
			RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLQ;
			RCC->PLLCFGR |= PLL->PLLQ << RCC_PLLCFGR_PLLQ_Pos;
			//PLL Clock source
			if(PLL->PLL_SRC == PLLSRC_HSI)
			{RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLSRC;}
			else if(PLL->PLL_SRC == PLLSRC_HSE)
			{RCC->PLLCFGR |=  RCC_PLLCFGR_PLLSRC;}
			RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLP;
			RCC->PLLCFGR |=  (((PLL->PLLP >> 1U) - 1U) << RCC_PLLCFGR_PLLP_Pos);
			RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLN;
			RCC->PLLCFGR |=  PLL->PLLN << RCC_PLLCFGR_PLLN_Pos;
			RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLM;
			RCC->PLLCFGR |=  PLL->PLLM << RCC_PLLCFGR_PLLM_Pos;
			//Enable PLLON
			RCC->CR |= RCC_CR_PLLON;
			//wait until it's locked.
			while((RCC->CR & RCC_CR_PLLRDY) == 0);
		}
	}
}

/*
 * @brief generate System clock = 84MHz using HSE = 25MHz and PLL.
 * @param void
 * @ret   void
 */
void HSE25Mhz_84MHzOUT(void)
{
	OSC_CFG_type oscillator =
	{
			.OSC_type  		= RCC_OSC_HSE,
			.HSE_state 		= HSE_OSC_ON
	};
	PLL_CFG_type PLL =
	{
			.PLL_state 		= PLL_ON,
			.PLL_SRC   		= PLLSRC_HSE,
			.PLLM 	   		= 25,
			.PLLN      		= 168,
			.PLLP      		= 2,
			.PLLQ      		= 4
	};
	CLK_CFG_type sys_clk =
	{
			.SYSCLK_SRC     = CLKSRC_PLL,
			.AHB_prescaler  = RCC_SYSCLK_DIV1,
			.APB1_prescaler = RCC_APB1_HCLK_DIV2,
			.APB2_prescaler = RCC_APB2_HCLK_DIV1
	};
	OSC_CFG_init(&oscillator);
	PLL_CFG_init(&PLL);
	CLK_CFG_init(&sys_clk);
}
/*
 * @brief generate default clock = 16MHz using HSI.
 * @param void
 * @ret   void
 */
void RESET_DEFAULT_CLCK(void)
{
	//Enable HSI.
	RCC->CR |= RCC_CR_HSION;
	//clear CFGR
	RCC->CFGR = 0;
	//Wait for HSI to be ready.
	while((RCC->CR & RCC_CR_HSIRDY) == 0);
	//Disable PLL.
	RCC->CR &= ~ RCC_CR_PLLON;
    //wait until it's disabled.
    while((RCC->CR & RCC_CR_PLLRDY) == 1);

}

