#include "AppDelegate.h"
#include "GameMenu.h"
//#include "GameScene.h"
USING_NS_CC;

bool AppDelegate::applicationDidFinishLaunching()
{
	cocos2d::Director* director = Director::getInstance();
	cocos2d::GLView* glview = director->getOpenGLView();
	if (!glview)
	{
		glview = GLViewImpl::create("Game Menu");
		glview->setFrameSize(1360, 768);
		director->setOpenGLView(glview);
	}

	// create a scene and run it
	auto scene = GameMenu::createScene();
	director->runWithScene(scene);
	return true;
}

void AppDelegate::applicationDidEnterBackground() 
{

}

void AppDelegate::applicationWillEnterForeground() 
{

}