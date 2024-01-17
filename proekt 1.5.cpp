#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>

using namespace std;

void printUserBoard(const vector<vector<char>>& board, int n)
{
	std::cout << "   ";
	for (int i = 0; i < n; i++)
	{
		std::cout << " " << i << " ";
	}
	std::cout << "\n";

	std::cout << "   ";
	for (int i = 0; i < n; i++)
	{
		std::cout << " " << "-" << " ";
	}
	std::cout << "\n";

	for (int i = 0; i < n; i++)
	{
		std::cout << " " << i << " ";

		for (int j = 0; j < n; j++)
		{
			std::cout << "|" << board[i][j] << "|";
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}

bool gameLost(const vector<vector<char>>& hiddenBoard, vector<vector<char>>& userBoard, const int& dimention)
{
	for (int i = 0; i < dimention; i++)
	{
		for (int j = 0; j < dimention; j++)
		{
			if (userBoard[i][j] == 'M')
			{
				return true;
			}
		}
	}
	return false;
}

bool gameWon(const vector<vector<char>>& hiddenBoard, const vector<vector<char>>& userBoard, const int& mineCount, const int& dimention)
{
	int count = 0;

	for (int i = 0; i < dimention; i++)
	{
		for (int j = 0; j < dimention; j++)
		{
			if (hiddenBoard[i][j] == 'M')
			{
				if (userBoard[i][j] == '*')
				{
					count++;
				}
			}
		}
	}

	return (count == mineCount);
}

bool areCoordinatesValid(int x, int y, int dimention)
{
	return (x >= 0 && x < dimention && y >= 0 && y < dimention);
}

void incrementNeighbors(vector<vector<char>>& hiddenBoard, int dimention, int row, int coll)
{
	for (int i = row - 1; i <= row + 1; i++)
	{
		for (int j = coll - 1; j <= coll + 1; j++)
		{
			if (areCoordinatesValid(i, j, dimention) && (i != row || j != coll) && hiddenBoard[i][j] != 'M')
			{
				int value = hiddenBoard[i][j] - '0';
				value++;
				hiddenBoard[i][j] = value + '0';
			}
		}
	}
}

void placeMines(vector<vector<char>>& hiddenBoard, const int& dimention, int& mineCount)
{
	std::cout << "Choose how many mines you want to be hidden between 1 and " << 3 * dimention << ": ";
	std::cin >> mineCount;
	//validaciq za inputa

	srand(time(0));

	int count = mineCount;

	while (count > 0)
	{
		int rowIndex = rand() % dimention;
		int collIndex = rand() % dimention;

		if (hiddenBoard[rowIndex][collIndex] != 'M')
		{
			hiddenBoard[rowIndex][collIndex] = 'M';
			count--;

			incrementNeighbors(hiddenBoard, dimention, rowIndex, collIndex);
		}
	}

	printUserBoard(hiddenBoard, dimention);
}

void showTile(const vector<vector<char>>& hiddenBoard, vector<vector<char>>& userBoard, int x, int y, int dimention)
{
	if (areCoordinatesValid(x, y, dimention) && userBoard[x][y] == '#')
	{
		userBoard[x][y] = hiddenBoard[x][y];

		if (hiddenBoard[x][y] == '0')
		{
			for (int i = x - 1; i <= x + 1; i++)
			{
				for (int j = y - 1; j <= y + 1; j++)
				{
					if (i != x || j != y)
					{
						showTile(hiddenBoard, userBoard, i, j, dimention);
					}
				}
			}
		}
	}
}

void inputAction(const vector<vector<char>>& hiddenBoard, vector<vector<char>>& userBoard, const int& dimention);

void openTile(const vector<vector<char>>& hiddenBoard, vector<vector<char>>& userBoard, const int& dimention)
{
	int row;
	int coll;

	cin >> row >> coll;

	if (!areCoordinatesValid(row, coll, dimention))
	{
		cout << "Invalid coordinates. Please try again" << endl;
		inputAction(hiddenBoard, userBoard, dimention);
	}

	showTile(hiddenBoard, userBoard, row, coll, dimention);
}

void unmarkTile(const vector<vector<char>>& hiddenBoard, vector<vector<char>>& userBoard, const int& dimention) //da izmislq kak eventualno da kombiniram dwete funk
{
	int row;
	int coll;
	cin >> row>> coll;

	if (userBoard[row][coll] == '*')
	{
		userBoard[row][coll] = '#';
	}
	else
	{
		cout << "Invalid action. Please try again." << endl;
		inputAction(hiddenBoard, userBoard, dimention);
	}
}

void markTile(const vector<vector<char>>& hiddenBoard, vector<vector<char>>& userBoard, const int& dimention)
{
	int row;
	int coll;
	cin >> row >> coll;

	if (userBoard[row][coll] == '#' )
	{
		userBoard[row][coll] = '*';
	}
	else
	{
		cout << "Invalid action. Please try again." << endl;
		inputAction(hiddenBoard, userBoard, dimention);
	}
}

void inputAction(const vector<vector<char>>& hiddenBoard, vector<vector<char>>& userBoard, const int& dimention)
{
	char action;

	cout << "Select an action (o) for open tile, (m) for mark a tile, (u) for unmark a tile" << endl;
	cout << "Then select coordinates (row, colomn):" << endl;

	cin >> action;

	if (action == 'o')
	{
		openTile(hiddenBoard, userBoard, dimention);
	}
	else if (action == 'm')
	{
		markTile(hiddenBoard, userBoard, dimention);
	}
	else if (action == 'u')
	{
		unmarkTile(hiddenBoard, userBoard, dimention);
	}
	else
	{
		cout << "Invalid action. Please try again";
		inputAction(hiddenBoard, userBoard, dimention);
	}
}

void playGame(const int dimention)
{
	vector<vector<char>> userBoard(dimention, vector<char>(dimention, '#'));
	vector<vector<char>> hiddenBoard(dimention, vector<char>(dimention, '0'));

	int mineCount = 0;
	placeMines(hiddenBoard, dimention, mineCount);

	bool isWon = false;
	bool isLost = false;


	while (!isWon || !isLost)
	{
		printUserBoard(userBoard, dimention);

		inputAction(hiddenBoard, userBoard, dimention);

		isWon = gameWon(hiddenBoard, userBoard, mineCount, dimention);
		isLost = gameLost(hiddenBoard, userBoard, dimention);

		if (isWon == true)
		{
			cout << "Congratulations! You won!";
			return;
		}
		else if (isLost == true)
		{
			cout << "GAME OVER! You opened a mine.";
			return;
		}
	}
}

int main()
{
	std::cout << "Welcome to Minesweeper!" << std::endl;

	int dimention;
	std::cout << "Before we start, please select a dimention for the board between 3 and 10: ";
	std::cin >> dimention;
	//To do: validation for the unput

	playGame(dimention);

	return 0;
}