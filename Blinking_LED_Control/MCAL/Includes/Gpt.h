/*
 * Gpt.h
 *
 * Created: 10/18/2022 1:16:40 PM
 *  Author: Abdallah
 */ 


#ifndef GPT_H_
#define GPT_H_

/************************************************************************/
/* Includes                                                                     */
/************************************************************************/
#include "Platform_Types.h"
#include "TM4C_Registers.h"
#include "Typedefs.h"

/************************************************************************/
/* Macros                                                                     */
/************************************************************************/
#define ONE_SHOT_TIMER_MODE		0x01
#define PERIODIC_TIMER_MODE		0x02

#define CPU_FREQUENCY		16000000U

#define TATOCINT		0u		/* Writing 1 to this clears the timeout interrupt flag */
#define TATOIM			0u		/* Writing 1 to this enables the timeout interrupt for timer A */
#define TAEN			0u		/* Writing 1 to this enables timer A and it begins counting */


/************************************************************************/
/* TIMER APIs                                                                     */
/************************************************************************/
Error TIMER1_16_32_Delay_Sec(uint16_t delay_in_seconds);


/************************************************************************/
/* TIMER Callback                                                                     */
/************************************************************************/
static void (*Timer_Callback)(void);
void Set_Timer_Callback (void(*ptr)(void));

#endif /* GPT_H_ */
