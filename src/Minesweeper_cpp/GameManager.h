#pragma once
#include <vector>

using namespace std;

class GameManager
{
public:
	GameManager(const int row, const int column, const int minesCount);

	void InitializeMinesweeperBoard();
	void InitializeBoardFlag();
	void PrintBoard();
	void OpenCell(const int x, const int y);
	bool CheckIsMine(int x, int y);
	void TraversalZeroNode(int x, int y);

		
private:
	vector<vector<int>> _board;
	vector<vector<bool>> _boardFlag;
	const int _row;
	const int _column;

	const int _minesCount;
};