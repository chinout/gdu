# 随机

请见random.h。C库提供的随机函数，使用上分为两步：设置种子和获取随机数。而且，当种子值为恒定值时，随机结果的顺序是一致的。多线程时，多个随机数会相互影响。使用GDU的随机函数，则完全可以避免这些情况，而且使用简单。

```cpp
//Example：
#include “random.h”

GDP::CGDRandom r;
UINT32 rand = r.Random();//返回0－RAN_MAX之间的随机值
rand = r.Random(10);//返回[0, 10)之间的值
rand = r.Random(10, 20);//返回[10, 20)之间的值
```
