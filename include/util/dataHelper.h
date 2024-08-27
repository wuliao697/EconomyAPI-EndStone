//
// Created by admin on 2024/8/26.
//
#include "endstone/plugin/plugin.h"

#include <iostream>
#include <filesystem>
#include <string>

#pragma once

class dataHelper{
public:
    virtual std::vector<std::string> getEconomyData(const std::string& uuid) = 0;
    virtual void addEconomyData(const std::string& playerName, const std::string& uuid, int& money) = 0;
    virtual void hasEconomyData(const std::string& uuid) = 0;
    virtual int getPlayerMoney(const std::string& uuid) = 0;
    virtual void addPlayerMoney(const std::string& uuid,const int& addMoney) = 0;
    virtual void setPlayerMoney(const std::string& uuid,const int& money) = 0;
};
