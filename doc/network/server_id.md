# ServerID

请见gdserverid.h。serverid是盛大内部网游服务器的标识符。它是gdnet，gdpipe，gdgate的基础。

```cpp
//Example：
CgdServerId ServerId;
ServerId.SetID(“1-1-6-1”);
UINT32 id = ServerId.AsInteger();
UINT32 groupId = ServerId.GetGroupId();
UINT32 serverType = ServerId.GetServerType();
UINT32 serverIndex = ServerId.GetServerIndex();
UINT32 areaId = ServerId.GetAreaId();
```
