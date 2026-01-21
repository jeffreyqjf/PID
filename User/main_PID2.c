#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "GPIO_Init.h"
#include "OLED.h"
#include "Motor.h"
#include "RP.h"
#include "Key_Full.h"
#include "Encoder.h"
#include "Serial.h"
#include <math.h>
#include <stdlib.h>
#include "PID.h"


PID_t Inner = {
	.Kp = 0.60,
	.Ki = 0.35,
	.Kd = 0.0,
	.OutMax = 100.0,
	.OutMin = -100.0,
};
// 调Outer Kd过大会出现震动
PID_t Outer = {
	.Kp = 0.30,
	.Ki = 0.0,
	.Kd = 0.10,
	.OutMax = 100.0,
	.OutMin = -100.0,
};

int16_t Speed, Location;


int main(void){
	OLED_Init();
	Key_Init();
	Motor_Init();
	Encoder_Init();
	RP_Init();
	Serial_Init();

	
	while(1){

		/* Inner PID test */
//		Inner.Kp = RP_GetVaule(RP1) / 4095.0 * 2;
//		Inner.Ki = RP_GetVaule(RP2) / 4095.0 * 2;
//		Inner.Kd = RP_GetVaule(RP3) / 4095.0 * 2;
//		Inner.Target = RP_GetVaule(RP4) / 4095.0 * 300 - 150;
//		
//		Serial_Printf("%.0f %.0f %.0f\r\n", Inner.Target, Inner.Actual, Inner.Out);
//		OLED_Printf(0, 0, OLED_8X16, "p:%+3.2f Ta:%+04.0f", Inner.Kp, Inner.Target);
//		OLED_Printf(0, 20, OLED_8X16, "i:%+3.2f Ac:%+04.0f", Inner.Ki, Inner.Actual);
//		OLED_Printf(0, 40, OLED_8X16, "d:%+3.2f Ou:%+04.0f", Inner.Kd, Inner.Out);
		
		/* Outer PID test */
//		Outer.Kp = RP_GetVaule(RP1) / 4095.0 * 2;
//		Outer.Ki = RP_GetVaule(RP2) / 4095.0 * 2;
//		Outer.Kd = RP_GetVaule(RP3) / 4095.0 * 2;
		Outer.Target = RP_GetVaule(RP4) / 4095.0 * 816 - 408;
		
		Serial_Printf("%.0f %.0f %.0f %.0f\r\n", Outer.Target, Outer.Actual, Outer.Out);
		OLED_Printf(0, 0, OLED_8X16, "p:%+3.2f Ta:%+04.0f", Outer.Kp, Outer.Target);
		OLED_Printf(0, 20, OLED_8X16, "i:%+3.2f Ac:%+04.0f", Outer.Ki, Outer.Actual);
		OLED_Printf(0, 40, OLED_8X16, "d:%+3.2f Ou:%+04.0f", Outer.Kd, Outer.Out);
		
		
		OLED_Update();
	}
}

void TIM1_UP_IRQHandler(void){
	static uint8_t Count_Inner = 0;
	static uint8_t Count_Outer = 0;
	if(TIM_GetITStatus(TIM1, TIM_IT_Update) == SET){
		Key_Tick();
		Count_Inner ++;
		Count_Outer ++; 
		if(Count_Inner >= 40)
		{
			Count_Inner = 0;
			Speed = Encoder_Get();
			Location += Speed;
			
			Inner.Actual = (float)Speed;
			PID_Update(&Inner);
			
			Motor_SetPWM(Inner.Out);
			
			
		}
		if(Count_Outer >= 40)
		{
			Count_Outer = 0;
			
			Outer.Actual = Location;
			PID_Update(&Outer);
			
			Inner.Target = Outer.Out;
		}
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
	}
}




