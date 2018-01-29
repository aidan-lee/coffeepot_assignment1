#ifndef uTTCOS_H
#define uTTCOS_H

// #define __ARM__

#if 0
	#ifndef BOOL
	  #define BOOL // An issue with the ARM compiler
	  typedef enum {FALSE = 0, TRUE = 1} bool;  
	#endif
#else
	#define FALSE 0
	#define TRUE !FALSE
	#define __CPP__
#endif



// TTCOS Function prototypes
//-------------------------------------------------------------------
#ifdef __CPP__
  extern "C" void uTTCOS_Init(void);
  extern "C" void uTTCOS_Start_Scheduler(int numberThreads);
  extern "C" void uTTCOS_Update(void);
  extern "C" void uTTCOS_DispatchThreads(void);
  extern "C" void uTTCOS_GoToSleep(void);
  
  extern "C" int uTTCOS_maxTasksPermitted(void);
  extern "C" void uTTCOS_ReportError(const unsigned int error);
  extern "C" unsigned int TTCOS_LastError(void);
  
  extern "C" unsigned int uTTCOS_AddThread(void (*)(void), const unsigned int , const unsigned int );
  extern "C" unsigned int uTTCOS_AddPreEmptiveThread(void (*)(void), const unsigned int, const unsigned int);
  extern "C" void         uTTCOS_AudioTalkThrough(void);

  extern "C" unsigned int uTTCOS_AddThread__pV(void (*)(void *), void *, const unsigned int , const unsigned int );
  extern "C" unsigned int uTTCOS_AddPreEmptiveThread__pV(void (*)(void *), void *, const unsigned int, const unsigned int);

  extern "C" unsigned int uTTCOS_AddThread__fI(void (*)(int), int, const unsigned int , const unsigned int );
  extern "C" unsigned int uTTCOS_AddPreEmptiveThread__fI(void (*)(int), int, const unsigned int, const unsigned int);

  extern "C" unsigned int uTTCOS_DeleteThread(const unsigned int threadID);
  extern "C" unsigned int uTTCOS_GetTickFrequency(void);
  
  extern "C" void	  	  uTTCOS_InitLED(void);
  extern "C" unsigned int uTTCOS_ReadLED(void);
  extern "C" void	  	  uTTCOS_WriteLED(unsigned int LEDvalue);
  
  extern "C" void	      uTTCOS_InitSwitches(void);
  extern "C" unsigned int uTTCOS_ReadSwitches(void);
  
  extern "C" void uTTCOS_InitializeSystemWatchDogTimer(void);
  extern "C" void uTTCOS_StartSystemWatchDogTimer(void);
  extern "C" void uTTCOS_FeedSystemWatchDogTimer(void);
#else   // C interface
  void uTTCOS_Init(void);
  void uTTCOS_Start_Scheduler(int numberThreads);
  void uTTCOS_Update(void);
  void uTTCOS_DispatchThreads(void);
  void uTTCOS_GoToSleep(void);
  
  int uTTCOS_maxTasksPermitted(void);
  void uTTCOS_ReportError(const unsigned int error);
  unsigned int TTCOS_LastError(void);
  
  unsigned int uTTCOS_AddThread(void (*)(void), const unsigned int , const unsigned int );
  unsigned int uTTCOS_AddPreEmptiveThread(void (*)(void), const unsigned int, const unsigned int);
  void         uTTCOS_AudioTalkThrough(void);

  unsigned int uTTCOS_AddThread__pV(void (*)(void *), void *, const unsigned int , const unsigned int );
  unsigned int uTTCOS_AddPreEmptiveThread__pV(void (*)(void *), void *, const unsigned int, const unsigned int);

  unsigned int uTTCOS_AddThread__fI(void (*)(int), int const unsigned int , const unsigned int );
  unsigned int uTTCOS_AddPreEmptiveThread__fI(void (*)(int), int, const unsigned int, const unsigned int);

  unsigned int uTTCOS_DeleteThread(const unsigned int threadID);
  
  void         uTTCOS_AudioTalkThrough(void);
  unsigned int uTTCOS_GetTickFrequency(void);
  
  void	        uTTCOS_InitLED(void);
  unsigned int	uTTCOS_ReadLED(void);
  void          uTTCOS_WriteLED(unsigned int LEDvalue);
  
  void          uTTCOS_InitSwitches(void);
  unsigned int	uTTCOS_ReadSwitches(void);
  
  void uTTCOS_InitializeSystemWatchDogTimer(void);
  void uTTCOS_StartSystemWatchDogTimer(void);
  void uTTCOS_FeedSystemWatchDogTimer(void);
#endif

#define UART_DELAY 10000

// TODO "UART prototypes currently excluded from uTTCOS.h"
#if 0
#ifdef __CPP__  // Only useful if system has a UART interface
  void UART_Init(void);
  void UART_WriteChar(void);
  void UART_CheckForCommand(void);
  void UART_DPIInit(void);		//makes UART0 signal connections to DPI pins
  void UART_Printf(int thisLine, char format[ ], char thisString[ ]);
  void UART_Printf(int thisLine, char format[ ], int thisInt);
  void UART_Printf(int thisLine, char format[ ], float thisFloat);
  void UART_Printf(int thisLine, char format[ ], float beginBand, float endBand, float MaxValue);
  void UART_Puts(int whichMessage);
  void UART_WriteLineToScreen(void); 
#endif																						 
#endif

