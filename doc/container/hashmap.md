# HashMap

请见sdhashmap.h。使用Hash桶实现的HashMap相对于Tree结构的Map而言，查找算法复杂度仅为O（1）。在大数据量的存储的情况下
，查找速度非常快。此类并非线程安全。

```cpp
//Example：
#include “sdhashmap.h”

typedef std::string key;
typedef std::string value;
HashMap<key, value> map;
typedef HashMap<key, value>::iterator HashMapItr;

key key1 = “key1”;
value value1 = “value1”;

//插入数据
bool Set(HashMap<key, value> map, key k, value v)
{
    return map.insert(k, v).second;//插入成功返回true，插入失败返回false
}

//获取数据
bool Get(HashMap<key, value> map, key k, value & v)
{
    HashMapItr itr = map.find(k);
    if(itr != map.end())
    {
        v = (*itr).second;
        return true;//获取数据成功
    }
    return false;//没有该数据，获取数据失败
}

//删除数据
bool Remove(HashMap<key, value> map, key k)
{
    return map.erase(k) > 0;//删除成功返回true，没有该元素返回false
}

//是否含有某数据
bool contain(HashMap<key, value> map, key k)
{
    return map.count(k) > 0;//有该元素返回true，没有该元素返回false
}
```
