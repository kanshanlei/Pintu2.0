#ifndef __CASUAL_SCENE_H__
#define __CASUAL_SCENE_H__

#include "GameFactory.h"
USING_NS_CC;
using namespace CocosDenshion;

class CasualScene : public GameFactory
{
protected:
	int _level;
	int _row, _column;
public:
	static cocos2d::Scene* createScene(int level,int row,int column);

	virtual bool init() override;
	virtual void nextLevel() override;
	virtual void gameOver()override;
	static CasualScene* create(int level,int row,int column);
};

#endif // __HELLOWORLD_SCENE_H__

