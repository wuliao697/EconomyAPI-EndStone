//
// Created by admin on 2024/11/29.
//
#pragma once

#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/writer.h"
#include "rapidjson/prettywriter.h"

#include "util/files/filesManager.h"

//clang这里警告我也不知道什么原因，以后再填
static rapidjson::Document cfg;
static rapidjson::Document lang;

class filesInitialize{
public:
    /**
     * dataBaseInitialize JSON数据库初始化
     * 已实现基本功能
     */
    static void dataBaseInitialize();

    /**
     * languageInitialize 语言配置初始化
     * TODO
     */
    static void languageInitialize();

    /**
     * configInitialize 插件配置文件初始化
     * 已实现基本功能
     */
    static void configInitialize();
};

void filesInitialize::configInitialize() {
    //检测文件是否存在
    if (!std::filesystem::exists(FilesManager::getDataPath("config.json"))) {
        cfg.SetObject();
        auto& cfg_allocator = cfg.GetAllocator();

        cfg.AddMember("money",
                      rapidjson::Value(rapidjson::kObjectType)
                              .AddMember("monetary-unit", "¥", cfg_allocator)
                              .AddMember("currency-location", true,cfg_allocator)
                              .AddMember("default", 1000, cfg_allocator)
                              .AddMember("max", 2147483647, cfg_allocator),
                      cfg_allocator);
        cfg.AddMember("setting",
                      rapidjson::Value(rapidjson::kObjectType)
                              .AddMember("version",1.0,cfg_allocator)
                              .AddMember("language", "en_US", cfg_allocator),
                      cfg_allocator);
        cfg.AddMember("database",
                      rapidjson::Value(rapidjson::kObjectType)
                              .AddMember("type", rapidjson::Value(rapidjson::kArrayType).PushBack("json", cfg_allocator), cfg_allocator)
                              .AddMember("connect", false, cfg_allocator)
                              .AddMember("address", "", cfg_allocator)
                              .AddMember("port", "", cfg_allocator)
                              .AddMember("userName", "", cfg_allocator)
                              .AddMember("password", "", cfg_allocator)
                              .AddMember("detail", rapidjson::Value(rapidjson::kArrayType), cfg_allocator),
                      cfg_allocator);
        rapidjson::StringBuffer buffer;
        rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
        cfg.Accept(writer);
        std::filesystem::create_directories(FilesManager::getDataFolder());

        std::ofstream file(FilesManager::getDataPath("config.json"));
        if (file.is_open()) {
            file << buffer.GetString();
            file.close();
        } else {
            throw std::runtime_error("Exception caught: Error opening file");
        }
    }

    cfg.SetObject();
    std::ifstream ifs(FilesManager::getDataPath("config.json"));
    if (ifs.is_open()) {
        rapidjson::IStreamWrapper isw(ifs);
        cfg.ParseStream(isw);
        ifs.close();
    } else {
        throw std::runtime_error("Exception caught: Error reading file");
    }
}


void filesInitialize::dataBaseInitialize(){
    if (!std::filesystem::exists(FilesManager::getDataPath("database.json"))){
        rapidjson::Document data;
        data.SetObject();

        rapidjson::StringBuffer buffer;
        rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
        data.Accept(writer);

        std::ofstream file(FilesManager::getDataPath("database.json"));
        if (file.is_open()) {
            file << buffer.GetString();
            file.close();
        } else {
            throw std::runtime_error("Exception caught: Error opening file");
        }
    }
}

void filesInitialize::languageInitialize(){
    if (!std::filesystem::exists(FilesManager::getLanguagePath( "en_US.json"))){
        lang.SetObject();
        auto& lang_allocator = lang.GetAllocator();

        lang.AddMember("target-not-found","The target player account was not found.",lang_allocator);
        lang.AddMember("player-balance","This player's current balance: ",lang_allocator);
        lang.AddMember("own-balance","Your current balance is: ",lang_allocator);
        lang.AddMember("check-format","Please check the format of your input.",lang_allocator);
        lang.AddMember("transfer-error","You can't transfer money to yourself.",lang_allocator);
        lang.AddMember("transfer-anomaly","Error when transferring money.",lang_allocator);
        lang.AddMember("transfer-successful","Transfer successful!",lang_allocator);
        lang.AddMember("successful-arrival","You have been successfully credited:",lang_allocator);
        lang.AddMember("money-reduce","Target account amount reduced successfully",lang_allocator);
        lang.AddMember("money-add","Target account amount add successfully",lang_allocator);
        lang.AddMember("money-set","Target account amount set successfully",lang_allocator);
        lang.AddMember("no-permission","You don't have this permission",lang_allocator);

        rapidjson::StringBuffer buffer;
        rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
        lang.Accept(writer);

        std::filesystem::create_directories(FilesManager::getLanguageFolder());

        std::ofstream file(FilesManager::getLanguagePath("en_US.json"));
        if (file.is_open()) {
            file << buffer.GetString();
            file.close();
        } else {
            throw std::runtime_error("Exception caught: Error opening file");
        }
    }

    //TODO:lang文件校验
    lang.SetObject();
    std::string langFile = cfg["setting"]["language"].GetString();
    std::ifstream ifs(FilesManager::getLanguagePath(langFile + ".json"));
    if (ifs.is_open()) {
        rapidjson::IStreamWrapper isw(ifs);
        lang.ParseStream(isw);
        ifs.close();
    } else {
        throw std::runtime_error("Exception caught: Error reading file");
    }
}
