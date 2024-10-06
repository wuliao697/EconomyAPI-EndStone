//
// Created by admin on 2024/10/6.
//

#pragma once

#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/filewritestream.h"
#include "rapidjson/writer.h"

#include "util/files/filesManager.h"

class jsonBase{
public:
    static void jsonWrite(const rapidjson::Document& file);
    static rapidjson::Document jsonRead();
};

void jsonBase::jsonWrite(const rapidjson::Document& file){
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

rapidjson::Document jsonBase::jsonRead(){
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