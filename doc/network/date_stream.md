# 网络数据转化系列

请见gddatastream.h。

为什么要提供这个数据转化函数？

在网络编程中，尤其是在异构网络的软件编程中，由于存在主机不一致的情况，包括位数的不一致，大小端的不一致等。为了解决>位数不一致导致的结构体对齐不一致的问题，使用gddatastream是一种方式。您完全不用关心结构体对齐的问题，直接使用gddatastream的Add*的方法，则可以解决此问题，并输出正确的buffer。

```cpp
//Example：
#include “gddatastream.h”
CgdDataStream DataStream;
CHAR Buffer[1024]
DataStream.Prepare(Buffer,1024);
DataStream.AddChar(‘A’);
DataStream.AddInt(32);
//得到最终结果
CHAR * pData = DataStream.GetData();
INT32 DataLen = DataStream.GetDataLen();
```
