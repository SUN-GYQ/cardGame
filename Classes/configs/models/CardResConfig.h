#ifndef CARD_RES_CONFIG_H
#define CARD_RES_CONFIG_H

#include <string>
#include <array>
#include "LevelConfig.h"
#include "models/CardModel.h"

/*
    ������Դ������
    �����ṩ������ص�������Դ·������,
    ���þ�̬������ƣ�����ʵ�������ɵ��ã�����Դ·�����й���
    ���ں�����չ�¿�����Դ���޸�·�����򣬱���Ӳ�������⣬������ά���ԡ�
 */
class CardResConfig
{
public:
    /*
    ��ȡ��Ƭ����ͼƬ·��
    ��Դ�ļ�·������"res/card_general.png"��
     */
    static std::string getBackGround()
    {
        return "res/card_general.png";
    }

    /*
    ��ȡ��ɫͼ����Դ·�������Ͻ���ʾ��
    suit ��ɫö������
    ��Դ�ļ�·������"res/suits/club.png"�����Ƿ�ö�ٷ��ؿ��ַ���
     */
    static std::string getSuitRes(CardSuitType suit)
    {
        switch (suit)
        {
        case CardSuitType::CST_CLUBS:    return "res/suits/club.png";
        case CardSuitType::CST_DIAMONDS: return "res/suits/diamond.png";
        case CardSuitType::CST_HEARTS:   return "res/suits/heart.png";
        case CardSuitType::CST_SPADES:   return "res/suits/spade.png";
        default: return ""; // ����Ƿ�ö��ֵ
        }
    }

    /*
    ��ȡ���Ͻ�С������Դ·��
    suit ��ɫ������������ɫ����/�죩
    face �����������������ݣ�
    ��Դ�ļ�·������"res/number/small_black_3.png"�����Ƿ��������ؿ��ַ���
     */
    static std::string getSmallNumberRes(CardSuitType suit, CardFaceType face)
    {
        std::string color = suitToColor(suit);
        std::string faceStr = faceToString(face);

        if (color.empty() || faceStr.empty())
        {
            return ""; // �Ƿ���������
        }

        return "res/number/small_" + color + "_" + faceStr + ".png";
    }

    /*
    ��ȡ�м��������Դ·��
    suit ��ɫ������������ɫ����/�죩
    face �����������������ݣ�
    ��Դ�ļ�·������"res/number/big_red_3.png"�����Ƿ��������ؿ��ַ���
     */
    static std::string getBigNumberRes(CardSuitType suit, CardFaceType face)
    {
        std::string color = suitToColor(suit);
        std::string faceStr = faceToString(face);

        if (color.empty() || faceStr.empty())
        {
            return ""; // �Ƿ���������
        }

        return "res/number/big_" + color + "_" + faceStr + ".png";
    }

private:
    /*
    ������ö��ת��Ϊ��Ӧ�ַ���
    ����ö�٣���CFT_THREE��
    �����ַ�������"3"�����Ƿ�ö�ٷ��ؿ��ַ���
     */
    static std::string faceToString(CardFaceType face)
    {
        const std::string faceNames[] = {
            "A", "2", "3", "4", "5", "6", "7",
            "8", "9", "10", "J", "Q", "K"
        };

        int index = static_cast<int>(face);
        // У��ö�ٷ�Χ���ų�CFT_NONE��CFT_NUM_CARD_FACE_TYPES��
        if (index < 0 || index >= static_cast<int>(CardFaceType::CFT_NUM_CARD_FACE_TYPES))
        {
            return ""; // �Ƿ�ö�ٴ���
        }

        return faceNames[index];
    }

    /*
    ���ݻ�ɫ�ж���ɫ����/�죩
    suit ��ɫö��
    ��ɫ�ַ�����"black" �� "red"��
    ÷��������Ϊ��ɫ�����顢����Ϊ��ɫ
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