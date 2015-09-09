#ifndef SIMA_MUTEX_H
#define SIMA_MUTEX_H
#include <pthread.h>
#include <assert.h>
#include <boost/noncopyable.hpp>
#include "CurrentThread.h"
namespace siam
{
class MutexLock :boost::noncopyable
{
public:
	MutexLock():mutex_holder_(0)
	{
		int ret = pthread_mutex_init(&mutex_,NULL);
		assert(0 == ret);
	}
	~MutexLock()
	{
		assert(0 == mutex_holder_);
		int ret = pthread_mutex_destroy(&mutex_);
		assert(0 == ret);
	}
	void Lock()
	{
		mutex_holder_ = CurrentThread::tid();
		pthread_mutex_lock(&mutex_);
	}
	void unLock()
	{
		pthread_mutex_unlock(&mutex_);
		mutex_holder_ = 0;
	}
	bool isLockedByThisThread()
	{
		return mutex_holder_ == CurrentThread::tid();
	}
	pthread_mutex_t* getPthreadMutex() /* non-const */
	{
		return &mutex_;
	}
private:
	pthread_mutex_t mutex_;
	pid_t mutex_holder_;
};

class AutoMutex : boost::noncopyable
{
public:
	explicit AutoMutex(MutexLock &mutex):mutex_(mutex)
	{
		mutex_.Lock();
	}
	~AutoMutex()
	{
		mutex_.unLock();
	}
private:
	MutexLock& mutex_; 
};

}//end SIAM_
#endif