//
// Created by admin on 2024/8/26.
//
#include "util/dataHelper.h"

class TestHelper:public FileHelper{
public:
    void dataBaseInitialize() override{
        getLogger().info("数据库初始化");

    }
    bool getPlayerMoney() override{
        getLogger().info("0");
        return true;
    }
};
