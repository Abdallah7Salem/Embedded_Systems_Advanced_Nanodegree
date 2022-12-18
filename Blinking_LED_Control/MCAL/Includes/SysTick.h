/*
 * SysTick.h
 *
 * Created: 11/3/2022 11:02:52 PM
 *  Author: Abdallah
 */ 


#ifndef SYSTICK_H_
#define SYSTICK_H_

/************************************************************************/
/* INCLUDES                                                                     */
/************************************************************************/
#include "Platform_Types.h"

/************************************************************************/
/* Type Definitions                                                                     */
/************************************************************************/
typedef float64 SysTick_DurationInSType;

/************************************************************************/
/* GLOBAL Variables                                                                     */
/************************************************************************/
extern uint32_t numberOfOverFlows;
extern uint32_t onNumberOfOverFlows;
extern uint32_t offNumberOfOverFlows;

/************************************************************************/
/* FUCTIONS Prototypes                                                                     */
/************************************************************************/
void SysTick_Init(void);
void SysTick_SetDuration(SysTick_DurationInSType onDuration,
SysTick_DurationInSType offDuration);
void SysTick_SetISRCallBack(void (*funPtr)(void));

/************************************************************************/
/* SysTick CONFIGURATION                                                                     */
/************************************************************************/
#define SYSTICK_INIT_PRELOAD_VAL 48000
#define SYSTICK_INTERRUPT_STATE SYSTICK_ENABLE
#define SYSTICK_CLOCK_SOURCE SYSTICK_SYSTEM_CLOCK

#endif /* SYSTICK_H_ */