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


class economyAPI : public endstone::Plugin{

    public:
    void onLoad() override
    {
        getLogger().info("onLoad is called");
    }

    void onEnable() override{
        getLogger().info("onEnable is called");

        if (auto *command = getCommand("economy")) {
            command->setExecutor(std::make_unique<economyCommand>());
        }


        //8533950f-514c-3e7a-8871-6761d3b60501 uuid
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
        getLogger().info("onDisable is called");
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
