/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *
 -------------------------------------------------------------------------------------------------------------------
 *         File:  SysTick_Cfg.h
 *       Module:  SysTick
 *
 *  Description:  User Configuration file for the system timer module
 *
 *********************************************************************************************************************/
#ifndef SYSTICK_CFG_H
#define SYSTICK_CFG_H

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#define SYSTICK_INIT_PRELOAD_VAL 48000 // Interrupt happens every 1ms
/* ENABLE -> To enable the system timer interrupt
   DISABLE -> To disable the system timer interrupt
*/
#define SYSTICK_INTERRUPT_STATE SYSTICK_ENABLE
/*
SYSTICK_SYSTEM_CLOCK -> To use the system clock
SYSTICK_INERNAL -> to use the internal Precision internal oscillator divided by
4
*/
#define SYSTICK_CLOCK_SOURCE SYSTICK_SYSTEM_CLOCK

#endif /* SYSTICK_CFG_H */
/**********************************************************************************************************************
 *  END OF FILE: SysTick_Cfg.h
 *********************************************************************************************************************/
