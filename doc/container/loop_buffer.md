# 循环内存（LoopBuffer）

请见sdloopbuffer.h。当您需要使用内存，并且内存的使用是先分配先归还，并能够确定所需内存最大大小时，请使用LoopBuffer>。它并非是线程安全的，多线程情况下，请加锁使用。
