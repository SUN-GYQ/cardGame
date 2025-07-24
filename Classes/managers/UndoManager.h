#ifndef UNDO_MANAGER_H
#define UNDO_MANAGER_H
#include "models/UndoModel.h"
/*
����ͳһ������Ϸ�еĳ������������ϳ�����Ƽܹ���"managers���ṩȫ���Է��񣬿ɳ���model���ݲ��ӹ�"��ְ���塣
ͨ�����캯��ע��UndoModelģ�ͣ������볷�����ݵİ󶨹�ϵ��
�ṩrecordUndoState������¼ÿ�β����Ŀ���״̬����λ�á��㼶��������ջ�ṹʵ��"����ȳ�"�ĳ���˳��
undo����ִ�г���ʱ����UndoModel�л�ȡ���һ�μ�¼��״̬������ָ�����λ�ú����ԣ�
��������canUndo��clearUndoHistory�����ڲ�ѯ����״̬�������ʷ��¼��������˹��ܵĽ�������
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