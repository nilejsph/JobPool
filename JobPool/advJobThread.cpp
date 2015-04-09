#include "advJobThread.h"

/*Thread Internal function. entry fucntion thread context*/
DWORD advJobThread::_advJobProcessHandler(LPVOID parameters)
{	
	SIZE_T noOfbyesRead;
	jobRequestMessages jobRequest;
	advJobThread* thisThreadInstance = (advJobThread*)parameters;

	while (1)
	{		
		thisThreadInstance->_threadState = THREAD_WAITING;
		ReadFile(thisThreadInstance->pipeReadEnd, &jobRequest, sizeof(jobRequestMessages), &noOfbyesRead, NULL);
		switch (jobRequest.jobRequest)
		{
		case JOB_ADD_REQUEST:
			thisThreadInstance->jobInstance = (advJob*)jobRequest.jobData;
			thisThreadInstance->currentJobID = thisThreadInstance->jobInstance->getJobID();
			thisThreadInstance->_threadState = THREAD_ASSIGNED_WAITING;
			break;
		case JOB_START_REQUEST:			
			thisThreadInstance->jobInstance->advJobImpl();
			thisThreadInstance->_threadState = THREAD_RUNNING;
			/*Get some signal from the main thread on this waiting here Indicates to go back to pipe*/
			break;
		case JOB_PAUSE_REQUEST:
			thisThreadInstance->jobInstance->advJobPause();
			thisThreadInstance->_threadState = THREAD_WAITING;
			break;		
		case JOB_RESUME_REQUEST:
			thisThreadInstance->jobInstance->advJobResume();
			thisThreadInstance->_threadState = THREAD_RUNNING;
			break;
		case JOB_ABORT_REQUEST:
			thisThreadInstance->jobInstance->advJobAbort();
			thisThreadInstance->_threadState = THREAD_RUNNING;
			break;
		}
		
		

	}
}

DWORD advJobThread::advJobPostMessage(advJobMessage jobMessage, advJob* jobInstance)
{
	SIZE_T bytesWritten;
	jobRequestMessages jobRequest;
	jobRequest.jobRequest = jobMessage;
	jobRequest.jobData = jobInstance;
	WriteFile(pipeWriteEnd, &jobRequest, sizeof(jobRequestMessages), &bytesWritten, NULL);
	return true;
}

advJobThread::advJobThread()
{
	_threadState = THREAD_NOT_STARTED;
	jobInstance = NULL;
	currentJobID = 0;
	
	if (CreatePipe(&pipeReadEnd, &pipeWriteEnd, NULL, 0))
	{
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&_advJobProcessHandler, this, 0, &threadID);
	}
}