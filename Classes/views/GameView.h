#ifndef GAME_VIEW_H_
#define GAME_VIEW_H_

#include "cocos2d.h"
#include "models/GameModel.h"
#include "CardView.h"
#include <vector>
#include "managers/UndoManager.h"
#include "controllers/GameController.h"

USING_NS_CC;
/*
����ȫ�ִ����¼���UI��������״̬��ǩ���������ͨ���ص�֪ͨ��������

_playfieldCardViews��������������ͼ���ϣ���ӦGameModel�е�_playfield��
_stackfieldCardViews�������ƶѿ�����ͼ���ϣ���ӦGameModel�е�_stackfield��
_statusLabel����Ϸ״̬�ı���ǩ�������ǻ��˱�ǩ��
 */
class GameView : public Node {
public:
    /*
    ��̬���� GameView �ķ���
    model GameModel �������ڳ�ʼ�� GameView
     */
    static GameView* create(GameModel& model);

protected:
    /*
    ��ʼ�� GameView ���߼�
    model GameModel �������ڳ�ʼ�� GameView
    ��ʼ���ɹ����� true�����򷵻� false
     */
    bool init(GameModel& model);

    /*
    ���� GameModel ���ɶ�Ӧ�� CardView ����
    model GameModel ���󣬰�����Ƭ��Ϣ
     */
    void generateCardViews(GameModel& model);

private:
    std::vector<CardView*> _playfieldCardViews; // �洢 playfield ��Ӧ�� CardView ����
    std::vector<CardView*> _stackfieldCardViews; // �洢 stackfield ��Ӧ�� CardView ����

    // Label ��Ա����
    cocos2d::Label* _statusLabel;

    // GameController ��Ա����
    GameController* _gameController;
    // ���� Label ����Ļص�����
    void onLabelClicked();

    // ע�ᴥ���¼�
    void registerTouchEvents();
};

#endif // GAME_VIEW_H_