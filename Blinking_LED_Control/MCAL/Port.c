/*
 * Port.c
 *
 * Created: 11/4/2022 12:40:30 AM
 *  Author: Abdallah
 */ 

/************************************************************************/
/* INCLUDES                                                                     */
/************************************************************************/
#include "Port.h"
#include "TM4C_Registers.h"

/************************************************************************/
/* Port Configuration                                                                     */
/************************************************************************/
const Port_ConfigType Port_Config[PORT_NUMBER_OF_USED_CHANNELS] = {
    /*
        pinID,
        pinDirection,
        pinMode,
        pinInternalAttach
        pinOutputCurrent
        pinExternalInterrupt
    */
    {
        PORT_PIN_F1,
        PORT_PIN_OUTPUT,
        PORT_PIN_A0_MODE_DIO,
        PORT_ATTACH_NOTHING,
        PORT_PIN_OUTPUT_CURRENT_2MA,
        PORT_EXTI_DISABLE,

    }

};

#define NUMBER_OF_CHANNELS_PER_PORT 8u

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
extern const Port_ConfigType Port_Config[PORT_NUMBER_OF_USED_CHANNELS];

/**********************************************************************************************************************
 *  LOCAL DATA
 *********************************************************************************************************************/
static const uint32 gpioDataPorts[] = {
    GPIO_PORT_A_BASE_ADDRESS, GPIO_PORT_B_BASE_ADDRESS,
    GPIO_PORT_C_BASE_ADDRESS, GPIO_PORT_D_BASE_ADDRESS,
    GPIO_PORT_E_BASE_ADDRESS, GPIO_PORT_F_BASE_ADDRESS,
};

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/

/******************************************************************************
 * \Syntax          : void Port_Init(void)
 * \Description     : Initialization of Gpio Ports.
 *
 * \Sync\Async      : Synchronous
 * \Reentrancy      : Non Reentrant
 * \Parameters (in) : None
 * \Parameters (out): None
 * \Return value:   : void
 *******************************************************************************/
void Port_Init(void) {
  uint32 portIndex, pinIndex, portAddress, gpioPortBaseAdress;
  for (int i = 0; i < PORT_NUMBER_OF_USED_CHANNELS; i++) {
    portIndex = Port_Config[i].pinId / NUMBER_OF_CHANNELS_PER_PORT;
    pinIndex = Port_Config[i].pinId % NUMBER_OF_CHANNELS_PER_PORT;
    gpioPortBaseAdress = gpioDataPorts[portIndex];
    /* Enable the clock for the Port */
    SYSCTRL_RCGCGPIO_ADDRESS |= (1 << portIndex);

    /* Pin Direction */
    GET_REG(gpioPortBaseAdress, GPIO_DIR_OFFSET) |=
        (Port_Config[i].pinDirection << pinIndex);

    /* Pin Mode */
    if (Port_Config[i].pinMode % 16 == 0) {
      GET_REG(gpioPortBaseAdress, GPIO_AFSEL_OFFSET) &= ~(1 << pinIndex);

    } else {
      GET_REG(gpioPortBaseAdress, GPIO_AFSEL_OFFSET) |= (1 << pinIndex);
      GET_REG(gpioPortBaseAdress, GPIO_PCTL_OFFSET) |=
          (Port_Config[i].pinMode % 16 << pinIndex * 4);
    }

    /* Pin Output Current */
    if (Port_Config[i].pinOutputCurrent == PORT_PIN_OUTPUT_CURRENT_2MA) {
      GET_REG(gpioPortBaseAdress, GPIO_DR2R_OFFSET) |= (1 << pinIndex);
    } else if (Port_Config[i].pinOutputCurrent == PORT_PIN_OUTPUT_CURRENT_4MA) {
      GET_REG(gpioPortBaseAdress, GPIO_DR4R_OFFSET) |= (1 << pinIndex);
    } else if (Port_Config[i].pinOutputCurrent == PORT_PIN_OUTPUT_CURRENT_8MA) {
      GET_REG(gpioPortBaseAdress, GPIO_DR8R_OFFSET) |= (1 << pinIndex);
    }

    /* Pin Internal Attach */
    if (Port_Config[i].pinInternalAttach == PORT_ATTACH_PULLUP) {
      GET_REG(gpioPortBaseAdress, GPIO_PUR_OFFSET) |= (1 << pinIndex);
    } else if (Port_Config[i].pinInternalAttach == PORT_ATTACH_PULLDOWN) {
      GET_REG(gpioPortBaseAdress, GPIO_PDR_OFFSET) |= (1 << pinIndex);
    } else if (Port_Config[i].pinInternalAttach == PORT_ATTACH_OPENDRAIN) {
      GET_REG(gpioPortBaseAdress, GPIO_ODR_OFFSET) |= (1 << pinIndex);
    }

    /* TODO: Handle the case of analog modes (AMSEL) */
    /* Enable Digita I/O */
    GET_REG(gpioPortBaseAdress, GPIO_DEN_OFFSET) |= (1 << pinIndex);

    /* Interrupt Control */
    if (Port_Config[i].pinExternalInterrupt == PORT_EXTI_DISABLE) {
      GET_REG(gpioPortBaseAdress, GPIO_IM_OFFSET) &= ~(1 << pinIndex);
    } else {
      GET_REG(gpioPortBaseAdress, GPIO_IM_OFFSET) |= (1 << pinIndex);
      if (Port_Config[i].pinExternalInterrupt == PORT_EXTI_RISING_EDGE) {
        GET_REG(gpioPortBaseAdress, GPIO_IM_OFFSET) |= (1 << pinIndex);

      } else if (Port_Config[i].pinExternalInterrupt ==
                 PORT_EXTI_FALLING_EDGE) {
        GET_REG(gpioPortBaseAdress, GPIO_IM_OFFSET) &= ~(1 << pinIndex);

      } else if (Port_Config[i].pinExternalInterrupt == PORT_EXTI_BOTH_EDGES) {
        GET_REG(gpioPortBaseAdress, GPIO_IBE_OFFSET) |= (1 << pinIndex);
      }
    }
  }
}
