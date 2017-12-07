## MD5

请见gmd5.h。MD5是资讯-摘要算法（Message-Digest Algorithm
5）。它的开销相对于CRC而言，要大些。虽然目前出现了MD5码碰撞的问题，但它仍然是目前业界使用最多的校验算法之一。它主要用于文件的完整性校验。

一般而言，我们建议传输数据量较小时，使用CRC；传输数据量较大时，使用MD5。在有些P2P系统中，会对每一个Piece使用CRC算法，而对每一个Chunk使用MD5码（Chunk的大小一般是Piece的1000倍以上）。

```cpp
//Example
#include “gmd5.h”
unsigned char buffer[1024];
//这里给buffer赋值
UCHAR acDigest[16];
MD5(acDigest, buffer, 1024);
//一般的用法是将buffer分片传输给远端服务器，然后在远端服务器获取全部buffer后，再次生成一次acDigest，比较两次结果，看是否不同。
```
