#ifndef __KEY_FULL_H
#define __KEY_FULL_H

#define KEY_HOLD				0x01
#define KEY_DOWN				0x02
#define KEY_UP					0x04
#define KEY_SINGLE			0x08
#define KEY_DOUBLE			0x10
#define KEY_LONG				0x20
#define KEY_REPEAT			0x40

#define K0								0
#define K1								1
#define K2								2
#define K3								3

void Key_Init(void);
uint8_t Key_GetState(uint8_t Kn);
uint8_t Key_Check(uint8_t Flag, uint8_t Kn);
void Key_Tick(void);

#endif
