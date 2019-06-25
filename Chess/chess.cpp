#include <iostream>
#include <string>

using namespace std;


string whitePlayer;
string blackPlayer;

char table[8][8];

char turnHolder();

const char whiteFigurs[] = { 'R','H','O','K','Q','i' };
const char blackFigurs[] = { 'r','h','o','k','q','!' };

int turn;

int tableX1, tableY1; //From
int tableX2, tableY2; //To

int charInputToCoord(char);
int intInputToCoord(char);

int max(int, int);
int min(int, int);

void blankTable();
void drawTable();
void placeFigurs();
void registerPlayers();

bool checkFigure(char, int, int);
bool checkMate();
//figures
bool isValidWhitePawn();
bool isValidBlackPawn();
bool isValidWhiteKing();
bool isValidBlackKing();
bool isValidWhiteRock();
bool isValidBlackRock();
bool isValidWhiteOfficer();
bool isValidBlackOfficer();
bool isValidWhiteQueen();
bool isValidBlackQueen();
bool isValidWhiteHorse();
bool isValidBlackHorse();

int main()
{
	registerPlayers();

	blankTable();
	placeFigurs();
	drawTable();

	char charFrom, charTo;
	char intFrom, intTo;

	while (true)
	{
		if (turnHolder() == 'w')
		{
			//white
			cout << whitePlayer << " type coords: ";
		}
		else if (turnHolder() == 'b')
		{
			//black
			cout << blackPlayer << " type coords: ";
		}

		bool isRight = false;
		while (isRight == false) // 
		{
			cin >> charFrom >> intFrom;

			if (charFrom < 'A' || charFrom > 'H' || intFrom < '1' || intFrom > '8')
			{
				cout << "\nOut of the table! Try again: ";
				continue;
			}

			tableX1 = intInputToCoord(intFrom);
			tableY1 = charInputToCoord(charFrom);

			for (int i = 0; i < 6; i++)
			{
				if (turnHolder() == 'w' && table[tableX1][tableY1] == whiteFigurs[i]
					|| turnHolder() == 'b' && table[tableX1][tableY1] == blackFigurs[i])
				{
					isRight = true;
					break;
				}
			}
			if (!isRight)
			{
				cout << "\nNot your figure! Try again: ";
			}
		}

		bool reset = false;

		if (turnHolder() == 'w')
		{
			cout << "\n" << whitePlayer << " type second coords: ";
		}
		else if (turnHolder() == 'b')
		{
			cout << "\n" << blackPlayer << " type second coords: ";
		}

		isRight = false;
		while (isRight == false) // 
		{
			cin >> charTo >> intTo;

			if (charTo < 'A' || charTo > 'H' || intTo < '1' || intTo > '8')
			{
				cout << "\nOut of the table! Try again: ";
				continue;
			}
			else if (charFrom == charTo && intFrom == intTo)
			{
				reset = true;
				break;
			}

			tableX2 = intInputToCoord(intTo);
			tableY2 = charInputToCoord(charTo);

			bool respawn = false;

			switch (table[tableX1][tableY1])
			{
			case 'i':
				isRight = isValidWhitePawn();
				respawn = true;

				break;
			case '!':
				isRight = isValidBlackPawn();
				respawn = true;

				break;
			case 'K':
				isRight = isValidWhiteKing();
				break;
			case 'k':
				isRight = isValidBlackKing();
				break;
			case 'R':
				isRight = isValidWhiteRock();
				break;
			case 'r':
				isRight = isValidBlackRock();
				break;
			case 'O':
				isRight = isValidWhiteOfficer();
				break;
			case 'o':
				isRight = isValidBlackOfficer();
				break;
			case 'Q':
				isRight = isValidWhiteQueen();
				break;
			case 'q':
				isRight = isValidBlackQueen();
				break;
			case 'H':
				isRight = isValidWhiteHorse();
				break;
			case 'h':
				isRight = isValidBlackHorse();
				break;
			}

			if (!isRight)
			{
				cout << "\nYou cannot go there! Try again: ";
			}
		}

		if (checkMate())
		{
			table[tableX2][tableY2] = table[tableX1][tableY1];
			table[tableX1][tableY1] = ' ';
			drawTable();
			break;
		}

		if (isRight && tableX2 == 7) //respawn figure
		{
			table[tableX2][tableY2] = 'Q';
			table[tableX1][tableY1] = ' ';

			drawTable();
			reset = true;
			turn++;
			continue;
		}
		else if (isRight && tableX2 == 0) //respawn figure
		{
			table[tableX2][tableY2] = 'q';
			table[tableX1][tableY1] = ' ';

			drawTable();
			reset = true;
			turn++;
			continue;
		}

		table[tableX2][tableY2] = table[tableX1][tableY1];
		table[tableX1][tableY1] = ' ';


		drawTable();

		turn++;
	}


	if (turnHolder() == 'w')
	{
		cout << whitePlayer << " won the game!";
	}
	else
	{
		cout << whitePlayer << " won the game!";
	}

	system("pause>null");
	return 0;
}


