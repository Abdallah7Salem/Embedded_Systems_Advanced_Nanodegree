/*
 * Gpt.c
 *
 * Created: 10/18/2022 1:16:31 PM
 *  Author: Abdallah
 */ 

/************************************************************************/
/* Includes                                                                     */
/************************************************************************/
#include "TM4C_Registers.h"
#include "Gpt.h"
#include "Interrupt.h"


/************************************************************************/
/* TIMER APIs                                                                     */
/************************************************************************/
Error TIMER1_16_32_Delay_Sec(uint16_t delay_in_seconds)
{
	/* Enable the clock of Timer1 16-32bit */
	SYSCTL_RCGCTIMER_REG |= (1<<1);
	
	/* Disable Counting of Timer A --> TAEN = 0, TBEN = 0
	Bits in GPTMCFG register should only be changed when the TAEN and TBEN bits in the
	GPTMCTL register are cleared.
	*/
	TIMER1_16_32_CTL_R = 0x00000000;
	
	/* Configure the timer at 32-bit Mode 
	   0x00: For a 16/32-bit timer, this value selects the 32-bit timer
	   configuration.
	 */
	TIMER1_16_32_CFG_R = 0x00;
	
	/* Configure the timer for periodic count */
	TIMER1_16_32_TAMR_R = PERIODIC_TIMER_MODE;
	
	/* Configure the timer for down counting */
	TIMER1_16_32_TAMR_R &= (0<<4);
	
	/* Equation to put the LOAD Value in TAILR as it is the only register 
	   when working with Timer16_32 in a 32-bit mode 
	 */
	/* the CPU Frequency as a value is considered as 1 second,
	   so, if we want a delay of 10 sec --> 10 * CPU_FREQUENCY and put this 
	   value in the LOAD Register then count down ! 
	 */
	TIMER1_16_32_TAIL_R = delay_in_seconds * CPU_FREQUENCY - 1;
	
	/* Clear Timer A timeout flag (to avoid having a garbage value and calling ISR*/
	TIMER1_16_32_ICR_R |= (1<<TATOCINT);
	
	/* Enable Time-Out Interrupt for Timer A */
	TIMER1_16_32_IMR_R |= (1<<TATOIM);
	
	/* Enable timer A to start counting */
	TIMER1_16_32_CTL_R |= (1<<TAEN);
	
	/* Enable Interrupt for Timer1-A 16/32 bit */
	//NVIC_EnableInterrupt(TIMER1A_16_32_INTERRUPT_NUMBER);
	
	return E_OK;
}


/************************************************************************/
/* TIMER Callback                                                                     */
/************************************************************************/
TIMER1A_Handler()
{
		Timer_Callback();
}


/************************************************************************/
/* TIMER Set Callback                                                                     */
/************************************************************************/
void Set_Timer_Callback (void(*ptr)(void))
{
		Timer_Callback = ptr;
}
