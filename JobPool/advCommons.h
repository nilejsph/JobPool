#ifndef ADV_COMMONS_H
#define ADV_COMMONS_H
#include <windows.h>
typedef enum advJobState_enum
{
	JOB_NOT_STARTED = 0,
	JOB_RUNNIG,
	JOB_WAITING,
	JOB_SAVING,
	JOB_PAUSING,
	JOB_PAUSED,
	JOB_SAVED,
	JOB_ABORTING,
	JOB_ABORTED,
	JOB_RESUMING,
}advJobState;

typedef enum advThreadState_enum
{
	THREAD_NOT_STARTED = 0,
	THREAD_WAITING,
	THREAD_ASSIGNED_WAITING,
	THREAD_RUNNING,
}advThreadState;


#endif