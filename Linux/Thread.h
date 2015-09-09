#ifndef SIAM_THREAD_H
#define SIAM_THREAD_H

#include <boost/function.hpp>
#include <boost/noncopyable.hpp>
#include <pthread.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
namespace siam
{
	class Thread : boost::noncopyable
	{
		typedef boost::function<void()> ThreadCallback;
	public:
		Thread(const ThreadCallback &fun, const std::string &name = std::string());
		~Thread();
		void start();
		void join();
		bool is_started() { return isStarted_; }
	private:
		static void* StartInThread(void* param);
		void runInThread();
	private:
		ThreadCallback func_;
		pthread_t thread_t_;
		pid_t tid_;
		std::string name_;
		bool isStarted_;
	};
}
#endif // SIAM_THREAD_H
