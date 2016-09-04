#include "WelcomeScene.h"
#include "GlobalDefine.h"
#include "SceneMediator.h"
#include"StartScene.h"
Scene* WelcomeScene::createScene()
{
	auto scene = Scene::create();
	auto layer = WelcomeScene::create();
	scene->addChild(layer);
	return scene;
}
bool WelcomeScene::init()
{
	if (!Layer::init()) return false;

	logoSprite = Sprite::create("aipin.png");
	logoSprite->setPosition(WINSIZE.width / 2, WINSIZE.height / 2);
	this->addChild(logoSprite);

	setFloatToXML(SOUNDVOL, 0.80f);
	setFloatToXML(MUSICVOL, 0.35f);
	UserDefault::getInstance()->flush();
	m_iNumOfLoad = 0;
	// 图片和声音的异步加载
	// 主界面
	//Director::getInstance()->getTextureCache()->addImageAsync("pnglist/startGame.png", CC_CALLBACK_1(SplashLayer::loadingTextureCallBack, this));
	Director::getInstance()->getTextureCache()->addImageAsync("about.png", CC_CALLBACK_1(WelcomeScene::loadingTextureCallBack, this));
	_loadingAudioThread = new std::thread(&WelcomeScene::loadingAudio, this);

	return true;
}

void WelcomeScene::loadingTextureCallBack(Texture2D *texture)
{
	switch (m_iNumOfLoad++)
	{
	case 0:
		//SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pnglist/startGame.plist", texture);
		auto scene = StartScene::createScene();
		Director::getInstance()->replaceScene(scene);
		break;
	}	
}

void WelcomeScene::loadingAudio()
{
	log("loadAudio");
	//初始化 音乐
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("music/aipin.mp3");
	//初始化音效  
	SimpleAudioEngine::getInstance()->preloadEffect("music/7611.mp3");
}

void WelcomeScene::initUserData()
{
	setBoolToXML(SOUND_KEY, true);
	setBoolToXML(MUSIC_KEY, true);
	// 刷新
	UserDefault::getInstance()->flush();
}

void WelcomeScene::onExit()
{
	Layer::onExit();
	_loadingAudioThread->join();//当前线程阻塞，等待其他线程
	CC_SAFE_DELETE(_loadingAudioThread);
}