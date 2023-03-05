#pragma once

#ifdef BOARDSTATE_EXPORTS
#define BOARDSTATE_API __declspec(dllexport)
#else
#define BOARDSTATE_API __declspec(dllimport)
#endif

#include "TreeNode.h"
#include <vector>

namespace Board
{
	BOARDSTATE_API class BoardState {
	private:
		int width;
		int height;
		int x_X = 0, x_Y = 0, o_X = 0, o_Y = 0;
		int** board;
	public:
		BOARDSTATE_API BoardState();
		BOARDSTATE_API virtual ~BoardState();
		BOARDSTATE_API BoardState(int, int);
		BOARDSTATE_API BoardState(int, int, int, int, int, int);
		BOARDSTATE_API BoardState(BoardState&, bool, int, int);

		BOARDSTATE_API void fill();
		BOARDSTATE_API void GetPossibleBoardStates(std::vector<TreeNode<BoardState*>*>&, bool);
		BOARDSTATE_API void GetPossibleMoves(std::vector<std::pair<int, int>>&, bool);
		BOARDSTATE_API int GetPossibleMoves(bool);

		BOARDSTATE_API int getWidth() const;
		BOARDSTATE_API int getHeight() const;

		BOARDSTATE_API void setO(int, int);
		BOARDSTATE_API void setX(int, int);
		BOARDSTATE_API void moveO(int, int);
		BOARDSTATE_API void moveX(int, int);

		BOARDSTATE_API int getPos(int, int) const;
		BOARDSTATE_API void setPos(int, int, int);
	};

	BOARDSTATE_API void DisplayBoards(std::vector<TreeNode<BoardState*>*>, bool);
	BOARDSTATE_API void DisplayBoard(BoardState*, bool, int);
	BOARDSTATE_API void DisplayBoard(BoardState*, bool);
	BOARDSTATE_API void DisplayBoard(BoardState*);
	BOARDSTATE_API void DisplayBoard(BoardState*, int, int);
	BOARDSTATE_API void RandomMove(BoardState*&, bool);
	BOARDSTATE_API void EvaluatedMove(BoardState*&, bool, int, int);
}


