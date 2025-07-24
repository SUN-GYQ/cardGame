#include "AppDelegate.h"
#include "HelloWorldScene.h"

 // 音频引擎选择（二选一，当前均未启用）
 // #define USE_AUDIO_ENGINE 1
 // #define USE_SIMPLE_AUDIO_ENGINE 1

 // 音频引擎冲突检查
#if USE_AUDIO_ENGINE && USE_SIMPLE_AUDIO_ENGINE
#error "不能同时使用AudioEngine和SimpleAudioEngine，请仅选择其中一种！"
#endif

// 音频引擎头文件引入
#if USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
#elif USE_SIMPLE_AUDIO_ENGINE
#include "audio/include/SimpleAudioEngine.h"
using namespace CocosDenshion;
#endif

USING_NS_CC;

// 分辨率配置
static const Size designResolutionSize = Size(1080, 2080);  // 设计分辨率
static const Size smallResolutionSize = Size(480, 320);    // 小分辨率
static const Size mediumResolutionSize = Size(1024, 768);   // 中分辨率
static const Size largeResolutionSize = Size(2048, 1536);  // 大分辨率

// 构造函数
AppDelegate::AppDelegate() {}

// 析构函数
AppDelegate::~AppDelegate()
{
    // 释放音频引擎资源
#if USE_AUDIO_ENGINE
    AudioEngine::end();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::end();
#endif
}

/**
 * 初始化OpenGL上下文属性
 * 可修改颜色通道、深度缓存等参数，影响所有平台
 */
void AppDelegate::initGLContextAttrs()
{
    // OpenGL上下文属性: 红,绿,蓝,alpha,深度,模板,多重采样数
    GLContextAttrs glContextAttrs = { 8, 8, 8, 8, 24, 8, 0 };
    GLView::setGLContextAttrs(glContextAttrs);
}

/**
 * 包管理器注册函数
 * 如需使用包管理器安装更多包，请勿修改或移除此函数
 */
static int register_all_packages()
{
    return 0; // 包管理器标志
}

/**
 * 应用程序启动完成时调用
 * 初始化导演、视图并运行初始场景
 */
bool AppDelegate::applicationDidFinishLaunching()
{
    // 初始化导演
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();

    // 创建OpenGL视图（不同平台处理）
    if (!glview)
    {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect(
            "card_game",
            Rect(0, 0, designResolutionSize.width, designResolutionSize.height),
            0.5f
        );
#else
        glview = GLViewImpl::create("card_game");
#endif
        director->setOpenGLView(glview);
    }

    // 显示FPS信息
    director->setDisplayStats(true);

    // 设置帧率（默认60FPS）
    director->setAnimationInterval(1.0f / 60);

    // 设置设计分辨率（固定宽度模式）
    glview->setDesignResolutionSize(
        designResolutionSize.width,
        designResolutionSize.height,
        ResolutionPolicy::FIXED_WIDTH
    );

    // 分辨率适配代码（当前注释禁用）
#if 0
    auto frameSize = glview->getFrameSize();

    // 根据屏幕尺寸设置内容缩放因子
    if (frameSize.height > mediumResolutionSize.height)
    {
        director->setContentScaleFactor(
            MIN(
                largeResolutionSize.height / designResolutionSize.height,
                largeResolutionSize.width / designResolutionSize.width
            )
        );
    }
    else if (frameSize.height > smallResolutionSize.height)
    {
        director->setContentScaleFactor(
            MIN(
                mediumResolutionSize.height / designResolutionSize.height,
                mediumResolutionSize.width / designResolutionSize.width
            )
        );
    }
    else
    {
        director->setContentScaleFactor(
            MIN(
                smallResolutionSize.height / designResolutionSize.height,
                smallResolutionSize.width / designResolutionSize.width
            )
        );
    }
#endif // 0

    // 注册所有包
    register_all_packages();

    // 创建并运行初始场景
    auto scene = HelloWorld::createScene();
    director->runWithScene(scene);

    return true;
}

/**
 * 应用程序进入后台时调用（如接电话）
 */
void AppDelegate::applicationDidEnterBackground()
{
    // 停止动画
    Director::getInstance()->stopAnimation();

    // 暂停音频
#if USE_AUDIO_ENGINE
    AudioEngine::pauseAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    SimpleAudioEngine::getInstance()->pauseAllEffects();
#endif
}

/**
 * 应用程序返回前台时调用
 */
void AppDelegate::applicationWillEnterForeground()
{
    // 启动动画
    Director::getInstance()->startAnimation();

    // 恢复音频
#if USE_AUDIO_ENGINE
    AudioEngine::resumeAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    SimpleAudioEngine::getInstance()->resumeAllEffects();
#endif
}