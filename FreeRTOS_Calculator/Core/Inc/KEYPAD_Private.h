#ifndef KEYPAD_PRIVATE_H
#define KEYPAD_PRIVATE_H

#define NUMOF_KEYPADPINS 					8

#define KP0(x) 								HAL_GPIO_WritePin(KEYPAD_ROW1_PORT,KP0_PIN,x)
#define KP1(x) 								HAL_GPIO_WritePin(KEYPAD_ROW234_PORT,KP1_PIN,x)
#define KP2(x) 								HAL_GPIO_WritePin(KEYPAD_ROW234_PORT,KP2_PIN,x)
#define KP3(x) 								HAL_GPIO_WritePin(KEYPAD_ROW234_PORT,KP3_PIN,x)

#define KP4() 								HAL_GPIO_ReadPin(KEYPAD_COL123_PORT,KP4_PIN)
#define KP5() 								HAL_GPIO_ReadPin(KEYPAD_COL123_PORT,KP5_PIN)
#define KP6() 								HAL_GPIO_ReadPin(KEYPAD_COL123_PORT,KP6_PIN)
#define KP7() 								HAL_GPIO_ReadPin(KEYPAD_COL4_PORT,KP7_PIN)



#endif
