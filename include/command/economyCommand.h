//
// Created by admin on 2024/7/28.
//


#include "endstone/command/command_executor.h"
#include "endstone/color_format.h"
#include "util/jsonHelper.h"

#pragma once

    /*
    * sender.hasPermission待做
    */
class economyCommand : public endstone::CommandExecutor{

    bool onCommand(endstone::CommandSender &sender, const endstone::Command &command, const std::vector<std::string> &args) override
    {
        if(sender.asConsole() != nullptr){
            sender.sendMessage("todo功能老弟");
            return true;
        }
        if (command.getName() == "economy")
        {
            std::string uuid = sender.getServer().getPlayer(sender.getName())->getUniqueId().str();
            /*
             * 匹配第一级参数
             */
            if (args[0] == "show") {
                std::string moneyMsg = std::to_string(jsonHelper.getPlayerMoney(uuid));
                sender.sendMessage(endstone::ColorFormat::Gold + "您当前的余额为: " + moneyMsg + endstone::ColorFormat::Reset);
                return true;
            }
            if (args[0] == "top"){
                sender.sendMessage("todo功能老弟");
                return true;
            }
            /*
             * 检查第二级,第三级参数是否没填
             */
            if (args[2].empty()){
                sender.sendMessage(endstone::ColorFormat::Red + "不转钱就别用命令" + endstone::ColorFormat::Reset);
                return false;
            }
            if (args[1].empty()){
                sender.sendMessage(endstone::ColorFormat::Red + "不转钱就别用命令" + endstone::ColorFormat::Reset);
                return false;
            }
            /*
            * 匹配第一级参数
            */
            std::string targetUuid = sender.getServer().getPlayer(args[1])->getUniqueId().str();
            const int amount = canToInt(args[2]);
            if (args[0] == "pay") {
                if (canToInt(args[2])<0){
                    sender.sendMessage(endstone::ColorFormat::Red + "你给人家转1w得了" + endstone::ColorFormat::Reset);
                    return false;
                }
                if(args[1] == sender.getName()){
                    sender.sendMessage(endstone::ColorFormat::Red + "不能给自己转账" + endstone::ColorFormat::Reset);
                    return false;
                }else{
                    return payPlayerMoney(uuid,targetUuid,amount);
                }
            }
            if (sender.isOp()){
                sender.sendMessage(endstone::ColorFormat::Red + "你个人机" + endstone::ColorFormat::Reset);
                return false;
            }
            if (args[0] == "add"){
                jsonHelper.addPlayerMoney(targetUuid,amount);
                return true;
            }
            if (args[0] == "reduce"){
                jsonHelper.addPlayerMoney(targetUuid,-amount);
                return true;
            }
            if (args[0] == "set"){
                jsonHelper.setPlayerMoney(targetUuid,amount);
                return true;
            }
        }
        return false;
    }

    bool payPlayerMoney(std::string& transferor,std::string& transferee,int money){
        try{
            jsonHelper.addPlayerMoney(transferor,-money);
            jsonHelper.addPlayerMoney(transferee,money);
            return true;
        }catch (const std::exception& e){
            std::cerr << "Exception caught: " << e.what() << std::endl;
            return false;
        }
    }

    static int canToInt(const std::string& str){
        try{
            return std::stoi(str);
        }catch(const std::runtime_error& e){
            return 0;
        }
    }
private:
    jsonHelper jsonHelper;
};



