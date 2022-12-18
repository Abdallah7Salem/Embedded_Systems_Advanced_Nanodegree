/*
 * Blinking_LED_Control.c
 *
 * Created: 10/18/2022 1:13:43 PM
 * Author : Abdallah
 */ 

#include "../Service/Typedefs.h"
#include "../Service/TM4C_Registers.h"
#include "../Service/Platform_Types.h"
#include "../Service/Common_Macros.h"
#include "../MCAL/Includes/Gpio.h"
#include "../MCAL/Includes/Gpt.h"
#include "../MCAL//Includes/Interrupt.h"
#include "../MCAL/Includes/SysTick.h"
#include "../MCAL/Includes/Port.h"

/************************************************************************/
/* Global Data                                                                     */
/************************************************************************/
static int onTimeInSeconds = 0;
static int offTimeInSeconds = 0;
static int numberOfPresses = 0;
static int getInput = 1;

/************************************************************************/
/* Prototypes                                                                    */
/************************************************************************/
void sysTickISR(void);

int main(void)
{
	/* Enable Clock for Port F */
	SYSCTL_RCGC2GPIO_R |= (1<<5);
	
	/* Ensure that clock is enables */
	while ((SYSCTL_RCGC2GPIO_R & (1<<5)) == 0);
	
	Port_Init();
	
	SysTick_SetISRCallBack(sysTickISR);
	
	
	while(1)
	{
		if (getInput)
		{
			if(!Gpio_ReadChannel(GPIO_Channel_F0))
			{
				while(!Gpio_ReadChannel(GPIO_Channel_F0));
				
				if (numberOfPresses < 2)
				{
					numberOfPresses += 1;
				}
				else
				{
					getInput = 0;
					SysTick_SetDuration(onTimeInSeconds, offTimeInSeconds);
					SysTick_Init();
				}
			}
			
			if(!Gpio_ReadChannel(GPIO_Channel_F4))
			{
				while(!Gpio_ReadChannel(GPIO_Channel_F4));
				
					if(numberOfPresses == 1)
					{
						onTimeInSeconds += 1;
					}
					else if(numberOfPresses == 2)
					{
						offTimeInSeconds += 1;
					}
				
			}
		}
	}
	
	
	
}

void sysTickISR(void) {
	static uint32 isrCount = 0;
	static uint32 currentLedState = 0;
	isrCount++;
	if (isrCount > numberOfOverFlows) {
		if (currentLedState == 1) {
			currentLedState = 0;
			Gpio_WriteChannel(GPIO_Channel_F1, GPIO_LEVEL_LOW);
			numberOfOverFlows = offNumberOfOverFlows;
			} else {
			currentLedState = 1;
			Gpio_WriteChannel(GPIO_Channel_F1, GPIO_LEVEL_HIGH);
			numberOfOverFlows = onNumberOfOverFlows;
		}
		isrCount = 0;
	}
}


