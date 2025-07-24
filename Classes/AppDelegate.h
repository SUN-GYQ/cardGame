#ifndef _APP_DELEGATE_H_
#define _APP_DELEGATE_H_

#include "cocos2d.h"

 /**
  * @brief Cocos2d-x 应用程序入口类
  *
  * 采用私有继承自 cocos2d::Application，目的是隐藏 Director 的部分接口，
  * 仅暴露应用程序生命周期管理的必要方法。
  */
class AppDelegate : private cocos2d::Application
{
public:
    /**
     * @brief 构造函数
     * 初始化应用程序基础环境
     */
    AppDelegate();

    /**
     * @brief 析构函数
     * 释放应用程序相关资源
     */
    virtual ~AppDelegate();

    /**
     * @brief 初始化 OpenGL 上下文属性
     * 配置 OpenGL 渲染环境的参数（如颜色通道、深度缓冲等）
     */
    virtual void initGLContextAttrs() override;

    /**
     * @brief 应用程序启动完成时调用
     * 在此实现导演（Director）和场景（Scene）的初始化逻辑
     * @return 初始化成功返回 true（应用继续运行），失败返回 false（应用终止）
     */
    virtual bool applicationDidFinishLaunching() override;

    /**
     * @brief 应用程序进入后台时调用
     * 通常用于暂停游戏、释放资源等操作
     */
    virtual void applicationDidEnterBackground() override;

    /**
     * @brief 应用程序返回前台时调用
     * 通常用于恢复游戏状态、重新加载资源等操作
     */
    virtual void applicationWillEnterForeground() override;
};

#endif // _APP_DELEGATE_H_