
#pragma once
#include <cocos2d.h>
class Puzzle;

class PuzzlePiece: public cocos2d::Sprite//, public Puzzle
{
public:
	// Constructor
	PuzzlePiece();
	// Deconstructor
	~PuzzlePiece();

	static PuzzlePiece* create(std::string imageName, int puzzleSectionX,
		int puzzleSectionY, int puzzlePieceWidth, int puzzlePieceHeight,
			int inRowNo, int inColNo, int inPositionNo, int gameSize, int posX,
				int posY);

	// puclic functions used to access private variables
	int getPositionNo(int& x);
	void setPositionNo(int& x);
	int getRowNo(int& x);
	void setRowNo(int& x);
	int getColNo(int& x);
	void setColNo(int& x);

	void initOptions(int inRowNo, int inColNo, int inPositionNo, int gameSize,
		int posX, int posY);

private:
	int positionNo;
	int rowNo;
	int colNo;
};