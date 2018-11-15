#include<iostream>
#include<iomanip>
#include<string>
#include<windows.h>
#include<cstdlib>
#include<fstream>

#define CLEAR system("CLS");

using namespace std;

enum ConsoleColor
{
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15
};

void SetColor(int background,int text=15)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

struct Figure
{
	char Symbol;
	ConsoleColor color;
	int status=1;
	int pos_i, pos_j;

	//string new_status;
};

char pole[8][8];
Figure BlackTeam[16], WhiteTeam[16],blank;

void full(){
	blank.color = Red;

	BlackTeam[0].Symbol = 'T';
	BlackTeam[0].pos_i = 0;
	BlackTeam[0].pos_j = 0;

	BlackTeam[1].Symbol = 'H';
	BlackTeam[1].pos_i = 0;
	BlackTeam[1].pos_j = 1;

	BlackTeam[2].Symbol = 'O';
	BlackTeam[2].pos_i = 0;
	BlackTeam[2].pos_j = 2;

	BlackTeam[3].Symbol = 'Q';
	BlackTeam[3].pos_i = 0;
	BlackTeam[3].pos_j = 3;

	BlackTeam[4].Symbol = 'K';
	BlackTeam[4].pos_i = 0;
	BlackTeam[4].pos_j = 4;

	BlackTeam[5].Symbol = 'O';
	BlackTeam[5].pos_i = 0;
	BlackTeam[5].pos_j = 5;

	BlackTeam[6].Symbol = 'H';
	BlackTeam[6].pos_i = 0;
	BlackTeam[6].pos_j = 6;

	BlackTeam[7].Symbol = 'T';
	BlackTeam[7].pos_i = 0;
	BlackTeam[7].pos_j = 7;

	for (int i = 0; i < 8; i++){
		BlackTeam[i + 8].Symbol = 'P';
		BlackTeam[i + 8].pos_i = 1;
		BlackTeam[i + 8].pos_j = i;
		BlackTeam[i].color = Black;
		BlackTeam[i + 8].color = Black;
	}

	WhiteTeam[0].Symbol = 'T';
	WhiteTeam[0].pos_i = 7;
	WhiteTeam[0].pos_j = 0;

	WhiteTeam[1].Symbol = 'H';
	WhiteTeam[1].pos_i = 7;
	WhiteTeam[1].pos_j = 1;

	WhiteTeam[2].Symbol = 'O';
	WhiteTeam[2].pos_i = 7;
	WhiteTeam[2].pos_j = 2;

	WhiteTeam[3].Symbol = 'Q';
	WhiteTeam[3].pos_i = 7;
	WhiteTeam[3].pos_j = 3;

	WhiteTeam[4].Symbol = 'K';
	WhiteTeam[4].pos_i = 7;
	WhiteTeam[4].pos_j = 4;

	WhiteTeam[5].Symbol = 'O';
	WhiteTeam[5].pos_i = 7;
	WhiteTeam[5].pos_j = 5;

	WhiteTeam[6].Symbol = 'H';
	WhiteTeam[6].pos_i = 7;
	WhiteTeam[6].pos_j = 6;

	WhiteTeam[7].Symbol = 'T';
	WhiteTeam[7].pos_i = 7;
	WhiteTeam[7].pos_j = 7;

	for (int i = 0; i < 8; i++){
		WhiteTeam[i + 8].Symbol = 'P';
		WhiteTeam[i + 8].pos_i = 6;
		WhiteTeam[i + 8].pos_j = i;
		WhiteTeam[i].color = White;
		WhiteTeam[i + 8].color = White;
	}
	for (int i = 0; i < 16; i++)
	{
		pole[BlackTeam[i].pos_i][BlackTeam[i].pos_j] = BlackTeam[i].Symbol;
		pole[WhiteTeam[i].pos_i][WhiteTeam[i].pos_j] = WhiteTeam[i].Symbol;
	}
	for (int i = 2; i < 6; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			pole[i][j] = ' ';
		}
	}
}

Figure& FindFigure(int _i,int _j)
{
	for (int i = 0; i < 16; i++)
	{
		if (BlackTeam[i].pos_i == _i&&BlackTeam[i].pos_j == _j)
			return BlackTeam[i];
		else if (WhiteTeam[i].pos_i == _i&&WhiteTeam[i].pos_j == _j)
			return WhiteTeam[i];
	}
	return blank;
}

