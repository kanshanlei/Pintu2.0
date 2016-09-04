#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "GameFactory.h"

USING_NS_CC;
using namespace CocosDenshion;

class HelloWorld :public GameFactory//一定要是公有继承，默认是私有
{
protected:
	void initLevelDataList();
public:
    static cocos2d::Scene* createScene();

    virtual bool init() override;
    CREATE_FUNC(HelloWorld);//默认创建法
};

#endif // __HELLOWORLD_SCENE_H__
