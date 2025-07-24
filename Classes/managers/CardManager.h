// CardManager.h
#ifndef CARD_MANAGER_H
#define CARD_MANAGER_H

#include "models/CardModel.h"
#include "views/CardView.h"
#include "cocos2d.h"

class CardView;
/*
初始化卡牌触摸事件监听器（setupTouchEvents），处理点击检测逻辑，包括触摸开始（onTouchBegan）、移动（onTouchMoved）、结束（onTouchEnded）等事件；
维护卡牌模型（CardModel）与视图（CardView）的双向引用，通过setCard方法绑定模型与视图实例（）；
提供点击回调接口（setCardClickedCallback），将用户操作事件传递给控制器（Controller），
管理卡牌选中状态（_isSelected），控制视觉反馈（如缩放动画）。 
 */
class CardManager {
public:
    CardManager(const CardModel& model);
    ~CardManager();

    void setCard(const CardModel& model, CardView* view);
    void setupTouchEvents();

    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event);

    // 设置点击回调函数
    void setCardClickedCallback(const std::function<void(CardModel&)>& callback);
    CardView* getView() { return _view; }
    CardModel getModel() {return _model;}

private:
    CardModel _model;
    CardView* _view;
    bool _isSelected;

    std::function<void(CardModel&)> _cardClickedCallback;
};

#endif // CARD_MANAGER_H