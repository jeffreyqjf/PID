#include "stm32f10x.h"                  // Device header
#include "GPIO_Init.h"
#include "Key_Full.h"


#define KEY_PRESSED       1
#define KEY_UNPRESSED			0
#define KEY_NUM           4

#define KEY_TIME_LONG 		2000
#define KEY_TIME_DOUBLE		200
#define KEY_TIME_REPEAT		100

uint8_t Key_Flag[KEY_NUM] = {0};


void Key_Init(void){
	
	// GPIO Init
	GPIOA_Init(GPIO_Mode_IPU, GPIO_Pin_11 | GPIO_Pin_12);
	GPIOB_Init(GPIO_Mode_IPU, GPIO_Pin_10 | GPIO_Pin_11);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	
	// switch Clock
	TIM_InternalClockConfig(TIM1);
	
	// TIM(Timer) init
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 1000 - 1; // ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1; // PSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0x00; // not use 
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStructure);
	
	TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE); // TIM_IT_Update is about what?
	
	// NVIC init
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	
	// Turn up TIM1
	TIM_Cmd(TIM1,ENABLE);
}


uint8_t Key_GetState(uint8_t Kn){
	switch(Kn){
		case K0:
			if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_10) == 0){ 
				return KEY_PRESSED;
			}
			break;

		case K1:
			if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11) == 0){ 
				return KEY_PRESSED;
			}
			break;

		case K2:
			if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_11) == 0){ 
				return KEY_PRESSED;
			}
			break;

		case K3:
			if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_12) == 0){ 
				return KEY_PRESSED;
			}
			break;

		default:
			break;

	}
	return KEY_UNPRESSED;
}


uint8_t Key_Check(uint8_t Flag, uint8_t Kn){
	if(Key_Flag[Kn] & Flag){
		if(Flag != KEY_HOLD){
			Key_Flag[Kn] &= ~Flag;
		}
		return 1;
	}
	return 0;
}


void Key_Tick(void){
	static uint8_t Count = 0;
	static uint8_t CurrentState[KEY_NUM], PrevState[KEY_NUM];
	static uint8_t State[KEY_NUM] = {0};
	static int16_t Time[KEY_NUM] = {0};
	
	// Counting all Key individal
	for(int i = 0; i < KEY_NUM; i++){
		if(Time[i] > 0){
			Time[i]--;
		}
	}

	
	if(Count >= 20){
		Count = 0;
	
		for(int i = 0; i < KEY_NUM; i++){
			PrevState[i] = CurrentState[i];
			CurrentState[i] = Key_GetState(i);
			
			if(CurrentState[i] == KEY_PRESSED){
				// HOLD
				Key_Flag[i] |= KEY_HOLD;
			}else{
				Key_Flag[i] &= ~KEY_HOLD;
			}
			
			if(CurrentState[i] == KEY_PRESSED && PrevState[i] == KEY_UNPRESSED){
				// DOWN
				Key_Flag[i] |= KEY_DOWN;
			}
			if(CurrentState[i] == KEY_UNPRESSED && PrevState[i] == KEY_PRESSED){
				// UP
				Key_Flag[i] |= KEY_UP;
			}
			
			switch(State[i]){
				case 0:
					if(CurrentState[i] == KEY_PRESSED){
						State[i] = 1;
						Time[i] = KEY_TIME_LONG;
					}
					break;
					
				case 1:
					if(CurrentState[i] == KEY_UNPRESSED){
						Time[i] = KEY_TIME_DOUBLE; // for double click
						State[i] = 2; // click one time 
					}else if(Time[i] == 0){
						// long hold
						Key_Flag[i] |= KEY_LONG;
						Time[i] = KEY_TIME_REPEAT;
						State[i] = 4; // for repeat
					}
					break;
					
				case 2:
					if(CurrentState[i] == KEY_PRESSED){
						// double click
						Key_Flag[i] |= KEY_DOUBLE;
						State[i] = 3;
					}else if(Time[i] == 0){
						// single click
						Key_Flag[i] |= KEY_SINGLE;
						State[i] = 0;
					}
					break;
					
				case 3:
					if(CurrentState[i] == KEY_UNPRESSED){
						State[i] = 0;
					}
					break;
				
				case 4:
					if(CurrentState[i] == KEY_UNPRESSED){
						State[i] = 0;
					}else if(Time[i] == 0){
						// repeat
						Key_Flag[i] |= KEY_REPEAT;
						Time[i] = KEY_TIME_REPEAT;
						State[i] = 4;
					}
					break;
			}
		}
		
	}
	Count ++;
}


//void TIM1_IRQHandler(void){
//	if(TIM_GetITStatus(TIM1, TIM_IT_Update) == SET){
//		
//		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
//	}
//}
