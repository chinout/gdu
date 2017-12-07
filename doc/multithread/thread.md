# 线程

请见gthread.h。可能您早就了解如何创建，操作，销毁线程，但是，我们还是决定提供一套线程类和函数，用以统一Windows和Linux的实现。并且，在Windows平台上，我们限制您犯错误使用CreateThread这个函数的机会。


```cpp
Example：
#include “gthread.h”
unsigned int GAPI PFThrdProc(void * param)
{
    //您的线程函数
};

SGDP::CGThread thread;
if(thread.start(PFThrdProc, param))
{
    printf(“创建线程成功”);
}
```
