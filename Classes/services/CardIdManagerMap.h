#ifndef CARD_ID_VIEW_MAP_H
#define CARD_ID_VIEW_MAP_H

#include "managers/CardManager.h"
#include <unordered_map>

/*
ͨ������ģʽ��getInstance���ṩȫ��Ψһ���ʵ㣬ʵ�ֿ��ƹ�������ע�ᣨaddCardManager���������getCardManager����
����unordered_mapʵ�ָ�Ч��O(1)���Ӷ�ӳ���ѯ��֧�ֿ��������Controller�������ƹ���ʵ����
 */
class CardIdManagerMap {
public:
    static CardIdManagerMap& getInstance() {
        static CardIdManagerMap instance;
        return instance;
    }

    void addCardManager(int cardId, CardManager* manager) {
        _cardIdManagerMap[cardId] = manager;
    }

    CardManager* getCardManager(int cardId) {
        auto it = _cardIdManagerMap.find(cardId);
        if (it != _cardIdManagerMap.end()) {
            return it->second;
        }
        return nullptr;
    }

private:
    CardIdManagerMap() {}
    ~CardIdManagerMap() {}

    std::unordered_map<int, CardManager*> _cardIdManagerMap;
};

#endif 