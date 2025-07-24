#ifndef CARD_ID_VIEW_MAP_H
#define CARD_ID_VIEW_MAP_H

#include "managers/CardManager.h"
#include <unordered_map>

/*
通过单例模式（getInstance）提供全局唯一访问点，实现卡牌管理器的注册（addCardManager）与检索（getCardManager）；
基于unordered_map实现高效的O(1)复杂度映射查询，支持跨控制器（Controller）共享卡牌管理实例；
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