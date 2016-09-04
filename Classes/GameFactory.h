#ifndef __GAME_FACTORY_H__
#define __GAME_FACTORY_H__

#include "LevelData.h"
#include "SimpleAudioEngine.h"
#include "CuttingPhotos.h"
#include "CallbackTimeCounter.h"
#include "Pause.h"
#include "SceneMediator.h"
#include "ScoreTimer.h"
#include "ui/cocosGUI.h"
USING_NS_CC;
using namespace CocosDenshion;

class GameFactory : public cocos2d::Layer
{
protected:
	Size visibleSize;
	bool isPause;
	int _nowLevel;
	int _allLevel;
	std::vector<LevelData> _levelDataList;
	LevelData _nowLevelData;

	CuttingPhotos* photo;
	ui::Button* _pauseButton;
	ui::Button* _implyButton;
//	void initLevelDataList();
	ScoreTimer* timer;
	void initUI();
	void onKeyReleased(EventKeyboard::KeyCode keycode, cocos2d::Event *event);
public:
	~GameFactory();
	//static cocos2d::Scene* createScene();

	virtual bool init();
	//	virtual bool initWithLevelData(LevelData* leveldata);
	// a selector callback
	virtual void nextLevel();
	virtual void gameOver();
	void menuMusicCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(GameFactory);//默认创建法
};

#endif // __HELLOWORLD_SCENE_H__

