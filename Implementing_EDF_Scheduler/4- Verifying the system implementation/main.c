/*
 * FreeRTOS Kernel V10.2.0
 * Copyright (C) 2019 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://www.FreeRTOS.org
 * http://aws.amazon.com/freertos
 *
 * 1 tab == 4 spaces!
 */

/* 
	NOTE : Tasks run in system mode and the scheduler runs in Supervisor mode.
	The processor MUST be in supervisor mode when vTaskStartScheduler is 
	called.  The demo applications included in the FreeRTOS.org download switch
	to supervisor mode prior to main being called.  If you are not using one of
	these demo application projects then ensure Supervisor mode is used.
*/


/*
 * Creates all the demo application tasks, then starts the scheduler.  The WEB
 * documentation provides more details of the demo application tasks.
 * 
 * Main.c also creates a task called "Check".  This only executes every three 
 * seconds but has the highest priority so is guaranteed to get processor time.  
 * Its main function is to check that all the other tasks are still operational.
 * Each task (other than the "flash" tasks) maintains a unique count that is 
 * incremented each time the task successfully completes its function.  Should 
 * any error occur within such a task the count is permanently halted.  The 
 * check task inspects the count of each task to ensure it has changed since
 * the last time the check task executed.  If all the count variables have 
 * changed all the tasks are still executing error free, and the check task
 * toggles the onboard LED.  Should any task contain an error at any time 
 * the LED toggle rate will change from 3 seconds to 500ms.
 *
 */

/* Standard includes. */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "lpc21xx.h"
#include "queue.h"

/* Peripheral includes. */
#include "serial.h"
#include "GPIO.h"

#define STACK_SIZE 100
#define XTAL 	12000000


/* prototype of xTaskPeriodicCreate */
BaseType_t xTaskPeriodicCreate( TaskFunction_t pxTaskCode,
                            const char * const pcName, /*lint !e971 Unqualified char types are allowed for strings and single characters only. */
                            const configSTACK_DEPTH_TYPE usStackDepth,
                            void * const pvParameters,
                            UBaseType_t uxPriority,
                            TaskHandle_t * const pxCreatedTask,
							TickType_t period );

/*-----------------------------------------------------------*/

/* Constants to setup I/O and processor. */
#define mainBUS_CLK_FULL	( ( unsigned char ) 0x01 )

/* Constants for the ComTest demo application tasks. */
#define mainCOM_TEST_BAUD_RATE	( ( unsigned long ) 115200 )


/*
 * Configure the processor for use with the Keil demo board.  This is very
 * minimal as most of the setup is managed by the settings in the project
 * file.
 */
static void prvSetupHardware( void );
/*-----------------------------------------------------------*/

#define TICK_PIN			PIN0

/* --------------- Execution Time Variables -------------- */
unsigned int Button1_inTime;
unsigned int Button2_inTime;
unsigned int Load1_inTime;
unsigned int Load2_inTime;
unsigned int Periodic_Tx_inTime;
unsigned int Uart_Rx_inTime;
unsigned int totalExecutionTime;
unsigned int cpuLoad;

/* --------------- Tasks' Handlers ----------------- */
BaseType_t xReturn;

TaskHandle_t Button1_Handler = NULL;
TaskHandle_t Button2_Handler = NULL;
TaskHandle_t Periodic_Tx_Handler = NULL;
TaskHandle_t Uart_Rx_Handler = NULL;
TaskHandle_t Load1_Handler = NULL;
TaskHandle_t Load2_Handler = NULL;


/* ------------- Queues' Handlers ----------------- */
QueueHandle_t Queue1 = NULL;
QueueHandle_t Queue2 = NULL;
QueueHandle_t Queue3 = NULL;

/* -------------- Prototypes ------------------ */
void Button_1_Monitor (void * pvParameters);
void Button_2_Monitor (void * pvParameters);
void Periodic_Transmitter (void * pvParameters);
void Uart_Receiver (void * pvParameters);
void Load_1_Simulation (void * pvParameters);
void Load_2_Simulation (void * pvParameters);
void vApplicationTickHook (void);
void vApplicationIdleHook (void);

