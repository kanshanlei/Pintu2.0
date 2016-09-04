#include "SuccessScene.h"
#include"UserData.h"
#include"SceneMediator.h"
#include"GlobalDefine.h"
SuccessScene::SuccessScene()
{
}


SuccessScene::~SuccessScene()
{
}

bool SuccessScene::init()
{
	if (Layer::init() == false) {
		return false;
	}
	//背景
	_background = Background::create();
	addChild(_background);
	auto viewSize = Director::getInstance()->getVisibleSize();
	/*
	_background = Background::create();
	addChild(_background);
	*/
	//返回按钮
	_backBut = ui::Button::create("back.png");
	_backBut->setAnchorPoint(Vec2(0, 1));
	_backBut->setPosition(Vec2(10, viewSize.height - 10));
	addChild(_backBut);
	_backBut->addClickEventListener([](Ref* ref){
		SceneMediator::getInstance()->gotoStartScene();
	});
	//庆祝图片
	_successTitle = Sprite::create("success.png");
	_successTitle->setPosition(WINSIZE.width, WINSIZE.height - 150);
	//行列数
	XMLParser *textParser = XMLParser::parseWithFile("text.xml");
	String *text1 = textParser->getString("rowText");
	LabelTTF* rowText = LabelTTF::create(text1->getCString(), "Arial", 38);
	rowText->setHorizontalAlignment(TextHAlignment::LEFT);
	rowText->setColor(Color3B(100, 100, 255));
	//	textView->setDimensions(Size(600, 300));
	rowText->setAnchorPoint(Vec2(0.5, 0.5));
	rowText->setPosition(Vec2(100, WINSIZE.height/2));
	this->addChild(rowText);

	_row= ui::TextAtlas::create("0", "number.png", 63, 83, "0");
	_row->setPosition(Vec2(200, WINSIZE.height / 2));
	auto  newrow = UserDefault::getInstance()->getIntegerForKey(row, 0);
	_row->setString(StringUtils::format("%d", newrow));
	this->addChild(_row);

	String *text2 = textParser->getString("columnText");
	LabelTTF* columnText = LabelTTF::create(text2->getCString(), "Arial", 38);
	columnText->setHorizontalAlignment(TextHAlignment::LEFT);
	columnText->setColor(Color3B(100, 100, 255));
	//	textView->setDimensions(Size(600, 300));
	columnText->setAnchorPoint(Vec2(0.5, 0.5));
	columnText->setPosition(Vec2(WINSIZE.width / 2, WINSIZE.height / 2));
	this->addChild(columnText);

	_column = ui::TextAtlas::create("0", "number.png", 63, 83, "0");
	_column->setPosition(Vec2(viewSize.width / 2 +100, viewSize.height / 2 ));
	auto newcolumn = UserDefault::getInstance()->getIntegerForKey(column, 0);
	_column->setString(StringUtils::format("%d", newcolumn));
	this->addChild(_column);
	//用时
	String *text = textParser->getString("timeText");
	LabelTTF* timeText = LabelTTF::create(text->getCString(), "Arial", 38);
	timeText->setHorizontalAlignment(TextHAlignment::LEFT);
	timeText->setColor(Color3B(100, 100, 255));
	//	textView->setDimensions(Size(600, 300));
	timeText->setAnchorPoint(Vec2(0.5, 0.5));
	timeText->setPosition(Vec2(100, 100));
	this->addChild(timeText);

	_newTime = ui::TextAtlas::create("0", "number.png", 63, 83, "0");
	_newTime->setPosition(Vec2(viewSize.width/2 , 100));
	auto newTime = UserDefault::getInstance()->getIntegerForKey(NEW_TIME, 1000);
	_newTime->setString(StringUtils::format("%d", newTime));
	this->addChild(_newTime);
	return true;
}

Scene* SuccessScene::createScene()
{
	auto layer = SuccessScene::create();

	auto scene = Scene::create();

	scene->addChild(layer);

	return scene;
}