char turnHolder() // w or b 
{
	if (turn % 2 == 0)
	{
		return 'w';
	}
	else
	{
		return 'b';
	}
}

int min(int first, int second)
{
	if (first < second)
	{
		return first;
	}
	return second;
}

int max(int first, int second)
{
	if (first > second)
	{
		return first;
	}
	return second;
}

int charInputToCoord(char current)
{
	return current - 'A';
}
int intInputToCoord(char current)
{
	return current - '1';
}

void registerPlayers()
{
	string player1, player2;

	cout << "Type name for player1(white): ";
	cin >> player1;

	cout << "\nType name for player2(black): ";
	cin >> player2;

	whitePlayer = player1;
	blackPlayer = player2;
}

void drawTable()
{
	cout << endl;
	for (int i = 0; i < 8; i++)
	{
		cout << "| ";
		for (int j = 0; j < 8; j++)
		{
			cout << table[7 - i][j] << " | ";
		}
		cout << " " << 8 - i << endl;
		cout << "|---+---+---+---+---+---+---+---|" << endl;
	}
	cout << "\n  A - B - C - D - E - F - G - H" << endl;

}

void blankTable()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			table[i][j] = ' ';
		}
	}
}

void placeFigurs()
{
	//white
	table[0][0] = 'R';
	table[0][1] = 'H';
	table[0][2] = 'O';
	table[0][3] = 'Q';
	table[0][4] = 'K';
	table[0][5] = 'O';
	table[0][6] = 'H';
	table[0][7] = 'R';

	//black
	table[7][0] = 'r';
	table[7][1] = 'h';
	table[7][2] = 'o';
	table[7][3] = 'q';
	table[7][4] = 'k';
	table[7][5] = 'o';
	table[7][6] = 'h';
	table[7][7] = 'r';

	//white & black peshki
	for (int i = 0; i < 8; i++)
	{
		table[1][i] = 'i';
		table[6][i] = '!';
	}
}

bool checkFigure(char side, int x, int y)
{
	char requestedChar = table[x][y];

	for (int i = 0; i < 6; i++)
	{
		if (side == 'w' && whiteFigurs[i] == requestedChar
			|| side == 'b' && blackFigurs[i] == requestedChar)
		{
			return true;
		}
	}

	return false;
}

bool checkMate()
{
	if (table[tableX2][tableY2] == 'K' && turnHolder() == 'b'
		|| table[tableX2][tableY2] == 'k' && turnHolder() == 'w' )
	{
		return true;
	}
	return false;
}

//**Figures**//
bool isValidWhitePawn()
{
	bool isValid = false;
	if (tableX1 == 1 && tableX1 + 2 == tableX2 && tableY1 == tableY2 && table[tableX1 + 1][tableY1] == ' ' && table[tableX1 + 2][tableY1] == ' ') //Double start
	{
		isValid = true;
	}
	else if (tableX1 + 1 == tableX2 && tableY1 == tableY2 && table[tableX2][tableY2] == ' ') //1 step in line
	{
		isValid = true;
	}
	else if (tableX1 + 1 == tableX2 && tableY1 + 1 == tableY2 && checkFigure('b', tableX2, tableY2)) //taking right figure
	{
		isValid = true;
	}
	else if (tableX1 + 1 == tableX2 && tableY1 - 1 == tableY2 && checkFigure('b', tableX2, tableY2)) //taking left figure
	{
		isValid = true;
	}
	else if (tableX1 + 1 == tableX2 && tableY1 - 1 == tableY2 && checkFigure('b', tableX2, tableY2)) //taking left figure
	{
		isValid = true;
	}

	return isValid;
}

bool isValidBlackPawn()
{
	bool isValid = false;
	if (tableX1 == 6 && tableX1 - 2 == tableX2 && tableY1 == tableY2 && table[tableX1 - 1][tableY1] == ' ' && table[tableX1 - 2][tableY1] == ' ') //Double start
	{
		isValid = true;
	}
	else if (tableX1 - 1 == tableX2 && tableY1 == tableY2 && table[tableX2][tableY2] == ' ') //1 step in line
	{
		isValid = true;
	}
	else if (tableX1 - 1 == tableX2 && tableY1 + 1 == tableY2 && checkFigure('w', tableX2, tableY2)) //taking right figure
	{
		isValid = true;
	}
	else if (tableX1 - 1 == tableX2 && tableY1 - 1 == tableY2 && checkFigure('w', tableX2, tableY2)) //taking left figure
	{
		isValid = true;
	}

	return isValid;
}

