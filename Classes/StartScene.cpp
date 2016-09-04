
#include "StartScene.h"
#include"SceneMediator.h"
#include "SimpleAudioEngine.h"
#include "XMLParser.h"
#include"GlobalDefine.h"
USING_NS_CC;
using namespace CocosDenshion;
StartScene::StartScene():
_title(nullptr),
_startBtn(nullptr),
_scoreBtn(nullptr),
_aboutBtn(nullptr)
{
}


StartScene::~StartScene()
{
	
}

bool StartScene::init()
{
	if (Layer::init() == false){ return false; }
	_background = Background::create();
	addChild(_background);
	auto viewSize = Director::getInstance()->getVisibleSize();
	
	_title = Sprite::create("aipin.png");
	_title->setPosition(viewSize.width / 2, viewSize.height - 100);
	addChild(_title);

	XMLParser *textParser = XMLParser::parseWithFile("text.xml");
	String *text = textParser->getString("normal");
	Label* start = Label::create(text->getCString(), "Arial", 38);
	start->setTextColor(Color4B(100, 100, 100, 255));
	_startBtn = MenuItemLabel::create(start, CC_CALLBACK_1(StartScene::normalCallback, this));
	_startBtn->setPosition(Vec2(viewSize.width / 2-150, viewSize.height / 2 + 50));
	
	String *text2 = textParser->getString("casual");
	Label* start2 = Label::create(text2->getCString(), "Arial", 38);	
	start2->setTextColor(Color4B(100, 100, 100, 255));
	_startBtn2 = MenuItemLabel::create(start2, CC_CALLBACK_1(StartScene::casualCallback,this));
	_startBtn2->setPosition(Vec2(viewSize.width / 2+150, viewSize.height / 2 + 50));
	auto startMenu = Menu::create(_startBtn, _startBtn2,NULL);//这句一定要写，不写不是一个完整的menu
	startMenu->setPosition(Vec2::ZERO);
	addChild(startMenu);

	_scoreBtn = ui::Button::create("charts.png");
	_scoreBtn->setPosition(Vec2(viewSize.width / 2, viewSize.height / 2 -50));
	addChild(_scoreBtn);

	_aboutBtn = ui::Button::create("about.png");
	_aboutBtn->setPosition(Vec2(viewSize.width / 2, viewSize.height / 2 - 150));
	
	addChild(_aboutBtn);

	_endBtn = ui::Button::create("end_game.png");
	_endBtn->setPosition(Vec2(viewSize.width / 2, viewSize.height / 2 - 250));
	addChild(_endBtn);
	//android返回事件监听
	auto listenerkeyPad = EventListenerKeyboard::create();
	listenerkeyPad->onKeyReleased = CC_CALLBACK_2(StartScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerkeyPad, this);


	_scoreBtn->addClickEventListener([](Ref* ref){
		SceneMediator::getInstance()->gotoScoreScene();
	});
	_aboutBtn->addClickEventListener([](Ref* ref){
		SceneMediator::getInstance()->gotoaboutScene();
	});
	_endBtn->addClickEventListener([](Ref* ref){
		Director::getInstance()->end();
	});
	// 添加 声音  的开关按钮
	auto _turnOn = MenuItemImage::create(
		"button_voi_on.png",
		"button_voi_on.png");
	auto _turnOff = MenuItemImage::create(
		"button_voi_off.png",
		"button_voi_off.png");
	MenuItemToggle *toggleItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(StartScene::menuMusicCallback, this), _turnOn, _turnOff, NULL);

	toggleItem->setScale(0.3f);
	toggleItem->setPosition(Point(viewSize.width-50, 50));
	auto menu = Menu::create(toggleItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);
	// 预加载背景音乐和音效
	//SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("music/aipin.mp3");

	// 先默认播放背景音乐
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("music/aipin.mp3", true);
	SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.8);

	isPause = false;
}

Scene* StartScene::createScene()
{
	auto layer = StartScene::create();

	auto scene = Scene::create();
	scene->addChild(layer);

	return scene;
}
void StartScene::menuMusicCallback(cocos2d::Ref* pSender)
{
	if (isPause == false)
	{
		SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
		isPause = true;
	}
	else
	{
		SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
		isPause = false;
	}
}

void StartScene::normalCallback(cocos2d::Ref* pSender)
{
	SceneMediator::getInstance()->gotoGameScene();
}

void StartScene::casualCallback(cocos2d::Ref* pSender)
{
	SceneMediator::getInstance()->gotoSelectScene();
}

void StartScene::onKeyReleased(EventKeyboard::KeyCode keycode, cocos2d::Event *event)
{
	if (keycode == EventKeyboard::KeyCode::KEY_BACKSPACE || keycode == EventKeyboard::KeyCode::KEY_ESCAPE)  //返回
	{
		Director::getInstance()->end();
	}
	else if (keycode == EventKeyboard::KeyCode::KEY_MENU)
	{

	}
}