#include <iostream>
#include <vector>
#include <windows.h>
#include "BoardState.h"


Board::BoardState::BoardState()
	: BoardState(5, 5, 0, 0, 4, 4) {};

Board::BoardState::~BoardState()
{
	for (int i = 0; i < this->height; i++) {
		delete[] this->board[i];
	}
	delete[] this->board;
}

Board::BoardState::BoardState(int width, int height)
	: width(width), height(height)
{
	board = new int* [height];
	for (int i = 0; height > i; i++)
		board[i] = new int[width];
	this->fill();
}
Board::BoardState::BoardState(int width, int height, int ox, int oy, int xx, int xy)
	: width(width), height(height), o_X(ox), x_X(xx), o_Y(oy), x_Y(xy)
{
	board = new int* [height];
	for (int i = 0; height > i; i++)
		board[i] = new int[width];
	this->fill();
	setPos(o_X, o_Y, 1);
	setPos(x_X, x_Y, 2);
}

Board::BoardState::BoardState(Board::BoardState& bs, bool side, int x, int y)
	: Board::BoardState(bs.width, bs.height) {
	for (int i = 0; i < this->height; i++)
		for (int j = 0; j < this->width; j++)
			setPos(j, i, bs.getPos(j, i));
	this->o_X = bs.o_X;
	this->x_X = bs.x_X;
	this->o_Y = bs.o_Y;
	this->x_Y = bs.x_Y;
	(side) ? setO(x, y) : setX(x, y);
}

void Board::BoardState::fill()
{
	for (int i = 0; i < this->height; i++)
		for (int j = 0; j < this->width; j++)
			this->setPos(j, i, 0);
}

void Board::BoardState::GetPossibleBoardStates(std::vector<TreeNode<Board::BoardState*>*>& vec, bool side)
{

	int x = (side) ? this->o_X : this->x_X;
	int y = (side) ? this->o_Y : this->x_Y;
	std::pair<int, int> moveSet[8] = { {1,1},{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1},{0,1} };

	for (int a = 0; a < 8; a++)
	{
		int _x = x + moveSet[a].first;
		int _y = y + moveSet[a].second;

		if (!((_x >= 0 && _x < this->width) && (_y >= 0 && _y < this->height)))
			continue;

		while ((_x >= 0 && _x < this->width) && (_y >= 0 && _y < this->height))
		{
			if (this->getPos(_x, _y) > 0)
				break;

			BoardState* bs = new BoardState(*this, side, _x, _y);

			TreeNode<BoardState*>* nodes = new TreeNode<BoardState*>(bs);

			vec.push_back(nodes);
			_x += moveSet[a].first;
			_y += moveSet[a].second;
		}
	}
}
void Board::BoardState::GetPossibleMoves(std::vector<std::pair<int, int>>& vec, bool side)
{
	int x = (side) ? this->o_X : this->x_X;
	int y = (side) ? this->o_Y : this->x_Y;
	std::pair<int, int> moveSet[8] = { {1,1},{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1},{0,1} };

	for (int a = 0; a < 8; a++)
	{
		int _x = x + moveSet[a].first;
		int _y = y + moveSet[a].second;

		if (!((_x >= 0 && _x < this->width) && (_y >= 0 && _y < this->height)))
			continue;

		while ((_x >= 0 && _x < this->width) && (_y >= 0 && _y < this->height))
		{
			if (this->getPos(_x, _y) > 0)
				break;
			vec.push_back(std::make_pair(_x, _y));
			_x += moveSet[a].first;
			_y += moveSet[a].second;
		}
	}
}

int Board::BoardState::GetPossibleMoves(bool side)
{
	int x = (side) ? this->o_X : this->x_X;
	int y = (side) ? this->o_Y : this->x_Y;
	int possibleMoves = 0;
	std::pair<int, int> moveSet[8] = { {1,1},{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1},{0,1} };

	for (int a = 0; a < 8; a++)
	{
		int _x = x + moveSet[a].first;
		int _y = y + moveSet[a].second;

		if (!((_x >= 0 && _x < this->width) && (_y >= 0 && _y < this->height)))
			continue;

		while ((_x >= 0 && _x < this->width) && (_y >= 0 && _y < this->height))
		{
			if (this->getPos(_x, _y) > 0)
				break;
			possibleMoves++;
			_x += moveSet[a].first;
			_y += moveSet[a].second;
		}
	}
	return possibleMoves;
}

