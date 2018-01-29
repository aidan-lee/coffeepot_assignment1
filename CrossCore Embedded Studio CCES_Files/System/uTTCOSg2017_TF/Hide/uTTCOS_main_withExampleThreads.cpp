/*************************************************************************************
* AUTO-GENERATED COMMENT - DO NOT MODIFY 
* Author: 
* File Type: TTCOS Main File
*************************************************************************************/

// This is an example TT_COS main( ) function with threads.
// Use this as a template for your own TT_COS main( ) for the various Threads

#include <uTTCOS2013/uTTCOS.h>

// This timing MACRO may need adjusting	
#define EXECUTE_EVERY_SECOND 		uTTCOS_GetTickFrequency( )

#include <stdio.h>

void Flash_LED1_If_Then_Else(void);
void Flash_LED3_StateMachinePoor(void);
void Flash_LED5_StateMachineClear(void);		// Prototype -- see code later

enum {USE_TIMER_OS = 1, USE_AUDIO_OS = 2, DEFAULT_OS = 2, INIT_BOTH_OS_USE_AUDIO_OS = 3};
extern int whichOS;

void main(void) {
	int maxNumberThreads = 10;   // Make at least 5 larger than the tasks you plan to add
	uTTCOS_Init( );
    uTTCOS_AddPreEmptiveThread(uTTCOS_AudioTalkThrough,  NO_DELAY, EVERY_TICK);

//  uTTCOS_InitLED();
//	uTTCOS_AddThread(Flash_LED1_If_Then_Else, NO_DELAY, EXECUTE_EVERY_SECOND);
//	uTTCOS_AddThread(Flash_LED3_StateMachinePoor, NO_DELAY, EXECUTE_EVERY_SECOND / 4);
//	uTTCOS_AddThread(Flash_LED5_StateMachineClear, NO_DELAY, EXECUTE_EVERY_SECOND);

	uTTCOS_Start_Scheduler(maxNumberThreads);
				// Execution time of TT_COS_Dispatch( ) and TT_COS_Update( ) improved by specifiying maxNumberTasks
	while (1) {

		// Wait, in low power mode, for an interrupt
		// The interrupt service routine calls TTCOS_Update( )
		uTTCOS_GoToSleep( );

		// Run all the threads in the system according
		// to whether their delays have expired
		uTTCOS_DispatchThreads( );
	}
}

void Flash_LED1_If_Then_Else(void) {
	static bool LED1_is_on = false;
	if (!LED1_is_on) {
		uTTCOS_WriteLED(0x1 << (1 - 1));  // Turn on LED 1
		LED1_is_on = true;
	}
	else {
		uTTCOS_WriteLED(0);  // Turn off LED 1
		LED1_is_on = false;
	}
}

enum LED3_State {JUST_STARTED, IS_OFF, IS_ON};

void Flash_LED3_StateMachinePoor(void) {
	static LED3_State currentState = JUST_STARTED;
	LED3_State nextStateToDo = currentState;

	switch (currentState) {
	case JUST_STARTED:
		uTTCOS_WriteLED(0); // Turn off LED 3
		nextStateToDo = IS_OFF;
		break;
	case IS_OFF:
		uTTCOS_WriteLED(0x1 << (3 - 1));  // Was off turn it on
		nextStateToDo = IS_ON;
		break;
	case IS_ON:
		uTTCOS_WriteLED(0); // Turn off LED 3
		nextStateToDo = IS_OFF;
	break;
	}

	currentState = nextStateToDo;
}

// Making some C++ extensions to handle "LED state machine"

#define BEGIN_STATE case
#define END_STATE break;
enum LED5_State {LED5_JUST_STARTED, LED5_IS_OFF, LED5_IS_ON, LED5_STAYS_ON};

void Flash_LED5_StateMachineClear(void) {
	static LED5_State currentState_LED5 = LED5_JUST_STARTED;
	LED5_State nextStateToDo = currentState_LED5;

	switch (currentState_LED5) {
	BEGIN_STATE LED5_JUST_STARTED:
		uTTCOS_WriteLED(0); 			 // Turn off LED 5
		nextStateToDo = LED5_IS_OFF;
	END_STATE
	
	BEGIN_STATE LED5_IS_OFF:
		uTTCOS_WriteLED(0x1 << (3 - 1));  // Was off turn it on
		nextStateToDo = LED5_IS_ON;
	END_STATE

	BEGIN_STATE LED5_IS_ON:
		nextStateToDo = LED5_STAYS_ON;		  // Just on -- keep on
	END_STATE

	BEGIN_STATE LED5_STAYS_ON:
		uTTCOS_WriteLED(0);  				// Was off turn it on
		nextStateToDo = LED5_IS_OFF;
	END_STATE
	}

	currentState_LED5 = nextStateToDo;
}

