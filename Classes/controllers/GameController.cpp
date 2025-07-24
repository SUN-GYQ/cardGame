#include "controllers/GameController.h"
#include <iostream>
#include "services/CardIdManagerMap.h"
#include "cocos2d.h"

GameController::GameController(GameModel gameModel)
    : _gameModel(gameModel), _undoManager(gameModel.getUndoModel()) {
    CCLOG(u8"��ʼ��ʱundoManager��СΪ��%d", _undoManager.getUndoSize());
}

GameController::~GameController() {}

bool GameController::selectCardFromPlayefieldAndMatch(CardModel& selectedCard) {
    if (_undoManager.getUndoSize() == 0) {
        CCLOG(u8"����ջΪ�գ��޷�����ƥ�����");
        return false;
    }

    CardModel bottomCard = getBottomCard();
    CCLOG(u8"Playfield���Ƶ�� - ѡ�п���ID��%d����ƥ�俨��ID��%d",
        selectedCard._id, bottomCard._id);

    if (isCardMatch(selectedCard, bottomCard)) {
        // ��¼��ǰ״̬���ڳ���
        UndoCardState state;
        state.id = selectedCard._id;
        state.position = selectedCard.getPosition();
        state.zone = selectedCard.getZone();
        _undoManager.recordUndoState(state);
        CCLOG(u8"����ƥ��ɹ����Ѽ�¼����״̬ - ID��%d", selectedCard._id);

        handleCardClicked(selectedCard);
        return true;
    }

    CCLOG(u8"����ƥ��ʧ�� - ��ֵ������");
    return false;
}

void GameController::clickStackCard(CardModel& card) {
    // ��¼��ǰ״̬���ڳ���
    UndoCardState state;
    state.id = card._id;
    state.position = card.getPosition();
    state.zone = card.getZone();
    _undoManager.recordUndoState(state);
    CCLOG(u8"Stack���Ƶ�� - �Ѽ�¼����״̬ - ID��%d", card._id);

    handleCardClicked(card);
}

bool GameController::undo() {
    UndoCardState state;
    if (_undoManager.undo(state)) {
        CCLOG(u8"ִ�г������� - ����ID��%d��Ŀ������%d",
            state.id, static_cast<int>(state.zone));
        moveCardToOriginalPosition(state);
        return true;
    }

    CCLOG(u8"����ջΪ�գ��޷�ִ�г�������");
    return false;
}

// ������������Stack����Ŀ��Ʋ���
bool GameController::undoStack() {
    UndoCardState state;
    if (_undoManager.undoStack(state)) {
        CCLOG(u8"ִ��Stack������ - ����ID��%d", state.id);
        moveCardToOriginalPosition(state);
        return true;
    }

    CCLOG(u8"û�пɳ�����Stack�������");
    return false;
}

CardModel GameController::getBottomCard() {
    UndoCardState state;
    int currentSize = _undoManager.getUndoSize();
    CCLOG(u8"��ȡջ�׿��� - ��ǰ����ջ��С��%d", currentSize);

    if (currentSize == 0) {
        CCLOG(u8"����ջΪ�գ�����Ĭ�Ͽ���");
        return CardModel(CardFaceType::CFT_ACE, CardSuitType::CST_SPADES, cocos2d::Vec2::ZERO);
    }

    if (_undoManager.undo(state)) {
        // ��ȡ����״̬���·Ż�ջ��
        _undoManager.recordUndoState(state);

        // ���Ҷ�Ӧ�Ŀ���ģ��
        const auto& playfield = _gameModel.getPlayfield();
        for (const auto& card : playfield) {
            if (card._id == state.id) {
                return card;
            }
        }

        const auto& stackfield = _gameModel.getStackfield();
        for (const auto& card : stackfield) {
            if (card._id == state.id) {
                return card;
            }
        }
    }

    CCLOG(u8"δ�ҵ�ջ�׿��ƣ�����Ĭ�Ͽ���");
    return CardModel(CardFaceType::CFT_ACE, CardSuitType::CST_SPADES, cocos2d::Vec2::ZERO);
}

