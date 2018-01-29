/*************************************************************************************
* AUTO-GENERATED COMMENT - DO NOT MODIFY 
* Author: %Username% 
* Date: %DateAndTime% 
* File Type: TTCOS Faulty Flash code File
*************************************************************************************/

// This is an example of uTTCOSg threads.


#include <uTTCOSg2017/uTTCOSg.h>
#include <GPIO2017/ADSP_GPIO_interface.h>
#include %ADSP_GPIO_Interface_H%

#include %faultyFlashLED_H%   // Should include links to other project header files

#warning "LED interface routines like this work on their own but not together -- fix"
// TODO  Fix INCORRECT_LED3_CODE
// Flash LED3
enum faulty_LED3_State {JUST_STARTED, IS_OFF, IS_ON};
	static LED3_State currentState = JUST_STARTED;
void Flash_LED3_StateMachinevoid) {
	faulty_LED3_State nextStateToDo = currentState;

	switch (currentState) {
	case JUST_STARTED:
		Write_LED_GPIOInterface(0); // Turn off LED 3
		nextStateToDo = IS_OFF;
		break;
	case IS_OFF:
		Write_LED_GPIOInterface(0x1 << (3 - 1));  // Was off turn it on
		nextStateToDo = IS_ON;
		break;
	case IS_ON:
		Write_LED_GPIOInterface(0); // Turn off LED 3
		nextStateToDo = IS_OFF;
	break;
	}

	currentState = nextStateToDo;
}

void Reset_LED3_StateMachine(void) {
     LED3_State currentState = JUST_STARTED;
}