void show(){
	Sleep(1000);
	CLEAR
	SetColor(0, White);
	cout << " | A  B  C  D  E  F  G  H \n";
	cout << "-+------------------------ \n";
	ConsoleColor bg, txt;
	for (int i = 0; i < 8; i++)
	{

		SetColor(0, White);
		cout << i+1 << "|";
		for (int j = 0; j < 8; j++)
		{

			if ((i +j)% 2 == 0)
			{
				bg = LightGray;
			}
			else
			{
				bg = DarkGray;
			}
			txt = FindFigure(i, j).color;
			SetColor(bg,txt);
			cout <<" "<< pole[i][j]<<" ";
		}
		cout << endl;
	}
	SetColor(0, LightGray);
}

void TurnWhite();
void TurnBlack();

void rebirth(ConsoleColor teamColor, int i, Figure& fig, char transform) {
	if (teamColor == White) {
		WhiteTeam[i].status = 1;
		WhiteTeam[i].pos_i = fig.pos_i;
		WhiteTeam[i].pos_j = fig.pos_j;
		fig.status = 0;
		fig.pos_i = 9;
		fig.pos_j = 9;
		pole[WhiteTeam[i].pos_i][WhiteTeam[i].pos_j] = transform;
	}
	else if (teamColor == Black) {
		BlackTeam[i].status = 1;
		BlackTeam[i].pos_i = fig.pos_i;
		BlackTeam[i].pos_j = fig.pos_j;
		fig.status = 0;
		fig.pos_i = 9;
		fig.pos_j = 9;
		pole[BlackTeam[i].pos_i][BlackTeam[i].pos_j] = transform;
	}
}

