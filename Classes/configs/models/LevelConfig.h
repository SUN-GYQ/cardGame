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
����洢��Ϸ�ؿ��ľ�̬������Ϣ����������������Playfield���Ŀ�������;�����ƶѣ�Stack���Ŀ�������
 ʵ�����ͳ�ʼ����LevelConfigLoader��ɣ�ͨ����Ԫ������Ȩ����˽�г�Ա��
 */
class LevelConfig final
{
public:
    // ��ȡ��������������
    std::vector<CardModel> getPlayfield()
    {
        return _playfieldCards;
    }
    // ��ȡ�����ƶ�����
    std::vector<CardModel> getStack()
    {
        return _stackCards;
    }

private:
    std::vector<CardModel> _playfieldCards;  //< ���������Ƽ��ϣ���ӦJSON�е�"Playfield"�ֶΣ�
    std::vector<CardModel> _stackCards;      //< �����ƶѿ��Ƽ��ϣ���ӦJSON�е�"Stack"�ֶΣ�

    // ��������������
    LevelConfig() = default;                  //< ˽��Ĭ�Ϲ��죬�����ⲿʵ����
    ~LevelConfig() = default;                 //< ˽����������
    LevelConfig(const LevelConfig&) = delete; //< ���ÿ�������
    LevelConfig& operator=(const LevelConfig&) = delete; //< ���ø�ֵ����

    friend class LevelConfigLoader;  //< ��ȨLevelConfigLoader����˽�г�Ա���г�ʼ��
};

#endif // CONFIGS_MODELS_LEVELCONFIG_H