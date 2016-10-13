#pragma once
#include "cocos2d.h"
#include "Buttons.h"

class GameMenu : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(GameMenu);

private:
	virtual bool init();
	void initMenu();
	void quitGame();
	void startGame(int inGameSize, std::string imageName);

	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
	void initButtons();
	void setStartPictureButtons();

	cocos2d::Sprite* easyButton;
	cocos2d::Sprite* mediumButton;
	cocos2d::Sprite* hardButton;
	cocos2d::Sprite* quitButton;
	cocos2d::Sprite* title;
	cocos2d::Label* myName;

	std::vector <Buttons*> menuButtons;
	std::vector <Buttons*> pictureButtons;
	std::vector <std::string> fileName;
	std::vector <std::string> inImageName;

	int gameSize;
	int posX;
	int posY;
	int tagNo;
	int picture;

	bool catPicRed;
	bool dogPicRed;
	bool tevezPicRed;
};