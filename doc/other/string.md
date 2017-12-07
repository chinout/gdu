# string相关

请见gdstring.h。对所有字符串操作的封装，统一了Windows平台和Linux平台的接口。包括：

* 字符串的设置0
* 获取字符串的长度
* 字符串的拚接
* 字符串的复制
* 字符串的切割
* 字符串的比较
* 字符串中的字符查找
* 字符串大小写转化
* Unicode与MultiBytes之间的转化

这里面有几个需要注意的地方：

1. printf, sprint, snprintf, wprintf, swprintf在Linux平台下，需要使用%ls代表Unicode宽字符集，使用%s代表MultiBytes字符集。因此，基于这些printf家族集合的GDSwprintf，GDSnwprintf也需要遵守该准则。Windows则全部使用%s即可。
2. Linux与Windows平台还有一点不同，即出现printf的情况下，不能使用wprintf输出任何信息到控制台，反之亦然。
