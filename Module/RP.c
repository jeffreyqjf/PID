#include "stm32f10x.h"                  // Device header
#include "GPIO_Init.h"


void RP_Init(void){
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, ENABLE);
	
	// GPIO init, the GPIO_Pin should correspond with ADC_Channel
	GPIOA_Init(GPIO_Mode_AIN, GPIO_Pin_2);
	GPIOA_Init(GPIO_Mode_AIN, GPIO_Pin_3);
	GPIOA_Init(GPIO_Mode_AIN, GPIO_Pin_4);
	GPIOA_Init(GPIO_Mode_AIN, GPIO_Pin_5);
	
	// ADCCLK init
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);
	
	// ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
	
	// ADC init
	ADC_InitTypeDef ADC_InitStructure;
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_NbrOfChannel = 1;
	ADC_Init(ADC2, &ADC_InitStructure);
	
	ADC_Cmd(ADC2, ENABLE);
	
	ADC_ResetCalibration(ADC2);
	while(ADC_GetResetCalibrationStatus(ADC2));
	ADC_StartCalibration(ADC2);
	while(ADC_GetCalibrationStatus(ADC2));
	
}


uint16_t RP_GetVaule(uint8_t RPn){
	switch(RPn){
		case 1:
			ADC_RegularChannelConfig(ADC2, ADC_Channel_2, 1, ADC_SampleTime_55Cycles5);
			break;
		case 2:
			ADC_RegularChannelConfig(ADC2, ADC_Channel_3, 1, ADC_SampleTime_55Cycles5);
			break;
		case 3:
			ADC_RegularChannelConfig(ADC2, ADC_Channel_4, 1, ADC_SampleTime_55Cycles5);
			break;
		case 4:
			ADC_RegularChannelConfig(ADC2, ADC_Channel_5, 1, ADC_SampleTime_55Cycles5);
			break;
		default:
			
			break;
	}
	
	ADC_SoftwareStartConvCmd(ADC2, ENABLE);
	while(ADC_GetFlagStatus(ADC2, ADC_FLAG_EOC) == RESET);
	return ADC_GetConversionValue(ADC2);
}
