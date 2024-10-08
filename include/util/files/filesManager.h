//
// Created by admin on 2024/8/12.
//
#pragma once

#include <iostream>
#include <iostream>
#include <filesystem>

class FilesManager{
public:
    /*
     * 说实话应该用endstone里的方法的
     */
    static std::filesystem::path getDataPath(const std::filesystem::path& path) {
        std::filesystem::path filePath = std::filesystem::current_path() / "plugins" / "economyAPI" / path;
        return filePath;
    }

    static std::filesystem::path getDataFolder(){
        return std::filesystem::current_path() / "plugins" / "economyAPI";
    }

    static std::filesystem::path getLanguagePath(const std::filesystem::path& path){
        return std::filesystem::current_path() / "plugins" / "economyAPI" / "language" / path;
    }

    static std::filesystem::path getLanguageFolder(){
        return std::filesystem::current_path() / "plugins" / "economyAPI" / "language";
    }
};
