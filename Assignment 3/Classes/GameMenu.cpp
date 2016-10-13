#include "GameMenu.h"
#include "GameScene.h"
USING_NS_CC;

cocos2d::Scene * GameMenu::createScene()
{
	// 'scene' & 'layer' are an autoreleased objects
	cocos2d::Scene* scene = Scene::create();
	auto layer = GameMenu::create();
	// add layer as a child to scene
	scene->addChild(layer);
	// return the scene
	return scene;
}

bool GameMenu::init()
{
	// Randomly Set a picture to use
	picture = rand() % 2;

	if (!Layer::init())
	{
		return false;
	}

	initMenu();

	return true;
}

void GameMenu::menuCloseCallback(cocos2d::Ref * pSender)
{
	Director::getInstance()->end();
}

void GameMenu::initMenu()
{
	// Sets the background for the game scene
	auto background = Sprite::create("Background1.png");
	background->setAnchorPoint(Vec2(0, 0));
	setPosition(Vec2(0, 0));
	this->addChild(background);

	auto title = Sprite::create("Title.png");
	this->addChild(title, 2);
	title->setPosition(Vec2(900, 650));

	myName = Label::createWithTTF("By Samuel Harden",
		"fonts/Marker Felt.ttf", 30);
	myName->setPosition(1000, 575);
	this->addChild(myName, 1);

	auto dogOut = cocos2d::LayerColor::create(Color4B(0, 0, 0, 255));
	this->addChild(dogOut, 1);
	dogOut->setContentSize((Size(260, 200)));
	dogOut->setPosition(Vec2(470, 100));

	auto dogPicture = Sprite::create("Dog.png");
	this->addChild(dogPicture, 2);
	dogPicture->setScale(0.3f, 0.3f);
	dogPicture->setPosition(Vec2(600, 200));

	auto catOut = cocos2d::LayerColor::create(Color4B(0, 0, 0, 255));
	this->addChild(catOut, 1);
	catOut->setContentSize((Size(260, 200)));
	catOut->setPosition(Vec2(770, 100));

	auto catPicture = Sprite::create("Cat.png");
	this->addChild(catPicture, 2);
	catPicture->setScale(0.3f, 0.3f);
	catPicture->setPosition(Vec2(900, 200));

	auto tevezOut = cocos2d::LayerColor::create(Color4B(0, 0, 0, 255));
	this->addChild(tevezOut, 1);
	tevezOut->setContentSize((Size(260, 200)));
	tevezOut->setPosition(Vec2(1070, 100));

	auto tevezPicture = Sprite::create("Tevez.png");
	this->addChild(tevezPicture, 2);
	tevezPicture->setScale(0.3f, 0.3f);
	tevezPicture->setPosition(Vec2(1200, 200));

	initButtons();
	setStartPictureButtons();
}

void GameMenu::initButtons()
{
	tagNo = 0;
	posY = 600;
	posX = 250;
	fileName = { "Easy.png", "Medium.png", "hard.png", "QuitGame.png",
			"DogButton.png", "CatButton.png",  "TevezButton.png" };

	for (int i = 0; i < 7; i++)
	{
		Buttons* _Buttons = Buttons::create(fileName[i], posX, posY);

		_Buttons->setTag(tagNo);

		this->addChild(_Buttons, 1);
		tagNo++;

		// Add Listener to new piece
		auto listener = EventListenerTouchOneByOne::create();
		listener->setSwallowTouches(true);

		listener->onTouchBegan = CC_CALLBACK_2(GameMenu::onTouchBegan, this);
		listener->onTouchEnded = CC_CALLBACK_2(GameMenu::onTouchEnded, this);

		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,
				_Buttons);

		menuButtons.push_back(_Buttons);

		if (i <= 4)
		{
			posY -= 100;
		}

		if (i >= 3)
		{
			if (i == 3)
			{
				posX = 300;
			}
			posX += 300;
			posY = 50;
			if (i > 3)
			{
				pictureButtons.push_back(_Buttons);
			}
		}
	}
}

void GameMenu::setStartPictureButtons()
{
	if (picture == 0)
	{
		pictureButtons[0]->changeImage("DogButtonPressed.png");
		dogPicRed = true;
		catPicRed = false;
		tevezPicRed = false;
	}

	if (picture == 1)
	{
		pictureButtons[1]->changeImage("CatButtonPressed.png");
		dogPicRed = false;
		catPicRed = true;
		tevezPicRed = false;
	}

	if (picture == 2)
	{
		pictureButtons[2]->changeImage("TevezButtonPressed.png");
		dogPicRed = false;
		catPicRed = false;
		tevezPicRed = true;
	}
}

bool GameMenu::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
	inImageName = { "Dog.png", "Cat.png", "Tevez.png" };

	auto target = static_cast<Sprite*>(event->getCurrentTarget());
	Point locationInNode = target->convertToNodeSpace(touch->getLocation());
	Size s = target->getContentSize();
	Rect rect = Rect(0, 0, s.width, s.height);

	int i = target->getTag();

	if (rect.containsPoint(locationInNode))
	{
		if (i == 0) // Tag 0 is The easy Button
		{
			CCLOG("Touched easy Button");
			startGame(3, inImageName[picture]);
			return true;
		}

		if (i == 1) // Tag 1 is The medium Button
		{
			CCLOG("Touched medium Button");
			startGame(4, inImageName[picture]);
			return true;
		}

		if (i == 2) // Tag 2 is The hard Button
		{
			CCLOG("Touched hard Button");
			startGame(5, inImageName[picture]);
			return true;
		}

		if (i == 3) // Tag 3 is The quit Button
		{
			CCLOG("Touched Quit Button");
			quitGame();
			return true;
		}

		if (i == 4)
		{
			CCLOG("Touched Dog Button");
			picture = 0;

			if (catPicRed == true)
			{
				pictureButtons[1]->changeImage("CatButton.png");
				catPicRed = false;
			}
			if (tevezPicRed == true)
			{
				pictureButtons[2]->changeImage("TevezButton.png");
				tevezPicRed = false;
			}

			pictureButtons[0]->changeImage("DogButtonPressed.png");
			dogPicRed = true;
			return true;
		}

		if (i == 5)
		{
			CCLOG("Touched Cat Button");
			picture = 1;

			if (dogPicRed == true)
			{
				pictureButtons[0]->changeImage("DogButton.png");
				dogPicRed = false;
			}
			if (tevezPicRed == true)
			{
				pictureButtons[2]->changeImage("TevezButton.png");
				tevezPicRed = false;
			}

			pictureButtons[1]->changeImage("CatButtonPressed.png");
			catPicRed = true;
			return true;
		}

		if (i == 6)
		{
			CCLOG("Touched Tevez Button");
			picture = 2;

			if (dogPicRed == true)
			{
				pictureButtons[0]->changeImage("DogButton.png");
				dogPicRed = false;
			}
			if (catPicRed == true)
			{
				pictureButtons[1]->changeImage("CatButton.png");
				catPicRed = false;
			}

			pictureButtons[2]->changeImage("TevezButtonPressed.png");
			tevezPicRed = true;
			return true;
		}
	}
	return false;
}
void GameMenu::quitGame()
{
	Director::getInstance()->end();
}

void GameMenu::startGame(int inGameSize, std::string inImageName)
{
	Director::getInstance()->replaceScene(
	TransitionFade::create(1, GameScene::createScene(inGameSize, inImageName)));
}