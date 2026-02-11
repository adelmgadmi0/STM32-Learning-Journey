#include "stm32f4xx_hal.h"
#include <string.h>



int main(void){

	RCC_OscInitTypeDef osc_init;
	RCC_ClkInitTypeDef clk_init;

	HAL_Init();

	osc_init.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	osc_init.HSIState = RCC_HSI_ON;
	osc_init.HSICalibrationValue = 16;
	osc_init.PLL.PLLState = RCC_PLL_ON;
	osc_init.PLL.PLLSource = RCC_PLLSOURCE_HSI;

	switch(clock_freq){

		case SYS_CLOCK_FREQ_50_MHZ:{
			osc_init.

		}
		case SYS_CLOCK_FREQ_50_MHZ:{

		}
		case SYS_CLOCK_FREQ_50_MHZ:{

		}




	}



	while(1);



	return 0;
}
