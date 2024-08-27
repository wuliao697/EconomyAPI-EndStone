# EconomyAPI-EndStone
## Plugin Introduction
Economy plugin for EndStone.Theoretically supports multiple platforms (not tested).


Welcome to the submission of issues!
Unless the endstone program is retired from history, I'll keep it updated!

## Command Introduction
```
- View your own money
/economy show

- Check out the money charts
/economy top

- Transferring money to the target player
/economy pay <playerName> <positiveNumber> 

-Increase the amount of money of the target player
/economy add <playerName> <positiveNumber> 

- Reduce the amount of money of the target player
/economy reduce <playerName> <positiveNumber> 

- Setting the target player's money
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

economy.command.add
economy.command.reduce
economy.command.set
economy.command.show.others
```

Note:I am waiting for a plugin like luckperms before you can configure these permissions. Otherwise, you can only change it from inside the plugin

## TODO(Chinese)
- 实现配置文件里的功能
- 支持i18n
- 使用持久层框架支持关系型数据库(看情况)
- 实现实体货币/支持多种货币共存(看情况)