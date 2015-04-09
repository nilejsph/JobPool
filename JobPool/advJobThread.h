#ifndef ADV_JOB_THREAD_H
#define ADV_JOB_THREAD_H
#include "advJob.h"
#include<windows.h>
/*jOB WHERE YOU HAVE THE THREAD IMPLEMENTATION*/
class advJobThread
{
private:
	advThreadState	_threadState;
	HANDLE			pipeReadEnd;
	HANDLE			pipeWriteEnd;
	int				currentJobID;
	DWORD				threadID;
	/*This is the jobInstance executing in this tread context. 
	  Each time it would be pointing to different jobs running at this thread context*/
	advJob *jobInstance;
	/*This has to be a static function as this is the tread entry*/
	static DWORD _advJobProcessHandler(LPVOID threadInstance);
public:
	DWORD advJobPostMessage(advJobMessage jobRequest, advJob* jobInstance);
	advJobThread();
	//void advExecuteJob(advJob& jobInstance);
	advThreadState getstate() {
		return _threadState;
	};
	int	getCurrentJobID()
	{
		return currentJobID;
	}
	//bool assignJob(advJob& jobInstance);

};
#endif