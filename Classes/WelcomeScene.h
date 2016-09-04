#ifndef __WelcomeScene__H__
#define __WelcomeScene__H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

class WelcomeScene : public Layer
{
public:
	virtual bool init();
	static Scene* createScene();
	CREATE_FUNC(WelcomeScene);

private:
	Sprite* logoSprite;
	// 场景切换
	void nextScene(float dt);
	void loadingTextureCallBack(Texture2D * texture);
	void loadingAudio();
	void onExit();
	// 初始化用户数据
	void initUserData();
	int m_iNumOfLoad;
	std::thread* _loadingAudioThread;
};

#endif
