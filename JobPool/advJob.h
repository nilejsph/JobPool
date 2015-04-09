#ifndef ADV_JOB_H
#define ADV_JOB_H
#include "advCommons.h"
typedef enum advJobMessage_enum
{
	JOB_ADD_REQUEST,
	JOB_START_REQUEST,
	JOB_PAUSE_REQUEST,
	JOB_RESUME_REQUEST,
	JOB_ABORT_REQUEST,	
}advJobMessage;

typedef struct jobRequestMessages_struct
{
	advJobMessage jobRequest;
	void	*jobData;
}jobRequestMessages;
class advJobThread;
class advJob 
{
	friend class advJobThread;
private:

	int			_advJobID;
	int			_percentCompleted;
	void*		_advJobParams;
	advJobState	_advJobState;
	/*this member is accesses across thread. Make it thread safe*/
	bool		_advJobMsgChanged;
	advJobMessage _advJobMessage;
	/*mutex for above objext*/
	HANDLE _advJobMsgMutex;
	void _setJobID(int jobID) { _advJobID = jobID; };
protected:
	bool _advJobRequiresPreemtion();
	
public:
	/*Basic constructor*/
	advJob()
	{
		_percentCompleted = 0; 
		_advJobID = reinterpret_cast<int>(this);		
		
	};
	/*Job with parameters*/
	advJob(void* advJobParams) :_advJobParams(advJobParams){}
	/*Triggering point to start the job in the current thread*/
	void advJobStart();
	int getJobID() { return _advJobID; }
	bool advJobPause();
	bool advJobAbort();
	bool advJobResume();
	bool advJobSaveCurretState();

	/*All derived classes should implement this*/
	virtual bool advJobImpl()=0;
	virtual bool advJobPauseImpl() = 0;
	virtual bool advJobAbortImpl() = 0;
	virtual bool advJobResumeImpl() = 0;
	virtual bool advJobSaveCurretStateImpl() = 0;

	bool setJobPercentCompleted(int value);
	int getJobPercentCompleted() { return _percentCompleted; }

	int advGetJobId();
	void* advGetJobParams();

	void setJobRequest(advJobMessage request);
	~advJob(){};
};
#endif