
#pragma once
#include<Background.h>
#include<ui/CocosGUI.h>
#include"XMLParser.h"
USING_NS_CC;
class SuccessScene :public Layer
{
protected:
	Background* _background;
	ui::Button* _backBut;
	Sprite* _successTitle;
	Sprite* _timeTitle;
	ui::TextAtlas* _row;
	ui::TextAtlas* _column;
	ui::TextAtlas* _newTime;
//	Sprite* _chartsSuccessTitle;
//	std::vector<Node*> _chartList;

public:
	SuccessScene();
	virtual ~SuccessScene();
	CREATE_FUNC(SuccessScene);
	virtual bool init();

	static Scene* createScene();
};

