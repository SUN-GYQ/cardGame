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
        CCLOG("GameView: 创建GameController失败");
        return false;
    }

    generateCardViews(model);

    // 1. 创建并添加状态标签
    _statusLabel = cocos2d::Label::createWithSystemFont(u8"回退", "Microsoft YaHei", 36);
    if (!_statusLabel) {
        CCLOG("GameView: 创建状态标签失败");
        CC_SAFE_DELETE(_gameController);
        return false;
    }

    _statusLabel->setPosition(900, 400);
    _statusLabel->setTextColor(cocos2d::Color4B::WHITE);
    this->addChild(_statusLabel, 100);

    // 打印标签信息用于调试
    CCLOG("Label size: %f, %f",
        _statusLabel->getContentSize().width,
        _statusLabel->getContentSize().height);
    CCLOG("Label position: %f, %f",
        _statusLabel->getPositionX(),
        _statusLabel->getPositionY());

    // 2. 注册触摸事件
    registerTouchEvents();
    return true;
}

void GameView::generateCardViews(GameModel& model) {
    // 生成主牌区卡牌视图
    const auto& playfield = model.getPlayfield();
    for (const auto& cardModel : playfield) {  // 添加const修饰
        CardView* cardView = CardView::create(cardModel, Vec2(0, 0));
        if (cardView) {
            _playfieldCardViews.push_back(cardView);
            this->addChild(cardView);
        }
        else {
            CCLOG("GameView: 创建主牌区卡牌视图失败，ID: %d", cardModel._id);
        }
    }

    // 生成备用牌堆视图
    const auto& stackfield = model.getStackfield();
    for (const auto& cardModel : stackfield) {  // 添加const修饰
        CardView* cardView = CardView::create(cardModel, Vec2(0, 0));
        if (cardView) {
            _stackfieldCardViews.push_back(cardView);
            this->addChild(cardView);
        }
        else {
            CCLOG("GameView: 创建备用牌堆视图失败，ID: %d", cardModel._id);
        }
    }

    // 卡牌点击处理逻辑
    auto handleCardClick = [this](CardView* cardView) {
        if (!cardView) return;  // 空指针检查

        // 改变卡牌透明度表示选中状态
        cardView->setOpacity(180);

        // 调用控制器处理业务逻辑
        CardModel& cardModel = cardView->_cardManager->getModel();
        CCLOG(u8"卡牌点击，ID: %d，区域: %d", cardModel._id, static_cast<int>(cardModel.getZone()));

        if (cardModel.getZone() == CardZone::Playfield) {
            _gameController->selectCardFromPlayefieldAndMatch(cardModel);
        }
        else if (cardModel.getZone() == CardZone::Stack) {
            _gameController->clickStackCard(cardModel);
        }
    };

    // 为主牌区卡牌设置点击回调
    for (auto cardView : _playfieldCardViews) {
        if (cardView) {
            cardView->setClickCallback(handleCardClick);
        }
    }

    // 为备用牌堆卡牌设置点击回调
    for (auto cardView : _stackfieldCardViews) {
        if (cardView) {
            cardView->setClickCallback(handleCardClick);
        }
    }
}

void GameView::registerTouchEvents() {
    auto touchListener = cocos2d::EventListenerTouchOneByOne::create();
    if (!touchListener) {
        CCLOG("GameView: 创建触摸监听器失败");
        return;
    }

    touchListener->setSwallowTouches(true);

    // 触摸开始事件
    touchListener->onTouchBegan = [this](cocos2d::Touch* touch, cocos2d::Event* event) {
        if (!touch || !_statusLabel) return false;

        cocos2d::Vec2 touchPos = this->convertToNodeSpace(touch->getLocation());
        if (_statusLabel->getBoundingBox().containsPoint(touchPos)) {
            _statusLabel->setScale(1.2f);  // 高亮效果
            return true;
        }
        return false;
    };

    // 触摸结束事件
    touchListener->onTouchEnded = [this](cocos2d::Touch* touch, cocos2d::Event* event) {
        if (!_statusLabel) return;

        _statusLabel->setScale(1.0f);  // 恢复原大小

        if (touch) {
            cocos2d::Vec2 touchPos = this->convertToNodeSpace(touch->getLocation());
            if (_statusLabel->getBoundingBox().containsPoint(touchPos)) {
                onLabelClicked();
            }
        }
    };

    // 触摸取消事件
    touchListener->onTouchCancelled = [this](cocos2d::Touch* touch, cocos2d::Event* event) {
        if (_statusLabel) {
            _statusLabel->setScale(1.0f);
        }
    };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

void GameView::onLabelClicked() {
    CCLOG(u8"回退标签被点击");
    if (_gameController) {
        _gameController->handleLabelClick();
    }
}

GameView::~GameView() {
    CC_SAFE_DELETE(_gameController);  // 释放控制器内存
}