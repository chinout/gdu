## 错误码

请见sderrno.h。当您需要获取上次所发生的错误码和错误信息时，请使用SDGetLastError和SDLastStrError。

为什么要设计errno？

确实，无论时windows环境还是linux环境，都已经有errno了。但我们希望能够将这些统一起来。另外，SDU内部的一些错误，我们也希望能够统一到一起。
