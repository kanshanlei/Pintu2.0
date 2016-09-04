/*!
* \brief 选关功能场景
*
*/

#ifndef __LevelSelectScene__H__
#define __LevelSelectScene__H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "SceneMediator.h"
#include "SelectGate.h"
USING_NS_CC;

class LevelSelectScene : cocos2d::Layer
{
protected:
	int _level;
	int _row;
	int _column;
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(LevelSelectScene);

	Layer* background;
	SelectGate* selectGateMenu;

	void changeScene();
	void gateOneCallBack(Ref* pSender);
	void gateTwoCallBack(Ref* pSender);
	void gateThreeCallBack(Ref* pSender);

	void closeFunc(Ref* pSender);
	void startFunc(Ref* pSender);
	
};

#endif

