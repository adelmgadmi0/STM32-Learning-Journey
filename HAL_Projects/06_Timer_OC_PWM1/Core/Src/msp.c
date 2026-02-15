#include"stm32f4xx_hal.h"
#include "main.h"
void HAL_MspInit(void)
{
//Here is the low level processor specific intis
	//1. Set the priority grouping of the arm cortex mx processor.
	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

	//2. Enable the required system exceptions of the arm cortex mx processor.
	SCB->SHCSR |= 0x7 << 16;

	//3. Configure the priority of the system exceptions.
	HAL_NVIC_SetPriority(MemoryManagement_IRQn, 0, 0);
	HAL_NVIC_SetPriority(BusFault_IRQn, 0, 0);
	HAL_NVIC_SetPriority(UsageFault_IRQn, 0, 0);



}

void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
	GPIO_InitTypeDef gpio_uart;
	//here we are going to do the low level inits. of the USART2 peripheral

	//1. enable the clock for the USART2 peripheral as well as for GPIOA peripheral
	__HAL_RCC_USART2_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();

	//2 . Do the pin muxing configurations
	gpio_uart.Pin = GPIO_PIN_2;
	gpio_uart.Mode =GPIO_MODE_AF_PP;
	gpio_uart.Pull = GPIO_PULLUP;
	gpio_uart.Speed = GPIO_SPEED_FREQ_LOW;
	gpio_uart.Alternate =  GPIO_AF7_USART2; //UART2_TX
	HAL_GPIO_Init(GPIOA,&gpio_uart);

	gpio_uart.Pin = GPIO_PIN_3; //UART2_RX
	HAL_GPIO_Init(GPIOA,&gpio_uart);
	//3 . Enable the IRQ and set up the priority (NVIC settings )
	HAL_NVIC_EnableIRQ(USART2_IRQn);
	HAL_NVIC_SetPriority(USART2_IRQn,15,0);
}

void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
	GPIO_InitTypeDef Tim2OC_CH_GPIOs;

	//1. Enable the clock :
	__HAL_RCC_TIM2_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	//2. config the gpios as tim2 channels :
	/*
	 TIM2_CH1 -----> PA0
	 TIM2_CH2 -----> PA1
	 TIM2_CH3 -----> PB10
	 TIM2_CH4 -----> PB2
	 */
	Tim2OC_CH_GPIOs.Pin = GPIO_PIN_5|GPIO_PIN_1 ;
	Tim2OC_CH_GPIOs.Mode = GPIO_MODE_AF_PP;
	Tim2OC_CH_GPIOs.Pull = GPIO_NOPULL;
	Tim2OC_CH_GPIOs.Speed = GPIO_SPEED_FREQ_HIGH;
	Tim2OC_CH_GPIOs.Alternate = GPIO_AF1_TIM2;
	HAL_GPIO_Init(GPIOA, &Tim2OC_CH_GPIOs);

	Tim2OC_CH_GPIOs.Pin = GPIO_PIN_10|GPIO_PIN_2;
	Tim2OC_CH_GPIOs.Mode = GPIO_MODE_AF_PP;
	Tim2OC_CH_GPIOs.Pull = GPIO_NOPULL;
	Tim2OC_CH_GPIOs.Speed = GPIO_SPEED_FREQ_HIGH;
	Tim2OC_CH_GPIOs.Alternate = GPIO_AF1_TIM2;
	HAL_GPIO_Init(GPIOB, &Tim2OC_CH_GPIOs);

	//3. nvic settings
	HAL_NVIC_EnableIRQ(TIM2_IRQn);
	HAL_NVIC_SetPriority(TIM2_IRQn,15,0);
}
