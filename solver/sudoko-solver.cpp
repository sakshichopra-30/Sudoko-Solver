#include <iostream>
#include <fstream>

using namespace std;

class SudokoGrid
{
	int sudoko[9][9];
	int editable[9][9];

public:
	SudokoGrid()
	{
		menu();
	}

private:
	void menu()
	{

		cout << "\n---------------------------\n";
		cout << "			Sudoko Solver          ";
		cout << "\n----------------------------\n";

		cout << "Before we start, please provide an Input\n\n";
		cout << "Either, \n";
		cout << "\t1. Input the puzzle by entering the values manually. (Enter 1)\n";
		cout << "\t2. Input the puzzle by reading a file with values in it. (Enter 2)\n";
		cout << "\t The file must not have a name more than 20 characters.\n";
		cout << "\t The file must be in the same directory as this C++ file. \n";
		cout << "\t The files must have all 81 values seperated with spaces\n";
		cout << "\t Blank cells must be filled in as 0 (eg: 1 0 0 2 0 0..). \n";

		int opt;
		cin >> opt;

		if (opt == 1)
		{
			readValue();
		}
		else if (opt == 2)
		{
			readValueFile();
		}
		else
		{
			while (true)
			{
				cout << "\n you may have entered an invalid option. Try again/. \n";
				cout << "\t";

				cin >> opt;
				if (opt == 1)
				{
					readValue();
				}
				else if (opt == 2)
				{
					readValueFile();
				}
				else
				{
					continue;
				}
				break;
			}
		}
	}

	void readValue()
	{
		cout << "\n Enter the specified value when prompted. \n";
		cout << "Enter 0 if cell is empty.\n\n";

		int rowI, colI;

		for (rowI = 0; rowI < 9; rowI++)
		{

			for (colI = 0; colI < 9; colI++)
			{

				int enteredValue;

				cout << "Enter value for cell[" << rowI + 1 << "][" << colI + 1 << "]";
				cin >> enteredValue;

				if (!(enteredValue >= 1 && enteredValue <= 9))
				{
					while (true)
					{
						cout << "You have entered the wrong value. Try again. \n";
						cout << "Enter value for cell [" << rowI + 1 << "][" << colI + 1 << "] ";
						cin >> enteredValue;
					}

					if (enteredValue >= 1 && enteredValue <= 9)
					{
						break;
					}
				}

				sudoko[rowI][colI] = enteredValue;

				if (enteredValue == 0)
				{
					editable[rowI][colI] = 0;
				}
				else
				{
					editable[rowI][colI] = 1;
				}
			}

			cout << "---------\n";
		}
	}

	void readValueFile()
	{
		char filename[30];

		cout << "Enter the name of the file that contains the Sudoko puzzle. \n";
		cin >> filename;

		ifstream sudokoFile;
		sudokoFile.open(filename, ios::in);

		int rowI, colI;

		for (rowI = 0; rowI < 9; rowI++)
		{

			for (colI = 0; colI < 9; colI++)
			{

				int readValue;
				sudokoFile >> readValue;

				if (!(readValue >= 0 && readValue <= 9))
				{
					cout << "\n Value " << ((rowI * 9) + colI + 1) << " in " << filename;
					cout << "seems to be wrong. Correct the value and try again.";
					exit(0);
				}

				sudoko[rowI][colI] = readValue;

				if (sudoko[rowI][colI] == 0)
				{
					editable[rowI][colI] = 0;
				}
				else
				{
					editable[rowI][colI] = 1;
				}

				if (sudokoFile.eof())
				{
					break;
				}
			}
		}

		sudokoFile.close();
	}

public:
	void setValue(int r, int c, int num)
	{
		if (editable[r][c] == 0)
		{
			editable[r][c] = num;
		}
	}

	int getValue(int r, int c)
	{
		return sudoko[r][c];
	}

	int isEditable(int r, int c)
	{
		return (editable[r][c] - 1) * (-1);
	}

	void clearGridFrom(int r, int c)
	{

		int jc = 0;
		int rowI, colI;

		for (rowI = r; rowI < 9; rowI++)
		{
			if (jc == 0)
			{
				colI = c;
			}
			else
			{
				colI = 0;
			}
			for (; colI < 9; colI++)
			{
				if (editable[rowI][colI] == 0)
				{
					sudoko[rowI][colI] = 0;
				}
			}
			jc++;
		}
	}

	void displayGrid()
	{

		cout << "\033[0;36m=======================================";

		int rowI, colI;
		for (rowI = 0; rowI < 9; rowI++)
		{
			int cellI = 1;
			cout << "\n\033[0;36m||";
			for (colI = 0; colI < 9; colI++)
			{
				if (cellI == 3)
				{
					cout << "\033[0m " << sudoko[rowI][colI] << " ";
					cout << "\033[0;36m||";
					cellI = 1;
				}
				else
				{
					cout << "\033[0m " << sudoko[rowI][colI] << " ";
					cellI++;
				}
			}

			if (rowI % 3 != 2)
			{
				cout << "\n\033[0;36m===========================================";
			}
			else
			{
				cout << "\n\033[0;36m===========================================";
			}
		}
	}
};

