#pragma once
#include<cocos2d.h>
USING_NS_CC;
class SelectGate :public Layer
{
public:
	CREATE_FUNC(SelectGate);
	//���Ӳ˵���
	void addMenuItem(cocos2d::MenuItem *item);
	//����λ��
	void updatePosition();
	//����λ�ã��ж���
	void updatePositionWithAnimation();
	//λ�ý���  �޸�λ��forwardΪ�ƶ�����  ������1/3����1
	//true Ϊ����  false ��
	void rectify(bool forward);
	//��ʼ��
	virtual bool init();
	//����  ��ʾ����������Ϊ0
	void reset();
	//���ر�ѡ�е�item
	cocos2d::MenuItem * getCurrentItem();
private:
	//���õ�ǰ��ʾ����
	void setIndex(int index);
	//���õ�ǰ��ʾ�˵����������
	float getIndex();

	//��ѧ����ʽwidth*index/(abs(index)+CALC_A) ,����CALC_AΪ����
	float calcFunction(float index, float width);
private:
	//�˵��˵����������
	float _index;
	//��һ�β˵����������
	float _lastIndex;
	//�˵����,_children˳���仯���½����鱣��˳��
	cocos2d::Vector<cocos2d::MenuItem *> _items;
	//��������
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	//���������ú����������Ҫ��ȷ����һ���˵�����ǰ��
	void actionEndCallBack(float dx);
	//��ǰ��ѡ���item
	cocos2d::MenuItem *_selectedItem;
};
