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
�ؿ����ü���������̬�ࣩ���������JSON��ʽ�Ĺؿ������ļ�
loadersģ����ѭ���ü����߼�������ģ�ͷ���ԭ��
���rapidjson��ʵ��JSON������cpp�ļ���ʵ�־�������߼���
 */
    class LevelConfigLoader final {
    public:
        // ����ָ���ؿ�����������
        static LevelConfig* loadLevelConfig(std::string fileName);
    private:
        static int currentId;
        // ˽�й��캯������ֹʵ��������̬����ƣ�
        LevelConfigLoader() = default;
        // ��ֹ�������캯��
        LevelConfigLoader(const LevelConfigLoader&) = delete;
        // ��ֹ��ֵ�����
        LevelConfigLoader& operator=(const LevelConfigLoader&) = delete;
        static bool parseCardModel(const rapidjson::Value& cardNode, std::vector<CardModel>& target, CardZone zone);
};

#endif // CONFIGS_LOADERS_LEVELCONFIGLOADER_H