#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "configs/loaders/LevelConfigLoader.h"
#include "configs/models/CardResConfig.h"
#include "views/CardView.h"
#include "models/GameModel.h"
#include "views/GameView.h"
#include "services/GameModelFromLevelGenerator.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// ��Դ���ش�����ʾ
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// ��ʼ������
bool HelloWorld::init()
{
    // 1. ���ø����ʼ��
    if (!Scene::init())
    {
        return false;
    }

    // ��ȡ��Ļ�ߴ��ԭ������
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 2. ��ӹرհ�ť������˳�����
    auto closeItem = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        CC_CALLBACK_1(HelloWorld::menuCloseCallback, this)
    );

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        // ����رհ�ťλ�ã����Ͻǣ�
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
        float y = origin.y + closeItem->getContentSize().height / 2;
        closeItem->setPosition(Vec2(x, y));
    }

    // �����˵�����ӹرհ�ť
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    // 3. ������������Ϸ��ʼ��

    // ========== �ϰ�������ɫ���� ==========
    float topHeight = visibleSize.height * 2.0f / 3.0f; // �߶�ռ��Ļ2/3
    Color4B topColor(165, 42, 42, 255); // ��ɫ��RGB��165,42,42��
    auto topLayer = LayerColor::create(topColor, visibleSize.width, topHeight);
    // λ�ã��ײ������°�������
    topLayer->setPosition(Vec2(0, visibleSize.height - topHeight));
    addChild(topLayer, 0); // z��㼶0���ײ㣩

    // ========== �°�������ɫ���� ==========
    float bottomHeight = visibleSize.height - topHeight; // �߶�ռ��Ļ1/3
    Color4B bottomColor(128, 0, 128, 255); // ��ɫ��RGB��128,0,128��
    auto bottomLayer = LayerColor::create(bottomColor, visibleSize.width, bottomHeight);
    bottomLayer->setPosition(Vec2(0, 0)); // ���½Ƕ���
    addChild(bottomLayer, 0);

    // ������Ϸģ�ͺ���ͼ
    auto gameModel = GameModelFromLevelGenerator::generateGameModel("level_1.json");
    GameModelFromLevelGenerator::generateGameView(gameModel, this);

    return true;
}

// �رհ�ť�ص�
void HelloWorld::menuCloseCallback(Ref* pSender)
{
    // �ر���Ϸ�������˳�Ӧ��
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

    /* ���践��iOSԭ����������˳�Ӧ�ã�
       ��ע������Ĵ��벢ʹ�����·�ʽ�����Զ����¼���
    EventCustom customEndEvent("game_scene_close_event");
    _eventDispatcher->dispatchEvent(&customEndEvent);
    */
}