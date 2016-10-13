
#include "PuzzlePiece.h"
#include "Puzzle.h"
USING_NS_CC;

// Constructor
PuzzlePiece::PuzzlePiece() {}

// Deconstructor
PuzzlePiece::~PuzzlePiece() {}

PuzzlePiece* PuzzlePiece::create(std::string imageName, int puzzleSectionX,
	int puzzleSectionY, int puzzlePieceWidth, int puzzlePieceHeight,
		int inRowNo, int inColNo, int inPositionNo, int gameSize,
			int posX, int posY)
{
	PuzzlePiece* pPiece = new PuzzlePiece();

	if (pPiece->initWithFile(imageName, Rect(puzzleSectionX, puzzleSectionY,
		(puzzlePieceWidth - 3), (puzzlePieceHeight - 3))))
	{
		pPiece->autorelease();
		pPiece->initOptions(inRowNo, inColNo, inPositionNo, gameSize, posX,
			posY);
		return pPiece;
	}
	CC_SAFE_DELETE(pPiece);
	return NULL;
}

void PuzzlePiece::initOptions(int inRowNo, int inColNo, int inPositionNo,
		int gameSize, int posX, int posY)
{
	// do things here like setTag(), setPosition() ect

	if (inPositionNo == (gameSize * gameSize - 1))
	{
		setColor(Color3B(0, 0, 0));
	}

	setAnchorPoint(Vec2(0, 0));
	setPosition(Vec2(posX, posY));
	positionNo = inPositionNo;
	rowNo = inRowNo;
	colNo = inColNo;
}

int PuzzlePiece::getPositionNo(int& x)
{
	x = positionNo;
	return x;
}

void PuzzlePiece::setPositionNo(int& x)
{
	positionNo = x;
}

int PuzzlePiece::getRowNo(int& x)
{
	x = rowNo;
	return x;
}

void PuzzlePiece::setRowNo(int& x)
{
	rowNo = x;
}

int PuzzlePiece::getColNo(int& x)
{
	x = colNo;
	return x;
}

void PuzzlePiece::setColNo(int& x)
{
	colNo = x;
}