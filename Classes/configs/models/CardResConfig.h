#ifndef CARD_RES_CONFIG_H
#define CARD_RES_CONFIG_H

#include <string>
#include <array>
#include "LevelConfig.h"
#include "models/CardModel.h"

/*
    卡牌资源配置类
    负责提供卡牌相关的所有资源路径配置,
    采用静态方法设计，无需实例化即可调用，将资源路径集中管理，
    便于后续扩展新卡牌资源或修改路径规则，避免硬编码问题，提升可维护性。
 */
class CardResConfig
{
public:
    /*
    获取卡片背景图片路径
    资源文件路径（如"res/card_general.png"）
     */
    static std::string getBackGround()
    {
        return "res/card_general.png";
    }

    /*
    获取花色图标资源路径（右上角显示）
    suit 花色枚举类型
    资源文件路径（如"res/suits/club.png"），非法枚举返回空字符串
     */
    static std::string getSuitRes(CardSuitType suit)
    {
        switch (suit)
        {
        case CardSuitType::CST_CLUBS:    return "res/suits/club.png";
        case CardSuitType::CST_DIAMONDS: return "res/suits/diamond.png";
        case CardSuitType::CST_HEARTS:   return "res/suits/heart.png";
        case CardSuitType::CST_SPADES:   return "res/suits/spade.png";
        default: return ""; // 处理非法枚举值
        }
    }

    /*
    获取左上角小数字资源路径
    suit 花色（决定数字颜色：黑/红）
    face 点数（决定数字内容）
    资源文件路径（如"res/number/small_black_3.png"），非法参数返回空字符串
     */
    static std::string getSmallNumberRes(CardSuitType suit, CardFaceType face)
    {
        std::string color = suitToColor(suit);
        std::string faceStr = faceToString(face);

        if (color.empty() || faceStr.empty())
        {
            return ""; // 非法参数处理
        }

        return "res/number/small_" + color + "_" + faceStr + ".png";
    }

    /*
    获取中间大数字资源路径
    suit 花色（决定数字颜色：黑/红）
    face 点数（决定数字内容）
    资源文件路径（如"res/number/big_red_3.png"），非法参数返回空字符串
     */
    static std::string getBigNumberRes(CardSuitType suit, CardFaceType face)
    {
        std::string color = suitToColor(suit);
        std::string faceStr = faceToString(face);

        if (color.empty() || faceStr.empty())
        {
            return ""; // 非法参数处理
        }

        return "res/number/big_" + color + "_" + faceStr + ".png";
    }

private:
    /*
    将点数枚举转换为对应字符串
    点数枚举（如CFT_THREE）
    点数字符串（如"3"），非法枚举返回空字符串
     */
    static std::string faceToString(CardFaceType face)
    {
        const std::string faceNames[] = {
            "A", "2", "3", "4", "5", "6", "7",
            "8", "9", "10", "J", "Q", "K"
        };

        int index = static_cast<int>(face);
        // 校验枚举范围（排除CFT_NONE和CFT_NUM_CARD_FACE_TYPES）
        if (index < 0 || index >= static_cast<int>(CardFaceType::CFT_NUM_CARD_FACE_TYPES))
        {
            return ""; // 非法枚举处理
        }

        return faceNames[index];
    }

    /*
    根据花色判断颜色（黑/红）
    suit 花色枚举
    颜色字符串（"black" 或 "red"）
    梅花、黑桃为黑色；方块、红桃为红色
     */
    static std::string suitToColor(CardSuitType suit)
    {
        if (suit == CardSuitType::CST_CLUBS || suit == CardSuitType::CST_SPADES)
        {
            return "black";
        }
        else
        {
            return "red";
        }
    }
};
#endif // CARD_RES_CONFIG_H