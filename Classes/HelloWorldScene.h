#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

 /**
  * @brief 游戏主场景类，继承自 cocos2d::Scene
  * 负责初始化游戏主界面，包含场景创建、UI 元素初始化及事件回调等功能
  */
class HelloWorld : public cocos2d::Scene
{
public:
    /**
     * @brief 创建场景实例的静态方法
     * @return 指向场景实例的指针
     */
    static cocos2d::Scene* createScene();

    /**
     * @brief 初始化场景（重写父类方法）
     * @return 初始化成功返回 true，否则返回 false
     */
    virtual bool init() override;

    /**
     * @brief 关闭按钮的回调函数
     * @param pSender 事件发送者
     */
    void menuCloseCallback(cocos2d::Ref* pSender);

    // 实现静态 create() 方法（通过宏自动生成）
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__