bool GameController::isCardMatch(const CardModel& card1, const CardModel& card2) {
    int face1 = static_cast<int>(card1.getFace());
    int face2 = static_cast<int>(card2.getFace());
    bool result = (face1 == face2 + 1) || (face1 == face2 - 1);
    CCLOG(u8"����ƥ���� - ����1��ֵ��%d������2��ֵ��%d�������%s",
        face1, face2, result ? u8"ƥ��" : u8"��ƥ��");
    return result;
}

void GameController::moveCardToOriginalPosition(const UndoCardState& state) {
    // ������Playfield�в��Ҳ��ƶ�����
    auto& playfield = _gameModel.getPlayfield();
    for (auto& card : playfield) {  // ʹ���������޸�ʵ�ʶ���
        if (card._id == state.id) {
            CardManager* cardManager = getCardManager(card);
            if (cardManager) {
                card.setPosition(state.position);
                card.setZone(state.zone);
                cardManager->getView()->runAction(cocos2d::MoveTo::create(0.5f, state.position));
                cardManager->getView()->setLocalZOrder(0);
                CCLOG(u8"�����ƻ�ԭλ�� - ID��%d������Playfield", state.id);
            }
            return;
        }
    }

    // ������Stackfield�в��Ҳ��ƶ�����
    auto& stackfield = _gameModel.getStackfield();
    for (auto& card : stackfield) {  // ʹ���������޸�ʵ�ʶ���
        if (card._id == state.id) {
            CardManager* cardManager = getCardManager(card);
            if (cardManager) {
                card.setPosition(state.position);
                card.setZone(state.zone);
                cardManager->getView()->runAction(cocos2d::MoveTo::create(0.5f, state.position));
                cardManager->getView()->setLocalZOrder(0);
                CCLOG(u8"�����ƻ�ԭλ�� - ID��%d������Stackfield", state.id);
            }
            return;
        }
    }

    CCLOG(u8"δ�ҵ����� - ID��%d���޷�ִ���ƶ�����", state.id);
}

CardManager* GameController::getCardManager(const CardModel& card) {
    CardManager* manager = CardIdManagerMap::getInstance().getCardManager(card._id);
    if (!manager) {
        CCLOG(u8"���棺δ�ҵ����ƹ����� - ID��%d", card._id);
    }
    return manager;
}

void GameController::handleCardClicked(CardModel& card) {
    CCLOG(u8"�����Ƶ�� - ID��%d����ǰ����%d",
        card._id, static_cast<int>(card.getZone()));

    if (card.getZone() != CardZone::Hand) {
        cocos2d::Vec2 newPos(700, 400);
        CardManager* cardManager = getCardManager(card);

        if (cardManager) {
            // ���¿���״̬
            card.setZone(CardZone::Hand);
            card.setPosition(newPos);

            // ִ���ƶ�����
            auto moveTo = cocos2d::MoveTo::create(0.5f, newPos);
            cardManager->getView()->runAction(moveTo);

            // ����Z��˳��ȷ���¿������Ϸ�
            if (_undoManager.getUndoSize() > 1) {  // ����1����Ϊ������˵�ǰ�����ļ�¼
                CardModel lastCard = getBottomCard();
                CardManager* lastCardManager = getCardManager(lastCard);
                if (lastCardManager) {
                    int newZOrder = lastCardManager->getView()->getLocalZOrder() + 1;
                    cardManager->getView()->setLocalZOrder(newZOrder);
                    CCLOG(u8"���¿���Z��˳�� - ID��%d��ZOrder��%d", card._id, newZOrder);
                }
            }

            CCLOG(u8"�����ƶ���Hand���� - ID��%d����λ�ã�(%.0f, %.0f)",
                card._id, newPos.x, newPos.y);
        }
    }
}

void GameController::handleLabelClick() {
    CCLOG(u8"������ǩ����¼� - ִ�г�������");
    undo();
}