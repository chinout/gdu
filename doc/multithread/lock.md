# 锁

请见glock.h。在GDU中，锁是对互斥量的包装，您可以根据您的喜好，来选择使用互斥量还是锁。从使用感觉上来说，此加锁为面
向范围（对一定代码范围，只能有一个线程同时进入）的加锁而非一般加锁的面向对象（对于某个类(CriticalSection, Mutex等)>的对象，只能有一个线程占有此资源）加锁。
