#include "LevelConfigLoader.h"

// ��ʼ����̬��Ա����
int LevelConfigLoader::currentId = 0;

/*
���عؿ������ļ�������ΪLevelConfig����
fileName �����ļ�·��
�����ɹ�����LevelConfigָ�룬ʧ�ܷ���nullptr
 */
LevelConfig* LevelConfigLoader::loadLevelConfig(std::string fileName)
{
    // ��ȡJSON�ļ�����
    std::string jsonStr = cocos2d::FileUtils::getInstance()->getStringFromFile(fileName);
    rapidjson::Document doc;
    doc.Parse<rapidjson::kParseDefaultFlags>(jsonStr.c_str());

    // ���JSON��������
    if (doc.HasParseError())
    {
        CCLOG("JSON parse error: %s", doc.GetParseError());
        return nullptr;
    }

    // �������ö��󲢼����ڵ�����
    auto config = new LevelConfig();
    if (!doc.IsObject())
    {
        CCLOG("LevelConfigLoader: Root node is not an object.");
        return nullptr;
    }

    // ����ID������
    currentId = 0;

    // ����Playfield����
    if (doc.HasMember("Playfield") && doc["Playfield"].IsArray())
    {
        const rapidjson::Value& playfieldArray = doc["Playfield"];
        for (rapidjson::SizeType i = 0; i < playfieldArray.Size(); ++i)
        {
            const rapidjson::Value& cardNode = playfieldArray[i];
            if (!parseCardModel(cardNode, config->_playfieldCards, CardZone::Playfield))
            {
                CCLOG("LevelConfigLoader: Invalid Playfield card at index %zu", i);
            }
        }
    }

    // ����Stack����
    if (doc.HasMember("Stack") && doc["Stack"].IsArray())
    {
        const rapidjson::Value& stackArray = doc["Stack"];
        for (rapidjson::SizeType i = 0; i < stackArray.Size(); ++i)
        {
            const rapidjson::Value& cardNode = stackArray[i];
            if (!parseCardModel(cardNode, config->_stackCards, CardZone::Stack))
            {
                CCLOG("LevelConfigLoader: Invalid Stack card at index %zu", i);
            }
        }
    }

    return config;
}

/*
����JSON�еĿ��ƽڵ㲢ת��ΪCardModel����
cardNode JSON�еĿ��ƽڵ�
target �洢���������CardModel����
zone ������������
�����ɹ�����true��ʧ�ܷ���false
 */
bool LevelConfigLoader::parseCardModel(const rapidjson::Value& cardNode,
    std::vector<CardModel>& target,
    CardZone zone)
{
    // ��������У��
    if (!cardNode.IsObject())
        return false;

    // У���Ҫ�ֶ�
    if (!cardNode.HasMember("CardFace") || !cardNode["CardFace"].IsInt())
        return false;
    if (!cardNode.HasMember("CardSuit") || !cardNode["CardSuit"].IsInt())
        return false;
    if (!cardNode.HasMember("Position") || !cardNode["Position"].IsObject())
        return false;

    // ����λ����Ϣ
    const rapidjson::Value& posNode = cardNode["Position"];
    if (!posNode.HasMember("x") || !posNode["x"].IsInt() ||
        !posNode.HasMember("y") || !posNode["y"].IsInt())
    {
        return false;
    }

    // ��ȡԭʼֵ
    int faceInt = cardNode["CardFace"].GetInt();
    int suitInt = cardNode["CardSuit"].GetInt();
    float x = posNode["x"].GetFloat();
    float y = posNode["y"].GetFloat();

    // У��ö�ٷ�Χ��CardFace: 0~12��CardSuit: 0~3��
    if (faceInt < 0 || faceInt > 12)
        return false;
    if (suitInt < 0 || suitInt > 3)
        return false;

    // ת��Ϊö������
    CardFaceType face = static_cast<CardFaceType>(faceInt);
    CardSuitType suit = static_cast<CardSuitType>(suitInt);
    cocos2d::Vec2 pos(x, y);

    // ��������λ�ò�����ID
    int id = currentId++;
    if (zone == CardZone::Stack)
        pos += cocos2d::Vec2(300, 400);
    else
        pos += cocos2d::Vec2(0, 600);

    // ֱ�ӹ���CardModel������ӵ�Ŀ������
    target.emplace_back(face, suit, pos, id, zone);
    return true;
}