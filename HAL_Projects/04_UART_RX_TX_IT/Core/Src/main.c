
#include <stm32u5xx_hal.h>
#include "main.h"
#include <string.h>

#define TRUE 1
#define FALSE 0

void SystemClockConfig(void);
void UART2_Init(void);
void Error_handler(void);


UART_HandleTypeDef huart2;

char *user_data = "The app is running!\r\n";
uint8_t data_buff[100];
uint8_t recvd_data;
uint8_t count = 0;
uint8_t recp_compl = FALSE;
int main(void){

	HAL_Init();
	SystemClockConfig();
	UART2_Init();

	uint16_t DataSize = strlen(user_data);
	HAL_UART_Transmit(&huart2, (uint8_t *)user_data, DataSize, HAL_MAX_DELAY);

	while (recp_compl != TRUE ) {
		HAL_UART_Receive_IT(&huart2, &recvd_data, 1);
	}

	while (1);

	return 0;
}

void SystemClockConfig(void){

}

void UART2_Init(void){
	huart2.Instance = USART1_NS;
	huart2.Init.BaudRate = 115200;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	if(HAL_UART_Init(&huart2)!=HAL_OK){
		//There is a Pb!
		Error_handler();
	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(recvd_data =='\r'){
		recp_compl = TRUE;
		data_buff[count++] = '\r';
		HAL_UART_Transmit(&huart2, data_buff, count, HAL_MAX_DELAY);
	}
	else{
	data_buff[count++] = recvd_data;
	}
}

void Error_handler(void){
	while(1);
}

