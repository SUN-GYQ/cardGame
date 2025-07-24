#include "GameView.h"

GameView* GameView::create(GameModel& model) {
    GameView* pRet = new(std::nothrow) GameView();
    if (pRet && pRet->init(model)) {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return nullptr;
}

bool GameView::init(GameModel& model) {
    if (!Node::init()) {
        return false;
    }

    _gameController = new (std::nothrow) GameController(model);
    if (!_gameController) {
        CCLOG("GameView: ����GameControllerʧ��");
        return false;
    }

    generateCardViews(model);

    // 1. ���������״̬��ǩ
    _statusLabel = cocos2d::Label::createWithSystemFont(u8"����", "Microsoft YaHei", 36);
    if (!_statusLabel) {
        CCLOG("GameView: ����״̬��ǩʧ��");
        CC_SAFE_DELETE(_gameController);
        return false;
    }

    _statusLabel->setPosition(900, 400);
    _statusLabel->setTextColor(cocos2d::Color4B::WHITE);
    this->addChild(_statusLabel, 100);

    // ��ӡ��ǩ��Ϣ���ڵ���
    CCLOG("Label size: %f, %f",
        _statusLabel->getContentSize().width,
        _statusLabel->getContentSize().height);
    CCLOG("Label position: %f, %f",
        _statusLabel->getPositionX(),
        _statusLabel->getPositionY());

    // 2. ע�ᴥ���¼�
    registerTouchEvents();
    return true;
}

void GameView::generateCardViews(GameModel& model) {
    // ����������������ͼ
    const auto& playfield = model.getPlayfield();
    for (const auto& cardModel : playfield) {  // ���const����
        CardView* cardView = CardView::create(cardModel, Vec2(0, 0));
        if (cardView) {
            _playfieldCardViews.push_back(cardView);
            this->addChild(cardView);
        }
        else {
            CCLOG("GameView: ����������������ͼʧ�ܣ�ID: %d", cardModel._id);
        }
    }

    // ���ɱ����ƶ���ͼ
    const auto& stackfield = model.getStackfield();
    for (const auto& cardModel : stackfield) {  // ���const����
        CardView* cardView = CardView::create(cardModel, Vec2(0, 0));
        if (cardView) {
            _stackfieldCardViews.push_back(cardView);
            this->addChild(cardView);
        }
        else {
            CCLOG("GameView: ���������ƶ���ͼʧ�ܣ�ID: %d", cardModel._id);
        }
    }

    // ���Ƶ�������߼�
    auto handleCardClick = [this](CardView* cardView) {
        if (!cardView) return;  // ��ָ����

        // �ı俨��͸���ȱ�ʾѡ��״̬
        cardView->setOpacity(180);

        // ���ÿ���������ҵ���߼�
        CardModel& cardModel = cardView->_cardManager->getModel();
        CCLOG(u8"���Ƶ����ID: %d������: %d", cardModel._id, static_cast<int>(cardModel.getZone()));

        if (cardModel.getZone() == CardZone::Playfield) {
            _gameController->selectCardFromPlayefieldAndMatch(cardModel);
        }
        else if (cardModel.getZone() == CardZone::Stack) {
            _gameController->clickStackCard(cardModel);
        }
    };

    // Ϊ�������������õ���ص�
    for (auto cardView : _playfieldCardViews) {
        if (cardView) {
            cardView->setClickCallback(handleCardClick);
        }
    }

    // Ϊ�����ƶѿ������õ���ص�
    for (auto cardView : _stackfieldCardViews) {
        if (cardView) {
            cardView->setClickCallback(handleCardClick);
        }
    }
}

void GameView::registerTouchEvents() {
    auto touchListener = cocos2d::EventListenerTouchOneByOne::create();
    if (!touchListener) {
        CCLOG("GameView: ��������������ʧ��");
        return;
    }

    touchListener->setSwallowTouches(true);

    // ������ʼ�¼�
    touchListener->onTouchBegan = [this](cocos2d::Touch* touch, cocos2d::Event* event) {
        if (!touch || !_statusLabel) return false;

        cocos2d::Vec2 touchPos = this->convertToNodeSpace(touch->getLocation());
        if (_statusLabel->getBoundingBox().containsPoint(touchPos)) {
            _statusLabel->setScale(1.2f);  // ����Ч��
            return true;
        }
        return false;
    };

    // ���������¼�
    touchListener->onTouchEnded = [this](cocos2d::Touch* touch, cocos2d::Event* event) {
        if (!_statusLabel) return;

        _statusLabel->setScale(1.0f);  // �ָ�ԭ��С

        if (touch) {
            cocos2d::Vec2 touchPos = this->convertToNodeSpace(touch->getLocation());
            if (_statusLabel->getBoundingBox().containsPoint(touchPos)) {
                onLabelClicked();
            }
        }
    };

    // ����ȡ���¼�
    touchListener->onTouchCancelled = [this](cocos2d::Touch* touch, cocos2d::Event* event) {
        if (_statusLabel) {
            _statusLabel->setScale(1.0f);
        }
    };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

void GameView::onLabelClicked() {
    CCLOG(u8"���˱�ǩ�����");
    if (_gameController) {
        _gameController->handleLabelClick();
    }
}

GameView::~GameView() {
    CC_SAFE_DELETE(_gameController);  // �ͷſ������ڴ�
}