/* ------------- Run Time Stats Buffer ------------ */
char RuntimeStatsBuffer[300];

/*
 * Application entry point:
 * Starts all the other tasks, then starts the scheduler. 
 */
int main( void )
{
	/* Setup the hardware for use with the Keil demo board. */
	prvSetupHardware();

	/* Creation of Queues */
	Queue1 = xQueueCreate(1, sizeof(char));
	Queue2 = xQueueCreate(1, sizeof(char));
	Queue3 = xQueueCreate(15, sizeof(char));
	
  /* Create Tasks here */
	
   xReturn = xTaskPeriodicCreate(
         Button_1_Monitor,        /* Function that implements the task. */
          "Button1",     					/* Text name for the task. */
           STACK_SIZE,      			        	/* Stack size in words, not bytes. */
           ( void * ) 0,         		/* Parameter passed into the task. */
           1,						            /* Priority at which the task is created. */
           &Button1_Handler		    /* Used to pass out the created task's handle. */
					 ,50);      				    /* Task Deadline */	
	
   xReturn = xTaskPeriodicCreate(
         Button_2_Monitor,        /* Function that implements the task. */
          "Button2",     					/* Text name for the task. */
           STACK_SIZE,      			        	/* Stack size in words, not bytes. */
           ( void * ) 0,         		/* Parameter passed into the task. */
           1,						            /* Priority at which the task is created. */
           &Button2_Handler		    /* Used to pass out the created task's handle. */
					 ,50);      				    /* Task Deadline */	
					 
   xReturn = xTaskPeriodicCreate(
					Uart_Receiver,        /* Function that implements the task. */
          "Uart_Rx",     					/* Text name for the task. */
           STACK_SIZE,      			        	/* Stack size in words, not bytes. */
           ( void * ) 0,         		/* Parameter passed into the task. */
           1,						            /* Priority at which the task is created. */
           &Uart_Rx_Handler		    /* Used to pass out the created task's handle. */
					 ,20);      				    /* Task Deadline */	
					 
   xReturn = xTaskPeriodicCreate(
         Periodic_Transmitter,        /* Function that implements the task. */
          "Tx",     					/* Text name for the task. */
           STACK_SIZE,      			        	/* Stack size in words, not bytes. */
           ( void * ) 0,         		/* Parameter passed into the task. */
           1,						            /* Priority at which the task is created. */
           &Periodic_Tx_Handler		    /* Used to pass out the created task's handle. */
					 ,100);      				    /* Task Deadline */		
					 
   xReturn = xTaskPeriodicCreate(
         Load_1_Simulation,        /* Function that implements the task. */
          "Load1",     					/* Text name for the task. */
           STACK_SIZE,      			        	/* Stack size in words, not bytes. */
           ( void * ) 0,         		/* Parameter passed into the task. */
           1,						            /* Priority at which the task is created. */
           &Load1_Handler		    /* Used to pass out the created task's handle. */
					 ,10);      				    /* Task Deadline */	
					 
   xReturn = xTaskPeriodicCreate(
         Load_2_Simulation,        /* Function that implements the task. */
          "Load2",     					/* Text name for the task. */
           STACK_SIZE,      			        	/* Stack size in words, not bytes. */
           ( void * ) 0,         		/* Parameter passed into the task. */
           1,						            /* Priority at which the task is created. */
           &Load1_Handler		    /* Used to pass out the created task's handle. */
					 ,100);      				    /* Task Deadline */	
					 
	


	/* Now all the tasks have been started - start the scheduler.

	NOTE : Tasks run in system mode and the scheduler runs in Supervisor mode.
	The processor MUST be in supervisor mode when vTaskStartScheduler is 
	called.  The demo applications included in the FreeRTOS.org download switch
	to supervisor mode prior to main being called.  If you are not using one of
	these demo application projects then ensure Supervisor mode is used here. */
	vTaskStartScheduler();

	/* Should never reach here!  If you do then there was not enough heap
	available for the idle task to be created. */
	for( ;; );
}
/*-----------------------------------------------------------*/


