#ifndef UNDO_MANAGER_H
#define UNDO_MANAGER_H
#include "models/UndoModel.h"
/*
负责统一管理游戏中的撤销操作，符合程序设计架构中"managers层提供全局性服务，可持有model数据并加工"的职责定义。
通过构造函数注入UndoModel模型，建立与撤销数据的绑定关系；
提供recordUndoState方法记录每次操作的卡牌状态（如位置、层级），基于栈结构实现"后进先出"的撤销顺序；
undo方法执行撤销时，从UndoModel中获取最近一次记录的状态，逆向恢复卡牌位置和属性；
辅助方法canUndo、clearUndoHistory等用于查询撤销状态和清空历史记录，满足回退功能的交互需求。
 */
class UndoManager {
public:

    UndoManager(UndoModel& undoModel) {
        _undoModel = undoModel;
    }

    void recordUndoState(const UndoCardState& state) {
        _undoModel.record(state);
    }

    bool undo(UndoCardState& outState) {
        return _undoModel.undo(outState);
    }

    bool canUndo() const {
        return _undoModel.canUndo();
    }

    void clearUndoHistory() {
        _undoModel.clearHistory();
    }

    int getUndoSize() {
        return _undoModel.getSize();
    }

private:
    UndoModel _undoModel;
};
#endif