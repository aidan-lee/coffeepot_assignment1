/*************************************************************************************
* AUTO-GENERATED COMMENT - DO NOT MODIFY 
* Author: %Username% 
* Date: %DateAndTime% 
* File Type: TTCOS Main File
*************************************************************************************/

// This is an example TT_COS main( ) function with threads.
// Use this as a template for your own TT_COS main( ) for the various Threads

#include <uTTCOS2013/uTTCOS.h>

// This timing MACRO may need adjusting	
#define EXECUTE_EVERY_SECOND 		uTTCOS_GetTickFrequency( )

#include <stdio.h>

void main(void) {
	int maxNumberThreads = 10;   // Make at least 5 larger than the tasks you plan to add
	uTTCOS_Init( );
    uTTCOS_AddPreEmptiveThread(uTTCOS_AudioTalkThrough,  NO_DELAY, EVERY_TICK);
		
	// uTTCOS_AddThread(Thread_SayGreeting, NO_DELAY, RUN_ONCE);
	// uTTCOS_AddThread__fI(Thread_SayHiOccasionally__withParameters, 2, NO_DELAY, 3 * EXECUTE_EVERY_SECOND);

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