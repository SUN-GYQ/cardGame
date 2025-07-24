# cardgame

这是一个基于 Cocos2d-x 3.17 开发的纸牌游戏示例项目，采用 MVC（Model-View-Controller）架构模式，展示了如何使用 Cocos2d-x 引擎开发简单纸牌游戏。

## 目录
1. [核心功能](#核心功能)
2. [运行要求](#运行要求)
3. [项目结构](#项目结构)


## 核心功能
采用 MVC 架构，代码组织清晰，便于维护和扩展
支持从 JSON 文件加载纸牌数据（如 Resources/level_1.json）
实现纸牌触摸交互（点击、拖动等操作）
具备撤销操作功能（通过 UndoManager 和 UndoModel 实现）
可扩展卡牌类型和游戏逻辑

## 运行要求
- **Cocos2d-x**：确保你的系统已安装 Cocos2d-x 3.17 版本。
- **CMake**：用于构建项目。
- **运行可执行文件**：支持 Windows 等多平台运行


## 项目结构
项目主要目录和文件如下：
- **Classes**：包含游戏的主要源代码，按功能模块组织，如模型、视图、控制器、管理器和配置加载器。
  - **models**：定义游戏中使用的数据模型。
  - **views**：实现游戏的视觉组件。
  - **controllers**：处理游戏逻辑和交互。
  - **managers**：管理游戏的各个方面。
  - **configs/loaders**：从 JSON 文件加载游戏配置。
- **Resources**：包含游戏资源，如图像和 JSON 配置文件。
- **proj.win32**：Windows 特定的项目文件和配置。
- **CMakeLists.txt**：CMake 配置文件，用于构建项目。

