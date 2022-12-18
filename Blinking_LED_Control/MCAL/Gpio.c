/*
 * Gpio.c
 *
 * Created: 10/18/2022 1:16:03 PM
 *  Author: Abdallah
 */ 

/************************************************************************/
/* Includes                                                                     */
/************************************************************************/
#include "TM4C_Registers.h"
#include "Common_Macros.h"
#include "Typedefs.h"
#include "Platform_Types.h"
#include "Gpio.h"

/************************************************************************/
/* MACROS                                                                     */
/************************************************************************/
#define NUMBER_OF_CHANNELS_PER_PORT 8u
#define BAND_REGION_START 0x40000000
#define BAND_ALIAS_REGION_START 0x42000000
#define BIT_BANDING 1

/************************************************************************/
/* Global Data                                                                     */
/************************************************************************/
static const uint32 gpioDataPorts[] = {
	GPIO_PORT_A_BASE_ADDRESS, GPIO_PORT_B_BASE_ADDRESS,
	GPIO_PORT_C_BASE_ADDRESS, GPIO_PORT_D_BASE_ADDRESS,
	GPIO_PORT_E_BASE_ADDRESS, GPIO_PORT_F_BASE_ADDRESS,
};

/************************************************************************/
/* GPIO APIs                                                                     */
/************************************************************************/

/*
 * I will use just port F in my project 
 * so I didn't implement the code for other ports
 */
void GPIO_PinInit(GPIO_PinConfig* GPIO_PinCfg)
{
	if (GPIO_PinCfg->GPIO_Port == Port_A)
	{
		
	}
	else if (GPIO_PinCfg->GPIO_Port == Port_B)
	{
		
	}
	else if (GPIO_PinCfg->GPIO_Port == Port_C)
	{
		
	}
	else if (GPIO_PinCfg->GPIO_Port == Port_D)
	{
		
	}
	else if (GPIO_PinCfg->GPIO_Port == Port_E)
	{
		
	}
	else if (GPIO_PinCfg->GPIO_Port == Port_F)
	{
		/* Enable Clock for Port F */
		SYSCTL_RCGC2GPIO_R |= (1<<5);
		
		/* Ensure that clock is enables */
		while ((SYSCTL_RCGC2GPIO_R & (1<<5)) == 0)
		;
		
		/* Unlock GPIO Port F because it has some unlocked pins */
		 GPIO_PORTF_LOCK_R = 0x4C4F434B;
		 
		/* Allow changes to all port pins */
		GPIO_PORTF_CR_R = 0xFF;
		
		/* Disable Alternative Function of Port F */
		GPIO_PORTF_AFSEL_R = 0x00;
		
		/* Enable Digital Input/Output on all Port F pins */
		GPIO_PORTF_DEN_R = 0xFF;
		
		
		if (GPIO_PinCfg->GPIO_PinDirection == OUTPUT)
		{
			SET_BIT(GPIO_PORTF_DIR_R, GPIO_PinCfg->GPIO_PinNumber);
		}
		else if (GPIO_PinCfg->GPIO_PinDirection == INPUT)
		{
			CLEAR_BIT(GPIO_PORTF_DIR_R, GPIO_PinCfg->GPIO_PinNumber);
		}
	}
}

void Gpio_WriteChannel(Gpio_ChannelType channelId, Gpio_LevelType level) {
	uint32 pinIndex, portIndex, dataPortMaskAdd;
	portIndex = channelId / NUMBER_OF_CHANNELS_PER_PORT;
	pinIndex = channelId % NUMBER_OF_CHANNELS_PER_PORT;
	#if BIT_BANDING == 1
	uint32 bitWordOffset, byteOffset, bitNumber, bitWordAddress;
	byteOffset = gpioDataPorts[portIndex] + 0x3FC - BAND_REGION_START;
	bitNumber = pinIndex;
	bitWordOffset = (byteOffset * 32) + (bitNumber * 4);
	GET_REG(BAND_ALIAS_REGION_START, bitWordOffset) = level;
	#else
	dataPortMaskAdd = ((1 << pinIndex) << 2);
	GET_REG(gpioDataPorts[portIndex], GPIO_DATA_OFFSET + dataPortMaskAdd) =
	level << pinIndex;
	#endif
}

void GPIO_PinWrite(GPIO_PinConfig* GPIO_PinCfg, uint8_t State)
{
	if (GPIO_PinCfg->GPIO_Port == Port_A)
	{
		
	}
	else if (GPIO_PinCfg->GPIO_Port == Port_B)
	{
		
	}
	else if (GPIO_PinCfg->GPIO_Port == Port_C)
	{
		
	}
	else if (GPIO_PinCfg->GPIO_Port == Port_D)
	{
		
	}
	else if (GPIO_PinCfg->GPIO_Port == Port_E)
	{
		
	}
	else if (GPIO_PinCfg->GPIO_Port == Port_F)
	{
		if (State == HIGH)
		{
			SET_BIT(GPIO_PORTF_DATA_R, GPIO_PinCfg->GPIO_PinNumber);
		}
		else if (State == LOW)
		{
			CLEAR_BIT(GPIO_PORTF_DATA_R, GPIO_PinCfg->GPIO_PinNumber);
		}
	}
}

uint8_t Gpio_ReadChannel(Gpio_ChannelType channelId) {
	uint32 pinIndex, portIndex, dataPortMaskAdd, gpioDataPortAddress;
	Gpio_LevelType level;
	portIndex = channelId / NUMBER_OF_CHANNELS_PER_PORT;
	pinIndex = channelId % NUMBER_OF_CHANNELS_PER_PORT;
	#if BIT_BANDING == 1
	uint32 bitWordOffset, byteOffset, bitNumber, bitWordAddress;
	byteOffset = gpioDataPorts[portIndex] + 0x3FC - BAND_REGION_START;
	bitNumber = pinIndex;
	bitWordOffset = (byteOffset * 32) + (bitNumber * 4);
	level = GET_REG(BAND_ALIAS_REGION_START, bitWordOffset) & 1;

	#else
	gpioDataPortAddress = gpioDataPorts[portIndex];
	dataPortMaskAdd = ((1 << pinIndex) << 2);
	level = GET_REG(gpioDataPortAddress, GPIO_DATA_OFFSET + dataPortMaskAdd) >>
	pinIndex;
	#endif
	return level;
}
