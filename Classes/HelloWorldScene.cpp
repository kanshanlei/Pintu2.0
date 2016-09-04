#include "HelloWorldScene.h"
#include"UserData.h"
#include <algorithm>
USING_NS_CC;
Scene* HelloWorld::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = HelloWorld::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;

}
void HelloWorld::initLevelDataList()
{
	auto str = FileUtils::getInstance()->getStringFromFile("leveldata.csv");

	std::vector<std::string> rowList;

	char *row = strtok((char*)str.c_str(), "\n");
	while (row)
	{
		rowList.push_back(row);
		row = strtok(nullptr, "\n");
	}

	for (auto row = rowList.begin(); row != rowList.end(); ++row) {
		char* rows = strtok((char*)row->c_str(), ",");
		char* columns = strtok(nullptr, ",");
		char* loss = strtok(nullptr, ",");//������ÿһ�صļ�ֵ����ʱ��û��

		if (rows == nullptr || columns == nullptr || loss == nullptr) {
			continue;
		}

		LevelData level;

		level.rows = atoi(rows);
		level.columns = atoi(columns);
		level.loss = atoi(loss);

		if (level.rows*level.columns <= 0 || level.loss<0) {
			continue;
		}
		_levelDataList.push_back(level);

	}
	_allLevel = static_cast<int>(_levelDataList.size());
}


// on "init" you need to initialize your instance
bool HelloWorld::init()
{

	if (!Layer::init())
	{
		return false;
	}
	initLevelDataList();
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	// Ԥ���ر������ֺ���Ч
	SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("music/va1.mp3");
	isPause = false;
	// ��Ĭ�ϲ��ű�������
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("music/va1.mp3", true);
	//	SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(1.0);
	Layer* background = LayerColor::create(Color4B(255, 255, 255, 128));
	addChild(background);
	_nowLevel = -1;
	nextLevel();
	initUI();

	timer = ScoreTimer::create();
	this->addChild(timer);



	return true;
}
