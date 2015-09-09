#include "MutexLock.h"
#include "Thread.h"
#include <boost/shared_ptr.hpp>
#include <stdio.h>
boost::shared_ptr<int> g;
siam::MutexLock mutex;
void read_g()
{
	boost::shared_ptr<int> x;
	long sum = 0;
	for (int i = 0; i < 1000 * 1000; ++i)
	{
		x.reset();
		{
			siam::AutoMutex lock(mutex); // 可以加上mutex 以防止race condition
			x = g;
		}
		sum += *x;
	}
	printf("sum = %ld\n", sum);
}
void write_g()
{
	for (int i = 0; i < 1000 * 1000; ++i)
	{
		boost::shared_ptr<int> n(new int(42));
		{
			siam::AutoMutex lock(mutex); // 可以加上mutex 以防止race condition
			g = n;
		}
	}
}
int main()
{
	g.reset(new int(42));
	siam::Thread t1(read_g);
	siam::Thread t2(write_g);
	t1.start();
	t2.start();
	t1.join();
	t2.join();
}