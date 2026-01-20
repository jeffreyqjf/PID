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


float Target, Actual, Out;
float Kp, Ki, Kd;
float Error0, Error1, ErrorInt;
float Error2;
uint8_t Motor_Flag = 0;
float DifOut, Actual1;
float alpha = 0.9;

int main(void){
	OLED_Init();
	Key_Init();
	Motor_Init();
	Encoder_Init();
	RP_Init();
	Serial_Init();
	
	
	while(1){
		if(Key_Check(KEY_SINGLE, K0))
		{
			Motor_Flag = !Motor_Flag;
		}

		
		Kp = RP_GetVaule(RP1) / 4095.0 * 2;
		Ki = RP_GetVaule(RP2) / 4095.0 * 2;
		Kd = RP_GetVaule(RP3) / 4095.0 * 2;
		
		Target = RP_GetVaule(RP4) / 4095.0 * 300 - 150;
		
		// Serial_Printf("%.0f %.0f %.0f %.0f\r\n", Target, Actual, Out, ErrorInt);
		Serial_Printf("%.0f %.0f %.0f %.0f\r\n", Target, Actual, Out, DifOut);
		OLED_Printf(0, 0, OLED_8X16, "p:%+3.2f Ta:%+04.0f", Kp, Target);
		OLED_Printf(0, 20, OLED_8X16, "i:%+3.2f Ac:%+04.0f", Ki, Actual);
		OLED_Printf(0, 40, OLED_8X16, "d:%+3.2f Ou:%+04.0f", Kd, Out);
		OLED_Update();
	}
}

void TIM1_UP_IRQHandler(void){
	static uint8_t Count = 0;
	if(TIM_GetITStatus(TIM1, TIM_IT_Update) == SET){
		Key_Tick();
		Count ++;
		if(Count >= 40)
		{
			Count = 0;
			/* 位置式PID */
			Actual1 = Actual;
			Actual += Encoder_Get();
			
			/* 噪声 */
			// Actual += rand() % 41 - 20;
			
			Error1 = Error0;
			Error0 = Target - Actual;
			
			/* 变速积分 */
			float C = 1 / (0.7 * fabs(Error0) + 1);
			// 这个实验加一点 Kd 防止超调比较好
			if(Ki != 0){
				ErrorInt += C * Error0;
			}else{
				ErrorInt = 0.0;
			}
			
			/* 积分限幅 */
			if(ErrorInt > 500)ErrorInt = 500;
			if(ErrorInt < -500)ErrorInt = -500;
			

			/* 定位置控制 积分分离 */
//			if(Error0 > 10)ErrorInt = 0;
//			if(Error0 < -10)ErrorInt = 0;
			// 使用积分分离的时候要注意Kp的值要对应上面误差的大小，因为Kp减小的时候稳态误差会增大，导致上面的值可能需要适当增大，否则会导致积分误差一直为0
			
			/* 微分先行 */
			// Kd 过大的时候出现电机的卡顿是什么原因(微分先行能很好解决这个问题，思考)
			// DifOut = Kd * (Actual1 - Actual);
			
			/* 不完全微分 */
			// DifOut = (1 - alpha) * Kd * (Error0 - Error1) + alpha * DifOut;
			DifOut = Kd * (Error0 - Error1);
			
			Out = Kp * Error0 + Ki * ErrorInt + DifOut;
			
			/* 输入死区 */
			if(fabs(Error0) < 4){
				Out = 0;
			}
			
			/* 输出偏移 */
			if(Out > 0.1){
				Out += 5;
			}else if(Out < -0.1){
				Out -= 5;
			}else{
				Out = 0;
			}
			
			if(Out > 100)Out = 100;
			if(Out < -100)Out = -100;
			
			if(Motor_Flag){
					Out = 0;
			}
			Motor_SetPWM(Out);
			
			/* 增量式PID */
//			Actual = Encoder_Get();
//			
//			Error2 = Error1;
//			Error1 = Error0;
//			Error0 = Target - Actual;
//			Out += Kp * (Error1 - Error0) + Ki * Error0; + Kd * (Error0 - 2 * Error1 + Error2);
//			if(Out > 100)Out = 100;
//			if(Out < -100)Out = -100;
//			
//			Motor_SetPWM(Out);
		}
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
	}
}