int Board::BoardState::getWidth() const
{
	return this->width;
}
int Board::BoardState::getHeight() const
{
	return this->height;
}
void Board::BoardState::setO(int x, int y) {
	this->o_X = x;
	this->o_Y = y;
	this->setPos(x, y, 1);
}
void Board::BoardState::setX(int x, int y) {
	this->x_X = x;
	this->x_Y = y;
	this->setPos(x, y, 2);
}
void Board::BoardState::moveO(int x, int y) {
	this->setPos(o_X, o_Y, 3);
	this->setO(x, y);
}
void Board::BoardState::moveX(int x, int y) {
	this->setPos(x_X, x_Y, 3);
	this->setX(x, y);
}
int Board::BoardState::getPos(int x, int y) const
{
	return this->board[y][x];
}
void Board::BoardState::setPos(int x, int y, int v)
{
	this->board[y][x] = v;
}


void Board::DisplayBoard(Board::BoardState* bs) {

	for (int i = 0; i < bs->getHeight(); i++)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		std::cout << std::endl << "     ";
		for (int j = 0; j < bs->getWidth(); j++)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
				((j % 2) == (i % 2)) ?
				112 : 240);
			switch (bs->getPos(j, i))
			{
			case 0: std::cout << "   "; break;
			case 1: std::cout << " O "; break;
			case 2: std::cout << " X "; break;
			case 3: std::cout << " # "; break;
			}
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	std::cout << std::endl;

}
void Board::DisplayBoard(Board::BoardState* bs, int x, int y) {

	for (int i = 0; i < bs->getHeight(); i++)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		std::cout << std::endl << "     ";
		for (int j = 0; j < bs->getWidth(); j++)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
				((j % 2) == (i % 2)) ?
				112 : 240);
			if (x == j && y == i)
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 160);

			switch (bs->getPos(j, i))
			{
			case 0: std::cout << "   "; break;
			case 1: std::cout << " O "; break;
			case 2: std::cout << " X "; break;
			case 3: std::cout << " # "; break;
			}
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	std::cout << std::endl;

}
void Board::DisplayBoard(BoardState* bs, bool side) {
	std::vector<std::pair<int, int>> allMoves;

	bs->GetPossibleMoves(allMoves, side);
	for (int i = 0; i < bs->getHeight(); i++)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		std::cout << std::endl << "     ";
		for (int j = 0; j < bs->getWidth(); j++)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
				((j % 2) == (i % 2)) ?
				(std::find(allMoves.begin(), allMoves.end(), std::make_pair(j, i)) != allMoves.end()) ? 96 : 112 :
				(std::find(allMoves.begin(), allMoves.end(), std::make_pair(j, i)) != allMoves.end()) ? 224 : 240);
			switch (bs->getPos(j, i))
			{
			case 0: std::cout << "   "; break;
			case 1: std::cout << " O "; break;
			case 2: std::cout << " X "; break;
			case 3: std::cout << " # "; break;
			}
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	std::cout << std::endl;

}
void Board::DisplayBoard(Board::BoardState* bs, bool side, int move) {
	std::vector<std::pair<int, int>> allMoves;

	bs->GetPossibleMoves(allMoves, side);
	for (int i = 0; i < bs->getHeight(); i++)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		std::cout << std::endl << "     ";
		for (int j = 0; j < bs->getWidth(); j++)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
				((j % 2) == (i % 2)) ?
				(std::find(allMoves.begin(), allMoves.end(), std::make_pair(j, i)) != allMoves.end()) ? 96 : 112 :
				(std::find(allMoves.begin(), allMoves.end(), std::make_pair(j, i)) != allMoves.end()) ? 224 : 240);

			if (allMoves[move] == std::make_pair(j, i))
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 160);

			switch (bs->getPos(j, i))
			{
			case 0: std::cout << "   "; break;
			case 1: std::cout << " O "; break;
			case 2: std::cout << " X "; break;
			case 3: std::cout << " # "; break;
			}
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	std::cout << std::endl;

}
void Board::DisplayBoards(std::vector<TreeNode<Board::BoardState*>*> TNs, bool side)
{
	for (size_t i = 0; i < TNs.size(); i++)
	{
		std::cout << "\n";
		Board::DisplayBoard(TNs[i]->val, side);
	}
}

void Board::RandomMove(Board::BoardState*& board, bool start) {

	std::vector<std::pair<int, int>> allMoves;
	board->GetPossibleMoves(allMoves, false);

	if (start)
	{
		int x = 0, y = 0;
		do
		{
			x = rand() % (board->getWidth() - 1);
			y = rand() % (board->getHeight() - 1);
			std::cout << x << "  " << y;
		} while (board->getPos(x, y) != 0);

		board->setX(x, y);
	}
	else
	{
		int move = rand() % allMoves.size();
		board->moveX(allMoves[move].first, allMoves[move].second);
	}
}

void Board::EvaluatedMove(Board::BoardState*& board, bool start, int depth, int allowedSearch) {

}