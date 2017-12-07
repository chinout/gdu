# CRC

请见gcrc.h。CRC是循环冗余校验（Cyclic Redundancy
Check）。它具有检错能力极强，开销小。注意，它主要用于检查数据传输中是否发生改变和错误。

```cpp
//Example
#include “gcrc.h”
char buffer[128];
//这里给buffer赋值
UINT32 crcValue = GCalculateCRC(buffer, 128);//获取了CRC值
//一般的用法是将buffer和crcValue都传输给远端服务器，然后在远端服务器再次生成一次crcValue，比较两次结果，看是否不同。
```
