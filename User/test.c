//#include "stm32f10x.h"                  // Device header
//#include "Delay.h"
//#include "GPIO_Init.h"
//#include "OLED.h"
//#include "Motor.h"
//#include "RP.h"
//#include "Key_Full.h"
//#include "Encoder.h"
//#include "Serial.h"


/* 串口测试 */
//int main(void){
//	OLED_Init();
//	RP_Init();
//	Serial_Init();
//	uint16_t rp1, rp2, rp3, rp4;
//	while(1){
//		rp1 = RP_GetVaule(RP1);
//		rp2 = RP_GetVaule(RP2);
//		rp3 = RP_GetVaule(RP3);
//		rp4 = RP_GetVaule(RP4);
//		OLED_Printf(0, 0, OLED_8X16, "%04d", rp1);
//		OLED_Printf(0, 16, OLED_8X16, "%04d", rp2);
//		OLED_Printf(0, 32, OLED_8X16, "%04d", rp3);
//		OLED_Printf(0, 48, OLED_8X16, "%04d", rp4);
//		
//		Serial_Printf("%d %d %d %d \r\n", rp1, rp2, rp3, rp4);
//		
//		OLED_Update();
//		
//		Delay_ms(10);
//	}
//}



/* 编码器测试 */
//int16_t Speed;
//int16_t Location = 0;
//	
//int main(void){
//	OLED_Init();
//	Key_Init();
//	Motor_Init();
//	Encoder_Init();

//	int8_t PWM = 0;
//	
//	while(1){
//		if(Key_Check(KEY_SINGLE, K0))
//		{
//			if(PWM < 100)
//			{
//				PWM += 10;
//			}else{
//				PWM = 100;
//			}
//		}
//		if(Key_Check(KEY_SINGLE, K1))
//		{
//			if(PWM > -100)
//			{
//				PWM -= 10;
//			}else{
//				PWM = -100;
//			}
//		}
//		if(Key_Check(KEY_SINGLE, K2))
//		{
//			PWM = 0;
//		}
//		
//		Motor_SetPWM(PWM);		
//		OLED_Printf(0, 0, OLED_8X16, "RealSpeed: %+04d", PWM);
//		OLED_Printf(0, 20, OLED_8X16, "Speed: %+04d", Speed);
//		OLED_Printf(0, 40, OLED_8X16, "Location: %+04d", Location);
//		OLED_Update();
//	}
//}

//void TIM1_UP_IRQHandler(void){
//	static uint8_t Count = 0;
//	if(TIM_GetITStatus(TIM1, TIM_IT_Update) == SET){
//		Key_Tick();
//		Count ++;
//		if(Count >= 40)
//		{
//			Count = 0;
//			Speed = Encoder_Get();
//			Location += Speed;
//		}
//		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
//	}
//}


/* 电机测试 */
//int main(void){
//	OLED_Init();
//	Key_Init();
//	Motor_Init();

//	int8_t PWM = 0;
//	while(1){
//		if(Key_Check(KEY_SINGLE, K0))
//		{
//			if(PWM < 100)
//			{
//				PWM += 10;
//			}else{
//				PWM = 100;
//			}
//		}
//		if(Key_Check(KEY_SINGLE, K1))
//		{
//			if(PWM > -100)
//			{
//				PWM -= 10;
//			}else{
//				PWM = -100;
//			}
//		}
//		if(Key_Check(KEY_SINGLE, K2))
//		{
//			PWM = 0;
//		}
//		
//		Motor_SetPWM(PWM);		
//		OLED_Printf(0, 0, OLED_8X16, "%+04d", PWM);
//		OLED_Update();
//	}
//}
//
//void TIM1_UP_IRQHandler(void){
//	if(TIM_GetITStatus(TIM1, TIM_IT_Update) == SET){
//		Key_Tick();
//		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
//	}
//}


/* 旋钮器测试 */
//int main(void){
//	OLED_Init();
//	Key_Init();
//	RP_Init();
//	

//	while(1){
//		OLED_Printf(0, 0, OLED_8X16, "%04d", RP_GetVaule(RP1));
//		OLED_Printf(0, 16, OLED_8X16, "%04d", RP_GetVaule(RP2));
//		OLED_Printf(0, 32, OLED_8X16, "%04d", RP_GetVaule(RP3));
//		OLED_Printf(0, 48, OLED_8X16, "%04d", RP_GetVaule(RP4));
//		OLED_Update();
//	}
//}


/* 按钮测试 */
//int main(void){
//	OLED_Init();
//	Key_Init();
//	int8_t count = 0;
//	while(1){
//		if(Key_Check(KEY_SINGLE, K1))
//		{
//			if(count < 100)
//			{
//				count += 10;
//			}else{
//				count = 100;
//			}
//		}
//		if(Key_Check(KEY_SINGLE, K2))
//		{
//			if(count > -100)
//			{
//				count -= 10;
//			}else{
//				count = -100;
//			}
//		}
//		if(Key_Check(KEY_SINGLE, K3))
//		{
//			count = 0;
//		}
//		
//		OLED_Printf(0, 0, OLED_8X16, "%+04d", count);
//		OLED_Update();
//	}
//}





