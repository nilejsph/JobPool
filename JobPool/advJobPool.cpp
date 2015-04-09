#include<iostream>
#include<windows.h>
#include<stdio.h>
#include"advJobThread.h"
#include "advJob.h"
#include "advJobPool.h"
#include "myDownloadJob.h"
using namespace std;

typedef enum advJobThreadState_enum
{
	JOB_THREAD_NOT_STARTED,
	JOB_THREAD_BUSY,
	JOB_THREAD_WAITING,
}advJobThreadState;




advJobPool::advJobPool(int numberOfThreads)
{
	this->numberOfThreads = numberOfThreads;
	for (int i = 0; i < numberOfThreads; i++)
	{
		advJobThreadList.push_back(new advJobThread());
	}
}


void advJobPool::advAssginJob(advJob* jobInstance)
{
	for (std::vector<advJobThread*>::iterator it = advJobThreadList.begin(); it != advJobThreadList.end(); ++it)
	{
		if ((*it)->getstate() == THREAD_WAITING)
		{
			(*it)->advJobPostMessage(JOB_ADD_REQUEST, jobInstance);
			break;
		}
	}
}

void advJobPool::advStartJob(advJob* jobInstance)
{
	for (std::vector<advJobThread*>::iterator it = advJobThreadList.begin(); it != advJobThreadList.end(); ++it)
	{
		if ((*it)->getCurrentJobID() == jobInstance->getJobID())
		{
			(*it)->advJobPostMessage(JOB_START_REQUEST,jobInstance);
			break;
		}
	}
}

void advJobPool::advPauseJob(advJob* jobInstance)
{
	for (std::vector<advJobThread*>::iterator it = advJobThreadList.begin(); it != advJobThreadList.end(); ++it)
	{
		if ((*it)->getCurrentJobID() == jobInstance->getJobID())
		{
			(*it)->advJobPostMessage(JOB_PAUSE_REQUEST,NULL);
			jobInstance->setJobRequest(JOB_PAUSE_REQUEST);
			break;
		}
	}
}

void advJobPool::advResumeJob(advJob* jobInstance)
{
	for (std::vector<advJobThread*>::iterator it = advJobThreadList.begin(); it != advJobThreadList.end(); ++it)
	{
		if ((*it)->getstate() == THREAD_WAITING)
		{
			(*it)->advJobPostMessage(JOB_ADD_REQUEST, jobInstance); // Have to reassign the job to this thread
			(*it)->advJobPostMessage(JOB_RESUME_REQUEST,NULL);
			break;
		}
	}
}

void advJobPool::advAbortJob(advJob* jobInstance)
{
	for (std::vector<advJobThread*>::iterator it = advJobThreadList.begin(); it != advJobThreadList.end(); ++it)
	{
		if ((*it)->getCurrentJobID() == jobInstance->getJobID())
		{
			(*it)->advJobPostMessage(JOB_ABORT_REQUEST, NULL);
			jobInstance->setJobRequest(JOB_ABORT_REQUEST);
			break;
		}
	}
}


/*SAMPLE CODE TO TEST*/
void main()
{
	int i;
	advJobPool myJobPool(10);
	myDownloadJob *myJob = new myDownloadJob();
	std::cin >> i;
	myJobPool.advAssginJob(myJob);
	Sleep(0);
	myJobPool.advStartJob(myJob);
	std::cin >> i; 
	myJobPool.advAbortJob(myJob);
	std::cin >> i;
	/*JobScheduler myJobPool;
	jobParam myparam;
	cout << endl << "Enter a JobId:";
	cin >> i;
	myparam.jobID = i;
	myparam.param = NULL;
	myJobPool.assginJob(myparam);
	Sleep(2);   // Just for printing
	cout << endl << "Enter a JobId:";
	cin >> i;
	myparam.jobID = i;
	myparam.param = NULL;
	myJobPool.assginJob(myparam);
	Sleep(2);   // Just for priting
	cout << endl << "Enter a JobId:";
	cin >> i;
	myparam.jobID = i;
	myparam.param = NULL;
	myJobPool.assginJob(myparam);
	Sleep(2);   // Just for priting
	cout << endl << "Enter a JobId:";
	cin >> i;
	myparam.jobID = i;
	myparam.param = NULL;
	myJobPool.assginJob(myparam);
	Sleep(2);   // Just for priting

	cin >> i;
	*/
}