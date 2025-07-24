#include "CardView.h"
#include <iostream>

CardView* CardView::create(const CardModel& model, const Vec2& offset) {
    auto view = new (std::nothrow) CardView();
    if (view && view->init(model, offset)) {
        view->autorelease(); // �����ڴ������Զ��ͷ�
        return view;
    }
    CC_SAFE_DELETE(view);
    return nullptr;
}

void CardView::setClickCallback(const ClickCallback& callback) {
    _clickCallback = callback;
    if (_cardManager) {
        _cardManager->setCardClickedCallback([this, callback](CardModel& model) {
            if (callback) {
                callback(this);
            }
            });
    }
}

bool CardView::isTouchInside(const Vec2& touchPos) {
    if (!_background) return false;
    return _background->getBoundingBox().containsPoint(touchPos);
}

bool CardView::init(const CardModel& model, const Vec2& offset) {
    if (!Node::init()) {
        return false;
    }

    // 1. ���ر������������ȼ��أ�ȷ�����Ƴߴ磩
    loadBackground();
    if (!_background) {
        CCLOG("CardView: ����ͼ����ʧ�ܣ�");
        return false;
    }

    // 2. ��������ʼ��CardManager
    _cardManager = new (std::nothrow) CardManager(model);
    if (!_cardManager) {
        CCLOG("CardView: ����CardManagerʧ�ܣ�");
        return false;
    }

    // 3. ������Ԫ��
    loadSmallNumber(model);
    loadBigNumber(model);
    loadSuitIcon(model);

    // 4. ����λ��
    this->setPosition(model.getPosition() + offset);

    // 5. ������Ƭģ�ͺ���ͼ��������
    _cardManager->setCard(model, this);

    return true;
}

void CardView::loadBackground() {
    // ���ر���ͼ��Դ
    _background = Sprite::create(CardResConfig::getBackGround());
    if (_background) {
        _background->setAnchorPoint(Vec2::ANCHOR_MIDDLE); // ����ê����Ϊ����
        this->addChild(_background);
        // ͬ��CardView�ĳߴ��뱳��ͼһ��
        this->setContentSize(_background->getContentSize());
    }
    else {
        CCLOG("CardView: ������Դ��ȡʧ�� - %s", CardResConfig::getBackGround().c_str());
    }
}

void CardView::loadSmallNumber(const CardModel& model) {
    // 1. ��ȡ��Դ·��
    const auto suit = model.getSuit();
    const auto face = model.getFace();
    const std::string res = CardResConfig::getSmallNumberRes(suit, face);

    // 2. ����Sprite����Դ������ʱ����nullptr�����������
    _smallNumber = Sprite::create(res);
    if (_smallNumber) {
        _smallNumber->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT); // ���ϽǶ���
        _smallNumber->setPosition(_smallNumberPos);          // ��Ա������ĵ�λ��
        this->addChild(_smallNumber);
    }
    else {
        CCLOG("CardView: С������Դȱʧ: %s", res.c_str());
    }
}

void CardView::loadBigNumber(const CardModel& model) {
    // 1. ��ȡ��Դ·��
    const auto suit = model.getSuit();
    const auto face = model.getFace();
    const std::string res = CardResConfig::getBigNumberRes(suit, face);

    // 2. ����Sprite
    _bigNumber = Sprite::create(res);
    if (_bigNumber) {
        _bigNumber->setAnchorPoint(Vec2::ANCHOR_MIDDLE); // ���Ķ���
        _bigNumber->setPosition(_bigNumberPos);          // ��������λ��
        this->addChild(_bigNumber);
    }
    else {
        CCLOG("CardView: ��������Դȱʧ: %s", res.c_str());
    }
}

void CardView::loadSuitIcon(const CardModel& model) {
    // 1. ��ȡ��Դ·��
    const auto suit = model.getSuit();
    const std::string res = CardResConfig::getSuitRes(suit);

    // 2. ����Sprite
    _suitIcon = Sprite::create(res);
    if (_suitIcon) {
        _suitIcon->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT); // ���ϽǶ���
        _suitIcon->setPosition(_suitIconPos);              // ��Ա������ĵ�λ��
        this->addChild(_suitIcon);
    }
    else {
        CCLOG("CardView: ��ɫͼ����Դȱʧ: %s", res.c_str());
    }
}

CardView::~CardView() {
    CC_SAFE_DELETE(_cardManager); // ȷ���ͷŹ������ڴ�
}