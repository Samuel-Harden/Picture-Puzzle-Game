#include "main.h"
#include "AppDelegate.h"
#include "cocos2d.h"
#include <cstdlib>
#include <ctime>

USING_NS_CC;

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
	//srand((unsigned int)time(NULL));
	srand(static_cast<unsigned int>(time(0)));

    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // create the application instance
    AppDelegate app;
	return Application::getInstance()->run();
	
}
