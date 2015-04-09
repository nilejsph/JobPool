#include "myDownloadJob.h"
#include<iostream>
#include <windows.h>
myDownloadJob::myDownloadJob()
{
}


myDownloadJob::~myDownloadJob()
{
}

bool myDownloadJob::advJobImpl()
{
	std::cout << "Looks like the download job is starting";
	Sleep(10*1000);
	setJobPercentCompleted(25);
	if (_advJobRequiresPreemtion())
	{
		/*Save if required*/
		return true;
	}
	/*Consistancy point1*/
	Sleep(10 * 1000);
	setJobPercentCompleted(50);
	if (_advJobRequiresPreemtion())
	{
		/*Save if required*/
		return true;
	}
	/*Consistancy point2*/
	Sleep(10 * 1000);
	setJobPercentCompleted(75);
	
	/*Consistancy point3*/
	if (_advJobRequiresPreemtion())
	{
		/*Save if required*/
		return true;
	}
	Sleep(10 * 1000);
	setJobPercentCompleted(100);
	return true;
}

bool myDownloadJob::advJobPauseImpl() 
{
	std::cout << "job is Paused";
	return true;
}
bool myDownloadJob::advJobAbortImpl()
{
	std::cout << "job is Aborted";
	return true;
}
bool myDownloadJob::advJobResumeImpl() 
{
	std::cout << "job is Resumed";
	return true;
}
bool myDownloadJob::advJobSaveCurretStateImpl() 
{
	std::cout << "job is Saving the states";
	return true;
}