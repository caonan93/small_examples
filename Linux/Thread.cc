#include "Thread.h"
#include "CurrentThread.h"
#include <errno.h>


namespace siam {
	namespace CurrentThread {
		__thread int t_cachedTid = 0;
		__thread char t_tidString[32];
		__thread const char* t_threadName = "unknown";
		const bool sameType = boost::is_same<int, pid_t>::value;
		// BOOST_STATIC_ASSERT(sameType);
	}
	pid_t gettid() {
		return static_cast<pid_t>(::syscall(SYS_gettid));
	}
}//end SIAM_
using namespace siam;

void CurrentThread::cacheTid() {
	if (t_cachedTid == 0)
	{
		t_cachedTid = gettid();
		int n = snprintf(t_tidString, sizeof t_tidString, "%5d ", t_cachedTid);
		assert(n == 6); (void)n;
	}
}

bool CurrentThread::isMainThread() {
	return tid() == ::getpid();
}

Thread::Thread(const ThreadCallback &fun, const std::string &n) :
func_(fun),
thread_t_(0),
tid_(0),
name_(n),
isStarted_(false) {
}

Thread::~Thread() {}

void Thread::start() {
	errno = pthread_create(&thread_t_, NULL, StartInThread, this);
	if (errno != 0)
	{
		abort();
	}
	isStarted_ = true;
}

void Thread::join() {
	if (isStarted_)
	{
		pthread_join(thread_t_, NULL);
	} else
	{
		//waring not started
	}
}

void* Thread::StartInThread(void* param) {
	Thread *pthread_this = static_cast<Thread*>(param);
	pthread_this->runInThread();
	return NULL;
}

void Thread::runInThread() {
	tid_ = CurrentThread::tid();
	func_();//TODO:
}
