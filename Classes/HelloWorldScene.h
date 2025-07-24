#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

 /**
  * @brief ��Ϸ�������࣬�̳��� cocos2d::Scene
  * �����ʼ����Ϸ�����棬��������������UI Ԫ�س�ʼ�����¼��ص��ȹ���
  */
class HelloWorld : public cocos2d::Scene
{
public:
    /**
     * @brief ��������ʵ���ľ�̬����
     * @return ָ�򳡾�ʵ����ָ��
     */
    static cocos2d::Scene* createScene();

    /**
     * @brief ��ʼ����������д���෽����
     * @return ��ʼ���ɹ����� true�����򷵻� false
     */
    virtual bool init() override;

    /**
     * @brief �رհ�ť�Ļص�����
     * @param pSender �¼�������
     */
    void menuCloseCallback(cocos2d::Ref* pSender);

    // ʵ�־�̬ create() ������ͨ�����Զ����ɣ�
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__