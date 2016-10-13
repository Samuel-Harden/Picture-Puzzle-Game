// GameScene is used to create the Backdrop for the Puzzle itself

#include "GameMenu.h"
#include "WinScene.h"
USING_NS_CC;

int moves;
int seconds;
int minutes;

cocos2d::Scene* WinScene::createScene(int inMoves, int inSeconds, int inMinutes)
{

	moves = inMoves;
	seconds = inSeconds;
	minutes = inMinutes;
	// 'scene' & 'layer' are an autoreleased objects
	cocos2d::Scene* scene = Scene::create();

	auto layer = WinScene::create();
	// add layer as a child to scene
	scene->addChild(layer);
	// return the scene

	return scene;
}

bool WinScene::init()
{

	if (!Layer::init())
	{
		return false;
	}

	alternate = false;

	// Sets the background for the game scene
	auto background = Sprite::create("Background1.png");
	background->setAnchorPoint(Vec2(0, 0));
	setPosition(Vec2(0, 0));
	this->addChild(background);
	
	moveCount = Label::createWithTTF(std::to_string(moves+1),
		"fonts/Marker Felt.ttf", 40);
	moveCount->setPosition(645, 300);
	this->addChild(moveCount, 1);

	movesText = Label::createWithTTF("You completed the Puzzle in",
		"fonts/Marker Felt.ttf", 40);
	movesText->setPosition(680, 420);
	this->addChild(movesText, 1);

	movesText = Label::createWithTTF("      Mins and      Secs",
		"fonts/Marker Felt.ttf", 40);
	movesText->setPosition(680, 360);
	this->addChild(movesText, 1);

	secDisplay = Label::createWithTTF(std::to_string(seconds),
		"fonts/Marker Felt.ttf", 40);
	secDisplay->setPosition(755, 360);
	this->addChild(secDisplay, 1);

	minDisplay = Label::createWithTTF(std::to_string(minutes),
		"fonts/Marker Felt.ttf", 40);
	minDisplay->setPosition(545, 360);
	this->addChild(minDisplay, 1);

	movesText = Label::createWithTTF("Taking you         Moves to finish",
		"fonts/Marker Felt.ttf", 40);
	movesText->setPosition(680, 300);
	this->addChild(movesText, 1);
	
	Buttons* victory = Buttons::create("CongratBlue.png", 680, 592);
	victory->setTag(2);
	this->addChild(victory, 1);
	winButtons.push_back(victory);

	initButtons();

	this->schedule(schedule_selector(WinScene::update), 0.5f);

	return true;
}

void WinScene::initButtons()
{

		Buttons* _Buttons = Buttons::create("MainMenu.png", 680, 130);

		_Buttons->setTag(1);

		this->addChild(_Buttons, 1);

		// Add Listener to new piece
		auto listener = EventListenerTouchOneByOne::create();
		listener->setSwallowTouches(true);

		listener->onTouchBegan = CC_CALLBACK_2(WinScene::onTouchBegan, this);
		//listener->onTouchEnded = CC_CALLBACK_2(Puzzle::onTouchEnded, this);

		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,
			_Buttons);
}

bool WinScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
	auto target = static_cast<Buttons*>(event->getCurrentTarget());
	Point locationInNode = target->convertToNodeSpace(touch->getLocation());
	Size s = target->getContentSize();
	Rect rect = Rect(0, 0, s.width, s.height);
	int i = 0;
	int x = 0;

	if (rect.containsPoint(locationInNode))
	{
		CCLOG("Touched Object at location x = %f, y = %f",
			locationInNode.x, locationInNode.y);

		i = target->getTag();

		// 1 is the main menu Button
		if (i == 1)
		{
			CCLOG("Touched Main Menu Button");
			returnToMain();
			return true;
		}

		return true;
	}
	return false;
}

void WinScene::returnToMain()
{
	Director::getInstance()->replaceScene
		(TransitionFade::create(1, GameMenu::createScene()));
}

void WinScene::update(float dt)
{
	if (alternate == false)
	{
		CCLOG("Changing Win Colour to Red...");
		winButtons[0]->changeImage("CongratRed.png");
		alternate = true;
		return;
	}
	if (alternate == true)
	{
		CCLOG("Changing Win Colour to Blue...");
		winButtons[0]->changeImage("CongratBlue.png");
		alternate = false;
		return;
	}
}