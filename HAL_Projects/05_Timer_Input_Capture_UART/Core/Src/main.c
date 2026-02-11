#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_uart.h"
#include "main.h"
#include <string.h>
#include <stdio.h>

void SystemClockConfig(uint8_t clock_freq);
void Error_handler(void);
void UART2_Init(void);
void GPIO_Init(void);
void TIMER2_Init(void);
void LSE_Config(void);
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim);

UART_HandleTypeDef huart2;
TIM_HandleTypeDef htim2;

uint32_t input_captures[2] = {0};
uint8_t count  = 1;
uint8_t is_capture_done = FALSE;
uint32_t capture_difference = 0;

double time2_count_freq = 0;


int main(){
	double tim2_count_freq = 0;
	double tim2_count_res = 0;
	double user_signal_time_period = 0;
	double user_signal_freq = 0;

	char usr_msg[100];

	SystemClockConfig(SYS_CLOCK_FREQ_50_MHZ);
	UART2_Init();
	HAL_Init();
	GPIO_Init();
	TIMER2_Init();
	LSE_Config();

	HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_1);

	while(1){
		if (is_capture_done == TRUE){
			if(input_captures[1] > input_captures[0])
				capture_difference = input_captures[1] - input_captures[0];
			else
				capture_difference = (0xFFFFFFFF - input_captures[0]) + input_captures[1];

		tim2_count_freq = (HAL_RCC_GetPCLK1Freq() * 2) / (htim2.Init.Prescaler +1);
		tim2_count_res = 1 / tim2_count_freq;
		user_signal_time_period = (capture_difference * tim2_count_res);
		user_signal_freq = 1/user_signal_time_period;

		sprintf(usr_msg, "Frequency of the signal applied = %lf\r\n", user_signal_freq);
		HAL_UART_Transmit(&huart2, (uint8_t *)usr_msg, strlen(usr_msg), HAL_MAX_DELAY);

		is_capture_done = FALSE;
		}

	}
	return 0;
}

void TIMER2_Init(void){
	TIM_IC_InitTypeDef tim2IC_Config;

	htim2.Instance = TIM2;
	htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim2.Init.Period = 0xFFFFFFFF;
	htim2.Init.Prescaler = 1;

	if(HAL_TIM_IC_Init(&htim2) != HAL_OK){
		Error_handler();
	}

	tim2IC_Config.ICPolarity = TIM_ICPOLARITY_RISING;
	tim2IC_Config.ICSelection = TIM_ICSELECTION_DIRECTTI;
	tim2IC_Config.ICPrescaler = TIM_ICPSC_DIV1;
	tim2IC_Config.ICFilter = 0;

	if (HAL_TIM_IC_ConfigChannel(&htim2, &tim2IC_Config, TIM_CHANNEL_1) != HAL_OK){
		Error_handler();
	}
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if(!is_capture_done){
		if (count == 1){
			input_captures[0] = __HAL_TIM_GET_COMPARE(&htim2, TIM_CHANNEL_1);
			count++;
		}else if(count == 2){
			input_captures[1] = __HAL_TIM_GET_COMPARE(&htim2, TIM_CHANNEL_1);
			is_capture_done = TRUE;
			count = 1;
		}
	}
}

void LSE_Config(void){
	/*
	RCC_OscInitTypeDef Osc_Init;
	Osc_Init.OscillatorType = RCC_OSCILLATORTYPE_LSE;
	Osc_Init.LSEState = RCC_LSE_ON;
	if (HAL_RCC_OscConfig(&Osc_Init) != HAL_OK)
	{
		Error_handler();
	}*/

	HAL_RCC_MCOConfig(RCC_MCO1, RCC_MCO1SOURCE_LSE, RCC_MCODIV_1);


}

void GPIO_Init(void){
	GPIO_InitTypeDef led_gpio;
	led_gpio.Pin = GPIO_PIN_5;
	led_gpio.Mode = GPIO_MODE_OUTPUT_PP;
	led_gpio.Pull = GPIO_NOPULL;
	__HAL_RCC_GPIOA_CLK_ENABLE();
	HAL_GPIO_Init(GPIOA, &led_gpio);
}

