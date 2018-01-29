/*************************************************************************************
* AUTO-GENERATED COMMENT - DO NOT MODIFY 
* Author: %Username% 
* Date: %DateAndTime% 
* File Type: TTCOS Main File
*************************************************************************************/

// This is an example TT_COS main( ) function with threads.
// Use this as a template for your own TT_COS main( ) for the various Threads

#include %IncludeMain_H%

// #include %faultyFlashLED_H% -- Not needed as included in %IncludeMain_H%

// This timing MACRO may need adjusting	
#undef  EXECUTE_EVERY_SECOND
// #define EXECUTE_EVERY_SECOND 		uTTCOSg_GetTickFrequency( )
#define EXECUTE_EVERY_SECOND 		(5 * uTTCOSg_GetTickFrequency( )) // ADJUST ME


#include <stdio.h>

enum {USE_TIMER_OS = 1, USE_AUDIO_OS = 2, DEFAULT_OS = 2, INIT_BOTH_OS_USE_AUDIO_OS = 3};
extern int whichOS;

#if defined(__ADSPBF533__)
#warning  "Read class notes on why the next line is an error"
void BlackfinBF533_uTTCOSg_Audio_Rx_Tx_Task(void); 
#elif defined(__ADSP21469__)
extern "C" void SHARC21469_uTTCOSg_Audio_Rx_Tx_Task(void);
#else
	#error "Unknown processor in Audio thread"
#endif	

#warning "Fix these TODO's, then delete warning and TODO lines	
	// TODO  The call to uTTCOSg_AudioTalkThrough will cause a link error because of a missing file
	// TODO  You will need to add the file "BlackfinBF533_uTTCOSg_AudioPremptive_Task.cpp" 
	// TODO      to the project src directory. This file can be found in 
	// TODO            "C:\__CCES\AudioCapture_Files\"
	
	// TODO  The calls to uTTCOSg and GPIO functions will cause link errors until you add their libraries into the project
	// TODO       To add these libraries -- Right click on project name, select Properties, Setting, Library
	// TODO           Select "Add Library" then "Workspace"
	// TODO           "File libraries can be found at "C:\__CCES\Libraries\"
	
void main(void) {
	// Make maxNumberThreads at least 5 larger than the 
	//            number of threads you plan to add
	int numBackgroundThreads = 5;
	int numberYourThreads = 4;
	int maxNumberThreads = numBackgroundThreads + numberYourThreads;  

#if defined(__ADSPBF533__)
#if 1
	uTTCOSg_OS_Init(USE_AUDIO_INTERRUPT, 0, 44000);
//	uTTCOSg_AddPreEmptiveThread(BlackfinBF533_uTTCOSg_Audio_Rx_Tx_Task, NO_DELAY, EVERY_TICK);
#else
	uTTCOSg_OS_Init(USE_TIMER_INTERRUPT, 1000, 0);
#endif
#elif defined(__ADSP21469__)
	uTTCOSg_OS_Init(USE_AUDIO_INTERRUPT, 0, 44000);	// This changes LED pattern to 0xF8 for some reason
//	uTTCOSg_AddPreEmptiveThread(SHARC21469_uTTCOSg_Audio_Rx_Tx_Task, NO_DELAY, EVERY_TICK);
#else
	#error "Unknown processor in OS_Init"
#endif	

//  Init_LED_GPIOInterface();

// Add calls to activate I/O Threads to flash LEDs.  These I/O threads have NOT been coded correctly
// Test the calls one at a time -- then all together to this effect
//	uTTCOSg_AddThread(Faulty_Flash_LED1_If_Then_Else, NO_DELAY, EXECUTE_EVERY_SECOND);
//	uTTCOSg_AddThread(Faulty_Flash_LED3_StateMachinePoorExample, NO_DELAY, EXECUTE_EVERY_SECOND / 4);
//	uTTCOSg_AddThread(Faulty_Flash_LED5_StateMachineClearExample, NO_DELAY, EXECUTE_EVERY_SECOND);

// When you have fixed the code -- run these threads instead
//	uTTCOSg_AddThread(Bitwise_Flash_LED1_If_Then_Else, NO_DELAY, EXECUTE_EVERY_SECOND);
//	uTTCOSg_AddThread(Bitwise_Flash_LED3_StateMachinePoorExample, NO_DELAY, EXECUTE_EVERY_SECOND / 4);
//	uTTCOSg_AddThread(Bitwise_Flash_LED5_StateMachineClearExample, NO_DELAY, EXECUTE_EVERY_SECOND);

	uTTCOSg_Start_Scheduler(maxNumberThreads);   //  Start the scheduler timer
				// Execution time of TT_COS_Dispatch( ) and TT_COS_Update( ) improved by specifiying maxNumberTasks
	while (1) {

		// Wait, in low power mode, for an interrupt
		// The interrupt service routine calls TTCOS_Update( )
		uTTCOSg_GoToSleep( );

		// Run all the threads in the system according
		// to whether their delays have expired
		uTTCOSg_DispatchThreads( );
	}
}

#warning "Remember to fix these TODO's, then delete warning and TODO lines	

