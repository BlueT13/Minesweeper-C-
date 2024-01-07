#include <iostream>
#include <string>

#include "GameManager.h"
using namespace std;

//메크로
//#define ROW 9 

namespace
{
int* GetInputCoordinateFromKeyboard()
{
	int inputCoordinate[2] = { 0, 0 };
	while (true)
	{
		cout << "선택할 칸을 입력하시오(1 1 ~ 9 9): ";
		string input;
		getline(cin, input);
		char delimiter = ' ';
		size_t pos = input.find(delimiter);
		try
		{
			if (pos == string::npos)
			{
				throw exception();
			}
			int num1 = stoi(input.substr(0, pos));
			int num2 = stoi(input.substr(pos + 1));
			if (num1 < 1 || num1 > 9 || num2 < 1 || num2 > 9)
			{
				throw exception();
			}
			inputCoordinate[0] = num1 - 1;
			inputCoordinate[1] = num2 - 1;
			break;
		}
		catch (exception e)
		{
			cout << "잘못된 입력입니다!" << endl;
		}
	}

	return inputCoordinate;
}
}

using namespace std;
int main()
{	
	const int ROW = 9;
	const int COL = 9;
	const int MINES_COUNT = 10;

	GameManager gameManager(ROW, COL, MINES_COUNT);
	gameManager.InitializeMinesweeperBoard();
	gameManager.InitializeBoardFlag();

	//GameBoard* hi = &gameBoard;
	//GameBoard& hello = gameBoard;
	//hi->PrintBoard();
	//(*hi).PrintBoard();
	//hello.PrintBoard();

	//vector<pair<int, int>> mines = MakeMines(ROW, COL, MINES_COUNT);
	//int** minesweeperBoard = MakeMinesweeperBoard(ROW, COL, mines);
	//for (int i = 0; i < MINES_COUNT; i++)
	//{
	//	delete[] mines[i];
	//}
	//delete[] mines;

	//for (int i = 0; i < ROW; i++)
	//{
	//	for (int j = 0; j < COL; j++)
	//	{
	//		board[i][j] = minesweeperBoard[i][j];
	//		boardFlag[i][j] = false;
	//	}
	//}

	while (true)
	{
		gameManager.PrintBoard();

		int* inputCoordinate = GetInputCoordinateFromKeyboard();

		const int x = inputCoordinate[0];
		const int y = inputCoordinate[1];

		gameManager.OpenCell(x, y);
		if (gameManager.CheckIsMine(x, y))
		{
			cout << "지뢰를 밟았습니다!\nGame Over!" << endl;
			break;
		}
		else
		{
			gameManager.TraversalZeroNode(x, y);
		}

		//boardFlag[x][y] = true;
		//if (board[x][y] != -1)
		//{
		//	TraversalZeroNode(x, y);
		//}
		//else
		//{
		//	cout << "지뢰를 밟았습니다!\nGame Over!" << endl;
		//	break;
		//}
	}

	//for (int i = 0; i < ROW; i++)
	//{
	//	delete[] minesweeperBoard[i];
	//}
	//delete[] minesweeperBoard;

	return 0;
}


//int** MakeMines(const int row, const int col, const int minesCount)
//{
//	int** mines = new int* [minesCount];
//	for (int i = 0; i < minesCount; i++)
//	{
//		mines[i] = new int[2];
//		mines[i][0] = rand() % col;
//		mines[i][1] = rand() % row;
//	}
//	return mines;
//}

//vector<pair<int, int>> MakeMines(const int row, const int col, const int minesCount)
//{
//	//vector<pair<int, int>> mines;			최대사이즈가 만개인가의 디폴트값으로 정해짐
//	//vector<pair<int, int>> mines(minesCount);			최대사이즈가 10개
//	vector<pair<int, int>> mines;
//	mines.reserve(minesCount);							//최대사이즈 10개
//
//	for (int i = 0; i < minesCount; i++)
//	{
//		const int randomColumn = rand() % col;
//		const int randomRow = rand() % row;
//
//		mines.push_back(make_pair(randomColumn, randomRow));
//	}
//	return mines;
//}


//void MakeMines2(int row, int col, int minesCount, int** mines)
//{
//	mines = new int* [minesCount];
//	for (int i = 0; i < minesCount; i++)
//	{
//		mines[i] = new int[2];
//		mines[i][0] = rand() % col;
//		mines[i][1] = rand() % row;
//	}
//}

//int** MakeMinesweeperBoard(int row, int col, int** mines)
//{
//	int** minesweeperBoard = new int* [row];
//	for (int i = 0; i < row; i++)
//	{
//		minesweeperBoard[i] = new int[col];
//		for (int j = 0; j < col; j++)
//		{
//			minesweeperBoard[i][j] = 0;
//		}
//	}
//
//	for (int i = 0; i < MINES_COUNT; i++)
//	{
//		int x = mines[i][0];
//		int y = mines[i][1];
//		minesweeperBoard[x][y] = -1;
//	}
//
//	for (int i = 0; i < row; i++)
//	{
//		for (int j = 0; j < col; j++)
//		{
//			if (minesweeperBoard[i][j] == -1)
//				continue;
//
//			int mineCount = 0;
//			for (int k = i - 1; k <= i + 1; k++)
//			{
//				for (int l = j - 1; l <= j + 1; l++)
//				{
//					if (k < 0 || k >= 9 || l < 0 || l >= 9)
//						continue;
//
//					if (k == i && l == j)
//						continue;
//
//					if (minesweeperBoard[k][l] == -1)
//						mineCount++;
//				}
//			}
//			minesweeperBoard[i][j] = mineCount;
//		}
//	}
//
//	return minesweeperBoard;
//}
