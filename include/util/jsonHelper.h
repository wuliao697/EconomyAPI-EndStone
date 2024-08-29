//
// Created by admin on 2024/8/12.
//



#include "../cmake-build-debug/_deps/rapidjson-src/include/rapidjson/writer.h"
#include "../cmake-build-debug/_deps/rapidjson-src/include/rapidjson/stringbuffer.h"
#include "../cmake-build-debug/_deps/rapidjson-src/include/rapidjson/prettywriter.h"
#include "../cmake-build-debug/_deps/rapidjson-src/include/rapidjson/document.h"
#include "../../cmake-build-debug/_deps/rapidjson-src/include/rapidjson/istreamwrapper.h"
#include "../../cmake-build-debug/_deps/rapidjson-src/include/rapidjson/filereadstream.h"
#include "../../cmake-build-debug/_deps/rapidjson-src/include/rapidjson/filewritestream.h"

#include "endstone/plugin/plugin.h"
#include "util/files/filesManager.h"
#include "endstone/logger.h"
#include "dataHelper.h"

#include <iostream>
#include <filesystem>
#include <string>

#pragma once


class jsonHelper:public dataHelper{
public:
    /*
     * configInitialize 插件配置文件初始化
     * 已实现基本功能
     */
    static void configInitialize(){
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
                                  .AddMember("language", "zh_CN", cfg_allocator),
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
            std::filesystem::create_directories(FilesManager::getFolder());

            std::ofstream file(FilesManager::getDataPath("config.json"));
            if (file.is_open()) {
                file << buffer.GetString();
                file.close();
            } else {
                std::cerr << "Error opening file" << std::endl;
            }
        }
    }

    /**
     * getConfigData 获取插件配置
     * 待实现
     *
     * @return 返回配置文件选项值
     */
    template <typename T>
    static std::optional<T> getConfigData(const char* settings,const char* options){
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

    /*
     * dataBaseInitialize JSON数据库初始化
     * 已实现基本功能
     */
    static void dataBaseInitialize(){
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

    /*
     * getEconomyData 获取经济数据
     * 待实现
     *
     * 返回数据以数组形式
     */
    std::vector<std::string> getEconomyData(const std::string& uuid) override{
        rapidjson::Document data;

        const char *uuid_str = uuid.c_str();

        std::vector<std::string> result{};

        try{
            data = jsonRead();
        }catch (const std::runtime_error& e){
            throw std::runtime_error(e.what());
        }

        rapidjson::Value& playerObject = data[uuid_str].GetObj();
        rapidjson::Value::ConstMemberIterator itr = data.FindMember(playerObject);

        if (itr == playerObject.MemberEnd()) {
            throw std::runtime_error("Exception caught: Data is not a legal format");
        }

        result.emplace_back(playerObject["playerName"].GetString());
        result.emplace_back(playerObject["money"].GetString());
        return result;
    }

    /*
     * hasEconomyData 检查是否拥有经济数据
     * 已实现基本功能。
     *
     * 返回布尔值
     */

    void hasEconomyData(const std::string& uuid) override{
        rapidjson::Document data;

        const char *uuidCStr = uuid.c_str();

        try{
            data = jsonRead();
        }catch (const std::runtime_error& e){
            throw std::runtime_error(e.what());
        }

        rapidjson::Value::ConstMemberIterator itr;
        itr = data.FindMember(uuidCStr);

        if (itr == data.MemberEnd()) {
            throw std::runtime_error("Exception caught: Data is not a legal format");
        }
    }

    /*
     * addEconomyData 添加经济数据
     * 已实现基本功能
     *
     * 返回布尔值
     */
    void addEconomyData(const std::string& playerName, const std::string& uuid, int& money) override{
        rapidjson::Document data;

        const char* playerNameCstr = playerName.c_str();
        const char* uuidCstr = uuid.c_str();

        try{
            data = jsonRead();
        }catch (const std::runtime_error& e){
            throw std::runtime_error(e.what());
        }

        auto& allocator = data.GetAllocator();

        rapidjson::Value playerObject;

        playerObject.SetObject();
        playerObject.AddMember("playerName", rapidjson::Value(playerNameCstr,allocator), allocator);
        playerObject.AddMember("money", money, allocator);

        data.AddMember(rapidjson::Value(uuidCstr, allocator), playerObject, allocator);

        try{
            jsonWrite(data);
        }catch (const std::runtime_error& e){
            throw std::runtime_error(e.what());
        }
    };


    /**
     * getPlayerMoney 获取玩家金钱
     * 已实现基本功能
     *
     * @param uuid 玩家uuid
     *
     * @return 返回玩家金钱
     */
    int getPlayerMoney(const std::string& uuid) override;

    /*
     * setPlayerMoney 设置玩家金钱
     * 已实现基本功能
     *
     * 返回布尔值
     */
    void setPlayerMoney(const std::string& uuid,const int& money) override;

    /*
     * addPlayerMoney 增加玩家金钱
     * 已初步实现
     */
    void addPlayerMoney(const std::string& uuid,const int& addMoney) override;


    static void jsonWrite(const rapidjson::Document& file){
        FILE *fp;
#ifdef _WIN32
        errno_t err = fopen_s(&fp,FilesManager::getDataPath("database.json").string().c_str(), "wb");
        if (err != 0) {
            delete fp;
            throw std::runtime_error("Exception caught: File opening error");
        }
#else
        fp = nullptr;
        if ((fp= fopen(FilesManager::getDataPath("database.json").string().c_str(),"w"))==nullptr){
            delete fp;
            throw std::runtime_error("Exception caught: File opening error");
        }
#endif
        char writeBuffer[65536];
        rapidjson::FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));
        rapidjson::Writer<rapidjson::FileWriteStream> writer(os);
        file.Accept(writer);
        fclose(fp);
        delete fp;
    }

    static rapidjson::Document jsonRead(){
        rapidjson::Document data;
        FILE *fp;
#ifdef _WIN32
        errno_t err = fopen_s(&fp,FilesManager::getDataPath("database.json").string().c_str() , "rb");
        if (err != 0) {
            throw std::runtime_error("Exception caught: File opening error");
        }
#else
        fp = nullptr;
        if ((fp= fopen(FilesManager::getDataPath("database.json").string().c_str(),"r"))==nullptr){
            delete fp;
            throw std::runtime_error("Exception caught: File opening error");
        }
#endif
        char readBuffer[65536];
        rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
        data.ParseStream(is);
        if (data.HasParseError()){
            fclose(fp);
            throw std::runtime_error("Exception caught: File parsing error");
        }
        fclose(fp);
        return data;
    }
};


 int jsonHelper::getPlayerMoney(const std::string& uuid) {
    rapidjson::Document data;

    try{
        data = jsonRead();
    }catch (const std::runtime_error& e){
        throw std::runtime_error(e.what());
    }

    const char* uuidCStr = uuid.c_str();

    rapidjson::Value::ConstMemberIterator itr;
    itr = data.FindMember(uuidCStr);

    if (itr == data.MemberEnd()) {
        throw std::runtime_error("Exception caught: Data is not a legal format");
    }

    itr = data[uuidCStr].FindMember("money");

    if (itr == data[uuidCStr].MemberEnd()){
        throw std::runtime_error("Exception caught: Data is not a legal format");
    }

    if (!itr->value.Is<int>()){
        throw std::runtime_error("Exception caught: Data is not a legal format");
    }

    return itr->value.GetInt();
}