void Pawn(Figure& fig, char oldFigurePos[3]) {
	char figurePos[3];
	int pos_i, pos_j;
	cout <<"Pawn "<< oldFigurePos << " to:";
	cin >> figurePos;
	pos_i = figurePos[1] - 49;
	pos_j = figurePos[0] - 65;
	if (fig.color == White) {
		if (pos_i == fig.pos_i - 1 && (pos_j == fig.pos_j + 1 || pos_j == fig.pos_j - 1) && FindFigure(pos_i, pos_j).color == Black) {
			FindFigure(pos_i, pos_j).status = 0;
			FindFigure(pos_i, pos_j).pos_i = 9;
			FindFigure(9, pos_j).pos_j = 9;
			pole[fig.pos_i][fig.pos_j] = ' ';
			fig.pos_i = pos_i;
			fig.pos_j = pos_j;
			pole[pos_i][pos_j] = 'P';
			fig.status++;
		}
		else if (pos_i == fig.pos_i - 1 && pos_j == fig.pos_j && FindFigure(pos_i, pos_j).color == Red) {
			pole[fig.pos_i][fig.pos_j] = ' ';
			fig.pos_i = pos_i;
			pole[pos_i][pos_j] = 'P';
			fig.status++;
		}
		else if (pos_i == fig.pos_i - 2 && pos_j == fig.pos_j && fig.status == 1 &&
			FindFigure(pos_i + 1, pos_j).color == Red && FindFigure(pos_i, pos_j).color == Red) {
			pole[fig.pos_i][fig.pos_j] = ' ';
			fig.pos_i = pos_i;
			pole[pos_i][pos_j] = 'P';
			fig.status++;
		}
		else {
			cout << "Error";
			TurnWhite();
		}

		if (fig.pos_i == 0) {
			bool change = 0;
			for (int i = 0; i < 8; i++) {
				if (WhiteTeam[i].status == 0) {
					change = 1;
					break;
				}
			}
			if (change) {
				char transform;
				int i = 8;
				while (i == 8) {
					cout << "Pawn " << figurePos << " change to(letter) :";
					cin >> transform;
					switch (transform) {
					case 'T':
						if (WhiteTeam[0].status == 0) {
							i = 0;
						}
						else if (WhiteTeam[7].status == 0) {
							i = 7;
						}
						break;
					case 'H':
						if (WhiteTeam[1].status == 0) {
							i = 1;
						}
						else if (WhiteTeam[6].status == 0) {
							i = 6;
						}
						break;
					case 'O':
						if (WhiteTeam[2].status == 0) {
							i = 0;
						}
						else if (WhiteTeam[5].status == 0) {
							i = 7;
						}
						break;
					case 'Q':
						if (WhiteTeam[3].status == 0) {
							i = 0;
						}
						break;
					}
					if (i < 8) {
						rebirth(White, i, fig, transform);
					}
				}
			}
		}
	}
	else if (fig.color == Black) {
		if (pos_i == fig.pos_i + 1 && (pos_j == fig.pos_j + 1 || pos_j == fig.pos_j - 1) && FindFigure(pos_i, pos_j).color == White) {
			FindFigure(pos_i, pos_j).status = 0;
			FindFigure(pos_i, pos_j).pos_i = 9;
			FindFigure(9, pos_j).pos_j = 9;
			pole[fig.pos_i][fig.pos_j] = ' ';
			fig.pos_i = pos_i;
			fig.pos_j = pos_j;
			pole[pos_i][pos_j] = 'P';
			fig.status++;
		}
		else if (pos_i == fig.pos_i + 1 && pos_j == fig.pos_j && FindFigure(pos_i, pos_j).color == Red) {
			pole[fig.pos_i][fig.pos_j] = ' ';
			fig.pos_i = pos_i;
			fig.pos_j = pos_j;
			pole[pos_i][pos_j] = 'P';
			fig.status++;
		}
		else if (pos_i == fig.pos_i + 2 && pos_j == fig.pos_j && fig.status == 1 &&
			FindFigure(pos_i - 1, pos_j).color == Red && FindFigure(pos_i, pos_j).color == Red) {
			pole[fig.pos_i][fig.pos_j] = ' ';
			fig.pos_i = pos_i;
			fig.pos_j = pos_j;
			pole[pos_i][pos_j] = 'P';
			fig.status++;
		}
		else {
			cout << "Error";
			TurnBlack();
		}

		if (fig.pos_i == 7) {
			bool change = 0;
			for (int i = 0; i < 8; i++) {
				if (BlackTeam[i].status == 0) {
					change = 1;
					break;
				}
			}
			if (change) {
				char transform;
				int i = 8;
				while (i == 8) {
					cout << "Pawn " << figurePos << " change to(letter) :";
					cin >> transform;
					switch (transform) {
					case 'T':
						if (BlackTeam[0].status == 0) {
							i = 0;
						}
						else if (BlackTeam[7].status == 0) {
							i = 7;
						}
						break;
					case 'H':
						if (BlackTeam[1].status == 0) {
							i = 1;
						}
						else if (BlackTeam[6].status == 0) {
							i = 6;
						}
						break;
					case 'O':
						if (BlackTeam[2].status == 0) {
							i = 0;
						}
						else if (BlackTeam[5].status == 0) {
							i = 7;
						}
						break;
					case 'Q':
						if (BlackTeam[3].status == 0) {
							i = 0;
						}
						break;
					}
					if (i < 8) {
						rebirth(Black, i, fig, transform);
					}
				}
			}
		}
	}
}

bool TowerMove(int Tpos_i, int Tpos_j, int pos_i, int pos_j) {
	if ((Tpos_i != pos_i && Tpos_j != pos_j) || (Tpos_i == pos_i && Tpos_j == pos_j)) {
		return 0;
	}
	else if (Tpos_i == pos_i) {
		while (Tpos_j < pos_j-1) {
			Tpos_j++;
			if (FindFigure(Tpos_i, Tpos_j).color != Red) {
				return 0;
			}
		}
		while (Tpos_j > pos_j+1) {
			Tpos_j--;
			if (FindFigure(Tpos_i, Tpos_j).color != Red) {
				return 0;
			}
		}
	}
	else if (Tpos_j == pos_j) {
		while (Tpos_i < pos_i-1) {
			Tpos_i++;
			if (FindFigure(Tpos_i, Tpos_j).color != Red) {
				return 0;
			}
		}
		while (Tpos_i > pos_i+1) {
			Tpos_i--;
			if (FindFigure(Tpos_i, Tpos_j).color != Red) {
				return 0;
			}
		}
	}
	return 1;
}

