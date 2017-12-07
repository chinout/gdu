# 数据队列（DataQueue）

请见sddataqueue.h。定长循环数据队列，用于您了解存储数据最大数量的，任意类型的，先进先出的队列。此实现是“非”线程安全
的，在多线程情况下，请加锁使用。

```cpp
Example：
#include “sddataqueue.h”
#include “sdmutex.h”

//生产者消费者模式
SGDP::CSDDataQueue queue;
queue.Init(32);//初始化DataQueue
SGDP::CSDMutex mutex;
bool bRun = true;
//生产者线程
while(bRun)
{
    CResource * pResource = new CResource();
    mutex.Lock();
    queue.PushBack(pResource);
    mutex.Unlock();
}

//消费者线程
while(bRun)
{
    CResource * pResource = NULL;
    mutex.Lock();
    pResource = (CResource)queue.PopFront();
    mutex.Lock();
    if(NULL == pResource)
    {
        continue;
    }
    //使用Resouce
    delete pResource;
}
```