void jsonHelper::setPlayerMoney(const std::string &uuid, const int &money) {
    rapidjson::Document data;

    try{
        data = jsonRead();
    }catch (const std::runtime_error& e){
        throw std::runtime_error(e.what());
    }

    const char* uuidCStr = uuid.c_str();

    rapidjson::Value::ConstMemberIterator itr;
    itr = data.FindMember(uuidCStr);

    if (itr == data.MemberEnd()) {
        throw std::runtime_error("Exception caught: Data is not a legal format");
    }

    itr = data[uuidCStr].FindMember("money");

    if (itr == data[uuidCStr].MemberEnd()){
        throw std::runtime_error("Exception caught: Data is not a legal format");
    }

    if (!itr->value.Is<int>()){
        throw std::runtime_error("Exception caught: Data is not a legal format");
    }

    try {
        data[uuidCStr]["money"].SetInt(money);
        jsonWrite(data);
    }catch (const std::runtime_error& e){
        throw std::runtime_error(e.what());
    }
}

void jsonHelper::addPlayerMoney(const std::string &uuid, const int &addMoney) {
    rapidjson::Document data;

    try{
        data = jsonRead();
    }catch (const std::runtime_error& e){
        throw std::runtime_error(e.what());
    }

    const char* uuidCStr = uuid.c_str();

    rapidjson::Value::ConstMemberIterator itr;
    itr = data.FindMember(uuidCStr);

    if (itr == data.MemberEnd()) {
        throw std::runtime_error("Exception caught: Data is not a legal format");
    }

    itr = data[uuidCStr].FindMember("money");

    if (itr == data[uuidCStr].MemberEnd()){
        throw std::runtime_error("Exception caught: Data is not a legal format");
    }

    if (!itr->value.Is<int>()){
        throw std::runtime_error("Exception caught: Data is not a legal format");
    }

    try{
        data[uuidCStr]["money"].SetInt(itr->value.GetInt() + addMoney);
        jsonWrite(data);
    }catch(const std::runtime_error& e){
        throw std::runtime_error(e.what());
    }
}


