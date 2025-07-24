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

// 资源加载错误提示
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// 初始化场景
bool HelloWorld::init()
{
    // 1. 调用父类初始化
    if (!Scene::init())
    {
        return false;
    }

    // 获取屏幕尺寸和原点坐标
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 2. 添加关闭按钮（点击退出程序）
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
        // 计算关闭按钮位置（右上角）
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
        float y = origin.y + closeItem->getContentSize().height / 2;
        closeItem->setPosition(Vec2(x, y));
    }

    // 创建菜单并添加关闭按钮
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    // 3. 场景布局与游戏初始化

    // ========== 上半区：棕色背景 ==========
    float topHeight = visibleSize.height * 2.0f / 3.0f; // 高度占屏幕2/3
    Color4B topColor(165, 42, 42, 255); // 棕色（RGB：165,42,42）
    auto topLayer = LayerColor::create(topColor, visibleSize.width, topHeight);
    // 位置：底部对齐下半区顶部
    topLayer->setPosition(Vec2(0, visibleSize.height - topHeight));
    addChild(topLayer, 0); // z轴层级0（底层）

    // ========== 下半区：紫色背景 ==========
    float bottomHeight = visibleSize.height - topHeight; // 高度占屏幕1/3
    Color4B bottomColor(128, 0, 128, 255); // 紫色（RGB：128,0,128）
    auto bottomLayer = LayerColor::create(bottomColor, visibleSize.width, bottomHeight);
    bottomLayer->setPosition(Vec2(0, 0)); // 左下角对齐
    addChild(bottomLayer, 0);

    // 生成游戏模型和视图
    auto gameModel = GameModelFromLevelGenerator::generateGameModel("level_1.json");
    GameModelFromLevelGenerator::generateGameView(gameModel, this);

    return true;
}

// 关闭按钮回调
void HelloWorld::menuCloseCallback(Ref* pSender)
{
    // 关闭游戏场景并退出应用
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

    /* 如需返回iOS原生界面而非退出应用，
       请注释上面的代码并使用以下方式触发自定义事件：
    EventCustom customEndEvent("game_scene_close_event");
    _eventDispatcher->dispatchEvent(&customEndEvent);
    */
}