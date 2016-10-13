
#include "Puzzle.h"
USING_NS_CC;

// Constructor
Puzzle::Puzzle()
{

}

// Deconstructor
Puzzle::~Puzzle()
{

}

// Create the Puzzle within this function
void Puzzle::initPuzzle(GameScene* scene, int gameSize, std::string imageName)
{
	// variables initilisation
	z = 0;
	moves = 0;
	correctPieces = 0;
	blankTile = (((gameSize * gameSize) - 1));
	inPositionNo = 0;
	puzzleGameSize = gameSize;
	product = puzzleGameSize * puzzleGameSize;
	counter = 0;

	int inRowNo = 1;
	int inColNo = 1;
	int tagNo = 0;
		
	// creates a boarder for our puzzle
	auto puzzleBoarder = cocos2d::LayerColor::create(Color4B(0, 0, 0, 255));
	scene->addChild(puzzleBoarder, 1);
	puzzleBoarder->setContentSize((Size(810, 610)));
	puzzleBoarder->setAnchorPoint(Vec2(0.5, 0.5));
	puzzleBoarder->setPosition(Vec2(144, 94));

	// the puzzle area itself, where the puzzle pieces go
	auto puzzle = cocos2d::LayerColor::create(Color4B(0, 0, 0, 255));
	scene->addChild(puzzle, 1);
	puzzle->setContentSize((Size(800, 600)));
	puzzle->setAnchorPoint(Vec2(0.5, 0.5));
	puzzle->setPosition(Vec2(150, 100));

	// size of sprite image to load
	puzzlePieceWidth = puzzle->getBoundingBox().size.width / gameSize * 1;
	puzzlePieceHeight = puzzle->getBoundingBox().size.height / gameSize * 1;
	
	// starts top left, goes down, the across.
	for (int i = 0; i < gameSize; i++)
	{
		// used to set position and piece of image to use
		posX = puzzle->getBoundingBox().size.width / gameSize * i;
		puzzleSectionX = puzzle->getBoundingBox().size.width / gameSize * i;

		for (int j = (gameSize - 1); j > -1; j--)
		{
			// used to set position and piece of image to use
			posY = puzzle->getBoundingBox().size.height / gameSize * j;
			puzzleSectionY = puzzle->getBoundingBox().size.height
					/ gameSize * counter;

			// create new child piece
			PuzzlePiece* _Piece = PuzzlePiece::create(imageName, puzzleSectionX,
					puzzleSectionY, puzzlePieceWidth, puzzlePieceHeight,
						inRowNo, inColNo, inPositionNo, gameSize, posX, posY);

			_Piece->setTag(tagNo);

			if (inPositionNo < blankTile)
			{
				puzzle->addChild(_Piece, 2);
			}
			if (inPositionNo == blankTile)
			{
				puzzle->addChild(_Piece, 1);
			}

			// Add Listener to new piece
			auto listener = EventListenerTouchOneByOne::create();
			listener->setSwallowTouches(true);

			listener->onTouchBegan = CC_CALLBACK_2(Puzzle::onTouchBegan, this);
			listener->onTouchEnded = CC_CALLBACK_2(Puzzle::onTouchEnded, this);

			_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,
					_Piece);
			
			// used to store the Pieces.
			pPiece.push_back(_Piece);

			tagNo++;
			inPositionNo++;
			inRowNo++;
			counter++;
		}
		inColNo++;
		counter = 0;
		inRowNo = 1;
	} // Outer For loop finish
	
	initButtons(scene);
	
	cocos2d::Label* moveCount = Label::createWithTTF("Move Count: ",
			"fonts/Marker Felt.ttf", 40);
	moveCount->setPosition(1025, 370);
	puzzle->addChild(moveCount, 1);
	
	numberOfMoves = Label::createWithTTF(std::to_string (moves),
			"fonts/Marker Felt.ttf", 40);
	numberOfMoves->setPosition(1025, 320);
	puzzle->addChild(numberOfMoves, 1);
	
	//This function will set the game and move the tiles around
	while (z < (product * product))
	{
		// initGame only swaps one tile, so I keep recalling it until the
		// game is shuffled enough. could put loop in function?
		initGame();
	}
}

