#include "stm32f10x.h"                  // Device header
#include "PWM.h"
#include "GPIO_Init.h"

void Motor_Init(void){
	
	GPIOB_Init(GPIO_Mode_Out_PP, GPIO_Pin_12 | GPIO_Pin_13);
	
	PWM_Init();
}

void Motor_SetPWM(int8_t PWM){
	if(PWM >= 0){
		GPIO_SetBits(GPIOB, GPIO_Pin_12);
		GPIO_ResetBits(GPIOB, GPIO_Pin_13);
		PWM_SetCompare1(PWM);
	}else{
		GPIO_SetBits(GPIOB, GPIO_Pin_13);
		GPIO_ResetBits(GPIOB, GPIO_Pin_12);
		PWM_SetCompare1(-PWM);
	}
}
