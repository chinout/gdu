# FIFO

请见sdfifo.h。非定长的，先进先出的数据队列。当您在不知道存储数据的最大的大小，存储的所有类型一致时，请使用它。它有>两种实现，分别为deque实现和queue实现，每种实现，又可以各自实现其锁，来实现线程安全和非线程安全版本。

```cpp
//Example：
#include “sdfifo.h”

//生产者消费者模式
SGDP::CSDFifo<CResource> fifo;
bool bRun = true;
//生产者线程
while(bRun)
{
    CResource * pResource = new CResource();
    fifo.Push(pResource);//缺省是线程安全的,无需加锁
}

//消费者线程
while(bRun)
{
    CResource * pResource = NULL;
    fifo.Pop(pResource); //缺省是线程安全的,无需加锁
    if(NULL == pResource)
    {
        continue;
    }
    //使用Resouce
    delete pResource;
}
```
