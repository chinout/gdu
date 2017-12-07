# 互斥量

请见gmutex.h。互斥量，它在执行之前需要独占对一些共享资源的访问权。这种方式可以让多行代码以“原子方式”来对资源进行操
控。这里的原子方式，指的是代码知道除了当前线程外，没有其他任何线程会同时访问该资源。目前，我们为您实现了1）空互斥量
，2）普通互斥量或者说是均衡互斥量，3）读写互斥量。从实现上来讲，无论是Windows平台还是Linux平台，都是用户态的互斥量>，即，它适合于较短的代码段，或者说，代码段耗费CPU时间较短。如果说代码段过长或者耗费时间过长，则不适合使用GDU中的互>斥量。

```
注意：当需要互斥的代码段中有“Sleep”或者“等待中断”或者“读写文件”之类耗时较长的操作或者代码段较长时，不适合使用GDU的>互斥量。
```

从实现上，目前，GDU的Mutex在Windows平台上使用临界区实现，Linux平台使用pthread的互斥量实现。

```cpp
//Example：
//互斥量初始化：
#include “gmutex.h”
#include “gtime.h”
SGDP::CGMutex mutex;
std::list<int> g_list;

//生产者线程：
int resource = …;
mutex.Lock();
//原子操作开始
g_list.push_back(resource);
//原子操作结束
mutex.Unlock();

//消费者线程：
while(m_bRun)
{
    int resource;
    mutex.Lock();
    //原子操作开始
    if(g_list.empty())
    {
        //原子操作结束
        mutex.Unlock();
        SGDP::GSleep(10);
        continue;
    }
    resource = g_list.front();
    //原子操作结束
    mutex.Unlock();
   //处理resource
}
```

您还可以选择是否使用读写互斥量，读写互斥量对用户来说，它可以保证：当有写需求时，如果当前没有进入互斥量，则直接进入>写互斥状态；如果有任何互斥状态，则将此需求放入写队列。当有读需求时，如果当前没有进入互斥量，则进入读互斥状态，读取>数据；如果已经读互斥状态，直接读；如果已经进入写互斥状态，则将此需求放入读队列。当前没有互斥时，会轮训读队列和写队>列，写队列优先。
