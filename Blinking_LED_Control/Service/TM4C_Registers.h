/*
 * TM4C_Registers.h
 *
 * Created: 10/18/2022 1:17:14 PM
 *  Author: Abdallah
 */ 


#ifndef TM4C_REGISTERS_H_
#define TM4C_REGISTERS_H_


/***************************** Includes *******************************/
#include "Platform_Types.h"

/************************************************************************/
/* GPIO Clock Registers                                                                     */
/************************************************************************/
#define SYSCTL_RCGCGPIO_R          (*((volatile unsigned long *)0x400FE608))
#define SYSCTL_RCGC2GPIO_R          (*((volatile unsigned long *)0x400FE108))

/************************************************************************/
/* TIMER Clock Register                                                                     */
/************************************************************************/
#define SYSCTL_RCGCTIMER_REG      (*((volatile uint32 *)0x400FE604))

/***************************** GPIO PortF Registers *******************************/
#define GPIO_PORTF_DATA_R       (*((volatile unsigned long *)0x400253FC))
#define GPIO_PORTF_DIR_R        (*((volatile unsigned long *)0x40025400))
#define GPIO_PORTF_AFSEL_R      (*((volatile unsigned long *)0x40025420))
#define GPIO_PORTF_PUR_R        (*((volatile unsigned long *)0x40025510))
#define GPIO_PORTF_DEN_R        (*((volatile unsigned long *)0x4002551C))
#define GPIO_PORTF_LOCK_R       (*((volatile unsigned long *)0x40025520))
#define GPIO_PORTF_CR_R         (*((volatile unsigned long *)0x40025524))
#define GPIO_PORTF_AMSEL_R      (*((volatile unsigned long *)0x40025528))
#define GPIO_PORTF_PCTL_R       (*((volatile unsigned long *)0x4002552C))


/************************************************************************/
/* TIMER 1 Registers                                                                     */
/************************************************************************/
#define TIMER1_16_32_BASE_ADDRESS		0x40031000
#define TIMER1_16_32_CFG_R			(*((volatile unsigned long*)TIMER1_16_32_BASE_ADDRESS+0x000))
#define TIMER1_16_32_TAMR_R			(*((volatile unsigned long*)TIMER1_16_32_BASE_ADDRESS+0x004))
#define TIMER1_16_32_TBMR_R			(*((volatile unsigned long*)TIMER1_16_32_BASE_ADDRESS+0X008))
#define TIMER1_16_32_CTL_R			(*((volatile unsigned long*)TIMER1_16_32_BASE_ADDRESS+0x00C))
#define TIMER1_16_32_IMR_R			(*((volatile unsigned long*)TIMER1_16_32_BASE_ADDRESS+0x018))
#define TIMER1_16_32_RIS_R			(*((volatile unsigned long*)TIMER1_16_32_BASE_ADDRESS+0x01C))
#define TIMER1_16_32_MIS_R			(*((volatile unsigned long*)TIMER1_16_32_BASE_ADDRESS+0x020))
#define TIMER1_16_32_ICR_R			(*((volatile unsigned long*)TIMER1_16_32_BASE_ADDRESS+0x024))
#define TIMER1_16_32_TAIL_R			(*((volatile unsigned long*)TIMER1_16_32_BASE_ADDRESS+0x028))
#define TIMER1_16_32_TBIL_R			(*((volatile unsigned long*)TIMER1_16_32_BASE_ADDRESS+0x02C))



/************************************************************************/
/* Interrupts' Numbers (pg. 104 datasheet)                                                                     */
/************************************************************************/
#define TIMER1A_16_32_INTERRUPT_NUMBER		21u


/************************************************************************/
/* NVIC Registers                                                                     */
/************************************************************************/			
#define NVIC_BASE_ADDRESS		0xE000E000

#define NVIC_EN0				(*((volatile unsigned long*)NVIC_BASE_ADDRESS + 0x100))
#define NVIC_EN1				(*((volatile unsigned long*)NVIC_BASE_ADDRESS + 0x104))
#define NVIC_EN2				(*((volatile unsigned long*)NVIC_BASE_ADDRESS + 0x108))
#define NVIC_EN3				(*((volatile unsigned long*)NVIC_BASE_ADDRESS + 0x10C))

#define	NVIC_DIS0				(*((volatile unsigned long*)NVIC_BASE_ADDRESS + 0x180))
#define	NVIC_DIS1				(*((volatile unsigned long*)NVIC_BASE_ADDRESS + 0x184))
#define	NVIC_DIS2				(*((volatile unsigned long*)NVIC_BASE_ADDRESS + 0x188))
#define	NVIC_DIS3				(*((volatile unsigned long*)NVIC_BASE_ADDRESS + 0x18C))


#define CORTEXM4_PERI_BASE_ADDRESS 0xE000E000
/* SYSTICK Registers */
#define SYSTICK_BASE_OFFSET 0x010
#define SYSTICK_BASE_ADDRESS (CORTEXM4_PERI_BASE_ADDRESS + SYSTICK_BASE_OFFSET)

