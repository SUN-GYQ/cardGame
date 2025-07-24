#ifndef _APP_DELEGATE_H_
#define _APP_DELEGATE_H_

#include "cocos2d.h"

 /**
  * @brief Cocos2d-x Ӧ�ó��������
  *
  * ����˽�м̳��� cocos2d::Application��Ŀ�������� Director �Ĳ��ֽӿڣ�
  * ����¶Ӧ�ó����������ڹ���ı�Ҫ������
  */
class AppDelegate : private cocos2d::Application
{
public:
    /**
     * @brief ���캯��
     * ��ʼ��Ӧ�ó����������
     */
    AppDelegate();

    /**
     * @brief ��������
     * �ͷ�Ӧ�ó��������Դ
     */
    virtual ~AppDelegate();

    /**
     * @brief ��ʼ�� OpenGL ����������
     * ���� OpenGL ��Ⱦ�����Ĳ���������ɫͨ������Ȼ���ȣ�
     */
    virtual void initGLContextAttrs() override;

    /**
     * @brief Ӧ�ó����������ʱ����
     * �ڴ�ʵ�ֵ��ݣ�Director���ͳ�����Scene���ĳ�ʼ���߼�
     * @return ��ʼ���ɹ����� true��Ӧ�ü������У���ʧ�ܷ��� false��Ӧ����ֹ��
     */
    virtual bool applicationDidFinishLaunching() override;

    /**
     * @brief Ӧ�ó�������̨ʱ����
     * ͨ��������ͣ��Ϸ���ͷ���Դ�Ȳ���
     */
    virtual void applicationDidEnterBackground() override;

    /**
     * @brief Ӧ�ó��򷵻�ǰ̨ʱ����
     * ͨ�����ڻָ���Ϸ״̬�����¼�����Դ�Ȳ���
     */
    virtual void applicationWillEnterForeground() override;
};

#endif // _APP_DELEGATE_H_