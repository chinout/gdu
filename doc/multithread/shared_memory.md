# 共享内存

请见gshmem.h。共享内存用于在不同“进程”之间交换数据。

```cpp
//Example：
#include “gshmem.h”
//一个进程：
SGDP::CGShmem ShareMem;
void * p = ShareMem.Create(“MyShareMemory”, 1024);
//处理p

//另一个进程：
SGDP::CGShmem ShareMem;
void * p = ShareMem.Open(“MyShareMemory”);
//处理p
```
