#include "stm32f10x.h"                  // Device header
#include "GPIO_Init.h"


uint8_t Key_Num = 0;


void Key_Init(void){
	
	// GPIO Init
	GPIOA_Init(GPIO_Mode_IPU, GPIO_Pin_2 | GPIO_Pin_3);
	
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


uint8_t Key_GetNum(void){
	uint8_t Tmp = 0;
	if(Key_Num){
		Tmp = Key_Num;
		Key_Num = 0;
		return Tmp;
	}
	return 0;
}


uint8_t Key_GetState(void){
	if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2) == 0){ // could in define
		return 1;
	}
	if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3) == 0){ // could in define
		return 2;
	}
	return 0;
}


void Key_Tick(void){
	static uint8_t Count = 0;
	static uint8_t CurrentState, PrevState;
	
	if(Count >= 20){
		Count = 0;
		
		PrevState = CurrentState;
		CurrentState = Key_GetState();
		if(PrevState != 0 && CurrentState == 0){
			Key_Num = PrevState;
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
