//
// Created by admin on 2024/10/5.
//

#pragma once

#include "util/files/filesInitialize.h"

class jsonConfig{
public:
    /**
     * getConfigData 获取插件配置
     * 待实现
     *
     * @return 返回配置文件选项值
     */
    template <typename T>
    std::optional<T> getConfigData(const std::string&  settings,const std::string& options);
};


template<typename T>
std::optional<T> jsonConfig::getConfigData(const std::string& settings, const std::string& options) {
    const char *settingsCStr = settings.c_str();
    const char *optionsCStr = options.c_str();

    rapidjson::Value::ConstMemberIterator itr = filesInitialize::cfg[settingsCStr].FindMember(optionsCStr);

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

