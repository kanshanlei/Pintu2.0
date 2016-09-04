#pragma once
#include<cocos2d.h>
USING_NS_CC;
class SelectGate :public Layer
{
public:
	CREATE_FUNC(SelectGate);
	//添加菜单项
	void addMenuItem(cocos2d::MenuItem *item);
	//更新位置
	void updatePosition();
	//更新位置，有动画
	void updatePositionWithAnimation();
	//位置矫正  修改位置forward为移动方向  当超过1/3，进1
	//true 为正向  false 负
	void rectify(bool forward);
	//初始化
	virtual bool init();
	//重置  显示所引号设置为0
	void reset();
	//返回被选中的item
	cocos2d::MenuItem * getCurrentItem();
private:
	//设置当前显示索引
	void setIndex(int index);
	//设置当前显示菜单项的索引号
	float getIndex();

	//数学计算式width*index/(abs(index)+CALC_A) ,其中CALC_A为常数
	float calcFunction(float index, float width);
private:
	//菜单菜单项的索引号
	float _index;
	//上一次菜单项的索引号
	float _lastIndex;
	//菜单项集合,_children顺序会变化，新建数组保存顺序
	cocos2d::Vector<cocos2d::MenuItem *> _items;
	//监听函数
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	//动画完结调用函数，这个主要是确定哪一个菜单项在前面
	void actionEndCallBack(float dx);
	//当前被选择的item
	cocos2d::MenuItem *_selectedItem;
};