bool isValidWhiteKing()
{
	bool isValid = false;
	if ((tableX1 - 1 == tableX2 && tableY1 + 1 == tableY2
		|| tableX1 - 1 == tableX2 && tableY1 == tableY2
		|| tableX1 - 1 == tableX2 && tableY1 - 1 == tableY2
		|| tableX1 == tableX2 && tableY1 + 1 == tableY2
		|| tableX1 == tableX2 && tableY1 - 1 == tableY2
		|| tableX1 + 1 == tableX2 && tableY1 + 1 == tableY2
		|| tableX1 + 1 == tableX2 && tableY1 == tableY2
		|| tableX1 + 1 == tableX2 && tableY1 - 1 == tableY2)
		&& !checkFigure('w', tableX2, tableY2))
	{
		isValid = true;
	}

	return isValid;
}

bool isValidBlackKing()
{
	bool isValid = false;
	if ((tableX1 - 1 == tableX2 && tableY1 + 1 == tableY2
		|| tableX1 - 1 == tableX2 && tableY1 == tableY2
		|| tableX1 - 1 == tableX2 && tableY1 - 1 == tableY2
		|| tableX1 == tableX2 && tableY1 + 1 == tableY2
		|| tableX1 == tableX2 && tableY1 - 1 == tableY2
		|| tableX1 + 1 == tableX2 && tableY1 + 1 == tableY2
		|| tableX1 + 1 == tableX2 && tableY1 == tableY2
		|| tableX1 + 1 == tableX2 && tableY1 - 1 == tableY2)
		&& !checkFigure('b', tableX2, tableY2))
	{
		isValid = true;
	}

	return isValid;
}

bool isValidWhiteRock()
{
	bool isValid = false;
	bool somethingWrong = false;

	if (tableX1 == tableX2)
	{
		if (tableY1 > tableY2)
		{
			for (int i = tableY1 - 1; i > tableY2; i--)
			{
				if (checkFigure('w', tableX1, i) || checkFigure('b', tableX1, i))
				{
					somethingWrong = true;
					break;
				}
			}

		}
		else if (tableY1 < tableY2)
		{
			for (int i = tableY1 + 1; i < tableY2; i++)
			{
				if (checkFigure('w', tableX1, i) || checkFigure('b', tableX1, i))
				{
					somethingWrong = true;
					break;
				}
			}
		}
	}
	else if (tableY1 == tableY2)
	{
		if (tableX1 > tableX2)
		{
			for (int i = tableX1 - 1; i > tableX2; i--)
			{
				if (checkFigure('w', i, tableY1) || checkFigure('b', i, tableY1))
				{
					somethingWrong = true;
					break;
				}
			}

		}
		else if (tableX1 < tableX2)
		{
			for (int i = tableX1 + 1; i < tableX2; i++)
			{
				if (checkFigure('w', i, tableY2) || checkFigure('b', i, tableY2))
				{
					somethingWrong = true;
					break;
				}
			}
		}
	}
	else
	{
		somethingWrong = true;
	}

	if (!somethingWrong)
	{
		if (!checkFigure('w', tableX2, tableY2))
		{
			isValid = true;
		}
	}

	return isValid;
}

bool isValidBlackRock()
{
	bool isValid = false;
	bool somethingWrong = false;

	if (tableX1 == tableX2)
	{
		if (tableY1 > tableY2)
		{
			for (int i = tableY1 - 1; i > tableY2; i--)
			{
				if (checkFigure('w', tableX1, i) || checkFigure('b', tableX1, i))
				{
					somethingWrong = true;
					break;
				}
			}
		}
		else if (tableY1 < tableY2)
		{
			for (int i = tableY1 + 1; i < tableY2; i++)
			{
				if (checkFigure('w', tableX1, i) || checkFigure('b', tableX1, i))
				{
					somethingWrong = true;
					break;
				}
			}
		}
	}
	else if (tableY1 == tableY2)
	{
		if (tableX1 > tableX2)
		{
			for (int i = tableX1 - 1; i > tableX2; i--)
			{
				if (checkFigure('w', i, tableY1) || checkFigure('b', i, tableY1))
				{
					somethingWrong = true;
					break;
				}
			}

		}
		else if (tableX1 < tableX2)
		{
			for (int i = tableX1 + 1; i < tableX2; i++)
			{
				if (checkFigure('w', i, tableY2) || checkFigure('b', i, tableY2))
				{
					somethingWrong = true;
					break;
				}
			}
		}
	}
	else
	{
		somethingWrong = true;
	}

	if (!somethingWrong)
	{
		if (!checkFigure('b', tableX2, tableY2))
		{
			isValid = true;
		}
	}

	return isValid;
}