void vApplicationTickHook (void)
{
	GPIO_write(PORT_0 , TICK_PIN, PIN_IS_HIGH);
	GPIO_write(PORT_0 , TICK_PIN, PIN_IS_LOW);
}

/* -------------------- Tasks' body ------------------- */

/* Task 1 - Button 1 Monitor */

void Button_1_Monitor( void * pvParameters )
{
		pinState_t Button1_State;
		pinState_t previousState = GPIO_read(PORT_1, PIN0);
		TickType_t xLastWakeTime = xTaskGetTickCount();
		char edgeFlag = 0;
	
		
		for ( ; ; )
		{
				/* Read input of GPIO : port 1 --> pin 0 as configured in GPIO_Cfg.c*/
				Button1_State = GPIO_read(PORT_1, PIN0);
			
				
				/* Check for edges */
				if ((Button1_State == PIN_IS_HIGH) && (previousState == PIN_IS_LOW))	// this indicates rising edge 
				{
						edgeFlag = '+';		// A positive character representing rising edge
				}
				else if (Button1_State == PIN_IS_LOW && previousState == PIN_IS_HIGH)	// this indicate falling edge
				{
						edgeFlag = '-';		// A negative character representing falling edge
				}
				else
				{
						edgeFlag = '.';
				}
				
				/* Write data over the queue to send it */
				xQueueOverwrite(Queue1, &edgeFlag);
				
				/* Update the state of button 1 */
				previousState = Button1_State;
			
				/* Button1 Periodicity: 50 */
				vTaskDelayUntil(&xLastWakeTime, 50);
				
		}
}


/* Task 2 - Button 2 Monitor */

void Button_2_Monitor( void * pvParameters )
{
		pinState_t Button2_State;
		pinState_t previousState = GPIO_read( PORT_1, PIN1);
		TickType_t xLastWakeTime = xTaskGetTickCount();
		unsigned char edgeFlag = 0;
	
		
		for ( ; ; )
		{
				/* Read input of GPIO : port 1 --> pin 0 */
				Button2_State = GPIO_read(PORT_1, PIN1);
			
				
				/* Check for edges */
				if ((Button2_State == PIN_IS_HIGH) && (previousState == PIN_IS_LOW))	// this indicates rising edge 
				{
						edgeFlag = '+';		// A positive character representing rising edge
				}
				else if ((Button2_State == PIN_IS_LOW) && (previousState == PIN_IS_HIGH))	// this indicate falling edge
				{
						edgeFlag = '-';		// A negative character representing falling edge
				}
				else
				{
						edgeFlag = '.';
				}
				
				/* Write data over the queue to send it */
				xQueueOverwrite(Queue2, &edgeFlag);
				
				/* Update the state of button 1 */
				previousState = Button2_State;
			
				/* Button1 Periodicity: 50 */
				vTaskDelayUntil(&xLastWakeTime, 50);
				
		}
}


/* Task 3 - Periodic Transmitter */
void Periodic_Transmitter(void * pvParameters)
{
		TickType_t xLastWakeTime = xTaskGetTickCount();
		uint8_t i = 0;
		char pcString[15];
		strcpy(pcString, "\n100ms Marker.");
	
		/* Periodic transmitter will send the data to Uart Receiver through queue3 */
	
		for (; ;)
		{
				/* Send characters to Uart Receiver through Queue 3 */
				for (i = 0;  i < 15; i++)
				{
						xQueueSend(Queue3, pcString+i, 100);
				}
				
				/* Periodicity of Task3 = 100 */
				vTaskDelayUntil(&xLastWakeTime, 100);
		}
}

