//
// Created by admin on 2024/10/5.
//

#pragma once

#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/writer.h"
#include "rapidjson/prettywriter.h"

#include <filesystem>
#include <iostream>
#include <optional>

#include "util/files/filesManager.h"

class jsonConfig{
public:

    /**
     * configInitialize 插件配置文件初始化
     * 已实现基本功能
     */
    static void configInitialize();

    /**
     * getConfigData 获取插件配置
     * 待实现
     *
     * @return 返回配置文件选项值
     */
    template <typename T>
    static std::optional<T> getConfigData(const char* settings,const char* options);

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
};

void jsonConfig::configInitialize() {
    rapidjson::Document cfg;
    cfg.SetObject();
    auto& cfg_allocator = cfg.GetAllocator();
    //检测文件是否存在
    if (!std::filesystem::exists(FilesManager::getDataPath("config.json"))) {
        cfg.AddMember("money",
                      rapidjson::Value(rapidjson::kObjectType)
                              .AddMember("monetary-unit", "¥", cfg_allocator)
                              .AddMember("default", 1000, cfg_allocator)
                              .AddMember("max", 2147483647, cfg_allocator)
                              .AddMember("currency-location", true,cfg_allocator),
                      cfg_allocator);
        cfg.AddMember("setting",
                      rapidjson::Value(rapidjson::kObjectType)
                              .AddMember("language", "en_us", cfg_allocator),
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
            std::cerr << "Error opening file" << std::endl;
        }
    }
}

template<typename T>
std::optional<T> jsonConfig::getConfigData(const char *settings, const char *options) {
    rapidjson::Document cfg;
    std::ifstream file(FilesManager::getDataPath("config.json"));

    if (!file.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return std::nullopt;
    }

    rapidjson::IStreamWrapper isw(file);
    cfg.SetObject();
    cfg.ParseStream(isw);

    if (cfg.HasParseError()){
        throw std::runtime_error("Exception caught: File parsing error");
    }

    rapidjson::Value::ConstMemberIterator itr = cfg[settings].FindMember(options);

    try {
        if (!itr->value.Is<T>()){
            throw std::runtime_error("Exception caught: options is not a legal format");
        }
        return itr->value.Get<T>();
    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
        return std::nullopt;
    }
}

void jsonConfig::dataBaseInitialize(){
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
            std::cerr << "Error opening file" << std::endl;
        }
    }
};

void jsonConfig::languageInitialize(){
    if (!std::filesystem::exists(FilesManager::getLanguagePath("en_us"))){
        rapidjson::Document lang;
        auto& lang_allocator = lang.GetAllocator();
        lang.SetObject();

        lang.AddMember("target-not-found","The target player account was not found.",lang_allocator);
        lang.AddMember("player-balance","This player's current balance: ",lang_allocator);
        lang.AddMember("own-balance","Your current balance is: ",lang_allocator);
        lang.AddMember("check-format","Please check the format of your input.",lang_allocator);
        lang.AddMember("transfer-error","You can't transfer money to yourself.",lang_allocator);
        lang.AddMember("transfer-anomaly","Error when transferring money.",lang_allocator);
        lang.AddMember("transfer-successful","Transfer successful!",lang_allocator);
        lang.AddMember("successful-arrival","You have been successfully credited",lang_allocator);
        lang.AddMember("money-reduce","Target account amount reduced successfully",lang_allocator);
        lang.AddMember("money-add","Target account amount add successfully",lang_allocator);
        lang.AddMember("money-set","Target account amount set successfully",lang_allocator);


        rapidjson::StringBuffer buffer;
        rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
        lang.Accept(writer);

        std::filesystem::create_directories(FilesManager::getLanguageFolder());

        std::ofstream file(FilesManager::getLanguagePath("en_us"));
        if (file.is_open()) {
            file << buffer.GetString();
            file.close();
        } else {
            std::cerr << "Error opening file" << std::endl;
        }
    }
}