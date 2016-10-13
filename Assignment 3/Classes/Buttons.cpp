
#include "Buttons.h"
USING_NS_CC;

// Constructor
Buttons::Buttons() {}

// Deconstructor
Buttons::~Buttons() {}

Buttons* Buttons::create(std::string name, int posX, int posY)
{
	Buttons* button = new Buttons();

	if (button->initWithFile(name))
	{
		button->autorelease();

		button->initOptions(posX, posY);

		return button;
	}

	CC_SAFE_DELETE(button);
	return NULL;
}

void Buttons::initOptions( int posX, int posY)
{

	setPosition(Vec2(posX, posY));

}

void Buttons::changeImage(std::string newImage)
{
	initWithFile(newImage);
}