class Possibilities
{
	struct Node
	{
		int data;
		struct Node *next;
	};

	typedef struct Node *node;

	node head;
	node curr;

public:
	Possibilities()
	{
		head = new struct Node;
		head->next = NULL;
	}

	~Possibilities()
	{
		destroy();
	}

	void append(int num)
	{
		node temp = new struct Node;

		temp->data = num;
		temp->next = NULL;

		curr = head;

		while (curr != NULL)
		{
			if (curr->next == NULL)
			{
				curr->next = temp;
				break;
			}
			curr = curr->next;
		}
	}

	int operator[](int index)
	{
		int count = 0;
		curr = head->next;

		while (curr != NULL)
		{
			if (count == index)
			{
				return curr->data;
			}

			curr = curr->next;
			count++;
		}

		return -1;
	}

	void print()
	{
		curr = head->next;
		while (curr != NULL)
		{
			cout << curr->data << ",";
			curr = curr->next;
		}

		cout << "\b";
	}

	int length()
	{
		curr = head->next;
		int count = 0;
		while (curr != NULL)
		{
			count++;
			curr = curr->next;
		}

		return count;
	}

	void copy(Possibilities poss)
	{
		int oldlen = poss.length();
		int it = 0;
		curr = head;

		for (it = 0; it < oldlen; it++)
		{
			node temp = new struct Node;
			temp->next = NULL;
			temp->data = poss[it];
			curr->next = temp;
			curr = curr->next;
		}
	}

private:
	void destroy()
	{
		node temp;
		curr = head;
		while (curr != NULL)
		{
			temp = curr;
			curr = curr->next;
			delete temp;
		}
	}
};

class SudokoSolver
{

	int recCount = 0;
	SudokoGrid grid;

public:
	SudokoSolver()
	{
		recCount = 0;

		cout << "\n Calculating possibilities..\n";
		cout << "\n Backtracking across puzzles..\n";
		cout << "\n Validating cells and values..\n";

		solve();
		cout << "Your puzzle has been solved\n";
		displayGrid();
		cout << "\n\n";
	}

private:
	bool cellValValid(int r, int c, int val)
	{
		int rowI, colI;

		for (rowI = 0; rowI < 9; rowI++)
		{
			if (rowI != r)
			{
				int compareValue = grid.getValue(rowI, c);
				if (compareValue == val)
				{
					return false;
				}
			}
		}

		for (colI = 0; colI < 9; colI++)
		{
			if (colI != c)
			{
				int compareValue = grid.getValue(r, colI);
				if (compareValue == val)
				{
					return false;
				}
			}
		}

		if (ThreeByThreeVal(r, c, val) == false)
		{
			return false;
		}

		return true;
	}

	bool ThreeByThreeVal(int r, int c, int val)
	{

		int rowS = (r / 3) * 3;
		int rowE = rowS + 2;

		int colS = (c / 3) * 3;
		int colE = colS + 2;

		int rowI, colI;

		for (rowI = rowS; rowI < rowE; rowI++)
		{
			for (colI = colS; colI < colE; colI++)
			{
				if (grid.getValue(rowI, colI) == val)
				{
					return false;
				}
			}
		}

		return true;
	}

	Possibilities getCellPossibilities(int r, int c)
	{
		int it = 0;

		Possibilities poss;

		for (it = 1; it <= 9; it++)
		{
			if (cellValValid(r, c, it) == true)
			{
				poss.append(it);
			}
		}

		return poss;
	}

	int singleCellSolve(int r, int c)
	{
		statsIncrement();

		if (grid.isEditable(r, c) == true)
		{
			Possibilities poss;
			poss.copy(getCellPossibilities(r, c));

			int posLen = poss.length();
			int posI = 0, newRow = r, newCol = c;
			for (posI = 0; posI < posLen; posI++)
			{
				int possibility = poss[posI];
				grid.setValue(r, c, possibility);

				if (c < 8)
				{
					newCol = c + 1;
				}
				else if (c == 8)
				{
					if (r == 8)
					{
						return 1;
					}

					newRow = r + 1;
					newCol = 0;
				}
				{
					if (singleCellSolve(newRow, newCol) == 0)
					{
						grid.clearGridFrom(newRow, newCol);
					}
					else
					{
						return 1;
					}
				}
			}

			return 0;
		}

		else
		{
			int newRow = r, newCol = c;

			if (c < 8)
			{
				newCol = c + 1;
			}
			else if (c == 8)
			{
				if (r == 8)
				{
					return 1;
				}
				newRow = r + 1;
				newCol = 0;
			}

			return singleCellSolve(newRow, newCol);
		}
	}

	void solve()
	{
		int success = singleCellSolve(0, 0);
	}

	void displayGrid()
	{
		grid.displayGrid();
	}

	void statsIncrement()
	{
		recCount++;
	}

	void statsPrint()
	{
		cout << "\n The singleCellSolve() function was recursively called " << recCount << "times. \n";
	}
};

int main()
{

	SudokoSolver SS;
	return 0;
}