void Tower(Figure& fig, char oldFigurePos[3]) {
	char figurePos[3];
	int pos_i, pos_j;
	cout << "Tower " << oldFigurePos << " to:";
	cin >> figurePos;
	pos_i = figurePos[1] - 49;
	pos_j = figurePos[0] - 65;
	if (fig.color == White && TowerMove(fig.pos_i, fig.pos_j, pos_i, pos_j) == 1 && FindFigure(pos_i, pos_j).color == Black) {
		FindFigure(pos_i, pos_j).status = 0;
		FindFigure(pos_i, pos_j).pos_i = 9;
		FindFigure(9, pos_j).pos_j = 9;
		pole[fig.pos_i][fig.pos_j] = ' ';
		fig.pos_i = pos_i;
		fig.pos_j = pos_j;
		pole[pos_i][pos_j] = 'T';
		fig.status++;
	}
	else if (fig.color == Black && TowerMove(fig.pos_i, fig.pos_j, pos_i, pos_j) == 1 && FindFigure(pos_i, pos_j).color == White) {
		FindFigure(pos_i, pos_j).status = 0;
		FindFigure(pos_i, pos_j).pos_i = 9;
		FindFigure(9, pos_j).pos_j = 9;
		pole[fig.pos_i][fig.pos_j] = ' ';
		fig.pos_i = pos_i;
		fig.pos_j = pos_j;
		pole[pos_i][pos_j] = 'T';
		fig.status++;
	}
	else if (TowerMove(fig.pos_i, fig.pos_j, pos_i, pos_j) == 1 && FindFigure(pos_i, pos_j).color == Red) {
		pole[fig.pos_i][fig.pos_j] = ' ';
		fig.pos_i = pos_i;
		fig.pos_j = pos_j;
		pole[pos_i][pos_j] = 'T';
		fig.status++;
	}
	else {
		cout << "Error";
		if (fig.color == White)TurnWhite();
		else if (fig.color == Black)TurnBlack();
	}
}

bool HorseMove(int Hpos_i, int Hpos_j, int pos_i, int pos_j) {
	if (Hpos_i == pos_i + 1 || Hpos_i == pos_i - 1) {
		if (Hpos_j == pos_j + 2 || Hpos_j == pos_j - 2) {
			return 1;
		}
	}
	else if (Hpos_i == pos_i + 2 || Hpos_i == pos_i - 2) {
		if (Hpos_j == pos_j + 1 || Hpos_j == pos_j - 1) {
			return 1;
		}
	}
	return 0;
}

void Horse(Figure& fig, char oldFigurePos[3]) {
	char figurePos[3];
	int pos_i, pos_j;
	cout << "Horse " << oldFigurePos << " to:";
	cin >> figurePos;
	pos_i = figurePos[1] - 49;
	pos_j = figurePos[0] - 65;
	if (fig.color == White && HorseMove(fig.pos_i, fig.pos_j, pos_i, pos_j) == 1 && FindFigure(pos_i, pos_j).color == Black) {
		FindFigure(pos_i, pos_j).status = 0;
		FindFigure(pos_i, pos_j).pos_i = 9;
		FindFigure(9, pos_j).pos_j = 9;
		pole[fig.pos_i][fig.pos_j] = ' ';
		fig.pos_i = pos_i;
		fig.pos_j = pos_j;
		pole[pos_i][pos_j] = 'H';
		fig.status++;
	}
	else if (fig.color == Black && HorseMove(fig.pos_i, fig.pos_j, pos_i, pos_j) == 1 && FindFigure(pos_i, pos_j).color == White) {
		FindFigure(pos_i, pos_j).status = 0;
		FindFigure(pos_i, pos_j).pos_i = 9;
		FindFigure(9, pos_j).pos_j = 9;
		pole[fig.pos_i][fig.pos_j] = ' ';
		fig.pos_i = pos_i;
		fig.pos_j = pos_j;
		pole[pos_i][pos_j] = 'H';
		fig.status++;
	}
	else if (HorseMove(fig.pos_i, fig.pos_j, pos_i, pos_j) == 1 && FindFigure(pos_i, pos_j).color == Red) {
		pole[fig.pos_i][fig.pos_j] = ' ';
		fig.pos_i = pos_i;
		fig.pos_j = pos_j;
		pole[pos_i][pos_j] = 'H';
		fig.status++;
	}
	else {
		cout << "Error";
		if (fig.color == White)TurnWhite();
		else if (fig.color == Black)TurnBlack();
	}
}

