#ifndef __GPIO_INIT_H
#define __GPIO_INIT_H
      
void GPIOA_Init(GPIOMode_TypeDef GPIO_Mode, uint16_t GPIO_Pin_x);
void GPIOB_Init(GPIOMode_TypeDef GPIO_Mode, uint16_t GPIO_Pin_x);
void GPIOC_Init(GPIOMode_TypeDef GPIO_Mode, uint16_t GPIO_Pin_x);
void Indicator_Light_Init(void);

#endif
