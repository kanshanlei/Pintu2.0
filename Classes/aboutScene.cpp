#include "aboutScene.h"
#include"SceneMediator.h"
#include"XMLParser.h"
aboutScene::aboutScene()
{
}


aboutScene::~aboutScene()
{
}

bool aboutScene::init()
{
	if (Layer::init() == false){ return false; }
	_background = Background::create();
	addChild(_background);

	auto viewSize = Director::getInstance()->getVisibleSize();
	//使用九妹图做背景
	auto box = ui::Scale9Sprite::create("message_box.png");
	box->setContentSize(Size(viewSize.width - 100, viewSize.height - 100));
	box->setPosition(viewSize.width / 2, viewSize.height / 2);
	box->setAnchorPoint(Vec2(0.5, 0.5));
	this->addChild(box);

	

	XMLParser *textParser = XMLParser::parseWithFile("text.xml");
	String *text = textParser->getString("aboutText");
	LabelTTF* textView = LabelTTF::create(text->getCString(), "Arial", 38);
	textView->setHorizontalAlignment(TextHAlignment::LEFT);
	textView->setColor(Color3B(100, 100, 255));
//	textView->setDimensions(Size(600, 300));
	textView->setAnchorPoint(Vec2(0.5, 0.5));
	textView->setPosition(Vec2(viewSize.width / 2, viewSize.height / 2));

	this->addChild(textView);
	_backBut = ui::Button::create("back.png");
	_backBut->setAnchorPoint(Vec2(0, 1));
	_backBut->setPosition(Vec2(10, viewSize.height - 10));
	addChild(_backBut);
	_backBut->addClickEventListener([](Ref* ref){
		SceneMediator::getInstance()->gotoStartScene();
	});

	//android返回事件监听
	auto listenerkeyPad = EventListenerKeyboard::create();
	listenerkeyPad->onKeyReleased = CC_CALLBACK_2(aboutScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerkeyPad, this);
}

Scene* aboutScene::createScene()
{
	auto layer = aboutScene::create();

	auto scene = Scene::create();
	scene->addChild(layer);

	return scene;
}

void aboutScene::onKeyReleased(EventKeyboard::KeyCode keycode, cocos2d::Event *event)
{
	if (keycode == EventKeyboard::KeyCode::KEY_BACKSPACE || keycode == EventKeyboard::KeyCode::KEY_ESCAPE)  //返回
	{
		SceneMediator::getInstance()->gotoStartScene();
	}
	else if (keycode == EventKeyboard::KeyCode::KEY_MENU)
	{

	}
}