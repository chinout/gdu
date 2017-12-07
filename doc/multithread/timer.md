# 定时器

在许多情况下，线程需要等待特定长度的时间，例如等待特定日期或者时间的到来。您可以通过睡眠来实现这个功能，但现在我们>提供了对此功能的支持，并且，我们的GDU定时器能够同时支持多个定时，并且设定这些定时动作是否重复发生。假定我们希望每隔
1分钟就刷新一下在线人数。实现这个功能的方式之一就是通过一个专门线程的每隔一分种执行一次刷新操作。例如，在刷新了一次
信息后，执行Sleep(60000)，然后再苏醒过来并又刷新一次，等等。这种方式需要为每个这样的任务分配一个独立的线程。随着越>来越多的类似需求，为每个服务都提供这个专门的线程的设计方法无法实现可伸缩性。GDU的定时器可以完美的解决这个问题。


```cpp
Example：
#include “gtimer.h”

class TimerTask : public SGDP:: IGTimer
{
public:
    void OnTimer()
    {
        //您需要定时执行的任务
    }
};

TimerTask task;
SGDP:: CGTimer timer;
timer.SetTimer(&task, 1, 60000);
while(true)
{
    timer.Run();
}
timer.KillTimer(1);
```
