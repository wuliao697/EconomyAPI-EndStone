//
// Created by admin on 2024/8/12.
//

#pragma once

#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/filewritestream.h"

#include "endstone/plugin/plugin.h"

#include "util/files/filesManager.h"
#include "util/data/poco/dataHelper.h"
#include "util/data/dao/jsonBase.h"

#include <iostream>
#include <filesystem>
#include <string>


class jsonHelper:public dataHelper {
public:

    /**
     * getEconomyData 获取经济数据
     * 待实现
     *
     * 返回数据以数组形式
     */
    std::vector<std::string> getEconomyData(const std::string &uuid) override;

    /**
     * hasEconomyData 检查是否拥有经济数据
     * 已实现基本功能。
     *
     * 返回布尔值
     */

    void hasEconomyData(const std::string &uuid) override;

    /**
     * addEconomyData 添加经济数据
     * 已实现基本功能
     *
     * 返回布尔值
     */
    void addEconomyData(const std::string &playerName, const std::string &uuid, int &money) override;


    /**
     * getPlayerMoney 获取玩家金钱
     * 已实现基本功能
     *
     * @param uuid 玩家uuid
     *
     * @return 返回玩家金钱
     */
    int getPlayerMoney(const std::string &uuid) override;

    int getPlayerMoney(const char* uuid) override;

    /**
     * setPlayerMoney 设置玩家金钱
     * 已实现基本功能
     *
     * @param uuid 玩家uuid
     *
     * @throw DataError
     */
    void setPlayerMoney(const std::string &uuid, const int &money) override;

    void setPlayerMoney(const char* uuid, const int &money) override;

    /**
     * addPlayerMoney 增加玩家金钱
     * 已初步实现
     *
     * @param uuid 玩家uuid
     *
     * @throw DataError
     */
    void addPlayerMoney(const std::string &uuid, const int &addMoney) override;

    void addPlayerMoney(const char* uuid, const int &addMoney) override;
};



int jsonHelper::getPlayerMoney(const std::string& uuid) {
    rapidjson::Document data;

    try{
        data = jsonBase::jsonRead();
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
};

int jsonHelper::getPlayerMoney(const char *uuid) {
    rapidjson::Document data;

    try{
        data = jsonBase::jsonRead();
    }catch (const std::runtime_error& e){
        throw std::runtime_error(e.what());
    }

    rapidjson::Value::ConstMemberIterator itr;
    itr = data.FindMember(uuid);

    if (itr == data.MemberEnd()) {
        throw std::runtime_error("Exception caught: Data is not a legal format");
    }

    itr = data[uuid].FindMember("money");

    if (itr == data[uuid].MemberEnd()){
        throw std::runtime_error("Exception caught: Data is not a legal format");
    }

    if (!itr->value.Is<int>()){
        throw std::runtime_error("Exception caught: Data is not a legal format");
    }

    return itr->value.GetInt();
};

void jsonHelper::setPlayerMoney(const std::string &uuid, const int &money) {
    rapidjson::Document data;

    try{
        data = jsonBase::jsonRead();
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
        jsonBase::jsonWrite(data);
    }catch (const std::runtime_error& e){
        throw std::runtime_error(e.what());
    }
};

void jsonHelper::setPlayerMoney(const char *uuid, const int &money) {
    rapidjson::Document data;

    try{
        data = jsonBase::jsonRead();
    }catch (const std::runtime_error& e){
        throw std::runtime_error(e.what());
    }

    rapidjson::Value::ConstMemberIterator itr;
    itr = data.FindMember(uuid);

    if (itr == data.MemberEnd()) {
        throw std::runtime_error("Exception caught: Data is not a legal format");
    }

    itr = data[uuid].FindMember("money");

    if (itr == data[uuid].MemberEnd()){
        throw std::runtime_error("Exception caught: Data is not a legal format");
    }

    if (!itr->value.Is<int>()){
        throw std::runtime_error("Exception caught: Data is not a legal format");
    }

    try {
        data[uuid]["money"].SetInt(money);
        jsonBase::jsonWrite(data);
    }catch (const std::runtime_error& e){
        throw std::runtime_error(e.what());
    }
};

void jsonHelper::addPlayerMoney(const std::string &uuid, const int &addMoney) {
    rapidjson::Document data;

    try{
        data = jsonBase::jsonRead();
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
        jsonBase::jsonWrite(data);
    }catch(const std::runtime_error& e){
        throw std::runtime_error(e.what());
    }
};

void jsonHelper::addPlayerMoney(const char *uuid, const int &addMoney) {
    rapidjson::Document data;

    try{
        data = jsonBase::jsonRead();
    }catch (const std::runtime_error& e){
        throw std::runtime_error(e.what());
    }


    rapidjson::Value::ConstMemberIterator itr;
    itr = data.FindMember(uuid);

    if (itr == data.MemberEnd()) {
        throw std::runtime_error("Exception caught: Data is not a legal format");
    }

    itr = data[uuid].FindMember("money");

    if (itr == data[uuid].MemberEnd()){
        throw std::runtime_error("Exception caught: Data is not a legal format");
    }

    if (!itr->value.Is<int>()){
        throw std::runtime_error("Exception caught: Data is not a legal format");
    }

    try{
        data[uuid]["money"].SetInt(itr->value.GetInt() + addMoney);
        jsonBase::jsonWrite(data);
    }catch(const std::runtime_error& e){
        throw std::runtime_error(e.what());
    }
};

void jsonHelper::addEconomyData(const std::string &playerName, const std::string &uuid, int &money){
    rapidjson::Document data;

    const char *playerNameCstr = playerName.c_str();
    const char *uuidCstr = uuid.c_str();

    try {
        data = jsonBase::jsonRead();
    } catch (const std::runtime_error &e) {
        throw std::runtime_error(e.what());
    }
    auto &allocator = data.GetAllocator();

    rapidjson::Value playerObject;

    playerObject.SetObject();
    playerObject.AddMember("playerName", rapidjson::Value(playerNameCstr, allocator), allocator);
    playerObject.AddMember("money", money, allocator);

    data.AddMember(rapidjson::Value(uuidCstr, allocator), playerObject, allocator);

    try {
        jsonBase::jsonWrite(data);
    } catch (const std::runtime_error &e) {
        throw std::runtime_error(e.what());
    }
};

void jsonHelper::hasEconomyData(const std::string &uuid){
    rapidjson::Document data;

    const char *uuidCStr = uuid.c_str();

    try {
        data = jsonBase::jsonRead();
    } catch (const std::runtime_error &e) {
        throw std::runtime_error(e.what());
    }

    rapidjson::Value::ConstMemberIterator itr;
    itr = data.FindMember(uuidCStr);

    if (itr == data.MemberEnd()) {
        throw std::runtime_error("Exception caught: Data is not a legal format");
    }
}

std::vector<std::string> jsonHelper::getEconomyData(const std::string& uuid){
    rapidjson::Document data;

    const char *uuid_str = uuid.c_str();

    std::vector<std::string> result{};

    try{
        data = jsonBase::jsonRead();
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