void Puzzle::initButtons(GameScene* scene)
{
	// max game size is 25 (24 in vector/array) so using 25 as starting 
	// point for tags on the buttons
	int tagNo = 25;
	int posY = 230;
	fileName = { "Shuffle.png", "MainMenu.png" };

	for (int i = 0; i < 2; i++)
	{
		Buttons* _Buttons = Buttons::create(fileName[i], 1178, posY);

		_Buttons->setTag(tagNo);

		scene->addChild(_Buttons, 1);

		// Add Listener to new piece
		auto listener = EventListenerTouchOneByOne::create();
		listener->setSwallowTouches(true);

		listener->onTouchBegan = CC_CALLBACK_2(Puzzle::onTouchBegan, this);
		listener->onTouchEnded = CC_CALLBACK_2(Puzzle::onTouchEnded, this);

		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,
				_Buttons);

		menuButtons.push_back(_Buttons);

		tagNo++;
		posY -= 100;
	}
}

bool Puzzle::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
	auto target = static_cast<PuzzlePiece*>(event->getCurrentTarget());
	Point locationInNode = target->convertToNodeSpace(touch->getLocation());
	Size s = target->getContentSize();
	Rect rect = Rect(0, 0, s.width, s.height);
	int i = 0;
	int x = 0;

	if (rect.containsPoint(locationInNode))
	{
		CCLOG("Touched Object at location x = %f, y = %f",
				locationInNode.x, locationInNode.y);
		CCLOG("Touched Puzzle Piece with PositionNo = %i",
				target->getPositionNo(x));
		CCLOG("Object Tag = %i", target->getTag());

		// Get the tag of the puzzlePiece or button that was touched
		i = target->getTag();

		// If the Piece is the blank one, nothing should happen
		if (i == blankTile)
		{
			return true;
		}

		if (i == 25)
		{
			z = 0;
			CCLOG("Touched Shuffle Button at location x = %f, y = %f",
					locationInNode.x, locationInNode.y);

			while (z < (product * product))
			{
				initGame();
			}
			updateMoveCount();
			return true;
		}
		if (i == 26)
		{
			CCLOG("Touched MainMenu Button at location x = %f, y = %f",
					locationInNode.x, locationInNode.y);
			returnToMain();
			return true;
		}
		// If a button wasnt touched but a puzzlePiece was...
		rowAndColCheck(i);
		return true;
	}
	return false;
}

void Puzzle::returnToMain()
{
	Director::getInstance()->replaceScene
		(TransitionFade::create(1, GameMenu::createScene()));
}

void Puzzle::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
	CCLOG("Touch Ended x = %f, y = %f",
		touch->getLocation().x, touch->getLocation().y);
}

