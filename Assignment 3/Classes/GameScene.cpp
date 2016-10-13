#include "GameMenu.h"
#include "GameScene.h"
#include "Puzzle.h"
USING_NS_CC;

int gameSize;
std::string imageName;

cocos2d::Scene* GameScene::createScene(int inGameSize, std::string inImageName)
{
	gameSize = inGameSize;
	imageName = inImageName;

	// 'scene' & 'layer' are an autoreleased objects
	cocos2d::Scene* scene = Scene::create();

	auto layer = GameScene::create();
	// add layer as a child to scene
	scene->addChild(layer);
	// return the scene

	return scene;
}

bool GameScene::init()
{
	timeSec = 0;
	timeMin = 0;

	if (!Layer::init())
	{
		return false;
	}

	// Sets the background for the game scene
	auto background = Sprite::create("Background1.png");
	background->setAnchorPoint(Vec2(0, 0));
	setPosition(Vec2(0, 0));
	this->addChild(background);

	auto fpOutline = cocos2d::LayerColor::create(Color4B(0, 0, 0, 255));
	this->addChild(fpOutline, 1);
	fpOutline->setContentSize((Size(257, 200)));
	fpOutline->setPosition(Vec2(1044, 500));
	
	// Shows the finished puzzle for the game scene
	auto finishedPuzzle = Sprite::create(imageName);
	this->addChild(finishedPuzzle, 2);
	finishedPuzzle->setScale(0.3f, 0.3f);
	finishedPuzzle->setPosition(Vec2(1172, 600));
	
	displayTime = Label::createWithTTF("Time Taken: ",
		"fonts/Marker Felt.ttf", 40);
	displayTime->setPosition(1175, 365);
	this->addChild(displayTime, 1);

	mins = Label::createWithTTF(" Mins ",
		"fonts/Marker Felt.ttf", 40);
	mins->setPosition(1130, 310);
	this->addChild(mins, 1);

	secs = Label::createWithTTF(" Secs ",
		"fonts/Marker Felt.ttf", 40);
	secs->setPosition(1250, 310);
	this->addChild(secs, 1);

	timerMin = Label::createWithTTF(std::to_string(timeMin),
		"fonts/Marker Felt.ttf", 40);
	timerMin->setPosition(1075, 310);
	this->addChild(timerMin, 1);

	timerSec = Label::createWithTTF(std::to_string(timeSec),
		"fonts/Marker Felt.ttf", 40);
	timerSec->setPosition(1200, 310);
	this->addChild(timerSec, 1);

	createPuzzle = new Puzzle();

	createPuzzle->initPuzzle(this, gameSize, imageName);

	this->schedule(schedule_selector(GameScene::update), 1.0f);

	return true;
}

void GameScene::update(float dt)
{
	timeSec++;
	//CCLOG("Updating Time");
	timerSec->setString(std::to_string(timeSec));

	if (timeSec == 60)
	{
		timeSec = 0;
		timerSec->setString(std::to_string(timeSec));
		timeMin++;
		timerMin->setString(std::to_string(timeMin));
	}
	createPuzzle->setTime(timeSec, timeMin);
}