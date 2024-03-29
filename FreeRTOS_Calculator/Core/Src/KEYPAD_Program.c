#include "stdint.h"
#include "stm32f4xx_hal.h"

#include "KEYPAD_Interface.h"
#include "KEYPAD_Config.h"
#include "KEYPAD_Private.h"


const uint8_t keypad_matrix[] = {
        '1','2','3','/',
        '4','5','6','*',
        '7','8','9','-',
        'c','0','=','+'};


uint8_t KEYPAD_read(void)
{
	uint8_t i,VAL=1;

	KP0(1);KP1(1);KP2(1);KP3(1);
	for(i = 0; i < 4;i++)
	{
		switch(i){
		case 0: KP0(0);KP1(1);KP2(1);KP3(1); break;
		case 1: KP0(1);KP1(0);KP2(1);KP3(1); break;
		case 2: KP0(1);KP1(1);KP2(0);KP3(1); break;
		case 3: KP0(1);KP1(1);KP2(1);KP3(0); break;
		}
		if (!KP4()) return keypad_matrix[0 + i*4];
		if (!KP5()) return keypad_matrix[1 + i*4];
		if (!KP6()) return keypad_matrix[2 + i*4];
		if (!KP7()) return keypad_matrix[3 + i*4];


	}
	return 0;

}
