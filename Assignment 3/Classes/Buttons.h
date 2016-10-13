
#pragma once
#include <cocos2d.h>

class Buttons : public cocos2d::Sprite
{
public:
	// Constructor
	Buttons();
	// Deconstructor
	~Buttons();

	// just needs coordinates and a string
	static Buttons* create(std::string name, int posX, int posY);

	void initOptions(int posX, int posY);
	void changeImage(std::string newImage);

private:
};