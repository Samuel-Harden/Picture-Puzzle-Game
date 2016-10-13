
#pragma once
#include <cocos2d.h>
#include <vector>
#include "GameMenu.h"
#include "PuzzlePiece.h"
#include "WinScene.h"
#include <algorithm>

class Puzzle: public cocos2d::Sprite
{
public:
	
	// Constructor no Parameters
	Puzzle();
	// Deconstructor
	~Puzzle();

	void initPuzzle(GameScene* scene, int gameSize, std::string imageName);
	void setTime(int inSeconds, int inMinutes);

private:

	int puzzleSectionX;
	int puzzleSectionY;
	int puzzlePieceWidth;
	int puzzlePieceHeight;
	int inPositionNo;
	int posX;
	int posY;
	int z;
	int counter;
	int product;
	int puzzleGameSize;
	int blankTile;
	int piece1Rn;
	int piece2Rn;
	int piece1Cn;
	int piece2Cn;
	int blankPosNo;
	int blankRowNo;
	int blankColNo;
	int piecePosNo;
	int pieceRowNo;
	int pieceColNo;
	int correctPieces;
	int moves;
	int seconds;
	int minutes;
	int time;
	float tempPosXPiece;
	float tempPosYPiece;
	float tempPosXBlank;
	float tempPosYBlank;
	std::vector <PuzzlePiece*> pPiece;
	std::vector <Buttons*> menuButtons;
	std::vector <std::string> fileName;
	cocos2d::Label* numberOfMoves;
	cocos2d::Label* timer;

	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
	void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
	void initGame();
	void initButtons(GameScene* scene);
	void updateMoveCount();
	void rowAndColCheck(int i);
	void shuffle(int i);
	void returnToMain();
	void winCondition();
	void goToWinScene();
	void test(int i);
};