// test function to see check piece selection is working correctly
void Puzzle::test(int i)
{
	pPiece[i]->setColor(Color3B(100, 0, 0));
}
/* These functions are no longer needed! Decided to leave them in so you can
   see some of the earlier functionality I was using to move single tiles
   (not rows columns ect)
void Puzzle::adjacentPieceCheck(int i)
{
	// Local variable reused on each call
	int x = 0;
	int y = 0;

	pPiece[blankTile]->getRowNo(piece1Rn);
	pPiece[blankTile]->getColNo(piece1Cn);
	pPiece[i]->getRowNo(piece2Rn);
	pPiece[i]->getColNo(piece2Cn);

	//Quick check to see if the Piece is moving, if yes return
	if (pPiece[i]->getNumberOfRunningActions() != 0 || 
	pPiece[blankTile]->getNumberOfRunningActions() != 0)
	{
		return;
	}

	// Tells us where the onTouch piece is
	pPiece[i]->getPositionNo(x);
	// Tells us where the Blank piece is
	pPiece[blankTile]->getPositionNo(y);

	// Checks the piece below to see if its the Blank piece
	if (y == (x + 1) && (x + 1 >= 0) && (x + 1 <= blankTile))
	{
		if ((piece1Rn == piece2Rn) || (piece1Cn == piece2Cn))
		{
			swapPosition(i);
		}
	}
	// Checks the piece above to see if its the Blank piece
	if (y == (x - 1) && (x - 1 >= 0) && (x - 1 <= blankTile))
	{
		if ((piece1Rn == piece2Rn) || (piece1Cn == piece2Cn))
		{
			swapPosition(i);
		}
	}
	// Checks the piece to the right to see if its the Blank piece
	if (y == (x + puzzleGameSize) && (x + puzzleGameSize >= 0)
	&& (x + puzzleGameSize <= blankTile))
	{
		if ((piece1Rn == piece2Rn) || (piece1Cn == piece2Cn))
		{
			swapPosition(i);
		}
	}
	// Checks the piece to the left to see if its the Blank piece
	if (y == (x - puzzleGameSize) && (x - puzzleGameSize >= 0) 
	&& (x - puzzleGameSize <= blankTile))
	{
		if ((piece1Rn == piece2Rn) || (piece1Cn == piece2Cn))
		{
			swapPosition(i);

		}
	}
}

void Puzzle::swapPosition(int i)
{
	// Temp variables that hold each peices location and position no.
	blankPosNo;
	blankRowNo;
	blankColNo;
	piecePosNo;
	pieceRowNo;
	pieceColNo;

	// Get position of the blank piece and make a temp variable to hold it
	Vec2 blankPos = pPiece[blankTile]->getPosition();
	Vec2 piecePos = pPiece[i]->getPosition();

	//tempPosXBlank = pPiece[blankTile]->getPositionX();
	//tempPosYBlank = pPiece[blankTile]->getPositionY();

	pPiece[blankTile]->getPositionNo(blankPosNo);
	pPiece[blankTile]->getRowNo(blankRowNo);
	pPiece[blankTile]->getColNo(blankColNo);

	//tempPosXPiece = pPiece[i]->getPositionX();
	//tempPosYPiece = pPiece[i]->getPositionY();

	pPiece[i]->getPositionNo(piecePosNo);
	pPiece[i]->getRowNo(pieceRowNo);
	pPiece[i]->getColNo(pieceColNo);

	//pPiece[blankTile]->setPositionX(tempPosXPiece);
	//pPiece[blankTile]->setPositionY(tempPosYPiece);

	pPiece[blankTile]->setPositionNo(piecePosNo);
	pPiece[blankTile]->setRowNo(pieceRowNo);
	pPiece[blankTile]->setColNo(pieceColNo);

	//pPiece[i]->setPositionX(tempPosXBlank);
	//pPiece[i]->setPositionY(tempPosYBlank);

	pPiece[i]->setPositionNo(blankPosNo);
	pPiece[i]->setRowNo(blankRowNo);
	pPiece[i]->setColNo(blankColNo);

	MoveTo *blankAction = MoveTo::create(0.1f, piecePos);
	MoveTo *pieceAction = MoveTo::create(0.1f, blankPos);

	pPiece[blankTile]->runAction(blankAction);
	pPiece[i]->runAction(pieceAction);

	winCondition(2);

	updateMoveCount();
}
*/
void Puzzle::initGame()
{
	piece1Rn = 0;
	piece2Rn = 0;
	piece1Cn = 0;
	piece2Cn = 0;

		// Local variable reused on each call
		int x = 0;
		int y = 0;
		int a = 0;

		// get pos no for the blank piece
		pPiece[blankTile]->getPositionNo(x);

		// The Position of the piece to swap
		std::vector <int> positionToSwap = { (x + 1), (x - 1),
			(x + puzzleGameSize), (x - puzzleGameSize) };

		// i is a random number between 1 and 3 that is used to select a move
		int i = rand() % 4;

		if (positionToSwap[i] <= (blankTile) && positionToSwap[i] >= 0)
		{
			// Cycle through the pieces until we have the one we want
			while (1)
			{
				pPiece[a]->getPositionNo(y);
				if (y == positionToSwap[i])
				{
					break;
				}
				a++;
			}

			pPiece[blankTile]->getRowNo(piece1Rn);
			pPiece[blankTile]->getColNo(piece1Cn);
			pPiece[a]->getRowNo(piece2Rn);
			pPiece[a]->getColNo(piece2Cn);

			// Checks the piece below to see if its the Blank piece
			if (y == (x + 1) && (x + 1 >= 0) && (x + 1 <= blankTile))
			{
				if ((piece1Rn == piece2Rn) || (piece1Cn == piece2Cn))
				{
						shuffle(a);
						z++;
						return;
				}
			}
			// Checks the piece above to see if its the Blank piece
			if (y == (x - 1) && (x - 1 >= 0) && (x - 1 <= blankTile))
			{
				if ((piece1Rn == piece2Rn) || (piece1Cn == piece2Cn))
				{
						shuffle(a);
						z++;
						return;
				}
			}
			// Checks the piece to the right to see if its the Blank piece
			if (y == (x + puzzleGameSize) && (x + puzzleGameSize >= 0) &&
				(x + puzzleGameSize <= blankTile))
			{
				if ((piece1Rn == piece2Rn) || (piece1Cn == piece2Cn))
				{
						shuffle(a);
						z++;
						return;
				}
			}
			// Checks the piece to the left to see if its the Blank piece
			if (y == (x - puzzleGameSize) && (x - puzzleGameSize >= 0) &&
				(x - puzzleGameSize <= blankTile))
			{
				if ((piece1Rn == piece2Rn) || (piece1Cn == piece2Cn))
				{
						shuffle(a);
						z++;
						return;
				}
			}
		}
}

