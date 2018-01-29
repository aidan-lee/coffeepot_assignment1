/*************************************************************************************
* AUTO-GENERATED COMMENT - DO NOT MODIFY 
* Author: %Username% 
* Date: %DateAndTime% 
* File Type: TTCOS Faulty Flash code File
*************************************************************************************/

// This is an example of uTTCOS threads.

#include <uTTCOS2015/uTTCOS2015.h>
#include %faultyFlashLED_H%   // Should include links to other project header files

#warning "Each of these routines work -- on their own but not together -- fix"
// Flash LED1
void Faulty_Flash_LED1_If_Then_Else(void) {
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

// Flash LED3
enum faulty_LED3_State {JUST_STARTED, IS_OFF, IS_ON};
void Faulty_Flash_LED3_StateMachinePoorExample(void) {
	static faulty_LED3_State currentState = JUST_STARTED;
	faulty_LED3_State nextStateToDo = currentState;

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

// Flash LED5
enum faulty_LED5_State {LED5_JUST_STARTED, LED5_IS_OFF, LED5_IS_ON, LED5_STAYS_ON};

void Faulty_Flash_LED5_StateMachineClearExample(void) {
	static faulty_LED5_State currentState_LED5 = LED5_JUST_STARTED;
	faulty_LED5_State nextStateToDo = currentState_LED5;

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













#define TO_UNDERSTAND TODO

// void Reset_Faulty_Flash_LED_StateMachines(void) {
// TO_UNDERSTAND 1) 
/       This function will play a key role in making Lab 0 / Assignment 1 test code to work
// }

//  TO_UNDERSTAND 2) 
//      Doing a redefine or understanding the way that uTTCOS_ReadLED( ) and uTTCOS_WriteLED( )
//      really operate will play a key role in making Lab 0 / Assignment 1 test code work
//               and in getting Lab 0 / Assignment 1 uTTCOS system to flash LEDs correctly

//  TO_UNDERSTAND 3)
//  currently we have
//  unsigned char uTTCOS_ReadLED(void)    and void uTTCOS_WriteLED(unsigned char value);
//      unsigned char LEDresult = uTTCOS_ReadLED();
//      and then do  CHECK_EQUAL(6, LEDresult);  to compare values

//  Why to do the CHECK_EQUAL macros give MORE understandable results if we used these functions
//        unsigned int myReadLED(void) {  (unsigned int) uTTCOS_ReadLED(); } 
//        void myWriteLED(unsigned int value) { uTTCOS_WriteLED( (unsigned char) (value & 0x3F)); }
//			unsigned int LEDresult = myReadLED( );
//			and do CHECK_EQUAL(6, LEDresult);    to compare values 

//  TO_UNDERSTAND 4
//  What does this approach to programming the LEDs make their operation more understandable?
//
//  #define BIT_PATTERN  unsigned int
//        BIT_PATTERN myReadLEDBitPattern(void) {  (BIT_PATTERN) uTTCOS_ReadLED(); } 
//        void myWriteLEDBitPattern(BIT_PATTERN value) { uTTCOS_WriteLED( (unsigned char) (value & 0x3F)); }
//		  BIT_PATTERN LEDresult = myReadLEDBitPattern( );
//		  CHECK_EQUAL(6, LEDresult);

//  TO_UNDERSTAND 5  -- A new test macro example  
//  #define CHECK_HEX_EQUAL(A_hexValue,B_hexValue) \
//  		if (A_hexValue != B_hexValue) \
//  			fprintf(stderr, "Today %s you made  0x%X != 0x%X at line 0x%X\n", \
//           		__DATE__, A_hexValue, B_hexValue, __LINE__)
 
 