/* Task 4 - Uart Receiver */
void Uart_Receiver( void * pvParameters )
{
		TickType_t xLastWakeTime = xTaskGetTickCount();
		char Button1;
		char Button2;
		char rxString[15];
		uint8_t i = 0;
	
		/* Uart Receiver will receive the data from button1
		 * and button2 through queue1 and queue2 
		 */
	
		for (; ;)
		{
				/* Receive the state of Button 1 */
				if(xQueueReceive(Queue1, &Button1, 0) && Button1 != '.')
				{
						/* Transmit if rising/falling edge detected */
						xSerialPutChar('\n');
						xSerialPutChar('B');
						xSerialPutChar('1');
						xSerialPutChar(':');
						xSerialPutChar(Button1);
				}
				else
				{
						/* to keep the same execution time, we will send spaces */
						xSerialPutChar(' ');
						xSerialPutChar(' ');
						xSerialPutChar(' ');
						xSerialPutChar(' ');
						xSerialPutChar(' ');
				}
			
				/* Receive the state of Button 2 */
				if(xQueueReceive(Queue2, &Button2, 0) && Button2 != '.')
				{
						/* transmit if rising/falling edge detected */
						xSerialPutChar('\n');
						xSerialPutChar('B');
						xSerialPutChar('2');
						xSerialPutChar(':');
						xSerialPutChar(Button2);
				}
				else
				{
						/* to keep the same execution time, we will send spaces */
						xSerialPutChar(' ');
						xSerialPutChar(' ');
						xSerialPutChar(' ');
						xSerialPutChar(' ');
						xSerialPutChar(' ');
				}
				
				
				/* Receive the string from Periodic Transmitter through queue3 */
				if (uxQueueMessagesWaiting(Queue3) != 0)
				{
						for (i = 0; i < 15; i++)
						{
								xQueueReceive(Queue3, rxString+i, 0);
						}
						vSerialPutString( (signed char*)rxString, strlen(rxString));
						xQueueReset(Queue3);
					
				}
				
				
				/* Uart Receiver Periodicity: 20 */
				xTaskDelayUntil(&xLastWakeTime, 20);
				
		}
	
}

/* Load 1 Simulation Task */
void Load_1_Simulation (void * pvParameters)
{
		TickType_t xLastWakeTime = xTaskGetTickCount();
		uint32_t i = 0;
		uint32_t x = (XTAL/1000) * 5;
	
		for(; ;)
		{
				/* Delay for 5 milliseconds */
				for(i = 0; i <= x; i++)
				{
				
				}
			
				/* Load 1 Simulation Task Periodicity: 10 */
				vTaskDelayUntil(&xLastWakeTime, 10);
		}
	
}

/* Load 2 Simulation Task */
void Load_2_Simulation (void * pvParameters)
{
		TickType_t xLastWakeTime = xTaskGetTickCount();
		uint32_t i = 0;
		uint32_t x = (XTAL/1000) * 12;
	
		for(; ;)
		{
				/* delay for 12 milliseconds */
				for(i = 0; i <= x; i++)
				{
				
				}
					
				/* Load 2 Simulation Task Periodicity: 100 */
				vTaskDelayUntil(&xLastWakeTime, 100);	
		}
}




/* Function to reset timer 1 */
void timer1Reset(void)
{
	T1TCR |= 0x2;
	T1TCR &= ~0x2;
}

/* Function to initialize and start timer 1 */
static void configTimer1(void)
{
	T1PR = 1000;
	T1TCR |= 0x1;
}

static void prvSetupHardware( void )
{
	/* Perform the hardware setup required.  This is minimal as most of the
	setup is managed by the settings in the project file. */

	/* Configure UART */
	xSerialPortInitMinimal(mainCOM_TEST_BAUD_RATE);

	/* Configure GPIO */
	GPIO_init();
	
	/* Config trace timer 1 and read T1TC to get current tick */
	configTimer1();

	/* Setup the peripheral bus to be the same as the PLL output. */
	VPBDIV = mainBUS_CLK_FULL;
}
/*-----------------------------------------------------------*/


