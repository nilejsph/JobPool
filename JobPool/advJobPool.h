#ifndef ADV_JOB_POOL_H
#define ADV_JOB_POOL_H
#include "advJobThread.h"
#include <vector>
/*THE JOB Pool WOULD BE RUNNING IN MAIN THREAD*/
class advJobPool
{
private:
	int numberOfThreads;
	std::vector<advJobThread*> advJobThreadList;
public:
	advJobPool(int numberOfThreads);

	void advAssginJob(advJob* job);

	void advStartJob(advJob* job);

	void advPauseJob(advJob* job);

	void advResumeJob(advJob* job);

	void advAbortJob(advJob* job);

};
#endif