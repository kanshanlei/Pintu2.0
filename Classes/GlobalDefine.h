#ifndef __GlobalDefine__H__
#define __GlobalDefine__H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

#define WINSIZE Director::getInstance()->getWinSize()

#define setIntToXML     UserDefault::getInstance()->setIntegerForKey
#define setFloatToXML   UserDefault::getInstance()->setFloatForKey
#define setBoolToXML    UserDefault::getInstance()->setBoolForKey
#define getIntFromXML   UserDefault::getInstance()->getIntegerForKey
#define getFloatFromXML UserDefault::getInstance()->getFloatForKey
#define getBoolFromXML  UserDefault::getInstance()->getBoolForKey

#define GAMELEVEL_KEY   "gameLevel"        // ��ǰ�ؿ�
#define SOUND_KEY       "soundClose"            // ������Ч
#define MUSIC_KEY       "musicClose"              // ��������
#define SOUNDVOL        "soundVolume"        // ��Ч����
#define MUSICVOL        "musicVolume"          // ��������
#define EXP_KEY         "heroCurrentExp"        // Ӣ�۵�ǰ����

#define SELECTGATE      "selectGate"               // ѡ��Ĺؿ�
#define GATEONE         "gateOne"                     // ��һ��
#define GATETWO         "gateTwo"                    // �ڶ���
#define GATETHREE       "gateThree"               // ������
#define GAMEOVER        "gameOver"              // ��Ϸ�������

#define aduioEngine   SimpleAudioEngine::getInstance()


#define PLAYEFFECT if (getBoolFromXML(SOUND_KEY)) \
{\
	aduioEngine->setEffectsVolume(getFloatFromXML(SOUNDVOL)); \
	aduioEngine->playEffect("music/7611.mp3"); \
}

#endif

// ��ǰѡ��Ĺؿ�
extern int m_iSelectGate;