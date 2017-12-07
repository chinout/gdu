# 条件变量

请见gcondition.h。有时候，我们想让线程以原子方式把锁释放并将自己阻塞，直到某一个条件成立为止。要实现这样的线程同步
时比较复杂的。但是现在，我们有了GDU的条件变量，就可以解决这个问题。请看：

```cpp
//Example：
互斥量初始化：
#include “gmutex.h”
#include “gcondition.h”
SGDP::CGMutex mutex;
SGDP::CGCondition condition;
std::list<int> g_list;

//生产者线程：
int resource = …;
mutex.Lock();
g_list.push_back(resource);
mutex.Unlock();
condition.Signal();//当生产者生产了一个资源，通知一个消费者线程进行处理

//消费者线程：
while(m_bRun)
{
    int resource;
    condition .Wait (mutex);//等待生产者生产一个资源
    resource = g_list.front();
    mutex.Unlock();
    //处理resource
}
```

请对比一下Mutex和此Condition的Example之间的区别，在Mutex例子中，为了在生产者生产资源特别慢的时候，避免消费者线程频>繁探测g_list中是否有资源，我们必须使用Sleep()，而在Condition的例子中，该问题被完美的解决掉。
