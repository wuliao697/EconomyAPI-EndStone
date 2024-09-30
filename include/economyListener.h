//
// Created by admin on 2024/7/29.
//
#pragma once

#include "endstone/plugin/plugin.h"
#include "endstone/event/player/player_join_event.h"
#include "util/jsonHelper.h"


class economyListener {
public:
    explicit economyListener(endstone::Plugin &plugin): plugin_(plugin){
    }

    void onPlayerJoin(endstone::PlayerJoinEvent &event)
    {
        std::string uuid = event.getPlayer().getUniqueId().str();
        const std::string playerName = event.getPlayer().getName();
        if(!hasAccount(uuid)){
            creatAccount(event.getPlayer().getName(),uuid,0);
            plugin_.getLogger().info("玩家: "+ playerName +" 账户创建成功");
        }
        plugin_.getLogger().info(playerName);
    }

    bool creatAccount(const std::string& playerName, std::string& uuid, int money){
        try{
            jsonHelper_.addEconomyData(playerName,uuid,money);
            return true;
        }catch (const std::runtime_error& e){
            return false;
        }
    }

    bool hasAccount(const std::string& uuid) {
        try{
            jsonHelper_.hasEconomyData(uuid);
            return true;
        }catch (const std::runtime_error& e){
            return false;
        }
    }

private:
    endstone::Plugin &plugin_;
    jsonHelper jsonHelper_;
};