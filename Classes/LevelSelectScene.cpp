#include "LevelSelectScene.h"
#include "GlobalDefine.h"
#include "XMLParser.h"
#include "ui/cocosGUI.h"
USING_NS_CC;
using namespace CocosDenshion;

Scene* LevelSelectScene::createScene()
{
	auto scene = Scene::create();
	auto layer = LevelSelectScene::create();
	scene->addChild(layer);
	return scene;
}

bool LevelSelectScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	/*
	if (getBoolFromXML(MUSIC_KEY))
	{
		float music = getFloatFromXML(MUSICVOL)*100.0f;
		aduioEngine->setBackgroundMusicVolume(getFloatFromXML(MUSICVOL));
		if (SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
		{
			aduioEngine->pauseBackgroundMusic();
			aduioEngine->playBackgroundMusic("Sound/gateMap.wav", true);
		}
		else
			aduioEngine->playBackgroundMusic("Sound/gateMap.wav", true);
	}
	else
		aduioEngine->pauseBackgroundMusic();
*/
	_row = 0;
	_column = 0;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	//背景
	background = LayerColor::create(Color4B(255, 255, 255, 128));
	this->addChild(background);
	//开始和返回
	auto closeItem = MenuItemSprite::create(
		Sprite::create("back.png"),
		Sprite::create("back_click.png"),
		CC_CALLBACK_1(LevelSelectScene::closeFunc, this)); // 退出

	auto startItem = MenuItemSprite::create(
		Sprite::create("start1.png"),
		Sprite::create("start1_click.png"),
		CC_CALLBACK_1(LevelSelectScene::startFunc, this)); // 挑战

	closeItem->setPosition(WINSIZE.width - 72, WINSIZE.height - 44);
	startItem->setPosition(WINSIZE.width - 72, 7 * WINSIZE.height / 72);
	auto menu = Menu::create(closeItem, startItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);
	//创建提示文字
	XMLParser *textParser = XMLParser::parseWithFile("text.xml");
	String *text = textParser->getString("rowText");
	Label* label_r = Label::create(text->getCString(), "Arial", 38);
	label_r->setTextColor(Color4B(200, 100, 100, 255));
	label_r->setPosition(100, 100);
	addChild(label_r);
	text = textParser->getString("columnText");
	Label* label_c = Label::create(text->getCString(), "Arial", 38);
	label_c->setTextColor(Color4B(200, 100, 100, 255));
	label_c->setPosition(500, 100);
	addChild(label_c);
	/*
	//文本框背景
	//使用九妹图做背景
	auto box = ui::Scale9Sprite::create("message_box.png");
	box->setContentSize(Size(200,100));
	box->setPosition(200, 100);
	this->addChild(box);
	auto box2 = ui::Scale9Sprite::create("message_box.png");
	box2->setContentSize(Size(200, 100));
	box2->setPosition(600, 100);
	this->addChild(box2);
	*/
	//创建文本框
	auto textField_r = ui::TextField::create("0", "Arial", 38);
	textField_r->setPosition(Vec2(200, 100));
	textField_r->setMaxLength(2);
	textField_r->setColor(Color3B(0,0,0));
	textField_r->addEventListener([=](Ref *pSender, ui::TextField::EventType type){
		if (type == ui::TextField::EventType::INSERT_TEXT)
		{
			_row =atoi(textField_r->getStringValue().c_str());
		}
	});
	addChild(textField_r);
	auto textField_c = ui::TextField::create("0", "Arial", 38);
	textField_c->setPosition(Vec2(600, 100));
	textField_c->setMaxLength(2);
	textField_c->setColor(Color3B(0, 0, 0));
	textField_c->addEventListener([=](Ref *pSender, ui::TextField::EventType type){
		if (type == ui::TextField::EventType::INSERT_TEXT)
		{
			_column = atoi(textField_c->getStringValue().c_str());
		}
	});
	addChild(textField_c);
	//创建精灵图片
	auto sp1 = Sprite::create("gule.jpg");
	float scale = WINSIZE.width/sp1->getContentSize().width/3;
	sp1->setAnchorPoint(Vec2(0.5, 0.5));
	sp1->ignoreAnchorPointForPosition(false);	
	//sp1->setScale(scale);
	auto sp2 = Sprite::create("gule2.png");
	scale =  WINSIZE.width/ sp2->getContentSize().width / 3;
	sp2->setAnchorPoint(Vec2(0.5, 0.5));
	sp2->ignoreAnchorPointForPosition(false);	
	//sp2->setScale(scale);
	auto sp3 = Sprite::create("heying2.png");
	sp1->setAnchorPoint(Vec2(0.5, 0.5));
	scale =WINSIZE.width  / sp3->getContentSize().width / 3;
	sp3->ignoreAnchorPointForPosition(false);
	//sp3->setScale(scale);
	//使用精灵创建菜单
	auto gateOneItem = MenuItemSprite::create(
		//Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("Gate_1.png")),
		sp1,sp1,
		CC_CALLBACK_1(LevelSelectScene::gateOneCallBack, this)); 

	auto gateTwoItem = MenuItemSprite::create(
		sp2,sp2,
		CC_CALLBACK_1(LevelSelectScene::gateTwoCallBack, this)); 

	auto gateThreeItem = MenuItemSprite::create(
		sp3,sp3,
		CC_CALLBACK_1(LevelSelectScene::gateThreeCallBack, this)); 
	//将菜单项加入SelectGate

	selectGateMenu = SelectGate::create();	
	selectGateMenu->addMenuItem(gateOneItem);
	selectGateMenu->addMenuItem(gateTwoItem);
	selectGateMenu->addMenuItem(gateThreeItem);
	selectGateMenu->setPosition(visibleSize.width / 2, visibleSize.height / 2 + 74);
	this->addChild(selectGateMenu, 2);


	return true;
}

void LevelSelectScene::changeScene()
{
	if (_row > 1 && _row <= 10 && _column > 1 && _column <= 10)
		SceneMediator::getInstance()->gotoCasualScene(_level, _row, _column);
	else{
		auto warn = Label::create("2<=num<=10", "Arial", 30);
		warn->setColor(Color3B(255, 0, 0));
		warn->setPosition(10, 10);
		warn->setAnchorPoint(Vec2(0, 0));
		addChild(warn);
	}
}
// a selector callback  
void LevelSelectScene::gateOneCallBack(cocos2d::Ref* pSender)
{
	PLAYEFFECT;
	log("First gate select!");
	_level = 3;
	changeScene();
}
void LevelSelectScene::gateTwoCallBack(cocos2d::Ref* pSender)
{
	PLAYEFFECT;
	log("Second gate select!");
	_level = 4;
	changeScene();
}
void LevelSelectScene::gateThreeCallBack(cocos2d::Ref* pSender)
{
	PLAYEFFECT;
	log("Third gate select!");
	_level =5;
	changeScene();
}

void LevelSelectScene::closeFunc(Ref* pSender)
{
	PLAYEFFECT;
	SceneMediator::getInstance()->gotoStartScene();
}

void LevelSelectScene::startFunc(Ref* pSender)
{
	PLAYEFFECT;
	selectGateMenu->getCurrentItem()->activate();//回调
	// 	m_iSelectGate = 1;
	// 	Director::getInstance()->replaceScene(GameLayer::createScene());
}