/*
 * SysTick.c
 *
 * Created: 11/3/2022 11:02:41 PM
 *  Author: Abdallah
 */ 

/************************************************************************/
/* INCLUDES                                                                     */
/************************************************************************/
#include "SysTick.h"
#include "TM4C_Registers.h"
#include "Platform_Types.h"


/************************************************************************/
/* MACROS                                                                     */
/************************************************************************/
#define SYSTICK_STCURRENT_CLEAR 1
#define SYSTICK_ENABLE 1
#define SYSTICK_DISABLE 0
#define SYSTICK_SYSTEM_CLOCK 1
#define SYSTICK_INTERNAL 0
#define KEIL_SIM_CLOCK_FREQ 8e6

/************************************************************************/
/* Local Data                                                                     */
/************************************************************************/
static void (*sysTickISR)(void);
uint32 numberOfOverFlows = 0;
uint32 onNumberOfOverFlows = 0;
uint32 offNumberOfOverFlows = 0;

/************************************************************************/
/* SysTick APIs                                                                     */
/************************************************************************/
void SysTick_Init(void) {
  SYSTICK_STRELOAD_ADDRESS = SYSTICK_INIT_PRELOAD_VAL;

  SYSTICK_STCURRENT_ADDRESS = SYSTICK_STCURRENT_CLEAR;

  SYSTICK_STCTRL_ADDRESS.BF.CLK_SRC = SYSTICK_CLOCK_SOURCE;

  SYSTICK_STCTRL_ADDRESS.BF.INEN = SYSTICK_INTERRUPT_STATE;

  SYSTICK_STCTRL_ADDRESS.BF.EN = 1;
}

void SysTick_SetDuration(SysTick_DurationInSType onDuration, SysTick_DurationInSType offDuration) {

	onNumberOfOverFlows = (int)(onDuration * 1000.0);
	offNumberOfOverFlows = (int)(offDuration * 1000.0);

	numberOfOverFlows = offNumberOfOverFlows;

	SYSTICK_STCURRENT_ADDRESS = SYSTICK_STCURRENT_CLEAR;
}

void SysTick_SetISRCallBack( void (*funPtr)(void) ) 
{ 
	sysTickISR = funPtr; 
}

void SysTick_Handler(void) 
{ 
	sysTickISR(); 
}
