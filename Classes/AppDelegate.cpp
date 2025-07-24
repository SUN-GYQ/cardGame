#include "AppDelegate.h"
#include "HelloWorldScene.h"

 // ��Ƶ����ѡ�񣨶�ѡһ����ǰ��δ���ã�
 // #define USE_AUDIO_ENGINE 1
 // #define USE_SIMPLE_AUDIO_ENGINE 1

 // ��Ƶ�����ͻ���
#if USE_AUDIO_ENGINE && USE_SIMPLE_AUDIO_ENGINE
#error "����ͬʱʹ��AudioEngine��SimpleAudioEngine�����ѡ������һ�֣�"
#endif

// ��Ƶ����ͷ�ļ�����
#if USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
#elif USE_SIMPLE_AUDIO_ENGINE
#include "audio/include/SimpleAudioEngine.h"
using namespace CocosDenshion;
#endif

USING_NS_CC;

// �ֱ�������
static const Size designResolutionSize = Size(1080, 2080);  // ��Ʒֱ���
static const Size smallResolutionSize = Size(480, 320);    // С�ֱ���
static const Size mediumResolutionSize = Size(1024, 768);   // �зֱ���
static const Size largeResolutionSize = Size(2048, 1536);  // ��ֱ���

// ���캯��
AppDelegate::AppDelegate() {}

// ��������
AppDelegate::~AppDelegate()
{
    // �ͷ���Ƶ������Դ
#if USE_AUDIO_ENGINE
    AudioEngine::end();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::end();
#endif
}

/**
 * ��ʼ��OpenGL����������
 * ���޸���ɫͨ������Ȼ���Ȳ�����Ӱ������ƽ̨
 */
void AppDelegate::initGLContextAttrs()
{
    // OpenGL����������: ��,��,��,alpha,���,ģ��,���ز�����
    GLContextAttrs glContextAttrs = { 8, 8, 8, 8, 24, 8, 0 };
    GLView::setGLContextAttrs(glContextAttrs);
}

/**
 * ��������ע�ắ��
 * ����ʹ�ð���������װ������������޸Ļ��Ƴ��˺���
 */
static int register_all_packages()
{
    return 0; // ����������־
}

/**
 * Ӧ�ó����������ʱ����
 * ��ʼ�����ݡ���ͼ�����г�ʼ����
 */
bool AppDelegate::applicationDidFinishLaunching()
{
    // ��ʼ������
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();

    // ����OpenGL��ͼ����ͬƽ̨����
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

    // ��ʾFPS��Ϣ
    director->setDisplayStats(true);

    // ����֡�ʣ�Ĭ��60FPS��
    director->setAnimationInterval(1.0f / 60);

    // ������Ʒֱ��ʣ��̶����ģʽ��
    glview->setDesignResolutionSize(
        designResolutionSize.width,
        designResolutionSize.height,
        ResolutionPolicy::FIXED_WIDTH
    );

    // �ֱ���������루��ǰע�ͽ��ã�
#if 0
    auto frameSize = glview->getFrameSize();

    // ������Ļ�ߴ�����������������
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

    // ע�����а�
    register_all_packages();

    // ���������г�ʼ����
    auto scene = HelloWorld::createScene();
    director->runWithScene(scene);

    return true;
}

/**
 * Ӧ�ó�������̨ʱ���ã���ӵ绰��
 */
void AppDelegate::applicationDidEnterBackground()
{
    // ֹͣ����
    Director::getInstance()->stopAnimation();

    // ��ͣ��Ƶ
#if USE_AUDIO_ENGINE
    AudioEngine::pauseAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    SimpleAudioEngine::getInstance()->pauseAllEffects();
#endif
}

/**
 * Ӧ�ó��򷵻�ǰ̨ʱ����
 */
void AppDelegate::applicationWillEnterForeground()
{
    // ��������
    Director::getInstance()->startAnimation();

    // �ָ���Ƶ
#if USE_AUDIO_ENGINE
    AudioEngine::resumeAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    SimpleAudioEngine::getInstance()->resumeAllEffects();
#endif
}