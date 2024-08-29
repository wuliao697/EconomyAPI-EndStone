//
// Created by admin on 2024/7/28.
//

#include "endstone/plugin/plugin.h"
#include "endstone/event/event_handler.h"
#include "endstone/command/plugin_command.h"
#include "endstone/event/player/player_join_event.h"

#include "economyListener.h"
#include "command/economyCommand.h"
#include "util/jsonHelper.h"

#include <iostream>

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

class economyAPI : public endstone::Plugin{

    public:
    void onLoad() override
    {
        getLogger().info("EconomyAPI Loading!");
    }

    void onEnable() override{
        getLogger().info("EconomyAPI Activated");

        if (auto *command = getCommand("economy")) {
            command->setExecutor(std::make_unique<economyCommand>());
        }

        try{
            jsonHelper::configInitialize();
            jsonHelper::dataBaseInitialize();
        }catch (const std::runtime_error& e){
            getLogger().error(e.what());
        }

        listener_ = std::make_unique<economyListener>(*this);
        registerEvent(&economyListener::onPlayerJoin, *listener_, endstone::EventPriority::High);
    }

    void onDisable() override
    {
        getLogger().info("EconomyAPI Disable!");
    }

    void registerCommand(const std::vector<std::string>& names, std::unique_ptr<CommandExecutor>& executor) {
        for (const std::string& name : names) {
            auto * command = getCommand(name);
            if (command == nullptr) {
                throw std::invalid_argument("Unknown command '" + name + "'");
            }
            command->setExecutor(std::move(executor));
        }
    }


private:
    std::unique_ptr<economyListener> listener_;
    jsonHelper jsonHelper;
};

