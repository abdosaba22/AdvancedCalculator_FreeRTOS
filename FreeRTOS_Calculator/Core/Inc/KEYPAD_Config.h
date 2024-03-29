#ifndef KEYPAD_CONFIG_H
#define KEYPAD_CONFIG_H

	

/*
 * KEYPAD.h
 *
 * Created: 12/4/2021 5:58:00 PM
 *  Author: Abdalrahman_Amin
 */

/*
-------------------------
|     |     |     |     | <---------- KP0 - PA
-------------------------                    
|     |     |     |     | <---------- KP1 - PA
-------------------------                      
|     |     |     |     | <---------- KP2 - PA 
-------------------------                    
|     |     |     |     | <---------- KP3 - PA
-------------------------
|     |     |     | PULL UP
|     |     |     |
KP4   KP5   KP6   KP7




*/



#define KEYPAD_ROW1_PORT 				GPIOB
#define KEYPAD_ROW234_PORT 				GPIOA

#define KEYPAD_COL123_PORT 				GPIOB
#define KEYPAD_COL4_PORT 				GPIOA

#define KP0_PIN 						GPIO_PIN_0	/* GPIOB, B0 */
#define KP1_PIN 						GPIO_PIN_4	/* GPIOA, A4 */
#define KP2_PIN 						GPIO_PIN_1	/* GPIOA */
#define KP3_PIN 						GPIO_PIN_0	/* GPIOA */

#define KP4_PIN 						GPIO_PIN_4	/* GPIOB, B4 */
#define KP5_PIN 						GPIO_PIN_5	/* GPIOB, B5 */
#define KP6_PIN 						GPIO_PIN_1	/* GPIOB, B1 */
#define KP7_PIN 						GPIO_PIN_10 /* GPIOA, A10 */


#endif
