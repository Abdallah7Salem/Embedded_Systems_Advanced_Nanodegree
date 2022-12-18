/*
 * Gpio.h
 *
 * Created: 10/18/2022 1:16:15 PM
 *  Author: Abdallah
 */ 


#ifndef GPIO_H_
#define GPIO_H_

/************************************************************************/
/* INCLUDES                                                                     */
/************************************************************************/
#include "Platform_Types.h"

/************************************************************************/
/* MACROS                                                                     */
/************************************************************************/
#define GPIO_LEVEL_LOW	0u
#define GPIO_LEVEL_HIGH	1u

/************************************************************************/
/* Clock Control for all GPIO Ports                                                                     */
/************************************************************************/
typedef enum
{
	PortA_RCGCGPIO = 0b000001,
	PortB_RCGCGPIO = 0b000010,
	PortC_RCGCGPIO = 0b000100,
	PortD_RCGCGPIO = 0b001000,
	PortE_RCGCGPIO = 0b010000,
	PortF_RCGCGPIO = 0b100000,
}RCGCGPIO;


/************************************************************************/
/* GPIO Channels                                                                     */
/************************************************************************/
#define PIN0		0u
#define PIN1		1u
#define PIN2		2u
#define PIN3		3u
#define PIN4		4u
#define PIN5		5u
#define PIN6		6u
#define PIN7		7u 

/************************************************************************/
/* GPIO Ports                                                                     */
/************************************************************************/
#define Port_A		0u
#define Port_B		1u
#define Port_C		2u
#define Port_D		3u
#define Port_E		4u
#define Port_F		5u

/************************************************************************/
/* GPIO Pin Modes                                                                     */
/************************************************************************/
#define NORMAL_MODE		0u
#define ALTERNATIVE_MODE	1u

/************************************************************************/
/* GPIO Pin Directions                                                                     */
/************************************************************************/
#define INPUT		0u
#define OUTPUT		1u

/************************************************************************/
/* GPIO Pin Levels                                                                     */
/************************************************************************/
#define LOW		0u
#define HIGH	1u

/************************************************************************/
/* GPIO Pin Internal Attaches                                                                     */
/************************************************************************/
#define PULL_UP_RESISTOR		0u
#define PULL_DOWN_RESISTOR		1u
#define OPEN_DRAIN				2u

/************************************************************************/
/* GPIO Pin's Configuration Struct                                                                     */
/************************************************************************/
typedef struct
{
	uint8_t GPIO_Port;
	uint8_t GPIO_PinNumber;
	uint8_t GPIO_PinDirection;
}GPIO_PinConfig;

/************************************************************************/
/* GPIO Channels Enum                                                                     */
/************************************************************************/
typedef enum {
	GPIO_Channel_F0 = 40,
	GPIO_Channel_F1,
	GPIO_Channel_F2,
	GPIO_Channel_F3,
	GPIO_Channel_F4,
}Gpio_ChannelType;

typedef uint8_t Gpio_LevelType;

/************************************************************************/
/* GPIO APIs                                                                     */
/************************************************************************/
void GPIO_PinInit(GPIO_PinConfig* GPIO_PinCfg);
void Gpio_WriteChannel(Gpio_ChannelType channelId, Gpio_LevelType level);
void GPIO_PinWrite(GPIO_PinConfig* GPIO_PinCfg, uint8_t State);
Gpio_LevelType Gpio_ReadChannel(Gpio_ChannelType channelId);


#endif /* GPIO_H_ */