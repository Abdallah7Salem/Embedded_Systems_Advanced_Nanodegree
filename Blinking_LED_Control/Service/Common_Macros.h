/*
 * Common_Macros.h
 *
 * Created: 10/18/2022 1:17:24 PM
 *  Author: Abdallah
 */ 


#ifndef COMMON_MACROS_H_
#define COMMON_MACROS_H_


#define SET_BIT(PORT, BIT_NUMBER)  (PORT |= (1<<BIT_NUMBER))

#define CLEAR_BIT(PORT, BIT_NUMBER) (PORT &= ~(1<<BIT_NUMBER))

#define READ_BIT(PORT, BIT_NUMBER) ((PORT & (1<<BIT_NUMBER))>>BIT_NUMBER)

#define TOGGLE_BIT(PORT, BIT_NUMBER) (PORT ^= (1<<BIT_NUMBER))



#endif /* COMMON_MACROS_H_ */
