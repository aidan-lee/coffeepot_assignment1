/*************************************************************************************
*   AUTOMATICALLY GENERATED COMMENT -- DO NOT MODIFY
* Author: %Username%
* Date: %DateAndTime%
* File Type: EUNIT Test File
*************************************************************************************/

#define EMBEDDEDUNIT_LITE
#include <EmbeddedUnit2017/EmbeddedUnit2017.h>
//#include "%TestGroupName%.h"
%Include1%%Include2%%Include3%%Include4%%Include5%

TEST_CONTROL(%TestGroupName%);

#if 1
void UpdateEunitGui(void);
TEST(%TestGroupName%_GUIUpdate) {
	UpdateEunitGui();  // Conditionally compile this line (use #if 0) to stop an GUI update based on last completed test
}
#endif

TEST(%TestName%)
{ 
	#warning 'Dummy test has been inserted -- replace with your own -- %DateAndTime% '
	// TODO -- 'Dummy test has been inserted  -- replace with your own -- %DateAndTime% '
	printf("Dummy test has been inserted -- replace with your own -- %DateAndTime% \n");
	bool validTest = false;
	CHECK(validTest == true);
}

TEST_FILE_RUN_NOTIFICATION(%TestGroupName%);

