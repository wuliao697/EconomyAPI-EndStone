//
// Created by admin on 2024/7/28.
//

#include "economyAPI.h"

ENDSTONE_PLUGIN("economy_api", "0.1.1", economyAPI)
{
    description = "Economy for minecraftBE";
    command("economy")
            .description("Economy System")
            .usages("/economy (show|top|pay|add|reduce|set)<parameter:enum> [playerName:player] [money:int]")
            .permissions("economy.use.base");

    permission("economy.use.base")
    /*
     * children(true是继承parent权限范围 false是反转)
     */
            .description("Allow users to use the /economy command.")
            .default_(endstone::PermissionDefault::True)
            .children("economy.command.show", true)
            .children("economy.command.pay", true)
            .children("economy.command.add", false)
            .children("economy.command.reduce", false)
            .children("economy.command.set", false)
            .children("economy.command.show.others", false)
            .children("economy.command.top", true);
}


#ifdef _WIN32
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
#else
extern "C" {

    bool setPlayerMoney(const std::string& uuid,const int& money){
        jsonHelper jsonHelper;
        try {
            jsonHelper.setPlayerMoney(uuid, money);
            return true;
        }catch (const std::runtime_error& e){
            return false;
        }
    }

    int getPlayerMoney(std::string& uuid){
        jsonHelper jsonHelper;
        try {
            return jsonHelper.getPlayerMoney(uuid);
        }catch (const std::runtime_error& e){
            return -1;
        }
    }

    bool addPlayerMoney(std::string& uuid,int& money){
        jsonHelper jsonHelper;
        try {
            jsonHelper.addPlayerMoney(uuid, money);
            return true;
        }catch (const std::runtime_error& e){
            return false;
        }
    }
}
#endif



