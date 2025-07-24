#pragma once
#ifndef CONFIGS_MODELS_LEVELCONFIG_H
#define CONFIGS_MODELS_LEVELCONFIG_H

#include "cocos2d.h"
#include <vector>
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
#include "json/prettywriter.h"
#include "json/filereadstream.h"
#include "models/CardModel.h"

using namespace rapidjson;

/*
负责存储游戏关卡的静态配置信息，包括：主牌区（Playfield）的卡牌配置;备用牌堆（Stack）的卡牌配置
 实例化和初始化由LevelConfigLoader完成，通过友元机制授权访问私有成员。
 */
class LevelConfig final
{
public:
    // 获取主牌区卡牌配置
    std::vector<CardModel> getPlayfield()
    {
        return _playfieldCards;
    }
    // 获取备用牌堆配置
    std::vector<CardModel> getStack()
    {
        return _stackCards;
    }

private:
    std::vector<CardModel> _playfieldCards;  //< 主牌区卡牌集合（对应JSON中的"Playfield"字段）
    std::vector<CardModel> _stackCards;      //< 备用牌堆卡牌集合（对应JSON中的"Stack"字段）

    // 构造与析构控制
    LevelConfig() = default;                  //< 私有默认构造，限制外部实例化
    ~LevelConfig() = default;                 //< 私有析构函数
    LevelConfig(const LevelConfig&) = delete; //< 禁用拷贝构造
    LevelConfig& operator=(const LevelConfig&) = delete; //< 禁用赋值运算

    friend class LevelConfigLoader;  //< 授权LevelConfigLoader访问私有成员进行初始化
};

#endif // CONFIGS_MODELS_LEVELCONFIG_H