# 单例(单件)模式

请见gdsingleton.h。单例模式又称为单件模式。它是一种由于确保整个应用程序中只有一个类实例。它是设计模式中最简单也是最
实用的一种模式。

gdU中的单件模式，主要从以下2个方面保证全局有且只有一个单件。

1. 不直接使用类的构造函数，而另外提供一个Public的静态方法来构造类的实例。Public保证了它的全局可见性，静态方法保证了不会创建出多余的实例。
2. 将构造函数，拷贝构造函数，operator =设置为Private，即将这些方法隐藏起来。任何企图使用这些函数的方法都将编译期报错。目前，gdU提供了三种实现，示例如下：

```cpp
//Example：
#include “gdsingleton.h”
//第一种实现
//Sample.h
class CSample
{
    CSample();
    ~CSample();
    DECLARE_SINGLETON(CSample)
}

//Sample.cpp
IMPLEMENT_SINGLETON(CSample)

//使用处
if(!CSample::CreateInstance())
{
    printf(“创建不成功”);
}
CSample * pSample = CSample::Instance();

```

```cpp
//Example：
#include “gdsingleton.h”
//第二种实现
//Sample.h
class CSample
{
    CSample();
    ~CSample();
    SINGLETON_FRIEND_CLASS_REGISTER(CSample)
}

//使用处
if(!CSingleton<CSample>::CreateInstance())
{
    printf(“创建不成功”);
}
CSample * pSample = CSingleton<CSample>::Instance();
```

Example：
```cpp
#include “gdsingleton.h”
//第三种实现
//Sample.h
class CSample
{
    CSample();
    ~CSample();
    SINGLETON_FRIEND_CLASS_REGISTER(CSample)
}

typedef CgdSingleton<CSample> CSampleSingleton;

//使用处
if(!CSampleSingleton::CreateInstance())
{
    printf(“创建不成功”);
}
CSample * pSample = CSampleSingleton::Instance();
```