// Universal constants used in TTCOS
#define NO_DELAY      0
#define RUN_ONCE      0
#define EVERY_TICK    1
#define ONE_TICK      1
  
#define TICK_FREQUENCY	uTTCOS_GetTickFrequency( )
  
#define SHORT_DELAY             ONE_TICK
#define DELAY_ONE_SECOND        uTTCOS_GetTickFrequency( )
#define EXECUTE_EVERY_SECOND    uTTCOS_GetTickFrequency( )

#define uTTCOS_MAX_THREADS_ALLOWED	uTTCOS_maxThreadsPermitted( )

// System specific structures and constant -- DONOT CHANGE

#define __MAX_TODO_THREADS 40

 // Scheduler data structure for storing task data
 // ******** CCES compacts the structure for display
enum  THREAD_TYPE {NO_THREAD, THREAD, THREAD__pV, THREAD__fI}  ;
typedef struct
{
	// Pointer to task
	enum THREAD_TYPE threadType;

	void (* pThread)(void);

	void (* pThread__pV)(void *);
	void *pArg__pV;

	void (* pThread__fI)(int);
	int pArg__fI;

	// Initial thread delay in ticks
	unsigned int Delay;
	// Periodic interval in ticks
	unsigned int Period;
	// Runme flag (indicating when the thread is due to run)
	unsigned char RunMe;
	// Set to true if true is co-operative
	// Set to FALSE if FALSE is pre-emptive
	unsigned char Pre_emptiveThread;
} __uTTCOS_todoList;

// Include all processor dependent includes
#if defined(__ARM__)
// Don't want any thing but system files
//# include "../uTTCOS_MPG_ARM_Specific\Jason_Code_Oct2012/configuration.h"
#elif defined(__ADSPBF533__)
  #include <blackfin.h>

#elif defined(__ADSP21469__)
  #include <cdef21469.h>
  #include <def21469.h>
  #include <21469.h>
  #include <stdlib.h>
  
#elif defined(__ADSPTS201__)
  #error "TigerSHARC not supported"
#else
  #error "Processor not supported"
#endif

// Following kept for historic reasons
// Meaning -- I can remember how to bring the functionality if I decide I want to
/*
#if 0
typedef struct
{
	unsigned int Tick_count;
   // Pointer to task
   void (* pTask)(void);
   // current index;
   int taskIndex;
   // startTime in cycles not interrupts
   unsigned long long int startTime;
   // runTime in cycles not interrupts
   unsigned long long int runTime;
      // Store Task Name for use with later analysis
//   char taskName[80];
} sTaskTimeInfo;
#endif


#if 0
  // Maximum number of tasks -- ********* MUST BE ADJUSTED FOR EACH NEW PROJECT
  #define TICK_FREQUENCY		uTTCOS_GetTickFrequency( )
  // Core scheduler functions
  extern "C" void TTCOS_SwitchToAudioInterrupt(void);
  
  // TTCOS Utilities
  //Function Prototypes
  #warning "Something weird here -- fix later"
  
  #if defined(__ADSPBF533__)	
    #include <blackfin.h>
          #include <ccblkfn.h>			// Only include in <blackfin.h> for BF533 and no newer products
          #include <sys/exception.h> 	
          
    #define CLOCK_FREQUENCY		500		//setting the clock frequency for BF533
  #else
          #error "Processor not supported"
  #endif // #if defined(___ADSPBF533__)
  
  #define CLOCK_CYCLES_PER_MICROSEC	(CLOCK_FREQUENCY)                     // ******
  #define CLOCK_CYCLES_PER_MILLISEC	(CLOCK_CYCLES_PER_MICROSEC * 1000)
  #define CLOCK_CYCLES_PER_SEC		  (CLOCK_CYCLES_PER_MILLISEC * 1000)
  
  #define SYSTEM_FREQUENCY		(CLOCK_FREQUENCY / 5)		// Approximately
  
  #define SYSTEM_CYCLES_PER_MICROSEC	(SYSTEM_FREQUENCY)
  #define SYSTEM_CYCLES_PER_MILLISEC	(SYSTEM_FREQUENCY * 1000)
  #define SYSTEM_CLOCK_CYCLES_PER_SEC	(SYSTEM_FREQUENCY * 10
  
  // Execution time information record length
  #define TTCOS_RECORD_NUMBER TTCOS_MAX_TASKS
  
  // Missing Functionality
  extern "C" void TTCOS_ReportStatus();
  
  #if 0
    #include "StateHistory.h"
    
    //include files
    // #include "Common_TTCOS.h"
    #include "./TTCOS_ISRTimer.h"
    #include "./LEDs.h"
    #include "./ReportError.h"
    #include "./Switches.h"
    #include "./WatchDog.h"
    #include "./Audio.h"
  
  #endif		// #ifndef TTCOS_H
  
  extern "C" void	TTCOS_InitLED(void);
  extern "C" unsigned int	TTCOS_ReadLED(void);
  extern "C" void	TTCOS_WriteLED(unsigned int LEDvalue);
  
  extern "C" void	TTCOS_InitSwitches(void);
  extern "C" unsigned int	TTCOS_ReadSwitches(void);
  
  extern "C" void TTCOS_InitializeSystemWatchDogTimer(void);
  extern "C" void TTCOS_StartSystemWatchDogTimer(void);
  extern "C" void TTCOS_FeedSystemWatchDogTimer(void);

#endif
*/

#endif
