# 线程池

请见gthreadpool.h。这个类可能是编写多线程程序的您最需要的类之一了。虽然Windows平台也为您提供了一个多线程函数QueueUserWorkItem，但是其性能并非令人满意（Windows Vista专门对此做了改进，性能可能会有所提高）。需要您注意的是：线程池中>执行内容的线程并行安全性需要您自己保证。

```cpp
//Example：
#include “gthreadpool.h”

class YourTask : public SGDP::IGRunable
{
public:
    void Run()
    {
        //您需要执行的任务
    }
};

YourTask task;
SGDP::CGThreadPool yourPool;
yourPool.Init(2, 5, 1000);//最小2个线程，最到5个线程，最大等待任务数量为1000个
int i=0
while(i<1000)
{
    yourPool.ScheduleJob(task);
    i++;
}
yourPool.TerminateWaitJobs();
```
