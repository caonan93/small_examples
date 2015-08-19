//环形缓冲区的一些测试
//2015-08-18 cao nan
#include <boost/circular_buffer.hpp>
#include <stdio.h>
#include <assert.h>
#include <boost/shared_ptr.hpp>
#include <unistd.h>
//测试class对象被覆盖会不会调用析构
class testDestructor {
public:
  testDestructor() {
	printf("testDestructor%d\n", iCount++);
  }
  ~testDestructor() {
	printf("~testDestructor%d\n", iCount--);
  }
  static int iCount;
};
int testDestructor::iCount = 0;
int main() {
  boost::circular_buffer<int> cb(3);

  cb.push_back(0);
  cb.push_back(1);
  cb.push_back(2);
  assert(cb[0] == 0 && cb[1] == 1 && cb[2] == 2);
  cb.push_back(3);
  cb.push_back(4);
  cb.resize(3);//设置环形缓冲大小 一旦放置数据个数超过其界限就会覆盖第一个
  assert(cb[0] == 2 && cb[1] == 3 && cb[2] == 4);

  for (boost::circular_buffer<int>::iterator 
	   it = cb.begin();
	   it != cb.end(); 
	   it++)
  {
	printf("%d ", *it);
  }
  printf("\n");
  boost::circular_buffer<int> cb1(3);

  cb1.push_front(0);
  cb1.push_front(1);
  cb1.push_front(2);
  //assert(cb1[0] == 0 && cb1[1] == 1 && cb1[2] == 2);
  cb1.push_front(3);
  cb1.push_front(4);
  cb1.resize(3);//设置环形缓冲大小 一旦放置数据个数超过其界限就会覆盖第一个
  //assert(cb1[0] == 2 && cb1[1] == 3 && cb1[2] == 4);

  for (boost::circular_buffer<int>::iterator 
	   it = cb1.begin(); 
	   it != cb1.end();
	   it++)
  {
	printf("%d ", *it);
  }
  printf("\n");


  //测试环形缓冲中装对象
  /*
	  boost::circular_buffer<testDestructor*> ctest(3);
	  ctest.push_front(new testDestructor);
	  ctest.push_front(new testDestructor);
	  ctest.push_front(new testDestructor);
	  ctest.push_front(new testDestructor);
	  ctest.push_front(new testDestructor);
	  testDestructor::iCount = 0;*/
  /*  result:
	  testDestructor1
	  testDestructor2
	  testDestructor3
	  testDestructor4
	  看来覆盖对象是不可以调用析构的
	  */
  //我们可以尝试RAII管理对象生命期
  typedef boost::shared_ptr<testDestructor> DestructorPtr;
  typedef boost::circular_buffer<DestructorPtr> CTestPtr;
  CTestPtr ctestPtr(3);
  DestructorPtr p(new testDestructor);
  ctestPtr.push_back(p);
  ctestPtr.push_back(DestructorPtr(new testDestructor));
  ctestPtr.push_back(DestructorPtr(new testDestructor));
  ctestPtr.push_back(DestructorPtr(new testDestructor));
  ctestPtr.push_back(DestructorPtr(new testDestructor));
  ctestPtr.push_back(DestructorPtr(new testDestructor));
  //智能指针被析构后会自动销毁它所指向的对象
  while (1)
  {
	sleep(1);
  }

  return 0;
}