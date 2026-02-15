#include "main.h"

extern TIM_HandleTypeDef htim2;
extern uint32_t pulse1_value;
extern uint32_t pulse2_value;
extern uint32_t pulse3_value;
extern uint32_t pulse4_value;


void SysTick_Handler(void){
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}


void TIM2_IRQHandler(){
	HAL_TIM_IRQHandler(&htim2);
}
