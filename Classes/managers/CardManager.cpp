#include "managers/CardManager.h"
#include <iostream>
#include "views/CardView.h"  
#include "services/CardIdManagerMap.h"
#include "cocos2d.h"

CardManager::CardManager(const CardModel& model)
    : _model(model), _view(nullptr), _isSelected(false) {
    CardIdManagerMap::getInstance().addCardManager(model._id, this);
    CCLOG(u8"����CardManager - ����ID��%d", model._id);
}

CardManager::~CardManager() {
    // ��ȫ��ӳ�����Ƴ���ǰ������
    CardIdManagerMap::getInstance().removeCardManager(_model._id);
    CCLOG(u8"����CardManager - ����ID��%d", _model._id);
}

void CardManager::setCard(const CardModel& model, CardView* view) {
    // ���Ƴ���ID��ӳ��
    if (_model._id != model._id) {
        CardIdManagerMap::getInstance().removeCardManager(_model._id);
    }

    _model = model;
    _view = view;
    CardIdManagerMap::getInstance().addCardManager(model._id, this);
    setupTouchEvents();
    CCLOG(u8"���¿�����Ϣ - ID��%d������%d", model._id, static_cast<int>(model.getZone()));
}

void CardManager::setupTouchEvents() {
    if (!_view) {
        CCLOG(u8"���棺CardViewΪ�գ��޷����ô����¼�");
        return;
    }

    // �Ƴ��Ѵ��ڵļ������������ظ�ע��
    auto dispatcher = _view->getEventDispatcher();
    if (dispatcher->getEventListenerForTarget(_view, -1)) {
        dispatcher->removeEventListenersForTarget(_view);
    }

    auto touchListener = cocos2d::EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(CardManager::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(CardManager::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(CardManager::onTouchEnded, this);
    touchListener->onTouchCancelled = CC_CALLBACK_2(CardManager::onTouchCancelled, this);

    dispatcher->addEventListenerWithSceneGraphPriority(touchListener, _view);
    CCLOG(u8"��Ϊ����ID��%d ���ô����¼�", _model._id);
}

bool CardManager::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
    if (!_view) return false;

    cocos2d::Vec2 touchPos = _view->convertToNodeSpace(touch->getLocation());
    if (!_view->isTouchInside(touchPos)) {
        CCLOG(u8"�������ڿ���ID��%d ��Χ��", _model._id);
        return false;
    }

    CCLOG(u8"�����ʼ����Ƭ�Ŵ� - ID��%d", _model._id);
    _view->setScale(1.1f);
    _isSelected = true;
    return true;
}

void CardManager::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event) {
    if (!_view || !_isSelected) return;

    // ����϶��߼������津��λ���ƶ�
    cocos2d::Vec2 delta = touch->getDelta();
    _view->setPosition(_view->getPosition() + delta);

    // ͬ������ģ��λ��
    _model.setPosition(_view->getPosition() - _view->getParent()->getPosition());
    CCLOG(u8"����ID��%d �϶��У���λ�ã�(%.0f, %.0f)",
        _model._id, _model.getPosition().x, _model.getPosition().y);
}

void CardManager::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) {
    if (!_view) return;

    _view->setScale(1.0f);
    CCLOG(u8"����������ָ�ԭ��С - ID��%d", _model._id);

    cocos2d::Vec2 touchPos = _view->convertToNodeSpace(touch->getLocation());
    if (_view->isTouchInside(touchPos) && _cardClickedCallback) {
        CCLOG(u8"��������ص� - ����ID��%d", _model._id);
        _cardClickedCallback(_model);
    }

    _isSelected = false;
}

void CardManager::onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event) {
    if (!_view) return;

    _view->setScale(1.0f);
    _isSelected = false;
    CCLOG(u8"����ȡ�� - ����ID��%d �ָ�ԭ��С", _model._id);
}

void CardManager::setCardClickedCallback(const std::function<void(CardModel&)>& callback) {
    _cardClickedCallback = callback;
    CCLOG(u8"�����ÿ���ID��%d �ĵ���ص�", _model._id);
}