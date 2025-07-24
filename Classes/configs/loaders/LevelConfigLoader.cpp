#include "LevelConfigLoader.h"

// 初始化静态成员变量
int LevelConfigLoader::currentId = 0;

/*
加载关卡配置文件并解析为LevelConfig对象
fileName 配置文件路径
解析成功返回LevelConfig指针，失败返回nullptr
 */
LevelConfig* LevelConfigLoader::loadLevelConfig(std::string fileName)
{
    // 读取JSON文件内容
    std::string jsonStr = cocos2d::FileUtils::getInstance()->getStringFromFile(fileName);
    rapidjson::Document doc;
    doc.Parse<rapidjson::kParseDefaultFlags>(jsonStr.c_str());

    // 检查JSON解析错误
    if (doc.HasParseError())
    {
        CCLOG("JSON parse error: %s", doc.GetParseError());
        return nullptr;
    }

    // 创建配置对象并检查根节点类型
    auto config = new LevelConfig();
    if (!doc.IsObject())
    {
        CCLOG("LevelConfigLoader: Root node is not an object.");
        return nullptr;
    }

    // 重置ID计数器
    currentId = 0;

    // 解析Playfield数组
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

    // 解析Stack数组
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
解析JSON中的卡牌节点并转换为CardModel对象
cardNode JSON中的卡牌节点
target 存储解析结果的CardModel向量
zone 卡牌所属区域
解析成功返回true，失败返回false
 */
bool LevelConfigLoader::parseCardModel(const rapidjson::Value& cardNode,
    std::vector<CardModel>& target,
    CardZone zone)
{
    // 基础类型校验
    if (!cardNode.IsObject())
        return false;

    // 校验必要字段
    if (!cardNode.HasMember("CardFace") || !cardNode["CardFace"].IsInt())
        return false;
    if (!cardNode.HasMember("CardSuit") || !cardNode["CardSuit"].IsInt())
        return false;
    if (!cardNode.HasMember("Position") || !cardNode["Position"].IsObject())
        return false;

    // 解析位置信息
    const rapidjson::Value& posNode = cardNode["Position"];
    if (!posNode.HasMember("x") || !posNode["x"].IsInt() ||
        !posNode.HasMember("y") || !posNode["y"].IsInt())
    {
        return false;
    }

    // 提取原始值
    int faceInt = cardNode["CardFace"].GetInt();
    int suitInt = cardNode["CardSuit"].GetInt();
    float x = posNode["x"].GetFloat();
    float y = posNode["y"].GetFloat();

    // 校验枚举范围（CardFace: 0~12，CardSuit: 0~3）
    if (faceInt < 0 || faceInt > 12)
        return false;
    if (suitInt < 0 || suitInt > 3)
        return false;

    // 转换为枚举类型
    CardFaceType face = static_cast<CardFaceType>(faceInt);
    CardSuitType suit = static_cast<CardSuitType>(suitInt);
    cocos2d::Vec2 pos(x, y);

    // 计算最终位置并分配ID
    int id = currentId++;
    if (zone == CardZone::Stack)
        pos += cocos2d::Vec2(300, 400);
    else
        pos += cocos2d::Vec2(0, 600);

    // 直接构造CardModel对象添加到目标容器
    target.emplace_back(face, suit, pos, id, zone);
    return true;
}