//
// Created by admin on 2024/7/28.
//

#pragma once

#include "endstone/command/command_executor.h"
#include "endstone/color_format.h"

#include "util/data/poco/jsonHelper.h"
#include "util/files/filesInitialize.h"

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

        /* debug
        for (const std::string& str:args) {
            std::cout << str<<std::endl;
        }*/
        if(command.getName() != "economy"){
            return false;
        }

        std::string uuid;
        std::string targetUuid;
        int amount;
        endstone::Server& server= sender.getServer();

        if (args.size()>=2){
            if(!isOnlinePlayer(server,args[1])){
                    sender.sendMessage(endstone::ColorFormat::Red  + lang["target-not-found"].GetString()+ endstone::ColorFormat::Reset);
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
                sender.sendMessage(endstone::ColorFormat::Gold + lang["player-balance"].GetString() + money + endstone::ColorFormat::Reset);
                return true;
            }
            money = std::to_string(jsonHelper.getPlayerMoney(uuid));
            sender.sendMessage(endstone::ColorFormat::Gold + lang["player-balance"].GetString() + money + endstone::ColorFormat::Reset);
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
                sender.sendMessage(endstone::ColorFormat::Red + lang["check-format"].GetString() + endstone::ColorFormat::Reset);
                return false;
            }
            if(args[1] == sender.getName()){
                sender.sendMessage(endstone::ColorFormat::Red + lang["transfer-error"].GetString() + endstone::ColorFormat::Reset);
                return false;
            }
            if (!payPlayerMoney(uuid,targetUuid,amount)){
                sender.sendMessage(endstone::ColorFormat::Red + lang["transfer-anomaly"].GetString() + endstone::ColorFormat::Reset);
                return false;
            }
            sender.sendMessage(endstone::ColorFormat::Green + lang["transfer-successful"].GetString() + endstone::ColorFormat::Reset);
            server.getPlayer(args[1])->sendMessage(endstone::ColorFormat::Green + lang["successful-arrival"].GetString() + args[2] + cfg["money"]["monetary-unit"].GetString() + endstone::ColorFormat::Reset);
            return true;
        }
        if (!sender.isOp()){
            sender.sendMessage(endstone::ColorFormat::Red + lang["no-permission"].GetString() + endstone::ColorFormat::Reset);
            return false;
        }
        //用的不是很安全
        if (args[0] == "add"){
            if(!legalityCheck(targetUuid,sender,amount)){
                return false;
            }
            jsonHelper.addPlayerMoney(targetUuid,amount);
            sender.sendMessage(endstone::ColorFormat::Green + lang["money-add"].GetString() + endstone::ColorFormat::Reset);
            return true;
        }
        if (args[0] == "reduce"){
            if(!legalityCheck(targetUuid,sender,amount)){
                return true;
            }
            jsonHelper.addPlayerMoney(targetUuid,-amount);
            sender.sendMessage(endstone::ColorFormat::Green + lang["money-reduce"].GetString() + endstone::ColorFormat::Reset);
            return true;
        }
        if (args[0] == "set"){
            if(!legalityCheck(targetUuid,sender,amount)){
                return true;
            }
            jsonHelper.setPlayerMoney(targetUuid,amount);
            sender.sendMessage(endstone::ColorFormat::Green + lang["money-set"].GetString() + endstone::ColorFormat::Reset);
            return true;
        }
        return false;
    };

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



