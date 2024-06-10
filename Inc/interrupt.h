/*
 * interrupt.h
 *
 *  Created on: Feb 2, 2024
 *      Author: sameh
 */

#ifndef INTERRUPT_H_
#define INTERRUPT_H_

/*================= includes =================*/
#include "main.h"
extern uint32_t steps;
extern uint32_t stepper_f;
extern uint32_t delay_flag;

/*================= Processor exceptions' Handlers =================*/
void NMI_Handler(void);
void HardFault_Handler(void);
void MemManage_Handler(void);
void BusFault_Handler(void);
void UsageFault_Handler(void);
void SVC_Handler(void);
void DebugMon_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);

/*================= Peripherals Interrupt Handlers =================*/
void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);
void EXTI2_IRQHandler(void);
void EXTI3_IRQHandler(void);
void EXTI4_IRQHandler(void);
void EXTI9_5_IRQHandler(void);
void EXTI15_10_IRQHandler(void);
void TIM1_CC_IRQHandler(void);
void TIM2_IRQHandler(void);
void TIM3_IRQHandler(void);
void TIM4_IRQHandler(void);
void TIM1_BRK_TIM9_IRQHandler(void);
void USART1_IRQHandler(void);
void USART2_IRQHandler(void);
void USART6_IRQHandler(void);
#endif /* INTERRUPT_H_ */