bool isValidWhiteOfficer()
{
	bool somethingWrong = false;


	int distance = max(tableX1, tableX2) - min(tableX1, tableX2);

	if (distance == max(tableY1, tableY2) - min(tableY1, tableY2))
	{
		for (int i = 1; i < distance; i++)
		{
			if (tableX2 > tableX1 && tableY2 > tableY1 && table[tableX1 + i][tableY1 + i] != ' ')
			{
				somethingWrong = true;
				break;
			}
			else if (tableX2 > tableX1 && tableY2 < tableY1 && table[tableX1 + i][tableY1 - i] != ' ')
			{
				somethingWrong = true;
				break;
			}
			else if (tableX2 < tableX1 && tableY2 < tableY1 && table[tableX1 - i][tableY1 - i] != ' ')
			{
				somethingWrong = true;
				break;
			}
			else if (tableX2 < tableX1 && tableY2 > tableY1 && table[tableX1 - i][tableY1 + i] != ' ')
			{
				somethingWrong = true;
				break;
			}
		}

		if (somethingWrong)
		{
			return false;
		}

		if (!checkFigure('w', tableX2, tableY2))
		{
			return true;
		}
	}
	return false;
}

bool isValidBlackOfficer()
{
	bool somethingWrong = false;


	int distance = max(tableX1, tableX2) - min(tableX1, tableX2);

	if (distance == max(tableY1, tableY2) - min(tableY1, tableY2))
	{
		for (int i = 1; i < distance; i++)
		{
			if (tableX2 > tableX1 && tableY2 > tableY1 && table[tableX1 + i][tableY1 + i] != ' ')
			{
				somethingWrong = true;
				break;
			}
			else if (tableX2 > tableX1 && tableY2 < tableY1 && table[tableX1 + i][tableY1 - i] != ' ')
			{
				somethingWrong = true;
				break;
			}
			else if (tableX2 < tableX1 && tableY2 < tableY1 && table[tableX1 - i][tableY1 - i] != ' ')
			{
				somethingWrong = true;
				break;
			}
			else if (tableX2 < tableX1 && tableY2 > tableY1 && table[tableX1 - i][tableY1 + i] != ' ')
			{
				somethingWrong = true;
				break;
			}
		}

		if (somethingWrong)
		{
			return false;
		}

		if (!checkFigure('b', tableX2, tableY2))
		{
			return true;
		}
	}
	return false;
}

bool isValidWhiteQueen()
{
	if (isValidWhiteRock() || isValidWhiteOfficer())
	{
		return true;
	}
	return false;
}

bool isValidBlackQueen()
{
	if (isValidBlackRock() || isValidBlackOfficer())
	{
		return true;
	}
	return false;
}

bool isValidWhiteHorse()
{
	if (tableX1 + 1 == tableX2 && tableY1 + 2 == tableY2
		|| tableX1 + 2 == tableX2 && tableY1 + 1 == tableY2
		|| tableX1 - 2 == tableX2 && tableY1 + 1 == tableY2
		|| tableX1 - 1 == tableX2 && tableY1 + 2 == tableY2
		|| tableX1 - 1 == tableX2 && tableY1 - 2 == tableY2
		|| tableX1 - 2 == tableX2 && tableY1 - 1 == tableY2
		|| tableX1 + 2 == tableX2 && tableY1 - 1 == tableY2
		|| tableX1 + 1 == tableX2 && tableY1 - 2 == tableY2
		)
	{
		if (!checkFigure('w', tableX2, tableY2))
		{
			return true;
		}
	}
	return false;
}

bool isValidBlackHorse()
{
	if (tableX1 + 1 == tableX2 && tableY1 + 2 == tableY2
		|| tableX1 + 2 == tableX2 && tableY1 + 1 == tableY2
		|| tableX1 - 2 == tableX2 && tableY1 + 1 == tableY2
		|| tableX1 - 1 == tableX2 && tableY1 + 2 == tableY2
		|| tableX1 - 1 == tableX2 && tableY1 - 2 == tableY2
		|| tableX1 - 2 == tableX2 && tableY1 - 1 == tableY2
		|| tableX1 + 2 == tableX2 && tableY1 - 1 == tableY2
		|| tableX1 + 1 == tableX2 && tableY1 - 2 == tableY2
		)
	{
		if (!checkFigure('b', tableX2, tableY2))
		{
			return true;
		}
	}
	return false;
}