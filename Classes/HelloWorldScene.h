#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "GameFactory.h"

USING_NS_CC;
using namespace CocosDenshion;

class HelloWorld :public GameFactory//һ��Ҫ�ǹ��м̳У�Ĭ����˽��
{
protected:
	void initLevelDataList();
public:
    static cocos2d::Scene* createScene();

    virtual bool init() override;
    CREATE_FUNC(HelloWorld);//Ĭ�ϴ�����
};

#endif // __HELLOWORLD_SCENE_H__