void Puzzle::shuffle(int i)
{
	// Temp variables that hold each peices location and position no ect
	tempPosXBlank = 0;
	tempPosYBlank = 0;
	blankPosNo = 0;
	blankRowNo = 0;
	blankColNo = 0;

	tempPosXPiece = 0;
	tempPosYPiece = 0;
	piecePosNo = 0;
	pieceRowNo = 0;
	pieceColNo = 0;

	// Create Temp values...
	tempPosXBlank = pPiece[blankTile]->getPositionX();
	tempPosYBlank = pPiece[blankTile]->getPositionY();

	pPiece[blankTile]->getPositionNo(blankPosNo);
	pPiece[blankTile]->getRowNo(blankRowNo);
	pPiece[blankTile]->getColNo(blankColNo);

	tempPosXPiece = pPiece[i]->getPositionX();
	tempPosYPiece = pPiece[i]->getPositionY();

	pPiece[i]->getPositionNo(piecePosNo);
	pPiece[i]->getRowNo(pieceRowNo);
	pPiece[i]->getColNo(pieceColNo);

	// Set new values
	pPiece[blankTile]->setPositionX(tempPosXPiece);
	pPiece[blankTile]->setPositionY(tempPosYPiece);

	pPiece[blankTile]->setPositionNo(piecePosNo);
	pPiece[blankTile]->setRowNo(pieceRowNo);
	pPiece[blankTile]->setColNo(pieceColNo);

	pPiece[i]->setPositionX(tempPosXBlank);
	pPiece[i]->setPositionY(tempPosYBlank);

	pPiece[i]->setPositionNo(blankPosNo);
	pPiece[i]->setRowNo(blankRowNo);
	pPiece[i]->setColNo(blankColNo);
}

void Puzzle::winCondition()
{
	int b = 0;
	int a = 0;
	int totalPieces = ((puzzleGameSize * puzzleGameSize) - 1);
	correctPieces = 0;
	while (a <= totalPieces)
	{
		pPiece[a]->getPositionNo(b);
		if (b == pPiece[a]->getTag())
		{
			correctPieces++;
		}
		a++;
	}

	if (correctPieces == (totalPieces + 1))
	{
		CCLOG("GameWon!");
		//returnToMain();
		goToWinScene();
	}
}

