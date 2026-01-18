#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "GPIO_Init.h"
#include "OLED.h"
#include "EXTI_Init.h"
#include "Timer.h"
#include "PWM.h"
#include "RP.h"
#include "MyRTC.h"
#include "Key_Full.h"


int main(void){
	OLED_Init();
	Key_Init();
	RP_Init();
	

	while(1){
		OLED_Printf(0, 0, OLED_8X16, "%04d", RP_GetVaule(RP1));
		OLED_Printf(0, 16, OLED_8X16, "%04d", RP_GetVaule(RP2));
		OLED_Printf(0, 32, OLED_8X16, "%04d", RP_GetVaule(RP3));
		OLED_Printf(0, 48, OLED_8X16, "%04d", RP_GetVaule(RP4));
		OLED_Update();
	}
}


void TIM1_UP_IRQHandler(void){
	if(TIM_GetITStatus(TIM1, TIM_IT_Update) == SET){
		Key_Tick();
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
	}
}