bool OfficerMove(int Opos_i, int Opos_j, int pos_i, int pos_j) {
	if (Opos_i == pos_i || Opos_j == pos_j || abs(Opos_i - pos_i) != abs(Opos_j - pos_j)) {
		return 0;
	}
	else if (Opos_i < pos_i) {
		while (Opos_j < pos_j - 1) {
			Opos_j++;
			Opos_i++;
			if (FindFigure(Opos_i, Opos_j).color != Red) {
				return 0;
			}
		}
		while (Opos_j > pos_j + 1) {
			Opos_j--;
			Opos_i++;
			if (FindFigure(Opos_i, Opos_j).color != Red) {
				return 0;
			}
		}
	}
	else if (Opos_i > pos_i) {
		while (Opos_j < pos_j - 1) {
			Opos_j++;
			Opos_i--;
			if (FindFigure(Opos_i, Opos_j).color != Red) {
				return 0;
			}
		}
		while (Opos_j > pos_j + 1) {
			Opos_j--;
			Opos_i--;
			if (FindFigure(Opos_i, Opos_j).color != Red) {
				return 0;
			}
		}
	}
	return 1;
}

void Officer(Figure& fig, char oldFigurePos[3]) {
	char figurePos[3];
	int pos_i, pos_j;
	cout << "Officer " << oldFigurePos << " to:";
	cin >> figurePos;
	pos_i = figurePos[1] - 49;
	pos_j = figurePos[0] - 65;
	if (fig.color == White && OfficerMove(fig.pos_i, fig.pos_j, pos_i, pos_j) == 1 && FindFigure(pos_i, pos_j).color == Black) {
		FindFigure(pos_i, pos_j).status = 0;
		FindFigure(pos_i, pos_j).pos_i = 9;
		FindFigure(9, pos_j).pos_j = 9;
		pole[fig.pos_i][fig.pos_j] = ' ';
		fig.pos_i = pos_i;
		fig.pos_j = pos_j;
		pole[pos_i][pos_j] = 'O';
		fig.status++;
	}
	else if (fig.color == Black && OfficerMove(fig.pos_i, fig.pos_j, pos_i, pos_j) == 1 && FindFigure(pos_i, pos_j).color == White) {
		FindFigure(pos_i, pos_j).status = 0;
		FindFigure(pos_i, pos_j).pos_i = 9;
		FindFigure(9, pos_j).pos_j = 9;
		pole[fig.pos_i][fig.pos_j] = ' ';
		fig.pos_i = pos_i;
		fig.pos_j = pos_j;
		pole[pos_i][pos_j] = 'O';
		fig.status++;
	}
	else if (OfficerMove(fig.pos_i, fig.pos_j, pos_i, pos_j) == 1 && FindFigure(pos_i, pos_j).color == Red) {
		pole[fig.pos_i][fig.pos_j] = ' ';
		fig.pos_i = pos_i;
		fig.pos_j = pos_j;
		pole[pos_i][pos_j] = 'O';
		fig.status++;
	}
	else {
		cout << "Error";
		if (fig.color == White)TurnWhite();
		else if (fig.color == Black)TurnBlack();
	}
}

bool QueenMove(int Qpos_i, int Qpos_j, int pos_i, int pos_j) {
	if (Qpos_i == pos_i && Qpos_j == pos_j) {
		return 0;
	}
	else if (abs(Qpos_i - pos_i) == abs(Qpos_j - pos_j)) {
		return OfficerMove(Qpos_i, Qpos_j, pos_i, pos_j);
	}
	else {
		return TowerMove(Qpos_i, Qpos_j, pos_i, pos_j);
	}
}

