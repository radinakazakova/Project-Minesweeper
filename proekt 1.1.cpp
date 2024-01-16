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

bool gameLost(vector<vector<char>>& userBoard, int x, int y,const int& dimention)
{
	/*userBoard[x][y] = 'M';

	printUserBoard(userBoard, dimention);
	cout << "You opened a mine. GAME OVER!" << endl;

	return false;*/
}

void gameWon()
{

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
			if (i >= 0 && i < dimention && j >= 0 && j < dimention && (i != row || j != coll) && hiddenBoard[i][j] != 'M')//otdelna funkcioq za validirane na koordinati
			{
				int value = hiddenBoard[i][j] - '0';
				value++;
				hiddenBoard[i][j] = value + '0';
			}
		}
	}
}

void placeMines(vector<vector<char>>& hiddenBoard, const int& dimention)
{
	int mineCount;
	std::cout << "Choose how many mines you want to be hidden between 1 and " << 3 * dimention << ": ";
	std::cin >> mineCount;
	//validaciq za inputa

	srand(time(0));

	while (mineCount > 0)
	{
		// Generate a random index between 0 and 24
		int randomIndex = rand() % (dimention * dimention);

		// Convert the index to row and column indixes
		int rowIndex = randomIndex / dimention;
		int collIndex = randomIndex % dimention;

		// Check if the element at that index is '0'
		if (hiddenBoard[rowIndex][collIndex] == '0')
		{
			// Replace it with 'M' and decrement the count
			hiddenBoard[rowIndex][collIndex] = 'M';
			mineCount--;

			incrementNeighbors(hiddenBoard, dimention, rowIndex, collIndex);
		}
	}
}

void showTile(const vector<vector<char>>& hiddenBoard, vector<vector<char>>& userBoard, int x, int y, int dimention)
{
	if (hiddenBoard[x][y] != 'M' && userBoard[x][y] == '#' && areCoordinatesValid(x, y, dimention))
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
						showTile(hiddenBoard, userBoard, i, y, dimention);
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
		cout << "Invalid coordinates. Please try again";
		inputAction(hiddenBoard, userBoard, dimention);
	}

	if (hiddenBoard[row][coll] == 'M')
	{
		gameLost(userBoard, row, coll, dimention); //to do: game over game won
	}
	else
	{
		showTile(hiddenBoard, userBoard, row, coll, dimention);
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
		//markTile();
	}
	else if (action == 'u')
	{
		//unmarkTile();
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

	placeMines(hiddenBoard, dimention);

	int n = 6;

	while (n) //to do : until won or lost
	{
		printUserBoard(userBoard, dimention);

		inputAction(hiddenBoard, userBoard, dimention);

		n--;
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
}