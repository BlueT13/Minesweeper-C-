#include <iostream>

#include "gameManager.h"

namespace
{
	const int MINE_VALUE = -1;
}

GameManager::GameManager(const int row, const int column, const int minesCount)
	: _row(row), _column(column), _minesCount(minesCount)
{
	vector<vector<int>> board(row, vector<int>(column));
	_board = board;

	vector<vector<bool>> boardFlag(row, vector<bool>(column));
	_boardFlag = boardFlag;
}

void GameManager::InitializeMinesweeperBoard()
{
	srand(time(NULL));

	//Make Mines Randomly
	vector<pair<int, int>> mines;
	mines.reserve(_minesCount);

	for (int i = 0; i < _minesCount; i++)
	{
		const int randomColumn = rand() % _column;
		const int randomRow = rand() % _row;

		mines.push_back(make_pair(randomColumn, randomRow));
	}

	//Insert Mines On Board
	for (int i = 0; i < _row; i++)
	{
		for (int j = 0; j < _column; j++)
		{
			_board[i][j] = 0;
		}
	}

	for (int i = 0; i < _minesCount; i++)
	{
		int x = mines[i].first;
		int y = mines[i].second;
		_board[x][y] = MINE_VALUE;
	}

	for (int i = 0; i < _row; i++)
	{
		for (int j = 0; j < _column; j++)
		{
			if (_board[i][j] == MINE_VALUE)
				continue;

			int mineCount = 0;
			for (int k = i - 1; k <= i + 1; k++)
			{
				for (int l = j - 1; l <= j + 1; l++)
				{
					if (k < 0 || k >= 9 || l < 0 || l >= 9)
						continue;

					if (k == i && l == j)
						continue;

					if (_board[k][l] == MINE_VALUE)
						mineCount++;
				}
			}
			_board[i][j] = mineCount;
		}
	}

}

void GameManager::InitializeBoardFlag()
{
	for (int i = 0; i < _row; i++)
	{
		for (int j = 0; j < _column; j++)
		{
			_boardFlag[i][j] = false;
		}
	}
}

void GameManager::PrintBoard()
{
	for (int i = 0; i < _row; i++)
	{
		for (int j = 0; j < _column; j++)
		{
			if (_boardFlag[i][j] == true)
			{
				cout << " " << _board[i][j] << " ";
			}
			else
			{
				cout << " * ";
			}
		}
		cout << endl;
	}
}

void GameManager::OpenCell(const int x, const int y)
{
	_boardFlag[x][y] = true;
}

bool GameManager::CheckIsMine(const int x, const int y)
{
	return _board[x][y] == MINE_VALUE;
}

void GameManager::TraversalZeroNode(int x, int y)
{
	_boardFlag[x][y] = true;

	if (_board[x][y] == 0)
	{
		for (int k = x - 1; k <= x + 1; k++)
		{
			for (int l = y - 1; l <= y + 1; l++)
			{
				if (k < 0 || k >= 9 || l < 0 || l >= 9)
					continue;

				if (k == x && l == y)
					continue;

				if (!_boardFlag[k][l])
				{
					TraversalZeroNode(k, l);
				}
			}
		}
	}
	else
	{
		return;
	}
}