void Queen(Figure& fig, char oldFigurePos[3]) {
	char figurePos[3];
	int pos_i, pos_j;
	cout << "Queen " << oldFigurePos << " to:";
	cin >> figurePos;
	pos_i = figurePos[1] - 49;
	pos_j = figurePos[0] - 65;
	if (fig.color == White && QueenMove(fig.pos_i, fig.pos_j, pos_i, pos_j) == 1 && FindFigure(pos_i, pos_j).color == Black) {
		FindFigure(pos_i, pos_j).status = 0;
		FindFigure(pos_i, pos_j).pos_i = 9;
		FindFigure(9, pos_j).pos_j = 9;
		pole[fig.pos_i][fig.pos_j] = ' ';
		fig.pos_i = pos_i;
		fig.pos_j = pos_j;
		pole[pos_i][pos_j] = 'Q';
		fig.status++;
	}
	else if (fig.color == Black && QueenMove(fig.pos_i, fig.pos_j, pos_i, pos_j) == 1 && FindFigure(pos_i, pos_j).color == White) {
		FindFigure(pos_i, pos_j).status = 0;
		FindFigure(pos_i, pos_j).pos_i = 9;
		FindFigure(9, pos_j).pos_j = 9;
		pole[fig.pos_i][fig.pos_j] = ' ';
		fig.pos_i = pos_i;
		fig.pos_j = pos_j;
		pole[pos_i][pos_j] = 'Q';
		fig.status++;
	}
	else if (QueenMove(fig.pos_i, fig.pos_j, pos_i, pos_j) == 1 && FindFigure(pos_i, pos_j).color == Red) {
		pole[fig.pos_i][fig.pos_j] = ' ';
		fig.pos_i = pos_i;
		fig.pos_j = pos_j;
		pole[pos_i][pos_j] = 'Q';
		fig.status++;
	}
	else {
		cout << "Error";
		if (fig.color == White)TurnWhite();
		else if (fig.color == Black)TurnBlack();
	}
}

bool KingMove(int Kpos_i, int Kpos_j, int pos_i, int pos_j) {
	if (Kpos_i == pos_i && Kpos_j == pos_j) {
		return 0;
	}
	else if (abs(Kpos_i - pos_i) <= 1 && abs(Kpos_j - pos_j) <= 1) {
		return 1;
	}
	else {
		return 0;
	}
}

void King(Figure& fig, char oldFigurePos[3]) {
	char figurePos[3];
	int pos_i, pos_j;
	cout << "King " << oldFigurePos << " to:";
	cin >> figurePos;
	pos_i = figurePos[1] - 49;
	pos_j = figurePos[0] - 65;
	if (fig.color == White && KingMove(fig.pos_i, fig.pos_j, pos_i, pos_j) && FindFigure(pos_i, pos_j).color == Black) {
		FindFigure(pos_i, pos_j).status = 0;
		FindFigure(pos_i, pos_j).pos_i = 9;
		FindFigure(9, pos_j).pos_j = 9;
		pole[fig.pos_i][fig.pos_j] = ' ';
		fig.pos_i = pos_i;
		fig.pos_j = pos_j;
		pole[pos_i][pos_j] = 'K';
		fig.status++;
	}
	else if (fig.color == Black && KingMove(fig.pos_i, fig.pos_j, pos_i, pos_j) && FindFigure(pos_i, pos_j).color == White) {
		FindFigure(pos_i, pos_j).status = 0;
		FindFigure(pos_i, pos_j).pos_i = 9;
		FindFigure(9, pos_j).pos_j = 9;
		pole[fig.pos_i][fig.pos_j] = ' ';
		fig.pos_i = pos_i;
		fig.pos_j = pos_j;
		pole[pos_i][pos_j] = 'K';
		fig.status++;
	}
	else if (KingMove(fig.pos_i, fig.pos_j, pos_i, pos_j) && FindFigure(pos_i, pos_j).color == Red) {
		pole[fig.pos_i][fig.pos_j] = ' ';
		fig.pos_i = pos_i;
		fig.pos_j = pos_j;
		pole[pos_i][pos_j] = 'K';
		fig.status++;
	}
	else {
		cout << "Error";
		if (fig.color == White)TurnWhite();
		else if (fig.color == Black)TurnBlack();
	}

	if (fig.pos_i == 0 && fig.color == White) {
		int spawn = 0;
		for (int i = 8; i < 16; i++) {
			if (WhiteTeam[i].status == 0) {
				spawn = i;
				break;
			}
		}
		if (spawn >= 8) {
			while (true) {
				cout << "King " << figurePos << " spawn Pawn to: 8";
				cin >> figurePos;
				pos_j = figurePos[0] - 65;
				if (FindFigure(7, pos_j).color == Red) {
					WhiteTeam[spawn].Symbol = 'P';
					WhiteTeam[spawn].pos_i = 7;
					WhiteTeam[spawn].pos_j = pos_j;
					WhiteTeam[spawn].color = White;
					WhiteTeam[spawn].status == 1;
					pole[7][pos_j]=WhiteTeam[spawn].Symbol;
					break;
				}
			}
		}
	}
	else if (fig.pos_i == 7 && fig.color == Black) {
		int spawn = 0;
		for (int i = 8; i < 16; i++) {
			if (BlackTeam[i].status == 0) {
				spawn = i;
				break;
			}
		}
		if (spawn >= 8) {
			while (true) {
				cout << "King " << figurePos << " spawn Pawn to: 1";
				cin >> figurePos;
				pos_j = figurePos[0] - 65;
				if (FindFigure(0, pos_j).color == Red) {
					BlackTeam[spawn].Symbol = 'P';
					BlackTeam[spawn].pos_i = 0;
					BlackTeam[spawn].pos_j = pos_j;
					BlackTeam[spawn].color = Black;
					BlackTeam[spawn].status == 1;
					pole[0][pos_j] = BlackTeam[spawn].Symbol;
					break;
				}
			}
		}
	}
}

