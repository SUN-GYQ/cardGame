#pragma once
#ifndef CONFIGS_LOADERS_LEVELCONFIGLOADER_H
#define CONFIGS_LOADERS_LEVELCONFIGLOADER_H

#include "configs/models/LevelConfig.h"
#include "cocos2d.h"
#include <memory>
#include <fstream>
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
#include "json/prettywriter.h"
#include "json/filereadstream.h"
#include "models/CardModel.h"
using namespace rapidjson;

/*
关卡配置加载器（静态类），负责解析JSON格式的关卡配置文件
loaders模块遵循配置加载逻辑与数据模型分离原则
配合rapidjson库实现JSON解析（cpp文件中实现具体解析逻辑）
 */
    class LevelConfigLoader final {
    public:
        // 加载指定关卡的配置数据
        static LevelConfig* loadLevelConfig(std::string fileName);
    private:
        static int currentId;
        // 私有构造函数，禁止实例化（静态类设计）
        LevelConfigLoader() = default;
        // 禁止拷贝构造函数
        LevelConfigLoader(const LevelConfigLoader&) = delete;
        // 禁止赋值运算符
        LevelConfigLoader& operator=(const LevelConfigLoader&) = delete;
        static bool parseCardModel(const rapidjson::Value& cardNode, std::vector<CardModel>& target, CardZone zone);
};

#endif // CONFIGS_LOADERS_LEVELCONFIGLOADER_H