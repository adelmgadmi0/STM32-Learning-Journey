
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
void HAL_UART_MspInit(UART_HandleTypeDef *huart){
	GPIO_InitTypeDef gpio_uart;
	//here is the low level init of the usart2 peripheral

	//1. enable the clock
	__HAL_RCC_USART1_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();

	//2. do the pin muxing config
	gpio_uart.Pin = GPIO_PIN_9;
	gpio_uart.Mode = GPIO_MODE_AF_PP;
	gpio_uart.Pull = GPIO_PULLUP;
	gpio_uart.Speed = GPIO_SPEED_FREQ_LOW;
	gpio_uart.Alternate = GPIO_AF7_USART1; //UART1_TX
	HAL_GPIO_Init(GPIOA, &gpio_uart);

	gpio_uart.Pin = GPIO_PIN_10;///UART1_RX
	HAL_GPIO_Init(GPIOA, &gpio_uart);

	//3. enable the irq and set the priority (NVIC settings)
	HAL_NVIC_EnableIRQ(USART1_IRQn);
	HAL_NVIC_SetPriority(USART1_IRQn, 15, 0);

}
