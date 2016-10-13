// GameScene is used to create the Backdrop for the Puzzle itself

#pragma once
#include <cocos2d.h>

class Puzzle;

class GameScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene(int inGameSize, std::string imageName);

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);

private:
	virtual bool init();
	void update(float dt);

	int timeSec;
	int timeMin;

	cocos2d::Label* timerSec;
	cocos2d::Label* timerMin;
	cocos2d::Label* mins;
	cocos2d::Label* secs;
	cocos2d::Label* displayTime;
	Puzzle* createPuzzle;
};
