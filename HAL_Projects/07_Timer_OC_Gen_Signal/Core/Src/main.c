#include "stm32f4xx_hal.h"
#include "main.h"
#include <string.h>
#include <stdio.h>

void SystemClockConfig(uint8_t clock_freq);
void Error_handler(void);
void UART2_Init(void);
void GPIO_Init(void);
void TIMER2_Init(void);


TIM_HandleTypeDef htim2;
UART_HandleTypeDef huart2;

uint32_t pulse1_value = 50000; // to produce 500Hz
uint32_t pulse2_value = 25000; // to produce 1KHz
uint32_t pulse3_value = 12500;  // to produce 2KHz
uint32_t pulse4_value = 6250;  // to produce 4KHz

uint32_t ccr1_content = 0;
uint32_t temp_var = 0;

int main(){

	HAL_Init();
	SystemClockConfig(SYS_CLOCK_FREQ_50_MHZ);
	GPIO_Init();
	TIMER2_Init();
	UART2_Init();

	if(HAL_TIM_OC_Start_IT(&htim2, TIM_CHANNEL_1) != HAL_OK){
		Error_handler();
	}

	if(HAL_TIM_OC_Start_IT(&htim2, TIM_CHANNEL_2) != HAL_OK){
		Error_handler();
	}

	if(HAL_TIM_OC_Start_IT(&htim2, TIM_CHANNEL_3) != HAL_OK){
		Error_handler();
	}

	if(HAL_TIM_OC_Start_IT(&htim2, TIM_CHANNEL_4) != HAL_OK){
		Error_handler();
	}
	while(1);
	return 0;

}
void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim){

	//TIM2_CH1 toggling with 500Hz freq :
	if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1){
		ccr1_content = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
		temp_var =  (ccr1_content+pulse1_value);
		__HAL_TIM_SET_COMPARE(htim, TIM_CHANNEL_1, temp_var);
	}

	//TIM2_CH2 toggling with 1000Hz freq :
	if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2){
		ccr1_content = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2);
		temp_var =  (ccr1_content+pulse2_value);
		__HAL_TIM_SET_COMPARE(htim, TIM_CHANNEL_2, temp_var);
	}

	//TIM2_CH3 toggling with 2000Hz freq :
	if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_3){
		ccr1_content = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_3);
		temp_var =  (ccr1_content+pulse3_value);
		__HAL_TIM_SET_COMPARE(htim, TIM_CHANNEL_3, temp_var);
	}

	//TIM2_CH4 toggling with 4000Hz freq :
	if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_4){
		ccr1_content = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_4);
		temp_var =  (ccr1_content+pulse4_value);
		__HAL_TIM_SET_COMPARE(htim, TIM_CHANNEL_4, temp_var);
	}

}

void TIMER2_Init(void){
	TIM_OC_InitTypeDef Tim2_OC_Init;

	htim2.Instance = TIM2;
	htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim2.Init.Period = 0xFFFFFFFF;
	htim2.Init.Prescaler = 0;

	if(HAL_TIM_OC_Init(&htim2) != HAL_OK){
		Error_handler();
	}

	Tim2_OC_Init.OCMode = TIM_OCMODE_TOGGLE;
	Tim2_OC_Init.OCPolarity = TIM_OCPOLARITY_HIGH;

	Tim2_OC_Init.Pulse = pulse1_value;
	if (HAL_TIM_OC_ConfigChannel(&htim2, &Tim2_OC_Init, TIM_CHANNEL_1) != HAL_OK){
		Error_handler();
	}

	Tim2_OC_Init.Pulse = pulse2_value;
	if (HAL_TIM_OC_ConfigChannel(&htim2, &Tim2_OC_Init, TIM_CHANNEL_2) != HAL_OK){
			Error_handler();
		}

	Tim2_OC_Init.Pulse = pulse3_value;
	if (HAL_TIM_OC_ConfigChannel(&htim2, &Tim2_OC_Init, TIM_CHANNEL_3) != HAL_OK){
			Error_handler();
		}

	Tim2_OC_Init.Pulse = pulse4_value;
	if (HAL_TIM_OC_ConfigChannel(&htim2, &Tim2_OC_Init, TIM_CHANNEL_4) != HAL_OK){
			Error_handler();
		}
}


void GPIO_Init(void){
	GPIO_InitTypeDef led_gpio;
	led_gpio.Pin = GPIO_PIN_0;
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
	RCC_OscInitTypeDef Osc_Init = {0};
	RCC_ClkInitTypeDef Clock_Init = {0};

	Osc_Init.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	Osc_Init.HSEState = RCC_HSE_ON;
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
