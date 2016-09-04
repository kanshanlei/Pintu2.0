#include"stdlib.h"
#include "CuttingPhotos.h"
#include "SimpleAudioEngine.h"
/*
ע����������Ǻ�����ģ���ƽʱ�����з����෴
*/
CuttingPhotos::CuttingPhotos() :
_rows(3),
_columns(3)
{

}


CuttingPhotos::~CuttingPhotos()
{
	this->removeAllChildren();
}

CuttingPhotos* CuttingPhotos::create(const char *photo, unsigned int columns,
	unsigned int rows){
	CuttingPhotos *cp = new CuttingPhotos();
	
	if (cp&&cp->initWitchPhoto(photo, rows, columns)){
		cp->autorelease();
		return cp;
	}

	CC_SAFE_DELETE(cp);

	return nullptr;
}

bool CuttingPhotos::initWitchPhoto(const char* photo, unsigned int rows,
	unsigned int columns){
	bool result = false;
	_photo = const_cast<char*>(photo);
	this->_ignoreAnchorPointForPosition = false;//��һ������Ҫ�Ŵ���С��ʱ�����anchorpoint�Ļ���
	if (Layer::init()){
		_rows = rows;
		_columns = columns;
		if(initSlices(photo)){//��ʼ����
			initTouchEventListener();

			restart();

			result = true;
		}
		else{
			result = false;
		}
	}
	else{ result = false; }
	return result;
}

bool CuttingPhotos::initSlices(const char*photo){
	Texture2D *texture = Director::getInstance()->getTextureCache()->
		addImage(photo);
	
	if (texture == nullptr){ return false; }
	for (int w = 0; w < _rows; ++w){
		std::vector<Sprite*> row;
		for (int h = 0; h < _columns; h++){
			row.push_back(nullptr);
		}
		_slices.push_back(row);//��ʼ����*�и�Ԫ�صľ������
	}

	auto size = texture->getContentSize();
	_sliceWidth = size.width / _rows;
	_sliceHeight = size.height / _columns;

	this->setContentSize(size);
	//�ڳ����һ��
	auto endSlice = Sprite::createWithTexture(texture, Rect(_sliceWidth*
		(_rows - 1), _sliceHeight*(_columns - 1), _sliceWidth, _sliceHeight));
	endSlice->setAnchorPoint(Vec2(0, 0));
	endSlice->setPosition(_sliceWidth*(_rows - 1), 0);
	endSlice->setOpacity(100);//͸����
	this->addChild(endSlice);

	_slices[_rows - 1][_columns - 1] = nullptr;
	//��Ӹ���
	for (int w = 0; w < _rows; ++w){
		for (int h = 0; h < _columns; h++){
			if (w == _rows - 1 && h == _columns - 1) break;
			Sprite*slice = Sprite::createWithTexture(texture, Rect(_sliceWidth*
				w , _sliceHeight*h , _sliceWidth, _sliceHeight));
			slice->setAnchorPoint(Vec2(0, 0));
			//���ø����ʶ�Ա�����Ƿ�ƴ��
			std::stringstream ss;
			std::string str;
			ss << w*_columns+h;
			ss >> str;
			slice->setName(str);
			this->addChild(slice);

			_slices[w][h] = slice;
		}
	}
	return true;
}

void CuttingPhotos::initTouchEventListener()
{
	auto listner = EventListenerTouchOneByOne::create();

	listner->onTouchBegan = [&](Touch *touch, Event* event){
		Point locationInNode = this->convertToNodeSpace(touch->getLocation());

		Size s = this->getContentSize();//���ͼƬ����Ĵ�С

		Rect rect = Rect(0, 0, s.width, s.height);

		if (rect.containsPoint(locationInNode)){
			int x = static_cast<int>(floor(locationInNode.x / this->_sliceWidth));
			int y = static_cast<int>(floor(locationInNode.y / this->_sliceHeight));
			this->move(x, y);
			return true;
		}
		else{

			return false;
		}
	};
	/*
		listner->onTouchBegan = [&](Touch *touch, Event *event){
			Point locationInNode = this->convertToNodeSpace(touch->getLocation());
			int x = static_cast<int>(floor(locationInNode.x / this->_sliceWidth));
			int y = static_cast<int>(floor(locationInNode.y / this->_sliceHeight));
			this->move(x, y);
			return true;
		};
	*/
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listner, this); 
}