void UART2_Init(void)
{
	huart2.Instance = USART2;
	huart2.Init.BaudRate = 115200;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	if ( HAL_UART_Init(&huart2) != HAL_OK )
	{
		//There is a problem
		Error_handler();
	}
}

void SystemClockConfig(uint8_t clock_freq )
{
	RCC_OscInitTypeDef Osc_Init;
	RCC_ClkInitTypeDef Clock_Init;

	Osc_Init.OscillatorType = RCC_OSCILLATORTYPE_HSI | RCC_OSCILLATORTYPE_LSE;
	Osc_Init.HSIState = RCC_HSI_ON;
	Osc_Init.LSEState = RCC_LSE_ON;
	Osc_Init.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT; // aka 16
	Osc_Init.PLL.PLLState = RCC_PLL_ON;
	Osc_Init.PLL.PLLSource = RCC_PLLSOURCE_HSI;

	switch(clock_freq) {
	case SYS_CLOCK_FREQ_50_MHZ:
    Osc_Init.PLL.PLLM = 8;
    Osc_Init.PLL.PLLN = 50;
    Osc_Init.PLL.PLLP = RCC_PLLP_DIV2;
    Osc_Init.PLL.PLLQ = 2;
    Osc_Init.PLL.PLLR = 2;
    Clock_Init.ClockType = RCC_CLOCKTYPE_HCLK  | RCC_CLOCKTYPE_SYSCLK |
                           RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    Clock_Init.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    Clock_Init.AHBCLKDivider = RCC_SYSCLK_DIV1;
    Clock_Init.APB1CLKDivider = RCC_HCLK_DIV2;
    Clock_Init.APB2CLKDivider = RCC_HCLK_DIV1;
    break;

  case SYS_CLOCK_FREQ_84_MHZ:
    Osc_Init.PLL.PLLM = 8;
    Osc_Init.PLL.PLLN = 84;
    Osc_Init.PLL.PLLP = RCC_PLLP_DIV2;
    Osc_Init.PLL.PLLQ = 2;
    Osc_Init.PLL.PLLR = 2;
    Clock_Init.ClockType = RCC_CLOCKTYPE_HCLK  | RCC_CLOCKTYPE_SYSCLK |
                           RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    Clock_Init.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    Clock_Init.AHBCLKDivider = RCC_SYSCLK_DIV1;
    Clock_Init.APB1CLKDivider = RCC_HCLK_DIV2;
    Clock_Init.APB2CLKDivider = RCC_HCLK_DIV1;
    break;

  case SYS_CLOCK_FREQ_120_MHZ:
    Osc_Init.PLL.PLLM = 8;
    Osc_Init.PLL.PLLN = 120;
    Osc_Init.PLL.PLLP = RCC_PLLP_DIV2;
    Osc_Init.PLL.PLLQ = 2;
    Osc_Init.PLL.PLLR = 2;
    Clock_Init.ClockType = RCC_CLOCKTYPE_HCLK  | RCC_CLOCKTYPE_SYSCLK |
                           RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    Clock_Init.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    Clock_Init.AHBCLKDivider = RCC_SYSCLK_DIV1;
    Clock_Init.APB1CLKDivider = RCC_HCLK_DIV4;
    Clock_Init.APB2CLKDivider = RCC_HCLK_DIV2;
    break;

    default:
    return ;
	}

	if (HAL_RCC_OscConfig(&Osc_Init) != HAL_OK)
	{
	  Error_handler();
	}

	if (HAL_RCC_ClockConfig(&Clock_Init, FLASH_LATENCY_1) != HAL_OK)
	{
		Error_handler();
	}

	/*Configure the systick timer interrupt frequency (for every 1 ms) */
	uint32_t hclk_freq = HAL_RCC_GetHCLKFreq();
	HAL_SYSTICK_Config(hclk_freq/1000);

	/**Configure the Systick
	*/
	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

	/* SysTick_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

void Error_handler(void){
	while(1);
}