void Puzzle::rowAndColCheck(int i)
{
	int iRowNo = 0;
	int iColNo = 0;
	int blankRowNo = 0;
	int blankColNo = 0;
	int nextTilePos = 0;
	int blankPos = 0;

	int a = 0;
	int b = 0;
	// This Variable is for how many moves to make to move multiple tiles
	int movesToReposition = 0;

	// Get the Row and Col numbers for both pieces
	pPiece[i]->getRowNo(iRowNo);
	pPiece[i]->getColNo(iColNo);
	pPiece[blankTile]->getRowNo(blankRowNo);
	pPiece[blankTile]->getColNo(blankColNo);

	if(iRowNo == blankRowNo)
	{
		CCLOG("Piece is on the Same Row as Blank...");
		// Check if Blank is to the right of the touched piece
		if (blankColNo > iColNo)
		{
			movesToReposition = blankColNo - iColNo;

			for (int swaps = 0; swaps < movesToReposition; swaps++)
			{
				pPiece[blankTile]->getPositionNo(blankPos);
				nextTilePos = blankPos - puzzleGameSize;

				// Now find the piece at Pos 'nextTile'
				while (1)
				{
					pPiece[a]->getPositionNo(b);
					if (b == nextTilePos)
					{
						break;
					}
					a++;
				}
				shuffle(a);
				winCondition();
				updateMoveCount();
				a = 0;
			}
			return;
		}
		// Check if Blank is to the Left of the touched piece
		if (blankColNo < iColNo)
		{
			movesToReposition = iColNo - blankColNo;

			for (int swaps = 0; swaps < movesToReposition; swaps++)
			{
				pPiece[blankTile]->getPositionNo(blankPos);
				nextTilePos = blankPos + puzzleGameSize;

				// Now find the piece at Pos 'nextTile'
				while (1)
				{
					pPiece[a]->getPositionNo(b);
					if (b == nextTilePos)
					{
						break;
					}
					a++;
				}				
				shuffle(a);
				winCondition();
				updateMoveCount();
				a = 0;
			}
			return;
		}
	}

	if (iColNo == blankColNo)
	{
		CCLOG("Piece is on the Same Col as Blank...");
		// Check if Blank is lower than the touched piece
		if (blankRowNo > iRowNo)
		{
			movesToReposition = blankRowNo - iRowNo;

			for (int swaps = 0; swaps < movesToReposition; swaps++)
			{
				pPiece[blankTile]->getPositionNo(blankPos);
				nextTilePos = blankPos - 1;

				// Now find the piece at Pos 'nextTile'
				while (1)
				{
					pPiece[a]->getPositionNo(b);
					if (b == nextTilePos)
					{
						break;
					}
					a++;
				}
				shuffle(a);
				winCondition();
				updateMoveCount();
				a = 0;
			}
			return;
		}
		// Check if Blank is higher than the touched piece
		if (blankRowNo < iRowNo)
		{
			movesToReposition = iRowNo - blankRowNo;

			for (int swaps = 0; swaps < movesToReposition; swaps++)
			{
				pPiece[blankTile]->getPositionNo(blankPos);
				nextTilePos = blankPos + 1;

				// Now find the piece at Pos 'nextTile'
				while (1)
				{
					pPiece[a]->getPositionNo(b);
					if (b == nextTilePos)
					{
						break;
					}
					a++;
				}
				shuffle(a);
				winCondition();
				updateMoveCount();
				a = 0;
			}
			return;
		}
	}
}

void Puzzle::updateMoveCount()
{
	moves++;
	numberOfMoves->setString(std::to_string(moves));
}

void Puzzle::goToWinScene()
{
	Director::getInstance()->replaceScene(
	TransitionFade::create(1, WinScene::createScene(moves, seconds, minutes)));
}

void Puzzle::setTime(int inSeconds, int inMinutes)
{
	seconds = inSeconds;
	minutes = inMinutes;
}