void TurnWhite() {
	show();
	char figurePos[3];
	int pos_i, pos_j;
	cout << "White team turn :";
	cin >> figurePos;
	pos_i = figurePos[1] - 49;
	pos_j = figurePos[0] - 65;
	if (FindFigure(pos_i, pos_j).color == White && FindFigure(pos_i, pos_j).status>0) {
		switch (pole[pos_i][pos_j]) {
		case 'P':
			Pawn(FindFigure(pos_i, pos_j), figurePos);
			break;
		case 'T':
			Tower(FindFigure(pos_i, pos_j), figurePos);
			break;
		case 'H':
			Horse(FindFigure(pos_i, pos_j), figurePos);
			break;
		case 'O':
			Officer(FindFigure(pos_i, pos_j), figurePos);
			break;
		case 'Q':
			Queen(FindFigure(pos_i, pos_j), figurePos);
			break;
		case 'K':
			King(FindFigure(pos_i, pos_j), figurePos);
			break;
		}
	}
	else {
		cout << "Error";
		TurnWhite();
	}
}

void TurnBlack() {
	show();
	char figurePos[3];
	int pos_i, pos_j;
	cout << "Black team turn :";
	cin >> figurePos;
	pos_i = figurePos[1] - 49;
	pos_j = figurePos[0] - 65;
	if (FindFigure(pos_i, pos_j).color == Black && FindFigure(pos_i, pos_j).status>0) {
		switch (pole[pos_i][pos_j]) {
		case 'P':
			Pawn(FindFigure(pos_i, pos_j), figurePos);
			break;
		case 'T':
			Tower(FindFigure(pos_i, pos_j), figurePos);
			break;
		case 'H':
			Horse(FindFigure(pos_i, pos_j), figurePos);
			break;
		case 'O':
			Officer(FindFigure(pos_i, pos_j), figurePos);
			break;
		case 'Q':
			Queen(FindFigure(pos_i, pos_j), figurePos);
			break;
		case 'K':
			King(FindFigure(pos_i, pos_j), figurePos);
			break;
		}
	}
	else {
		cout << "Error";
		TurnBlack();
	}
}

int Game()
{	
	int a = 0;
	full();
	while (true) {
		TurnWhite();
		if (BlackTeam[4].status == 0) {
			show();
			cout << "White team win \n";
			break;
		}
		TurnBlack();
		if (WhiteTeam[4].status == 0) {
			show();
			cout << "Black team win \n";
			break;
		}
		a++;
	}
	Sleep(3000);
	return a;
}
void main() {
	string name;
	int choice;
	cout << " 1)Start game \n 2)Records \n 3)Exit \n";
	cin >> choice;
	switch (choice) {
	case 1:
		int score=Game();
		cout << "Input nick ";
		cin >> name;
		
		ofstream fout;
		fout.open("Records.txt", ios_base::app);
		fout << name << " score=" << score << endl;
		fout.close();
		
		break;
		/*
	case 2:
		ifstream fout;
		fout.open("Records.txt", ios_base::app);
		//fout >>;
		fout.close();

		break;
		*/
	}
	system("pause");
}