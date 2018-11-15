#include<iostream>
#include<iomanip>
#include<string>
#include<windows.h>

using namespace std;

enum ConsoleColor
{
	Black = 0,
	Blue = 1,
	Green = 2, //+
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
	bool status=1;
	int pos_i;
	int pos_j;

	//string new_status;
};
Figure BlackTeam[16];
Figure WhiteTeam[16];
char pole[8][8];


void full(){
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

ConsoleColor FindFigure(int _i,int _j)
{
	for (int i = 0; i < 16; i++)
	{
		if (BlackTeam[i].pos_i == _i&&BlackTeam[i].pos_j == _j)
			return Black;
		else if (WhiteTeam[i].pos_i == _i&&WhiteTeam[i].pos_j == _j)
			return White;
	}
	return Black;
}

void show(){
	cout << " |ABCDEFGH \n";
	cout << "-+-------- \n";
	ConsoleColor bg, txt;
	for (int i = 0; i < 8; i++)
	{
		SetColor(0, LightGray);
		cout << i << "|";
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
			txt = FindFigure(i, j);
			SetColor(bg,txt);
			cout << pole[i][j];
		}
		cout << endl;
	}
	SetColor(0, LightGray);
}

int main()
{
	full();
	show();
	system("pause");
}