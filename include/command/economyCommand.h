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

    bool onCommand(endstone::CommandSender &sender, const endstone::Command &command, const std::vector<std::string> &args) override {
        jsonHelper jsonHelper;

        if (sender.asConsole() != nullptr) {
            sender.sendMessage("todo功能老弟");
            return true;
        }

        for (const std::string& str:args) {
            std::cout << str<<std::endl;
        }

        if (command.getName() == "economy") {
            std::string uuid;
            std::string targetUuid;
            int amount;

            endstone::Server& server= sender.getServer();

            if (args.size()>=2){
                if(!isOnlinePlayer(server,args[1])){
                    sender.sendMessage(endstone::ColorFormat::Red  + "目标玩家账户并未找到"+ endstone::ColorFormat::Reset);
                    return false;
                }
                targetUuid = server.getPlayer(args[1])->getUniqueId().str();
            }
            /*
             * 匹配第一级参数
             */
            uuid = server.getPlayer(sender.getName())->getUniqueId().str();
            if (args[0] == "top") {
                sender.sendMessage("todo功能老弟");
                return true;
            }
            if (args[0] == "show") {
                std::string money;
                if (sender.isOp() && !targetUuid.empty()) {
                    if (!legalityCheck(targetUuid,sender)){
                        return false;
                    }
                    money = std::to_string(jsonHelper.getPlayerMoney(targetUuid));
                    sender.sendMessage(endstone::ColorFormat::Gold + "该玩家当前余额: " + money + endstone::ColorFormat::Reset);
                    return true;
                }
                money = std::to_string(jsonHelper.getPlayerMoney(uuid));
                sender.sendMessage(endstone::ColorFormat::Gold + "您当前的余额为: " + money + endstone::ColorFormat::Reset);
                return true;
            }
            /*
             * 匹配第一级参数
             */
            if( args.size() == 3){
                amount = stoi(args[2]);
            }
            if (args[0] == "pay") {
                if (targetUuid.empty() || amount <= 0){
                    sender.sendMessage(endstone::ColorFormat::Red + "请检查你输入的格式" + endstone::ColorFormat::Reset);
                    return false;
                }
                if(args[1] == sender.getName()){
                    sender.sendMessage(endstone::ColorFormat::Red + "不能给自己转账" + endstone::ColorFormat::Reset);
                    return false;
                }
                if (!payPlayerMoney(uuid,targetUuid,amount)){
                    sender.sendMessage(endstone::ColorFormat::Red + "转账时错误。" + endstone::ColorFormat::Reset);
                    return false;
                }
                sender.sendMessage(endstone::ColorFormat::Green + "您已成功转账" + endstone::ColorFormat::Reset);
                server.getPlayer(args[1])->sendMessage(endstone::ColorFormat::Green + "您已成功到账"+ args[2] + "货币" + endstone::ColorFormat::Reset);
                return true;
            }
            if (!sender.isOp()){
                sender.sendMessage(endstone::ColorFormat::Red + "你个人机" + endstone::ColorFormat::Reset);
                return false;
            }
            //用的不是很安全
            if (args[0] == "add"){
                if(!legalityCheck(targetUuid,sender,amount)){
                    return false;
                }
                jsonHelper.addPlayerMoney(targetUuid,amount);
                sender.sendMessage(endstone::ColorFormat::Green + "目标账户金额增加成功" + endstone::ColorFormat::Reset);
                return true;
            }
            if (args[0] == "reduce"){
                if(!legalityCheck(targetUuid,sender,amount)){
                    return true;
                }
                jsonHelper.addPlayerMoney(targetUuid,-amount);
                sender.sendMessage(endstone::ColorFormat::Green + "目标账户金额减少成功" + endstone::ColorFormat::Reset);
                return true;
            }
            if (args[0] == "set"){
                if(!legalityCheck(targetUuid,sender,amount)){
                    return true;
                }
                jsonHelper.setPlayerMoney(targetUuid,amount);
                sender.sendMessage(endstone::ColorFormat::Green + "目标账户金额设置成功" + endstone::ColorFormat::Reset);
                return true;
            }
        }
        return false;
    }

    static bool payPlayerMoney(std::string& transferor,std::string& transferee,int& money){
        jsonHelper jsonHelper;
        if (jsonHelper.getPlayerMoney(transferor) < money){
            return false;
        }
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

    static bool legalityCheck(const std::string& uuid,endstone::CommandSender &sender,int money = 1){
        jsonHelper jsonHelper;
        if (uuid.empty() || money <= 0){
            sender.sendMessage(endstone::ColorFormat::Red + "请检查你输入的格式" + endstone::ColorFormat::Reset);
            return false;
        }
        try{
            jsonHelper.hasEconomyData(uuid);
            return true;
        }catch (const std::runtime_error& e){
            sender.sendMessage(endstone::ColorFormat::Red  + "目标玩家账户并未找到"+ endstone::ColorFormat::Reset);
            return false;
        }
    }

    static bool isOnlinePlayer(endstone::Server &server,const std::string& player){
        std::vector<endstone::Player*> onlinePlayers = server.getOnlinePlayers();
        std::vector<endstone::Player*>::iterator it;
        it = find(onlinePlayers.begin(), onlinePlayers.end(), server.getPlayer(player));
        if (it != onlinePlayers.end()){
            onlinePlayers.clear();
            return true;
        }
        else{
            onlinePlayers.clear();
            return false;
        }
    }
};



