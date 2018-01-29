/*************************************************************************************
* AUTO-GENERATED COMMENT - DO NOT MODIFY 
* Author: 
* File Type: TTCOS Main File
*************************************************************************************/

// This is an example TT_COS main( ) function with threads.
// Use this as a template for your own TT_COS main( ) for the various Threads

#include <uTTCOS2013/uTTCOS.h>

	
#define EXECUTE_EVERY_SECOND 		uTTCOS_GetTickFrequency( )

#include <stdio.h>

volatile int whichProgram = 0;

void Thread_SayHiOccasionally(void) {
	static int counter = 0;
	counter = (counter + 1) & 0xF;

	int value = counter + uTTCOS_ReadLED( ) & 0xF ;
	if (whichProgram == 1)
		uTTCOS_WriteLED(value);
	 else
		uTTCOS_WriteLED(counter);

	printf("Hi Occasionally  %d   %d\n", counter, value);
}

void Thread_SayHiOccasionally__withParameters(int pArg__fI) {
	static int counter = 0;
	counter = (counter + 1) & 0xF;
	
	int value = counter + uTTCOS_ReadLED( ) & 0xF ;
	if (whichProgram == 1)
		uTTCOS_WriteLED(value);
	 else
		uTTCOS_WriteLED(counter);
		
	for (int count = 0; count < pArg__fI; count++) {
		printf("Thread_SayHiOccasionally__withParameters -- note interaction   %d   %d  ", counter, value);
	}
	printf("\n");
}

void Thread_SayGreeting(void) {
	printf("Greetings from uTTCOS2013\n");
}

#include <stdio.h>

void main(void) {
	int maxNumberThreads = 10;   // Make at least 5 larger than the tasks you plan to add

	uTTCOS_Init( );	
	uTTCOS_InitLED( );
	uTTCOS_WriteLED(0);
	
	uTTCOS_InitSwitches( );

	whichProgram = uTTCOS_ReadSwitches( );
	printf("%d\n", whichProgram);
	
	whichProgram = uTTCOS_ReadSwitches( );
	printf("%d\n", whichProgram);
	
	
	whichProgram = uTTCOS_ReadSwitches( );
	printf("%d\n", whichProgram);

    uTTCOS_AddPreEmptiveThread(uTTCOS_AudioTalkThrough,  NO_DELAY, EVERY_TICK);
		
	uTTCOS_AddThread(Thread_SayGreeting, NO_DELAY, RUN_ONCE);
	uTTCOS_AddThread(Thread_SayHiOccasionally, NO_DELAY, EXECUTE_EVERY_SECOND);
	uTTCOS_AddThread__fI(Thread_SayHiOccasionally__withParameters, 2, NO_DELAY, 3 * EXECUTE_EVERY_SECOND);
	uTTCOS_AddThread__fI(Thread_SayHiOccasionally__withParameters, 3, NO_DELAY, 4 * EXECUTE_EVERY_SECOND);

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