#define SYSTICK_STCTRL_OFFSET 0x0
#define SYSTICK_STRELOAD_OFFSET 0x4
#define SYSTICK_STCURRENT_OFFSET 0x8

typedef struct {
  uint32 EN : 1;
  uint32 INEN : 1;
  uint32 CLK_SRC : 1;
  uint32 : 13;
  uint32 COUNT : 1;
  uint32 : 15;
} SysTick_STCTRL_BF;
typedef union {
  uint32 R;
  SysTick_STCTRL_BF BF;
} SysTick_STCTRL_Tag;

#define SYSTICK_STCTRL_ADDRESS                                                 \
  (*((volatile SysTick_STCTRL_Tag *)(SYSTICK_BASE_ADDRESS +                    \
                                     SYSTICK_STCTRL_OFFSET)))
#define SYSTICK_STRELOAD_ADDRESS                                               \
  *((volatile uint32 *)(SYSTICK_BASE_ADDRESS + SYSTICK_STRELOAD_OFFSET))
#define SYSTICK_STCURRENT_ADDRESS                                              \
  *((volatile uint32 *)(SYSTICK_BASE_ADDRESS + SYSTICK_STCURRENT_OFFSET))

/*SCB*/
#define SCB_BASE_OFFSET 0xD00
#define SCB_BASE_ADDRESS (CORTEXM4_PERI_BASE_ADDRESS + SCB_BASE_OFFSET)

/* NVIC Registers */
#define NVIC_BASE_OFFSET 0x100
#define NVIC_BASE_ADDRESS (CORTEXM4_PERI_BASE_ADDRESS + NVIC_BASE_OFFSET)

#define NVIC_EN_OFFSET 0x0
#define NVIC_PRI_OFFSET 0x300
#define NVIC_BASE_EN_ADDRESS (NVIC_BASE_ADDRESS + NVIC_EN_OFFSET)
#define NVIC_BASE_PRI_ADDRESS (NVIC_BASE_ADDRESS + NVIC_PRI_OFFSET)
#define APINT *((volatile uint32 *)(CORTEXM4_PERI_BASE_ADDRESS + 0xD0C))

/* GPIO Registers */
#define GPIO_PORT_A_BASE_ADDRESS 0x40004000
#define GPIO_PORT_B_BASE_ADDRESS 0x40005000
#define GPIO_PORT_C_BASE_ADDRESS 0x40006000
#define GPIO_PORT_D_BASE_ADDRESS 0x40007000
#define GPIO_PORT_E_BASE_ADDRESS 0x40024000
#define GPIO_PORT_F_BASE_ADDRESS 0x40025000

#define GPIO_DATA_OFFSET 0x0
#define GPIO_DIR_OFFSET 0x400
#define GPIO_IS_OFFSET 0x404
#define GPIO_IBE_OFFSET 0x408
#define GPIO_IEV_OFFSET 0x40C
#define GPIO_IM_OFFSET 0x410
#define GPIO_RIS_OFFSET 0x414
#define GPIO_MIS_OFFSET 0x418
#define GPIO_ICR_OFFSET 0x41C
#define GPIO_AFSEL_OFFSET 0x420
#define GPIO_DR2R_OFFSET 0x500
#define GPIO_DR4R_OFFSET 0x504
#define GPIO_DR8R_OFFSET 0x508
#define GPIO_ODR_OFFSET 0x50C
#define GPIO_PUR_OFFSET 0x510
#define GPIO_PDR_OFFSET 0x514
#define GPIO_SLR_OFFSET 0x518
#define GPIO_DEN_OFFSET 0x51C
#define GPIO_LOCK_OFFSET 0x520
#define GPIO_CR_OFFSET 0x524
#define GPIO_AMSEL_OFFSET 0x528
#define GPIO_PCTL_OFFSET 0x52C
#define GPIO_ADCCTL_OFFSET 0x530
#define GPIO_DMACTL_OFFSET 0x534

#define GPIO_PERIPH_ID4_OFFSET 0xFD0
#define GPIO_PERIPH_ID5_OFFSET 0xFD4
#define GPIO_PERIPH_ID6_OFFSET 0xFD8
#define GPIO_PERIPH_ID7_OFFSET 0xFDC
#define GPIO_PERIPH_ID0_OFFSET 0xFE0
#define GPIO_PERIPH_ID1_OFFSET 0xFE4
#define GPIO_PERIPH_ID2_OFFSET 0xFE8
#define GPIO_PERIPH_ID3_OFFSET 0xFEC

/* SYSCTRL Registers */
#define SYSCTRL_BASE_ADDRESS 0x400FE000
#define SYSCTRL_RCGCGPIO_OFFSET 0x608
#define SYSCTRL_RCGCGPIO_ADDRESS                                               \
  *((volatile uint32 *)(SYSCTRL_BASE_ADDRESS + SYSCTRL_RCGCGPIO_OFFSET))

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/
#define GET_REG(Base, Offset) *((volatile uint32 *)(Base + Offset))

#endif /* TM4C_REGISTERS_H_ */