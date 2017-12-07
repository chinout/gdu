# 对象池（ObjectPool）

请见sdobjectpool.h。当您需要频繁分配对象和释放对象时，请使用SDU的ObjectPool。

经过我们的测试，SDU的ObjectPool性能大幅度快于对象的new/delete以及boost的Pool，您可以放心使用。

SDU的ObjectPool并非时线程安全的，多线程环境下，请加锁后使用。

```cpp
Example：
#include “sdobjectpool.h”

class Object
{
public:
    Object(){};
    ~Object(){};
private:
    int data;
};

SGDP::CSDObjectPool< Object> pool;
Object o = pool.Alloc();
pool.Free(o);
```

您可以向SDU小组索要性能分析报告。
