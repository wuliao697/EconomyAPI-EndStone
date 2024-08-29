# EconomyAPI-EndStone
## Plugin Introduction
Economy plugin for EndStone.Theoretically supports multiple platforms (not tested).

Welcome to the submission of issues!
Unless the endstone program is retired from history, I'll keep it updated!

## Command Introduction
```
- View your own money
/economy show 

- View online players money(Only OP)
/economy show <playerName>

- Check out the money charts(TODO)
/economy top

- Transferring money to the target online player
/economy pay <playerName> <positiveNumber> 

-Increase the amount of money of the target online player
/economy add <playerName> <positiveNumber> 

- Reduce the amount of money of the target online player
/economy reduce <playerName> <positiveNumber> 

- Setting the target online player's money
/economy set <playerName> <positiveNumber>
```
## Permission Introduction
```
- Ordinary Player Permission Command(You can use the pay|top|show parameter)
economy.use.base

- Permissions represent the enumeration parameters that can be used
economy.command.show   
economy.command.top     
economy.command.pay     

- The following are used by administrators
economy.command.add
economy.command.reduce
economy.command.set
economy.command.show.others
```

Note:I am waiting for a plugin like luckperms before you can configure these permissions. Otherwise, you can only change it from inside the plugin

## Interface Related
```C++
extern "C" __declspec(dllexport) int getPlayerMoney(std::string& uuid){
    jsonHelper jsonHelper;
    try {
        return jsonHelper.getPlayerMoney(uuid);
    }catch (const std::runtime_error& e){
        return -1;
    }
}

extern "C" __declspec(dllexport) bool addPlayerMoney(std::string& uuid,int& money){
    jsonHelper jsonHelper;
    try {
        jsonHelper.addPlayerMoney(uuid, money);
        return true;
    }catch (const std::runtime_error& e){
        return false;
    }
}

extern "C" __declspec(dllexport) bool setPlayerMoney(const std::string& uuid,const int& money){
    jsonHelper jsonHelper;
    try {
        jsonHelper.setPlayerMoney(uuid, money);
        return true;
    }catch (const std::runtime_error& e){
        return false;
    }
}
```

## TODO(Chinese)
- 实现配置文件里的功能
- 支持i18n
- 使用持久层框架支持关系型数据库(看情况)
- 实现实体货币/支持多种货币共存(看情况)

## Express gratitude
### Plugin online testing
- Mcayear
### Plugin guide
- mdx