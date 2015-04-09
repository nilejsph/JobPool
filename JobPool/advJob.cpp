#include "advJob.h"
#include<iostream>
using namespace std;
void  advJob::advJobStart()
{
	cout << "Starting Job. \n";
	_advJobMsgMutex = CreateMutex(
		NULL,              // default security attributes
		FALSE,             // initially owned by this thread
		NULL);             // unnamed mutex
	if (_advJobMsgMutex == NULL)
	{
		printf("CreateMutex error: %d\n", GetLastError());
		exit(0); // TODO: do the cleanup if required
	}
	advJobImpl();
}
bool  advJob:: advJobAbort()
{
	this->_advJobState = JOB_ABORTING;
	cout << "aborting Job \n";
	advJobAbortImpl();
	this->_advJobState = JOB_ABORTED;
	return true;
}
bool advJob::setJobPercentCompleted(int value)
{
	if (value <= 100 && value >= 0)
	{
		_percentCompleted = value;
		cout << "Commpleted job :" << _advJobID << " : " << _percentCompleted << " % .\n";
		return true;
	}
	return false;
}


bool  advJob:: advJobPause()
{
	this->_advJobState = JOB_PAUSING;
	cout << "Pausing Job.\n";
	advJobPauseImpl();
	this->_advJobState = JOB_PAUSED;
	return true;
}
bool  advJob:: advJobResume()
{
	this->_advJobState = JOB_RESUMING;
	advJobResumeImpl();
	return true;
}
bool advJob::advJobSaveCurretState()
{
	this->_advJobState = JOB_SAVING;
	cout << "Saving Job.\n";
	advJobSaveCurretStateImpl();
	this->_advJobState = JOB_SAVED;
	return true;
}
int  advJob::advGetJobId()
{
	return _advJobID;
}

void*  advJob::advGetJobParams()
{

	return NULL;
}

bool advJob::_advJobRequiresPreemtion()
{
	WaitForSingleObject(_advJobMsgMutex, INFINITE);
	if (_advJobMsgChanged == true)
	{
		if (_advJobMessage == JOB_PAUSE_REQUEST || _advJobMessage == JOB_ABORT_REQUEST)
		{
			ReleaseMutex(_advJobMsgMutex);
			return true;
		}	
	_advJobMsgChanged = false;
	}
	ReleaseMutex(_advJobMsgMutex);
	return false;
}
/*Calling this multiple times will reset the message variable and proces only the last message*/
void advJob::setJobRequest(advJobMessage request)
{
	WaitForSingleObject(_advJobMsgMutex, INFINITE);
	_advJobMsgChanged = true;
	_advJobMessage = request;
	ReleaseMutex(_advJobMsgMutex);
}