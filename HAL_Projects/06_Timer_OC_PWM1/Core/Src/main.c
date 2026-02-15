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
TIM_OC_InitTypeDef Tim2_PWM_Config;

int main(){

	HAL_Init();
	SystemClockConfig(SYS_CLOCK_FREQ_50_MHZ);
	GPIO_Init();
	TIMER2_Init();
	UART2_Init();

	if(HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1) != HAL_OK){
		Error_handler();
	}

	if(HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2) != HAL_OK){
			Error_handler();
		}

	if(HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3) != HAL_OK){
			Error_handler();
		}

	if(HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4) != HAL_OK){
			Error_handler();
		}



	while(1){
		for(int i = 0; i<10;i++){
			Tim2_PWM_Config.Pulse = (htim2.Init.Period * i)/10;
			if(HAL_TIM_PWM_ConfigChannel(&htim2, &Tim2_PWM_Config, TIM_CHANNEL_1) != HAL_OK){
				Error_handler();
			}
			HAL_Delay(125);
		}
			for(int i = 10; i>0;i--){
				Tim2_PWM_Config.Pulse = (htim2.Init.Period * i)/10;
				if(HAL_TIM_PWM_ConfigChannel(&htim2, &Tim2_PWM_Config, TIM_CHANNEL_1) != HAL_OK){
					Error_handler();
				}
			HAL_Delay(125);
			}



		}

	return 0;

}

void TIMER2_Init(void){


	htim2.Instance = TIM2;
	htim2.Init.Period = 100-1;
	htim2.Init.Prescaler = 50-1;
	htim2.Init.CounterMode = TIM_COUNTERMODE_UP;

	if(HAL_TIM_PWM_Init(&htim2) != HAL_OK){
		Error_handler();
	}

	Tim2_PWM_Config.OCMode = TIM_OCMODE_PWM1	;
	Tim2_PWM_Config.OCPolarity = TIM_OCPOLARITY_HIGH;

	Tim2_PWM_Config.Pulse = htim2.Init.Period * 0.25;
	if(HAL_TIM_PWM_ConfigChannel(&htim2, &Tim2_PWM_Config, TIM_CHANNEL_1) != HAL_OK){
		Error_handler();
	}

	Tim2_PWM_Config.Pulse = htim2.Init.Period * 0.45;
	if(HAL_TIM_PWM_ConfigChannel(&htim2, &Tim2_PWM_Config, TIM_CHANNEL_2) != HAL_OK){
		Error_handler();
	}

	Tim2_PWM_Config.Pulse = htim2.Init.Period * 0.75;
	if(HAL_TIM_PWM_ConfigChannel(&htim2, &Tim2_PWM_Config, TIM_CHANNEL_3) != HAL_OK){
		Error_handler();
	}

	Tim2_PWM_Config.Pulse = htim2.Init.Period * 0.9;
	if(HAL_TIM_PWM_ConfigChannel(&htim2, &Tim2_PWM_Config, TIM_CHANNEL_4) != HAL_OK){
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