void CuttingPhotos::initMove(int& row, int& column)
{
	auto value = static_cast<int>(CCRANDOM_0_1() * 4);//��������
	switch (value){
	case 0:
		if (row > 0){
			_slices[row][column] = _slices[row - 1][column];
			_slices[row][column]->setPosition(row*_sliceWidth, _sliceHeight*_columns - (column + 1)*
				_sliceHeight);
			_slices[--row][column] = nullptr;
		}
		break;
	case 1:
		if (row < _rows-1){
			_slices[row][column] = _slices[row + 1][column];
			_slices[row][column]->setPosition(row*_sliceWidth, _sliceHeight*_columns - (column + 1)*
				_sliceHeight);
			_slices[++row][column] = nullptr;
		}
		break;
	case 2:
		if (column>0){
			_slices[row][column] = _slices[row][column - 1];
			_slices[row][column]->setPosition(row*_sliceWidth, _sliceHeight*_columns - (column + 1)*
				_sliceHeight);
			_slices[row][--column] = nullptr;
		}
		break;
	case 3:
		if (column < _columns-1){
			_slices[row][column] = _slices[row][column + 1];
			_slices[row][column]->setPosition(row*_sliceWidth, _sliceHeight*_columns - (column + 1)*
				_sliceHeight);
			_slices[row][++column] = nullptr;
		}
		break;
	default:break;
	}
}

bool CuttingPhotos::check(){
	for (int w = 0; w < _rows; w++)
	for (int h = 0; h < _columns; h++){
		if (w == _rows - 1 && h == _columns - 1)return true;
		if (_slices[w][h] == nullptr) return false;
		if (atoi(_slices[w][h]->getName().c_str()) != w*_columns + h) return false;
	}
}

void CuttingPhotos::move(int x, int y)
{
	y = _columns - y - 1;
	auto slice = _slices[x][y];

	if (slice == nullptr) return;

	bool isFind = false;
	Point targetPos;
	if (y < _columns - 1 && _slices[x][y + 1] == nullptr){
		targetPos.x = x;
		targetPos.y = y + 1;
		isFind = true;
	}
	else if (y>0 && _slices[x][y - 1] == nullptr){
		targetPos.x = x;
		targetPos.y = y - 1;
		isFind = true;
	}
	else if (x < _rows - 1 && _slices[x + 1][y] == nullptr){
		targetPos.x = x + 1;
		targetPos.y = y;
		isFind = true;
	}
	else if (x>0 && _slices[x - 1][y] == nullptr){
		targetPos.x = x-1;
		targetPos.y = y;
		isFind = true;
	}

	if (isFind == false) return;
	//�����ƶ���Ч
	auto music = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("music/7611.mp3");
	slice->runAction(MoveTo::create(0.25f, Vec2(targetPos.x*_sliceWidth,
		_sliceHeight*_columns - (targetPos.y + 1)*_sliceHeight)));
	_slices[targetPos.x][targetPos.y] = slice;
	_slices[x][y] = nullptr;
	
	if (check()){
		//������һ�ؿ�
		_completeCallback();
	}
}

void CuttingPhotos::restart(){
	_slices[_rows - 1][_columns - 1] = nullptr;
	int _randRound = _rows*_columns * 10;
	int row = _rows - 1;
	int column = _columns - 1;
	while (_randRound--){
		initMove(row,column);
	}
	
}

void CuttingPhotos::registerCallFunc(std::function<void()> completeCallback)
{
	_completeCallback = completeCallback;
}