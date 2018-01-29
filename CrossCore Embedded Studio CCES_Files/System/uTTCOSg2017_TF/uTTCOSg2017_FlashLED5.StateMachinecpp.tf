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
// TODO  Fix INCORRECT_LED5_CODE
// Flash LED5
enum faulty_LED5_State {JUST_STARTED, IS_OFF, IS_ON, IS_STILL_ON};
	static LED5_State currentState = JUST_STARTED;
	
#define BEGIN_STATE case
#define END_STATE break
	
void Flash_LED5_StateMachinevoid) {
	faulty_LED5_State nextStateToDo = currentState;

	switch (currentState) {
	BEGIN_STATE JUST_STARTED:
		Write_LED_GPIOInterface(0); // Turn off LED 5
		nextStateToDo = IS_OFF;
	END_STATE;
	BEGIN_STATE IS_OFF:
		Write_LED_GPIOInterface(0x1 << (5));  // Was off turn it on
		nextStateToDo = IS_ON;
	END_STATE;
	BEGIN_STATE IS_ON:
		Write_LED_GPIOInterface(0x1 << (5) ); // Keep LED 5 on
		nextStateToDo = IS_STILL_ON;
	END_STATE;
	BEGIN_STATE IS_STILL_ON:
	    Write_LED_GPIOInterface(0); // Turn LED 5 off
		nextStateToDo = IS_OFF;
	END_STATE;
	}

	currentState = nextStateToDo;
}

void Reset_LED5_StateMachine(void) {
     LED5_State currentState = JUST_STARTED;
}
