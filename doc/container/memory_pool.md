# 内存池（MemoryPool）

请见sdmemorypool.h。当您需要频繁分配内存，频繁归还内存时，请使用SDU的内存池。SDU的MemoryPool分为FixMemoryPool和VarMemoryPool，即分配定长内存的内存池和分配变长的内存池。

经过我们的测试，SDU的MemoryPool大幅度快于new/delete，malloc/free以及boost的Pool，您可以放心使用。

SDU的MemoryPool并非是线程安全的，多线程环境下，请加锁后使用。

```cpp
Example：
#include “sdmemorypool.h”
#include “sdmutex.h”

SGDP::CSDVarMemoryPool pool;
SGDP::CSDMutex mutex;
pool.Create();
//某一线程：
char * p1;
char * p2;
char * p3;

mutex.Lock();
p1 = pool.Malloc(512);//记得加锁
mutex.Unlock();

mutex.Lock();
p2 = pool.Malloc(31);//记得加锁
mutex.Unlock();

mutex.Lock();
p3 = pool.Malloc(128);//记得加锁
mutex.Unlock();

//另外一个线程：
mutex.Lock();
pool.Free(p3);//记得加锁
mutex.UnLock();

mutex.Lock();
pool.Free(p2);//记得加锁
mutex.UnLock();

mutex.Lock();
pool.Free(p1);//记得加锁
mutex.UnLock();
```

```cpp
//Example：
#include “sdmemorypool.h”
#include “sdmutex.h”

SGDP::CSDFixMemoryPool pool;
pool.Create(128);
SGDP::CSDMutex mutex;

//某一线程：
char * p1;
char * p2;
char * p3;
mutex.Lock();
p1 = pool.Malloc();//记得加锁
mutex.UnLock();

mutex.Lock();
p2 = pool.Malloc();//记得加锁
mutex.UnLock();

mutex.Lock();
p3 = pool.Malloc();//记得加锁
mutex.UnLock();

//另外一个线程：
mutex.Lock();
pool.Free(p3);//记得加锁
mutex.UnLock();

mutex.Lock();
pool.Free(p2);//记得加锁
mutex.UnLock();

mutex.Lock();
pool.Free(p1);//记得加锁
mutex.UnLock();
```

您可以向SDU小组索要性能分析报告。
