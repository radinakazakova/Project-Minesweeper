/**
*
* Solution to course project # 5
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2023/2024
*
* @author Radina Kazakova
* @idnumber 0MI0600282
* @compiler VC
*
* <game file>
*
*/
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

char** createMatrix(const int rows, const int colls, const char initialValue) //Allocate memory for a dynamic matrix
{
	char** matrix = new char* [rows];

	for (int i = 0; i < rows; ++i)
	{
		matrix[i] = new char[colls];

		for (int j = 0; j < colls; ++j)
		{
			matrix[i][j] = initialValue;
		}
	}
	return matrix;
}

void deleteMatrix(char** matrix, const int rows) //Release allocated memory for the matrix
{
	for (int i = 0; i < rows; ++i)
	{
		delete[] matrix[i];
	}
	delete[] matrix;
}

void handleIncorrectInput() //Clear the input buffer after an incorrect input
{
	cin.clear();

	while (cin.get() != '\n')
	{
		continue;
	}
}

void printBoard(char** board, const int n) //Print the board
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

bool gameLost(char** hiddenBoard, char** userBoard, const int dimention) //Check if game is lost - if a mine is opened
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

bool areAllTilesOpen(char** userBoard, const int dimention) //Check if all tiles are open except the mines
{
	for (int i = 0; i < dimention; i++)
	{
		for (int j = 0; j < dimention; j++)
		{
			if (userBoard[i][j] == '#')
			{
				return false;
			}
		}
	}
	return true;
}

bool gameWon(char** hiddenBoard, char** userBoard, const int mineCount, const int dimention) //Check if game is won - if all the tiles are opened, and all mines are marked
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

	return ((count == mineCount) && areAllTilesOpen(userBoard, dimention));
}

bool areCoordinatesValid(const int x, const int y, const int dimention)
{
	return (x >= 0 && x < dimention && y >= 0 && y < dimention);
}

bool isActionValid(const char action)
{
	return (action == 'o' || action == 'm' || action == 'u');
}

void incrementNeighbors(char** hiddenBoard, const int dimention, const int row, const int coll) //Increase the value of the tiles neighboring a mine
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

void placeMines(char** hiddenBoard, const int dimention, int& mineCount) //Randomly place the mines in the board hidden from the player
{
	cout << "Choose how many mines you want to be hidden between 1 and " << 3 * dimention << ": ";

	while (!(cin >> mineCount) || (mineCount < 1) || (mineCount > 3 * dimention))
	{
		cout << "Wrong input for the number of mines. Please try again." << endl;
		handleIncorrectInput();
	}

	srand(time(NULL));

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
}

void showTile(char** hiddenBoard, char** userBoard, int x, int y, const int dimention) //Open the chosen tile, if it has a value of 0 - open the neighboring ones except the mines
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

void unmarkTile(char** hiddenBoard, char** userBoard, const int dimention, const int x, const int y) //
{

	if (userBoard[x][y] == '*')
	{
		userBoard[x][y] = '#';
	}
	else
	{
		cout << "Invalid action. Please try again." << endl;
	}
}

void markTile(char** hiddenBoard, char** userBoard, const int dimention, const int x, const int y)
{

	if (userBoard[x][y] == '#')
	{
		userBoard[x][y] = '*';
	}
	else
	{
		cout << "Invalid action. Please try again." << '\n' << endl;
	}
}

void casesForOpenTile(char** userBoard, char** hiddenBoard, const int x, const int y, const int dimention) //Check if the tile is already open, or if it is marked
{
	if (userBoard[x][y] >= '0' && userBoard[x][y] <= '8')
	{
		cout << "Tile is already opened. Try again" << '\n' << endl;
	}
	else if (userBoard[x][y] == '*')
	{
		cout << "Tile is marked. Try again" << '\n' << endl;
	}
}

void doAction(char** hiddenBoard, char** userBoard, const int dimention, const char action, const int x, const int y)
{
	switch (action)
	{
	case 'o':
		casesForOpenTile(userBoard, hiddenBoard, x, y, dimention);
		showTile(hiddenBoard, userBoard, x, y, dimention);
		break;
	case 'm':
		markTile(hiddenBoard, userBoard, dimention, x, y);
		break;
	case 'u':
		unmarkTile(hiddenBoard, userBoard, dimention, x, y);
		break;
	default:
		break;
	}
}

void inputCommands(char** hiddenBoard, char** userBoard, const int dimention)
{
	char action;
	int coordinate_x;
	int coordinate_y;

	cout << "Select an action (o) to open a tile, (m) to mark a tile, (u) to unmark a tile" << endl;
	cout << "Then select coordinates (row), followed by (colomn):" << endl;

	while (!(cin >> action >> coordinate_x >> coordinate_y) || !isActionValid(action) || !areCoordinatesValid(coordinate_x, coordinate_y, dimention))
	{
		cout << "Invalid input! Please enter again." << endl;

		handleIncorrectInput();
	}

	doAction(hiddenBoard, userBoard, dimention, action, coordinate_x, coordinate_y);
}

void playGame(const int dimention) //Start the game - create 2 boards, place the mines, play until the game is won or lost
{
	char** userBoard = createMatrix(dimention, dimention, '#');
	char** hiddenBoard = createMatrix(dimention, dimention, '0');

	int mineCount = 0;
	placeMines(hiddenBoard, dimention, mineCount);

	bool isWon = false;
	bool isLost = false;

	while (!isWon || !isLost)
	{
		cout << "Current state of the board:" << "\n";
		printBoard(userBoard, dimention);
		inputCommands(hiddenBoard, userBoard, dimention);

		isWon = gameWon(hiddenBoard, userBoard, mineCount, dimention);
		isLost = gameLost(hiddenBoard, userBoard, dimention);

		if (isWon == true)
		{
			cout << "Congratulations! You won!" << endl;
			printBoard(hiddenBoard, dimention);
			return;
		}
		else if (isLost == true)
		{
			cout << "GAME OVER! You opened a mine." << endl;
			printBoard(hiddenBoard, dimention);
			return;
		}
	}

	deleteMatrix(userBoard, dimention);
	deleteMatrix(hiddenBoard, dimention);
}

int main()
{
	cout << "Welcome to Minesweeper!" << std::endl;

	int dimention;
	cout << "Before we start, please select a dimention for the board between 3 and 10: ";

	while (!(cin >> dimention) || dimention < 3 || dimention > 10)
	{
		cout << "Wrong dimention input. Please try again." << endl;
		handleIncorrectInput();
	}

	playGame(dimention);

	return 0;
}
