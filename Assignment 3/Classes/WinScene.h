
#pragma once
#include <cocos2d.h>
#include "Buttons.h"
#include"GameScene.h"

class WinScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene(int inMoves, int inSeconds,
		int inMinutes);

	// implement the "static create()" method manually
	CREATE_FUNC(WinScene);

private:
	virtual bool init();
	void initButtons();
	void returnToMain();
	void update(float dt);
	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
	std::vector <Buttons*> winButtons;
	cocos2d::Label* moveCount;
	cocos2d::Label* movesText;
	cocos2d::Label* secDisplay;
	cocos2d::Label* minDisplay;
	bool alternate;
};