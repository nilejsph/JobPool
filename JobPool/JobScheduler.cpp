#include<iostream>
#include<windows.h>
#include<stdio.h>
using namespace std;
typedef enum threadstate_enum
{
	RUNNIG,
	WAITING,
	NOT_STARTED,
}threadstate;

typedef struct jobParam_t
{
	int jobID;
	void* param;
}jobParam;

/*jOB WHERE YOU HAVE THE THREAD IMPLEMENTATION*/
class jobthread
{
private:
	threadstate threadstate;
	HANDLE pipeReadEnd;
	HANDLE pipeWriteEnd;
	DWORD threadID;
public:
	static DWORD jobthreadHandling(LPVOID parameters);

	jobthread();
	static void executeJob(jobParam jobParameters, void* Instanceparams);
	int getstate();
	bool assignJob(jobParam jobParameters);


};
/*THE JOB ASSIGNER WOULD BE RUNNING IN MAIN THREAD*/
class JobScheduler
{
private:

	jobthread *record[10];
public:
	JobScheduler();

	void assginJob(jobParam parameters);

};
/*JOB CLASS DEFNITION*/
DWORD jobthread::jobthreadHandling(LPVOID parameters)
{
	jobParam jobParameters;
	jobthread *threadInstace = (jobthread *)parameters;
	SIZE_T noOfbyesRead;
	while (1)
	{
		memset(&jobParameters, 0x00, sizeof(jobParam));
		threadInstace->threadstate = WAITING;
		ReadFile(threadInstace->pipeReadEnd, &jobParameters, sizeof(jobParam), &noOfbyesRead, NULL);
		threadInstace->threadstate = RUNNIG;
		executeJob(jobParameters, parameters);

	}
}
jobthread::jobthread()
{
	threadstate = NOT_STARTED;

	if (CreatePipe(&pipeReadEnd, &pipeWriteEnd, NULL, 0))
	{
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&jobthreadHandling, this, 0, &threadID);
	}
}
void jobthread::executeJob(jobParam jobParameters, void* Instanceparams)
{
	jobthread *threadInstace = (jobthread *)Instanceparams;
	cout << "Executing Job: " << jobParameters.jobID << "In Thread:" << threadInstace->threadID << endl;
	Sleep(1000 * 20);   // Just sleeping to simulate this job is taking 20 secs
	cout << "Done Executing Job: " << jobParameters.jobID << "In Thread:" << threadInstace->threadID << endl;
}
int jobthread::getstate()
{
	return threadstate;
}
bool jobthread::assignJob(jobParam jobParameters)
{
	SIZE_T bytesWritten;
	WriteFile(pipeWriteEnd, &jobParameters, sizeof(jobParam), &bytesWritten, NULL);
	return true;
}

/*JOB Scheduler DEFNITION*/

JobScheduler::JobScheduler()
{
	for (int i = 0; i < 10; i++)
	{
		record[i] = new jobthread();
	}
}
void JobScheduler::assginJob(jobParam parameters)
{
	for (int i = 0; i < 10; i++)
	{
		if (record[i]->getstate() == WAITING)
		{
			record[i]->assignJob(parameters);
			break;
		}

	}
}

/*SAMPLE CODE TO TEST*/
void main()
{
	int i;
	JobScheduler myJobPool;
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
}