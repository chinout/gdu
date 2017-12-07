## DES

请见gdes.h。DES算法为数据加密算法（Data Encryption
Algorithm，DEA），是一种对称加密算法，很可能是使用最广泛的密钥系统。它出自IBM的研究工作，IBM也曾对它拥有几年的专利权，但是在1983年已到期后，处于公有范围中，允许在特
定条件下可以免除专利使用费而使用。1977年被美国政府正式采纳。DES 使用一个 56
位的密钥以及附加的 8 位奇偶校验位，产生最大 64 位的分组大小。

DES 的常见变体是三重 DES，使用 168
位的密钥对资料进行三次加密的一种机制；它通常（但非始终）提供极其强大的安全性。如果三个
56 位的子元素都相同，则三重 DES 向后兼容 DES。

DES加密后的密文长度和原文长度是一致。

```cpp
//Example
#include “gdes.h”
CGDes des;
DESBlock block;
DESContext enContext;
DESContext deContext;

unsigned char in[1024];//需要加密的字符串
memset(in, 'A', 1024);
unsigned char out[1024];//加密后的字符串
memset(out, 0, 1024);

des.DESGenKey(&block);//生成DES Key
des.DESGenEncKeySche(&enContext, block);
des.DESGenDecKeySche(&deContext, block);

des.DESEncryptNCBC(&enContext, &block, 1024, in, out);//加密
des.DESDecryptNCBC(&deContext, &block, 1024, out, in);//解密
```
