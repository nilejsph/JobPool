#pragma once
#include "advJob.h"
class myDownloadJob :
	public advJob
{
public:
	myDownloadJob();
	bool advJobImpl();
	bool advJobPauseImpl();
	bool advJobAbortImpl();
	bool advJobResumeImpl();
	bool advJobSaveCurretStateImpl();
	virtual ~myDownloadJob();
};

