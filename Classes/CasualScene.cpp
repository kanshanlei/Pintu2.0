
#include "CasualScene.h"
#include "UserData.h"
Scene* CasualScene::createScene(int level,int row,int column)
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer =CasualScene::create(level,row,column);

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;

}

CasualScene* CasualScene::create(int level,int row,int column)
{
	CasualScene *cs = new CasualScene();
	cs->_level = level;
	cs->_row = row;
	cs->_column = column;
	
	if (cs&&cs->init()){
		cs->autorelease();
		return cs;
	}

	CC_SAFE_DELETE(cs);

	return nullptr;
}
bool CasualScene::init()
{

	if (!Layer::init())
	{
		return false;
	}
	/*
	//initLevelDataList();
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	// Ԥ���ر������ֺ���Ч
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("music/va1.mp3");
	isPause = false;
	// ��Ĭ�ϲ��ű�������
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("music/va1.mp3", true);
	//	SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(1.0);
	*/
	Layer* background = LayerColor::create(Color4B(255, 255, 255, 128));
	addChild(background);
	nextLevel();
	initUI();

	timer = ScoreTimer::create();
	this->addChild(timer);
	return true;
}

void CasualScene::nextLevel()
{
	visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	switch (_level)//���ﲻ�������ģʽ���Ժ��ٸ�
	{
	case 0:
		photo = CuttingPhotos::create("bada.jpg", _row, _column);
		break;
	case 1:
		photo = CuttingPhotos::create("daer.jpg", _row, _column);
		break;
	case 2:
		photo = CuttingPhotos::create("zhuguli.jpg", _row, _column);
		break;
	case 3:
		photo = CuttingPhotos::create("gule.jpg", _row, _column);
		break;
	case 4:
		photo = CuttingPhotos::create("gule2.png", _row, _column);
		break;
	case 5:
		photo = CuttingPhotos::create("heying2.png", _row, _column);
		break;
	case 6:
		photo = CuttingPhotos::create("bd.jpg", _row, _column);
		break;
	case 7:
		photo = CuttingPhotos::create("heying4.jpg", _row, _column);
		break;
	case 8:
		photo = CuttingPhotos::create("heying3.jpg", _row, _column);
		break;
	case 9:
		photo = CuttingPhotos::create("heying.png", _row, _column);
		break;

	default:
		photo = CuttingPhotos::create("psu.jpg", _row, _column);
	}
	photo->setAnchorPoint(Vec2(0.5, 0.5));

	auto size = photo->getContentSize();
	float scale = std::min((visibleSize.width - 100) / size.width, (visibleSize.height - 100) / size.height);
	photo->setScale(scale);
	//�����Ժ���ʵê��λ�����������ԭͼ��λ��

	photo->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	addChild(photo);


	CallbackTimeCounter* counter = CallbackTimeCounter::create();
	this->addChild(counter);
	photo->registerCallFunc([this, counter](){//��Ϸ�ɹ��Ķ���
		timer->stopTimer();
		auto particle = ParticleSystemQuad::create("ExplodingRing.plist");
		particle->setPosition(visibleSize.width / 2, visibleSize.height / 2);
		particle->setAutoRemoveOnFinish(true);
		this->addChild(particle);
		auto ye = SimpleAudioEngine::getInstance()->playEffect("music/victory_screen_start.mp3");
		UserDefault::getInstance()->setIntegerForKey(NEW_TIME, timer->getTime());
		UserDefault::getInstance()->setIntegerForKey(row, this->_row);
		UserDefault::getInstance()->setIntegerForKey(column, this->_column);

		counter->start(2.0f, [this](){

			this->removeChild(photo);
			SceneMediator::getInstance()->gotoSuccessScene();

		});
	});
	//��ʾ��ť
	_implyButton = ui::Button::create("background_nb.png");
	_implyButton->setScale(0.5);
	_implyButton->setAnchorPoint(Vec2(0, 0));
	_implyButton->setPosition(Vec2(0, 10));
	this->addChild(_implyButton);

	_implyButton->addTouchEventListener([this](Ref* ref, ui::Widget::TouchEventType type){
		Layer* background_imply = LayerColor::create(Color4B(255, 255, 255, 128));
		auto picture = Sprite::create(photo->getPhoto());
		picture->setPosition(visibleSize.width / 2, visibleSize.height / 2);
		background_imply->addChild(picture);
		background_imply->setName("imply");
		if (this->getChildByName("imply") != nullptr) CCLOG("exist\n");
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			this->addChild(background_imply);
			break;
		default:
			if (this->getChildByName("imply") != nullptr)
			{
				this->removeChildByName("imply");
			}

		}
	});
}

void CasualScene::gameOver()
{
	timer->stopTimer();//������ʱû�д���timeֵ�Ǹ��������
	//��������ӳɾ��ж�
	
	SceneMediator::getInstance()->gotoStartScene();
}