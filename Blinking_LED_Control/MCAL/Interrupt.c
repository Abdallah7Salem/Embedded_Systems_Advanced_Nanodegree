/*
 * Interrupt.c
 *
 * Created: 10/18/2022 1:16:52 PM
 *  Author: Abdallah
 */ 

/************************************************************************/
/* INCLUDES                                                                     */
/************************************************************************/
#include "Interrupt.h"
#include "Platform_Types.h"

/************************************************************************/
/* NVIC Macros                                                                     */
/************************************************************************/
#define NVIC_GROUPING_SYS_XXX 4
#define NVIC_GROUPING_SYS_XXY 5
#define NVIC_GROUPING_SYS_XYY 6
#define NVIC_GROUPING_SYS_YYY 7
#define APINT_VECTKEY 0x05FA


/************************************************************************/
/* NVIC Configuration                                                                     */
/************************************************************************/
const Nvic_CfgType NVIC_Cfg[NVIC_NUMBER_OF_ACTIVE_INT] = {
	{NVIC_DIO_PORT_F, 0, 1},
};

/************************************************************************/
/* NVIC Global Data                                                                     */
/************************************************************************/
extern const Nvic_CfgType NVIC_Cfg[NVIC_NUMBER_OF_ACTIVE_INT];


/************************************************************************/
/* NVIC APIs                                                                     */
/************************************************************************/           
void Nvic_Init(void) {
	uint32 interruptNumber, prio;
	uint8 groupPriority, subGroupPriority, i;
	/*Configure Grouping\SubGrouping System in APINT register in SCB*/
	APINT = (APINT_VECTKEY << 16) | (NVIC_GROUPING_SYS << 8);

	for (i = 0; i < NVIC_NUMBER_OF_ACTIVE_INT; i++) {
		interruptNumber = NVIC_Cfg[i].interruptNumber;
		groupPriority = NVIC_Cfg[i].groubPriority;
		subGroupPriority = NVIC_Cfg[i].subGroupPriority;
		/*Assign Group-Subgroup priority in NVIC_PRIx */
		#if NVIC_GROUPING_SYS == NVIC_GROUPING_SYS_XXX
		prio = groupPriority;
		#elif NVIC_GROUPING_SYS == NVIC_GROUPING_SYS_XXY
		prio = (groupPriority << 1) | subGroupPriority;
		#elif NVIC_GROUPING_SYS == NVIC_GROUPING_SYS_XYY
		prio = (groupPriority << 2) | subGroupPriority;
		#elif NVIC_GROUPING_SYS == NVIC_GROUPING_SYS_YYY
		prio = subGroupPriority;
		#endif
		GET_REG(NVIC_BASE_PRI_ADDRESS, (interruptNumber / 4)) |=
		(prio << ((interruptNumber % 4 * 8) + 5));

		/*Enable-Disable interrupts based on user configurations in NVIC_ENx */
		GET_REG(NVIC_BASE_EN_ADDRESS, (interruptNumber / 32) * 4) |=
		(1 << (interruptNumber % 32));
	}
}

         