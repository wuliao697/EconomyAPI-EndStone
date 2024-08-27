//
// Created by admin on 2024/7/29.
//

#include "endstone/plugin/plugin.h"
#include "endstone/event/player/player_join_event.h"
#include "util/jsonHelper.h"

#pragma once

class economyListener {
public:
    explicit economyListener(endstone::Plugin &plugin): plugin_(plugin){
    }

    void onPlayerJoin(endstone::PlayerJoinEvent &event)
    {
        std::string uuid = event.getPlayer().getUniqueId().str();
        if(!hasAccount(uuid)){
            creatAccount(event.getPlayer().getName(),uuid,0);
        }
    }

    bool creatAccount(const std::string& playerName, const std::string& uuid, int money){
        try{
            jsonHelper.addEconomyData(playerName,uuid,money);
            return true;
        }catch (const std::runtime_error& e){
            return false;
        }
    }

    bool hasAccount(const std::string& uuid) {
        try{
            jsonHelper.hasEconomyData(uuid);
            return true;
        }catch (const std::runtime_error& e){
            return false;
        }
    }

private:
    endstone::Plugin &plugin_;
    jsonHelper jsonHelper;
};