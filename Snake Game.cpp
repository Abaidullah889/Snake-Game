#include<iostream>
#include<string>
#include<windows.h>
#include<MMSystem.h>
#include<conio.h>
#include<ctime>
using namespace std;


#define BLACK 0
#define BROWN 6
#define WHITE 15
#define GREEN 2
#define RED 4
#define LBLUE 9

#define SRow 100
#define SCol 140




void SetClr(int tcl, int bcl)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (tcl + (bcl * 16)));
}
void gotoRowCol(int rpos, int cpos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = cpos;
	scrn.Y = rpos;
	SetConsoleCursorPosition(hOuput, scrn);
}
void getRowColbyLeftClick(int& rpos, int& cpos)
{
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD Events;
	INPUT_RECORD InputRecord;
	SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
	do
	{
		ReadConsoleInput(hInput, &InputRecord, 1, &Events);
		if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			cpos = InputRecord.Event.MouseEvent.dwMousePosition.X;
			rpos = InputRecord.Event.MouseEvent.dwMousePosition.Y;
			break;
		}
	} while (true);
}
enum Direction { UP, DOWN, LEFT, RIGHT };
struct Position
{
	int ri;
	int ci;
};
struct Food
{
	Position Fp;
};
struct Snake
{
	Position* Sp;
	int size = 0;
	Direction dir;
	int score = 0;
	string Pnames;
	char sym = 0;
	int UP = 0, RIGHT = 0, LEFT = 0, DOWN = 0;
};
void GenerateFood(Food& F, Snake& S, int height, int width);
void init(Snake& S, Food& F, int height, int width)
{
	S.Sp = new Position[3];
	S.Sp[0].ri = height / 2;
	S.Sp[0].ci = width - 10;

	S.Sp[1].ri = height / 2;
	S.Sp[1].ci = width - 10 - 1;

	S.Sp[2].ri = height / 2;
	S.Sp[2].ci = width - 10 - 2;

	S.size = 3;
	S.dir = RIGHT;
	S.score = 0;
	gotoRowCol(0, 102);
	cout << "Enter the Name of Snake: ";
	Sleep(1700);
	PlaySound(TEXT("snake.wav"), NULL, SND_ASYNC);
	Sleep(80);
	cin >> S.Pnames;
	gotoRowCol(0, 102);
	cout << "                                          ";
	S.sym = -37;
	S.RIGHT = 77, S.DOWN = 80, S.UP = 72, S.LEFT = 75;

	GenerateFood(F, S, height, width);
}
void init2(Snake& S, int height, int width)
{
	S.Sp = new Position[15];
	for (int i = 0; i < 15; i++)
	{
		S.Sp[i].ri = 28;
		S.Sp[i].ci = 63 - i;

	}


	S.size = 15;
	S.dir = RIGHT;
	S.score = 0;
	S.sym = -37;
	S.RIGHT = 77, S.DOWN = 80, S.UP = 72, S.LEFT = 75;


}
void init3(Snake& S, int height, int width)
{
	S.Sp = new Position[15];

	for (int i = 0; i < 15; i++)
	{
		S.Sp[i].ri = 52;
		S.Sp[i].ci = 63 + i;
	}

	S.size = 15;
	S.dir = LEFT;
	S.score = 0;
	S.sym = -37;
	S.RIGHT = 77, S.DOWN = 80, S.UP = 72, S.LEFT = 75;


}
void initM1(Snake& S, Food& F, int height, int width)
{
	S.Sp = new Position[3];
	S.Sp[0].ri = height - 20;
	S.Sp[0].ci = width / 2;

	S.Sp[1].ri = height - 20;
	S.Sp[1].ci = width / 2 - 1;

	S.Sp[2].ri = height - 20;
	S.Sp[2].ci = width / 2 - 2;

	S.size = 3;
	S.dir = RIGHT;
	S.score = 0;
	gotoRowCol(0, 102);
	SetClr(15, 0);
	cout << "Enter the Name of First Snake: ";
	Sleep(1700);
	PlaySound(TEXT("firstsnake.wav"), NULL, SND_ASYNC);
	Sleep(80);
	cin >> S.Pnames;
	gotoRowCol(0, 102);
	SetClr(0, 0);
	cout << "                                                                                     ";
	S.sym = -37;
	S.RIGHT = 77, S.DOWN = 80, S.UP = 72, S.LEFT = 75;

	GenerateFood(F, S, height, width);

}
void initM2(Snake& S, int height, int width)
{
	S.Sp = new Position[3];
	S.Sp[0].ri = (height / 2) - 8;
	S.Sp[0].ci = width / 2 - 2;

	S.Sp[1].ri = (height / 2) - 8;
	S.Sp[1].ci = (width / 2) - 1;

	S.Sp[2].ri = (height / 2) - 8;
	S.Sp[2].ci = (width / 2);

	S.size = 3;
	S.dir = LEFT;
	S.score = 0;
	SetClr(15, 0);
	gotoRowCol(0, 102);
	cout << "Enter the Name of Second Snake: ";
	PlaySound(TEXT("secondsnake.wav"), NULL, SND_ASYNC);
	Sleep(80);
	cin >> S.Pnames;
	gotoRowCol(0, 102);
	cout << "                                                            ";
	S.sym = -37;
	S.RIGHT = 100, S.DOWN = 115, S.UP = 119, S.LEFT = 97;

}
void initM3(Snake& S, int height, int width)
{
	S.Sp = new Position[3];
	S.Sp[0].ri = (height / 4);
	S.Sp[0].ci = width / 4;

	S.Sp[1].ri = (height / 4) - 1;
	S.Sp[1].ci = width / 4;

	S.Sp[2].ri = (height / 4) - 2;
	S.Sp[2].ci = (width / 4);

	S.size = 3;
	S.dir = DOWN;
	S.score = 0;
	gotoRowCol(0, 102);
	cout << "Enter the Name of Third Snake: ";
	PlaySound(TEXT("thirdsnake.wav"), NULL, SND_ASYNC);
	Sleep(80);
	cin >> S.Pnames;
	gotoRowCol(0, 102);
	cout << "                                                            ";
	S.sym = -37;
	S.RIGHT = 54, S.DOWN = 53, S.UP = 56, S.LEFT = 52;
}
void initM4(Snake& S, int height, int width)
{
	S.Sp = new Position[3];
	S.Sp[0].ri = (height / 3);
	S.Sp[0].ci = width / 8;

	S.Sp[1].ri = (height / 3) + 1;
	S.Sp[1].ci = width / 8;

	S.Sp[2].ri = (height / 3) + 2;
	S.Sp[2].ci = (width / 8);

	S.size = 3;
	S.dir = UP;
	S.score = 0;
	gotoRowCol(0, 102);
	cout << "Enter the Name of Fourth Snake: ";
	PlaySound(TEXT("fourthsnake.wav"), NULL, SND_ASYNC);
	Sleep(80);
	cin >> S.Pnames;
	gotoRowCol(0, 102);
	cout << "                                                            ";
	S.sym = -37;
	S.RIGHT = 108, S.DOWN = 107, S.UP = 105, S.LEFT = 106;

}
void DisplaySnake(Snake& S)
{
	for (int i = 0; i < S.size; i++)
	{
		if (i % 2 == 0)
		{
			SetClr(4, 0);
		}
		if (i % 2 != 0)
		{
			SetClr(2, 0);
		}
		gotoRowCol(S.Sp[i].ri, S.Sp[i].ci);
		cout << S.sym;
	}
}
void DisplaySnakeM2(Snake& S)
{
	for (int i = 0; i < S.size; i++)
	{
		if (i % 2 == 0)
		{
			SetClr(4, 0);
		}
		if (i % 2 != 0)
		{
			SetClr(15, 0);
		}
		gotoRowCol(S.Sp[i].ri, S.Sp[i].ci);
		cout << S.sym;
	}
}
void DisplaySnakeM3(Snake& S)
{
	for (int i = 0; i < S.size; i++)
	{
		if (i % 2 == 0)
		{
			SetClr(6, 0);
		}
		if (i % 2 != 0)
		{
			SetClr(15, 0);
		}
		gotoRowCol(S.Sp[i].ri, S.Sp[i].ci);
		cout << S.sym;
	}
}
void DisplaySnakeM4(Snake& S)
{
	for (int i = 0; i < S.size; i++)
	{
		if (i % 2 == 0)
		{
			SetClr(10, 0);
		}
		if (i % 2 != 0)
		{
			SetClr(6, 0);
		}
		gotoRowCol(S.Sp[i].ri, S.Sp[i].ci);
		cout << S.sym;
	}
}
void RemoveSnake(Snake& S)
{
	for (int i = 0; i < S.size; i++)
	{
		gotoRowCol(S.Sp[i].ri, S.Sp[i].ci);
		cout << " ";
	}
}
void ChangeDirection(char key, Snake& S)
{
	if (key == S.UP)
	{
		if (S.dir != DOWN)
		{
			S.dir = UP;
		}
	}
	if (key == S.DOWN)
	{
		if (S.dir != UP)
		{
			S.dir = DOWN;
		}
	}
	if (key == S.LEFT)
	{

		if (S.dir != RIGHT)
		{
			S.dir = LEFT;
		}
	}

	if (key == S.RIGHT)
	{
		if (S.dir != LEFT)
		{
			S.dir = RIGHT;
		}
	}
}
void MoveSnake(Snake& S, int height, int width)
{
	for (int i = S.size - 1; i - 1 >= 0; i--)
	{
		S.Sp[i] = S.Sp[i - 1];
	}

	switch (S.dir)
	{
	case LEFT:
		if (S.Sp[0].ci == 1)
		{
			S.Sp[0].ci = width - 2;
		}
		else
		{
			S.Sp[0].ci--;
		}
		break;

	case RIGHT:
		if (S.Sp[0].ci == width - 2)
		{
			S.Sp[0].ci = 1;
		}
		else
		{
			S.Sp[0].ci++;
		}
		break;
	case UP:
		S.Sp[0].ri--;
		if (S.Sp[0].ri == 0)
		{
			S.Sp[0].ri = height - 2;
		}
		break;
	case DOWN:
		S.Sp[0].ri++;
		if (S.Sp[0].ri == height - 1)
		{
			S.Sp[0].ri = 1;
		}
		break;
	}
}
void MoveSnake2(Snake& S, int height, int width)
{
	for (int i = S.size - 1; i - 1 >= 0; i--)
	{
		S.Sp[i] = S.Sp[i - 1];
	}

	switch (S.dir)
	{
	case LEFT:
		if (S.Sp[0].ci == 52 && S.Sp[0].ri == 52)
		{
			S.dir = UP;
		}
		else
		{
			S.Sp[0].ci--;
		}
		break;
	case RIGHT:
		if (S.Sp[0].ci == 103 && S.Sp[0].ri == 28)
		{
			S.dir = DOWN;
		}
		else
		{
			S.Sp[0].ci++;
		}
		break;
	case UP:
		S.Sp[0].ri--;
		if (S.Sp[0].ri == 28 && S.Sp[0].ci == 52)
		{
			S.dir = RIGHT;
		}
		break;
	case DOWN:
		S.Sp[0].ri++;
		if (S.Sp[0].ri == 52 && S.Sp[0].ci == 103)
		{
			S.dir = LEFT;
		}
		break;
	}
}
void MoveSnake3(Snake& S, int height, int width)
{
	for (int i = S.size - 1; i - 1 >= 0; i--)
	{
		S.Sp[i] = S.Sp[i - 1];
	}

	switch (S.dir)
	{
	case LEFT:
		if (S.Sp[0].ci == 52 && S.Sp[0].ri == 52)
		{
			S.dir = UP;
		}
		else
		{
			S.Sp[0].ci--;
		}
		break;
	case RIGHT:
		if (S.Sp[0].ci == 103 && S.Sp[0].ri == 28)
		{
			S.dir = DOWN;
		}
		else
		{
			S.Sp[0].ci++;
		}
		break;
	case UP:
		S.Sp[0].ri--;
		if (S.Sp[0].ri == 28 && S.Sp[0].ci == 52)
		{
			S.dir = RIGHT;
		}
		break;
	case DOWN:
		S.Sp[0].ri++;
		if (S.Sp[0].ri == 52 && S.Sp[0].ci == 103)
		{
			S.dir = LEFT;
		}
		break;
	}
}
void DrawBox(int height, int width)
{
	char c = -37;
	for (int i = 0; i < width; i++)
	{
		gotoRowCol(0, i);
		SetClr(4, 0);
		cout << c;
	}
	for (int i = 0; i < height; i++)
	{
		gotoRowCol(i, 0);
		SetClr(2, 0);
		cout << c;
	}
	for (int i = 0; i < height; i++)
	{
		gotoRowCol(i, width-1);
		SetClr(2, 0);
		cout << c;
	}
	for (int i = 0; i < width; i++)
	{
		gotoRowCol(height-1, i);
		SetClr(4, 0);
		cout << c;
	}
}

void DrawBoxH(int height, int width)
{
	char c = -37;
	for (int i = 0; i < width; i++)
	{
		gotoRowCol(0, i);
		SetClr(4, 0);
		cout << c;
	}
	for (int i = 0; i < height; i++)
	{
		gotoRowCol(i, 0);
		SetClr(2, 0);
		cout << c;
	}
	for (int i = 0; i < height; i++)
	{
		gotoRowCol(i, width - 1);
		SetClr(2, 0);
		cout << c;
	}
	for (int i = 0; i < width; i++)
	{
		gotoRowCol(height - 1, i);
		SetClr(4, 0);
		cout << c;
	}

	for (int i = 1; i <= 10; i++)
	{
		gotoRowCol(7 + i, 20);
		SetClr(15, 0);
		cout << c;
	}

	for (int i = 1; i <= 10; i++)
	{
		gotoRowCol(7 + i, 80);
		SetClr(15, 0);
		cout << c;
	}

	for (int i = 1; i <= 10; i++)
	{
		gotoRowCol(43 + i, 80);
		SetClr(15, 0);
		cout << c;
	}

	for (int i = 1; i <= 10; i++)
	{
		gotoRowCol(43 + i, 20);
		SetClr(15, 0);
		cout << c;
	}

	for (int i = 0; i < 5; i++)
	{
		gotoRowCol(30 + i, 50);
		SetClr(15, 0);
		cout << c;
	}

	for (int i = 0; i < 5; i++)
	{
		gotoRowCol(30 - i, 50);
		SetClr(15, 0);
		cout << c;
	}

	for (int i = 0; i < 5; i++)
	{
		gotoRowCol(30 , 50+i);
		SetClr(15, 0);
		cout << c;
	}

	for (int i = 0; i < 5; i++)
	{
		gotoRowCol(30, 50 - i);
		SetClr(15, 0);
		cout << c;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

																//ISLEGALFOOD SINGLE
bool IsLegalFood(Position P, Snake S)
{
	for (int i = 0; i < S.size; i++)
	{
		if (S.Sp[i].ri == P.ri && S.Sp[i].ci == P.ci)
		{
			return false;
		}
	}
	return true;
}
bool IsLegalFoodH(Position P, Snake S)
{
	for (int i = 0; i < S.size; i++)
	{
		if (S.Sp[i].ri == P.ri && S.Sp[i].ci == P.ci)
		{
			return false;
		}
	}

	if (P.ci == 20 && P.ri >= 7 && P.ri <= 17)
	{
		return false;
	}

	else if (P.ci == 80 && P.ri >= 7 && P.ri <= 17)
	{
		return false;
	}

	else if (P.ci == 80 && P.ri >= 43 && P.ri <= 53)
	{
		return false;
	}

	else if (P.ci == 20 && P.ri >= 43 && P.ri <= 53)
	{
		return false;
	}

	else if (P.ci >= 45 && P.ci <= 55 && P.ri == 30)
	{
		return false;
	}
	else if (P.ri >= 25 && P.ri <= 35 && P.ci == 50)
	{
		return false;
	}
	return true;
}
void GenerateFood(Food& F, Snake& S, int height, int width)
{
	do
	{
		F.Fp.ri = rand() % 60;
		if (F.Fp.ri == 0)
		{
			F.Fp.ri = 1;
		}
		if (F.Fp.ri == height - 1)
		{
			F.Fp.ri = height - 2;
		}
		F.Fp.ci = rand() % 100;
		if (F.Fp.ci == 0)
		{
			F.Fp.ci = 1;
		}
		if (F.Fp.ci == width - 1)
		{
			F.Fp.ci = width - 2;
		}
	} while (!IsLegalFood(F.Fp, S));




}
void GenerateFoodSH(Food& F, Snake& S, int height, int width)
{
	do
	{
		F.Fp.ri = rand() % 60;
		if (F.Fp.ri == 0)
		{
			F.Fp.ri = 1;
		}
		if (F.Fp.ri == height - 1)
		{
			F.Fp.ri = height - 2;
		}
		F.Fp.ci = rand() % 100;
		if (F.Fp.ci == 0)
		{
			F.Fp.ci = 1;
		}
		if (F.Fp.ci == width - 1)
		{
			F.Fp.ci = width - 2;
		}
	} while (!IsLegalFoodH(F.Fp, S));




}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
																// ISLEGALFOOD MULTIPLE

bool FoodMultipleCheck(Position P, Snake* S,int NOS)
{
	for (int j = 0; j < NOS; j++)
	{
		for (int i = 0; i < S[j].size; i++)
		{
			if (S[j].Sp[i].ri == P.ri && S[j].Sp[i].ci == P.ci)
			{
				return false;
			}
		}
	}
	return true;

}
bool FoodMultipleCheckH(Position P, Snake* S, int NOS)
{
	for (int j = 0; j < NOS; j++)
	{
		for (int i = 0; i < S[j].size; i++)
		{
			if (S[j].Sp[i].ri == P.ri && S[j].Sp[i].ci == P.ci)
			{
				return false;
			}
		}
	}
	if (P.ci == 20 && P.ri >= 7 && P.ri <= 17)
	{
		return false;
	}

	else if (P.ci == 80 && P.ri >= 7 && P.ri <= 17)
	{
		return false;
	}

	else if (P.ci == 80 && P.ri >= 43 && P.ri <= 53)
	{
		return false;
	}

	else if (P.ci == 20 && P.ri >= 43 && P.ri <= 53)
	{
		return false;
	}

	else if (P.ci >= 45 && P.ci <= 55 && P.ri == 30)
	{
		return false;
	}
	else if (P.ri >= 25 && P.ri <= 35 && P.ci == 50)
	{
		return false;
	}
	return true;
}
void FoodMultipleSnake(Food &F, Snake* &S,int height,int width, int NOS)
{
	do
	{
		F.Fp.ri = rand() % 60;
		if (F.Fp.ri == 0)
		{
			F.Fp.ri = 1;
		}
		if (F.Fp.ri == height - 1)
		{
			F.Fp.ri = height - 2;
		}
		F.Fp.ci = rand() % 100;
		if (F.Fp.ci == 0)
		{
			F.Fp.ci = 1;
		}
		if (F.Fp.ci == width - 1)
		{
			F.Fp.ci = width - 2;
		}
	} while (!FoodMultipleCheck(F.Fp, S, NOS));
}
void FoodMultipleSnakeMH(Food &F, Snake* &S, int height, int width, int NOS)
{
	do
	{
		F.Fp.ri = rand() % 60;
		if (F.Fp.ri == 0)
		{
			F.Fp.ri = 1;
		}
		if (F.Fp.ri == height - 1)
		{
			F.Fp.ri = height - 2;
		}
		F.Fp.ci = rand() % 100;
		if (F.Fp.ci == 0)
		{
			F.Fp.ci = 1;
		}
		if (F.Fp.ci == width - 1)
		{
			F.Fp.ci = width - 2;
		}
	} while (!FoodMultipleCheckH(F.Fp, S, NOS));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
																//BONUSFOOD SINGLE

bool IsLegalBonus(Position P, Snake S,Food F)
{
	if (F.Fp.ri == P.ri && F.Fp.ci == P.ci)
	{
		return false;
	}
	for (int i = 0; i < S.size; i++)
	{
		if (S.Sp[i].ri == P.ri && S.Sp[i].ci == P.ci)
		{
			return false;
		}
	}

	return true;
}
bool IsLegalBonusH(Position P, Snake S, Food F)
{
	if (F.Fp.ri == P.ri && F.Fp.ci == P.ci)
	{
		return false;
	}

	for (int i = 0; i < S.size; i++)
	{
		if (S.Sp[i].ri == P.ri && S.Sp[i].ci == P.ci)
		{
			return false;
		}
	}

	if (P.ci == 20 && P.ri >= 7 && P.ri <= 17)
	{
		return false;
	}

	else if (P.ci == 80 && P.ri >= 7 && P.ri <= 17)
	{
		return false;
	}

	else if (P.ci == 80 && P.ri >= 43 && P.ri <= 53)
	{
		return false;
	}

	else if (P.ci == 20 && P.ri >= 43 && P.ri <= 53)
	{
		return false;
	}

	else if (P.ci >= 45 && P.ci <= 55 && P.ri == 30)
	{
		return false;
	}
	else if (P.ri >= 25 && P.ri <= 35 && P.ci == 50)
	{
		return false;
	}
	return true;
}
void GenerateBonusFood(Food &B, Snake &S,Food F, int height, int width)
{
	do
	{
		B.Fp.ri = rand() % 60;
		if (B.Fp.ri == 0)
		{
			B.Fp.ri = 1;
		}
		if (B.Fp.ri == height - 1)
		{
			B.Fp.ri = height - 2;
		}
		B.Fp.ci = rand() % 100;
		if (B.Fp.ci == 0)
		{
			B.Fp.ci = 1;
		}
		if (B.Fp.ci == width - 1)
		{
			B.Fp.ci = width - 2;
		}
	} while (!IsLegalBonus(B.Fp, S,F));
}
void GenerateBonusFoodSH(Food& B, Snake& S, Food F, int height, int width)
{
	do
	{
		B.Fp.ri = rand() % 60;
		if (B.Fp.ri == 0)
		{
			B.Fp.ri = 1;
		}
		if (B.Fp.ri == height - 1)
		{
			B.Fp.ri = height - 2;
		}
		B.Fp.ci = rand() % 100;
		if (B.Fp.ci == 0)
		{
			B.Fp.ci = 1;
		}
		if (B.Fp.ci == width - 1)
		{
			B.Fp.ci = width - 2;
		}
	} while (!IsLegalBonusH(B.Fp, S, F));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
																//BONUSFOOD MULTIPLE


bool BonusMultipleCheck(Position P, Snake* S, int NOS,Food F)
{
	if (F.Fp.ri == P.ri && F.Fp.ci == P.ci)
	{
		return false;
	}

	for (int j = 0; j < NOS; j++)
	{
		for (int i = 0; i < S[j].size; i++)
		{
			if (S[j].Sp[i].ri == P.ri && S[j].Sp[i].ci == P.ci)
			{
				return false;
			}
		}
	}
	return true;
}
bool BonusMultipleCheckH(Position P, Snake* S, int NOS, Food F)
{

	if (F.Fp.ri == P.ri && F.Fp.ci == P.ci)
	{
		return false;
	}

	for (int j = 0; j < NOS; j++)
	{
		for (int i = 0; i < S[j].size; i++)
		{
			if (S[j].Sp[i].ri == P.ri && S[j].Sp[i].ci == P.ci)
			{
				return false;
			}
		}
	}

	if (P.ci == 20 && P.ri >= 7 && P.ri <= 17)
	{
		return false;
	}

	else if (P.ci == 80 && P.ri >= 7 && P.ri <= 17)
	{
		return false;
	}

	else if (P.ci == 80 && P.ri >= 43 && P.ri <= 53)
	{
		return false;
	}

	else if (P.ci == 20 && P.ri >= 43 && P.ri <= 53)
	{
		return false;
	}

	else if (P.ci >= 45 && P.ci <= 55 && P.ri == 30)
	{
		return false;
	}
	else if (P.ri >= 25 && P.ri <= 35 && P.ci == 50)
	{
		return false;
	}
	return true;
}
void BonusMultipleSnake(Food& B,Food& F, Snake*& S, int height, int width, int NOS)
{
	do
	{
		B.Fp.ri = rand() % 60;
		if (B.Fp.ri == 0)
		{
			B.Fp.ri = 1;
		}
		if (B.Fp.ri == height - 1)
		{
			B.Fp.ri = height - 2;
		}
		B.Fp.ci = rand() % 100;
		if (B.Fp.ci == 0)
		{
			B.Fp.ci = 1;
		}
		if (B.Fp.ci == width - 1)
		{
			B.Fp.ci = width - 2;
		}
	} while (!BonusMultipleCheck(B.Fp, S, NOS,F));
}
void BonusMultipleSnakeMH(Food& B, Food& F, Snake*& S, int height, int width, int NOS)
{
	do
	{
		B.Fp.ri = rand() % 60;
		if (B.Fp.ri == 0)
		{
			B.Fp.ri = 1;
		}
		if (B.Fp.ri == height - 1)
		{
			B.Fp.ri = height - 2;
		}
		B.Fp.ci = rand() % 100;
		if (B.Fp.ci == 0)
		{
			B.Fp.ci = 1;
		}
		if (B.Fp.ci == width - 1)
		{
			B.Fp.ci = width - 2;
		}
	} while (!BonusMultipleCheckH(B.Fp, S, NOS, F));
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void DisplayFood(Food F)
{
	char c = -37;
	gotoRowCol(F.Fp.ri, F.Fp.ci);
	SetClr(9, 0);
	cout << c;
}
void DisplayBonus(Food B)
{
	char c = -37;
	gotoRowCol(B.Fp.ri, B.Fp.ci);
	SetClr(10, 0);
	cout << 'O';
}
void RemoveBonus(Food B)
{
	char c = -37;
	gotoRowCol(B.Fp.ri, B.Fp.ci);
	SetClr(15, 0);
	cout << ' ';
}
bool IsFoodEaten(Food F, Snake S)
{
	if (S.Sp[0].ri == F.Fp.ri && S.Sp[0].ci == F.Fp.ci)
	{
		PlaySound(TEXT("foodeating.wav"), NULL, SND_ASYNC);
		return true;
	}
	return false;
}
bool IsBonusEaten(Food B, Snake S)
{
	if (S.Sp[0].ri == B.Fp.ri && S.Sp[0].ci == B.Fp.ci)
	{
		PlaySound(TEXT("foodeating.wav"), NULL, SND_ASYNC);
		return true;
	}
	return false;
}
void ExpandSnake(Snake& S)
{
	Position* Sp2;
	Sp2 = new Position[S.size + 1]{};
	for (int i = 0; i < S.size; i++)
	{
		Sp2[i].ri = S.Sp[i].ri;
		Sp2[i].ci = S.Sp[i].ci;
	}

	Sp2[S.size].ri = S.Sp[S.size - 1].ri;
	Sp2[S.size].ci = S.Sp[S.size - 1].ci - 1;
	S.size++;
	delete[] S.Sp;
	S.Sp = Sp2;
	Sp2 = nullptr;
}
void ExpandSnakeBonus(Snake& S)
{
	Position* Sp2;
	Sp2 = new Position[S.size + 2]{};
	for (int i = 0; i < S.size; i++)
	{
		Sp2[i].ri = S.Sp[i].ri;
		Sp2[i].ci = S.Sp[i].ci;
	}

	Sp2[S.size].ri = S.Sp[S.size - 1].ri;
	Sp2[S.size].ci = S.Sp[S.size - 1].ci - 1;

	Sp2[S.size+1].ri = S.Sp[S.size].ri;
	Sp2[S.size+1].ci = S.Sp[S.size].ci - 1;
	S.size+=2;
	delete[] S.Sp;
	S.Sp = Sp2;
	Sp2 = nullptr;
}
bool IsKill(Snake S)
{
	
	for (int i = 1; i < S.size; i++)
	{
		if (S.Sp[0].ri == S.Sp[i].ri && S.Sp[0].ci == S.Sp[i].ci)
		{
			PlaySound(TEXT("end.wav"), NULL, SND_ASYNC);
			return true;
		}
	}
	return false;
}
bool IsSnakeKill(Snake* S)
{
	for (int i = 0; i < S[0].size; i++)
	{
		for (int j = 0; j < S[1].size; j++)
		{
			if (S[0].Sp[i].ri == S[1].Sp[j].ri && S[0].Sp[i].ci == S[1].Sp[j].ci)
			{
				PlaySound(TEXT("end.wav"), NULL, SND_ASYNC);
				return true;
			}
		}
	}
	return false;
}
bool IsSnakeKillM3(Snake* S)
{
	for (int i = 0; i < S[0].size; i++)
	{
		for (int j = 0; j < S[1].size; j++)
		{
			if (S[0].Sp[i].ri == S[1].Sp[j].ri && S[0].Sp[i].ci == S[1].Sp[j].ci)
			{
				PlaySound(TEXT("end.wav"), NULL, SND_ASYNC);
				return true;
			}
		}
	}

	for (int i = 0; i < S[0].size; i++)
	{
		for (int j = 0; j < S[2].size; j++)
		{
			if (S[0].Sp[i].ri == S[2].Sp[j].ri && S[0].Sp[i].ci == S[2].Sp[j].ci)
			{
				PlaySound(TEXT("end.wav"), NULL, SND_ASYNC);
				return true;
			}
		}
	}

	for (int i = 0; i < S[2].size; i++)
	{
		for (int j = 0; j < S[1].size; j++)
		{
			if (S[2].Sp[i].ri == S[1].Sp[j].ri && S[2].Sp[i].ci == S[1].Sp[j].ci)
			{
				PlaySound(TEXT("end.wav"), NULL, SND_ASYNC);
				return true;
			}
		}
	}

	return false;
}
bool IsSnakeKillM4(Snake* S)
{
	for (int i = 0; i < S[0].size; i++)
	{
		for (int j = 0; j < S[1].size; j++)
		{
			if (S[0].Sp[i].ri == S[1].Sp[j].ri && S[0].Sp[i].ci == S[1].Sp[j].ci)
			{
				PlaySound(TEXT("end.wav"), NULL, SND_ASYNC);
				return true;
			}
		}
	}

	for (int i = 0; i < S[0].size; i++)
	{
		for (int j = 0; j < S[2].size; j++)
		{
			if (S[0].Sp[i].ri == S[2].Sp[j].ri && S[0].Sp[i].ci == S[2].Sp[j].ci)
			{
				PlaySound(TEXT("end.wav"), NULL, SND_ASYNC);
				return true;
			}
		}
	}
	for (int i = 0; i < S[0].size; i++)
	{
		for (int j = 0; j < S[3].size; j++)
		{
			if (S[0].Sp[i].ri == S[3].Sp[j].ri && S[0].Sp[i].ci == S[3].Sp[j].ci)
			{
				PlaySound(TEXT("end.wav"), NULL, SND_ASYNC);
				return true;
			}
		}
	}

	for (int i = 0; i < S[1].size; i++)
	{
		for (int j = 0; j < S[2].size; j++)
		{
			if (S[1].Sp[i].ri == S[2].Sp[j].ri && S[1].Sp[i].ci == S[2].Sp[j].ci)
			{
				PlaySound(TEXT("end.wav"), NULL, SND_ASYNC);
				return true;
			}
		}
	}

	for (int i = 0; i < S[1].size; i++)
	{
		for (int j = 0; j < S[3].size; j++)
		{
			if (S[1].Sp[i].ri == S[3].Sp[j].ri && S[1].Sp[i].ci == S[3].Sp[j].ci)
			{
				PlaySound(TEXT("end.wav"), NULL, SND_ASYNC);
				return true;
			}
		}
	}
	for (int i = 0; i < S[2].size; i++)
	{
		for (int j = 0; j < S[3].size; j++)
		{
			if (S[2].Sp[i].ri == S[3].Sp[j].ri && S[2].Sp[i].ci == S[3].Sp[j].ci)
			{
				PlaySound(TEXT("end.wav"), NULL, SND_ASYNC);
				return true;
			}
		}
	}

	return false;
}

void SCHAR(int r, int c)
{
	char x = -37;
	for (int i = 0; i < 6; i++)
	{
		gotoRowCol(r, c - 2 + i);
		SetClr(4, 0);
		cout << x;

	}
	for (int i = 0; i < 5; i++)
	{
		gotoRowCol(r + i, c - 2);
		SetClr(4, 0);
		cout << x;
	}
	for (int i = 0; i < 6; i++)
	{
		gotoRowCol(r + 4, c - 2 + i);
		SetClr(4, 0);
		cout << x;
	}
	for (int i = 0; i < 5; i++)
	{
		gotoRowCol(r + 4 + i, c - 2 + 5);
		SetClr(4, 0);
		cout << x;
	}
	for (int i = 0; i < 5; i++)
	{
		gotoRowCol(r + 4 + 4, c + 2 - i);
		SetClr(4, 0);
		cout << x;
	}

}
void NCHAR(int r, int c)
{
	char x = -37;
	for (int i = 0; i < 9; i++)
	{
		gotoRowCol(r + i, c);
		SetClr(4, 0);
		cout << x;
	}

	for (int i = 0; i < 9; i++)
	{
		gotoRowCol(r + i, c + i);
		SetClr(4, 0);
		cout << x;
	}
	for (int i = 0; i < 9; i++)
	{
		gotoRowCol(r + i, c + 8);
		SetClr(4, 0);
		cout << x;
	}
}
void ACHAR(int r, int c)
{
	char x = -37;
	for (int i = 0; i < 9; i++)
	{
		gotoRowCol(r + i, c - i);
		SetClr(4, 0);
		cout << x;

	}
	for (int i = 0; i < 9; i++)
	{
		gotoRowCol(r + i, c + i);
		SetClr(4, 0);
		cout << x;
	}
	for (int i = 0; i < 9; i++)
	{
		gotoRowCol(r + 5, c - 4 + i);
		SetClr(4, 0);
		cout << x;
	}
}
void KCHAR(int r, int c)
{
	char x = -37;
	for (int i = 0; i < 9; i++)
	{
		gotoRowCol(r + i, c);
		SetClr(4, 0);
		cout << x;
	}
	for (int i = 0; i < 5; i++)
	{
		gotoRowCol(r + 4 - i, c + i);
		SetClr(4, 0);
		cout << x;
	}
	for (int i = 0; i < 6; i++)
	{
		gotoRowCol(r + 3 + i, c + i);
		SetClr(4, 0);
		cout << x;
	}


}
void ECHAR(int r, int c)
{
	char x = -37;
	for (int i = 0; i < 9; i++)
	{
		gotoRowCol(r + i, c);
		SetClr(4, 0);
		cout << x;
	}
	for (int i = 0; i < 5; i++)
	{
		gotoRowCol(r + 4, c + i);
		SetClr(4, 0);
		cout << x;
	}
	for (int i = 0; i < 5; i++)
	{
		gotoRowCol(r, c + i);
		SetClr(4, 0);
		cout << x;
	}
	for (int i = 0; i < 5; i++)
	{
		gotoRowCol(r + 8, c + i);
		SetClr(4, 0);
		cout << x;
	}
}

void GCHAR(int r, int c)
{
	char x = -37;
	for (int i = 0; i < 7; i++)
	{
		gotoRowCol(r, c - 3 + i);
		SetClr(2, 0);
		cout << x;
	}
	for (int i = 0; i < 9; i++)
	{
		gotoRowCol(r + i, c - 3);
		SetClr(2, 0);
		cout << x;
	}
	for (int i = 0; i < 7; i++)
	{
		gotoRowCol(r + 8, c - 3 + i);
		SetClr(2, 0);
		cout << x;
	}
	for (int i = 1; i < 4; i++)
	{
		gotoRowCol(r + 8 - i, c - 3 + 6);
		SetClr(2, 0);
		cout << x;
	}
	for (int i = 1; i < 5; i++)
	{
		gotoRowCol(r + 4, c - 3 + 7 - i);
		SetClr(2, 0);
		cout << x;
	}
}
void ACHAR2(int r, int c)
{
	char x = -37;
	for (int i = 0; i < 9; i++)
	{
		gotoRowCol(r + i, c - i);
		SetClr(2, 0);
		cout << x;

	}
	for (int i = 0; i < 9; i++)
	{
		gotoRowCol(r + i, c + i);
		SetClr(2, 0);
		cout << x;
	}
	for (int i = 0; i < 9; i++)
	{
		gotoRowCol(r + 5, c - 4 + i);
		SetClr(2, 0);
		cout << x;
	}
}
void MCHAR(int r, int c)
{
	char x = -37;
	for (int i = 0; i < 9; i++)
	{
		gotoRowCol(r + i, c);
		SetClr(2, 0);
		cout << x;
	}
	for (int i = 0; i < 5; i++)
	{
		gotoRowCol(r + i, c + 1 + i);
		SetClr(2, 0);
		cout << x;
	}
	for (int i = 1; i < 5; i++)
	{
		gotoRowCol(r + 4 - i, c + 5 + i);
		SetClr(2, 0);
		cout << x;
	}
	for (int i = 0; i < 9; i++)
	{
		gotoRowCol(r + i, c + 10);
		SetClr(2, 0);
		cout << x;
	}
}
void ECHAR2(int r, int c)
{
	char x = -37;
	for (int i = 0; i < 9; i++)
	{
		gotoRowCol(r + i, c);
		SetClr(2, 0);
		cout << x;
	}
	for (int i = 0; i < 5; i++)
	{
		gotoRowCol(r + 4, c + i);
		SetClr(2, 0);
		cout << x;
	}
	for (int i = 0; i < 5; i++)
	{
		gotoRowCol(r, c + i);
		SetClr(2, 0);
		cout << x;
	}
	for (int i = 0; i < 5; i++)
	{
		gotoRowCol(r + 8, c + i);
		SetClr(2, 0);
		cout << x;
	}
}


void GBox(int r, int c, int row, int col,int n)
{

	int R, C;
	float mr, mc;
	for (int ri = 0; ri < row; ri++)
	{
		for (int ci = 0; ci < col; ci++)
		{
			R = ri + r;
			C = ci + c;
			mr = (row / 2.0) + r;
			mc = (col / 2.0) + c;
			SetClr(2, 0);
			gotoRowCol(R, C);
			cout << char(-37);
			if ((R = mr) && (C = mc))
			{

				gotoRowCol(R, C);
				SetClr(0, 2);
				cout << n;

			}
		}
	}
}

void Box(int r, int c, int row, int col)
{

	int R, C;
	float mr, mc;
	for (int ri = 0; ri < row; ri++)
	{
		for (int ci = 0; ci < col; ci++)
		{
			R = ri + r;
			C = ci + c;
			mr = (row / 2.0) + r;
			mc = (col / 2.0) + c;
			SetClr(2, 0);
			gotoRowCol(R, C);
			cout << char(-37);
			if ((R = mr) && (C = mc))
			{

				gotoRowCol(R, C - 9);
				SetClr(0, 2);
				cout << "Single Snake Game";

			}
		}
	}
}
void Box1(int r, int c, int row, int col)
{

	int R, C;
	float mr, mc;
	for (int ri = 0; ri < row; ri++)
	{
		for (int ci = 0; ci < col; ci++)
		{
			R = ri + r;
			C = ci + c;
			mr = (row / 2.0) + r;
			mc = (col / 2.0) + c;
			SetClr(4, 0);
			gotoRowCol(R, C);
			cout << char(-37);
			if ((R = mr) && (C = mc))
			{

				gotoRowCol(R, C - 9);
				SetClr(0, 4);
				cout << "Multi Snake Game";

			}
		}
	}
}
void Box2(int r, int c, int row, int col)
{

	int R, C;
	float mr, mc;
	for (int ri = 0; ri < row; ri++)
	{
		for (int ci = 0; ci < col; ci++)
		{
			R = ri + r;
			C = ci + c;
			mr = (row / 2.0) + r;
			mc = (col / 2.0) + c;
			SetClr(9, 0);
			gotoRowCol(R, C);
			cout << char(-37);
			if ((R = mr) && (C = mc))
			{

				gotoRowCol(R, C - 5);
				SetClr(15, 9);
				cout << "2 Snakes Game";

			}
		}
	}
}
void Box3(int r, int c, int row, int col)
{

	int R, C;
	float mr, mc;
	for (int ri = 0; ri < row; ri++)
	{
		for (int ci = 0; ci < col; ci++)
		{
			R = ri + r;
			C = ci + c;
			mr = (row / 2.0) + r;
			mc = (col / 2.0) + c;
			SetClr(9, 0);
			gotoRowCol(R, C);
			cout << char(-37);
			if ((R = mr) && (C = mc))
			{

				gotoRowCol(R, C - 5);
				SetClr(15, 9);
				cout << "3 Snakes Game";

			}
		}
	}
}
void Box4(int r, int c, int row, int col)
{

	int R, C;
	float mr, mc;
	for (int ri = 0; ri < row; ri++)
	{
		for (int ci = 0; ci < col; ci++)
		{
			R = ri + r;
			C = ci + c;
			mr = (row / 2.0) + r;
			mc = (col / 2.0) + c;
			SetClr(9, 0);
			gotoRowCol(R, C);
			cout << char(-37);
			if ((R = mr) && (C = mc))
			{

				gotoRowCol(R, C - 5);
				SetClr(15, 9);
				cout << "4 Snakes Game";

			}
		}
	}
}

void Box5(int r, int c, int row, int col)
{

	int R, C;
	float mr, mc;
	for (int ri = 0; ri < row; ri++)
	{
		for (int ci = 0; ci < col; ci++)
		{
			R = ri + r;
			C = ci + c;
			mr = (row / 2.0) + r;
			mc = (col / 2.0) + c;
			SetClr(15, 0);
			gotoRowCol(R, C);
			cout << char(-37);
			if ((R = mr) && (C = mc))
			{

				gotoRowCol(R, C - 1);
				SetClr(0, 15);
				cout << "EASY";

			}
		}
	}
}
void Box6(int r, int c, int row, int col)
{

	int R, C;
	float mr, mc;
	for (int ri = 0; ri < row; ri++)
	{
		for (int ci = 0; ci < col; ci++)
		{
			R = ri + r;
			C = ci + c;
			mr = (row / 2.0) + r;
			mc = (col / 2.0) + c;
			SetClr(15, 0);
			gotoRowCol(R, C);
			cout << char(-37);
			if ((R = mr) && (C = mc))
			{

				gotoRowCol(R, C - 2);
				SetClr(0, 15);
				cout << "MEDIUM";

			}
		}
	}
}
void Box7(int r, int c, int row, int col)
{

	int R, C;
	float mr, mc;
	for (int ri = 0; ri < row; ri++)
	{
		for (int ci = 0; ci < col; ci++)
		{
			R = ri + r;
			C = ci + c;
			mr = (row / 2.0) + r;
			mc = (col / 2.0) + c;
			SetClr(15, 0);
			gotoRowCol(R, C);
			cout << char(-37);
			if ((R = mr) && (C = mc))
			{

				gotoRowCol(R, C - 1);
				SetClr(0, 15);
				cout << "HARD";

			}
		}
	}
}

bool BoundaryCheck(Snake S, int h, int w)
{
	if (S.dir == RIGHT && S.Sp[0].ci+1==w-1)
	{
		PlaySound(TEXT("end.wav"), NULL, SND_ASYNC);
		return true;
	}
	if (S.dir == LEFT && S.Sp[0].ci-1 == 0)
	{
		PlaySound(TEXT("end.wav"), NULL, SND_ASYNC);
		return true;
	}
	if (S.dir == UP && S.Sp[0].ri-1 == 0)
	{
		PlaySound(TEXT("end.wav"), NULL, SND_ASYNC);
		return true;
	}
	if (S.dir == DOWN && S.Sp[0].ri+1 == h-1)
	{
		PlaySound(TEXT("end.wav"), NULL, SND_ASYNC);
		return true;
	}
	return false;
}
bool HurdleCheck(Snake S, int h, int w)
{

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
																// RIGHT DIRECTION


	if (S.dir == RIGHT)
	{

		if (S.Sp->ci == 19)
		{
			for (int i = 1; i <= 10; i++)
			{
				if (S.Sp[0].ri == 7 + i)
				{
					return true;
				}
			}

			for (int i = 1; i <= 10; i++)
			{
				if (S.Sp[0].ri == 43 + i)
				{
					return true;
				}
			}
		}
		
		else if (S.Sp->ci == 79)
		{
			for (int i = 1; i <= 10; i++)
			{
				if (S.Sp[0].ri == 7 + i)
				{
					return true;
				}
			}

			for (int i = 1; i <= 10; i++)
			{
				if (S.Sp[0].ri == 43 + i)
				{
					return true;
				}
			}

		}

		else if (S.Sp->ci == 49)
		{
			for (int i = 0; i < 5; i++)
			{
				if (S.Sp[0].ri == 30 + i)
				{
					return true;
				}
			}

			for (int i = 0; i < 5; i++)
			{
				if (S.Sp[0].ri == 30 - i)
				{
					return true;
				}
			}
		}

		else if (S.Sp[0].ri == 30 && S.Sp[0].ci == 45)
		{
			return true;
		}

	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
																// LEFT DIRECTION
	
	else if (S.dir == LEFT)
	{

		if (S.Sp->ci == 21)
		{
			for (int i = 1; i <= 10; i++)
			{
				if (S.Sp[0].ri == 7 + i)
				{
					return true;
				}
			}

			for (int i = 1; i <= 10; i++)
			{
				if (S.Sp[0].ri == 43 + i)
				{
					return true;
				}
			}
		}
		
		else if (S.Sp->ci == 81)
		{
			for (int i = 1; i <= 10; i++)
			{
				if (S.Sp[0].ri == 7 + i)
				{
					return true;
				}
			}

			for (int i = 1; i <= 10; i++)
			{
				if (S.Sp[0].ri == 43 + i)
				{
					return true;
				}
			}
		}

		else if (S.Sp->ci == 51)
		{
			for (int i = 0; i < 5; i++)
			{
				if (S.Sp[0].ri == 30 + i)
				{
					return true;
				}
			}

			for (int i = 0; i < 5; i++)
			{
				if (S.Sp[0].ri == 30 - i)
				{
					return true;
				}
			}

		}
	
		else if (S.Sp[0].ri == 30 && S.Sp[0].ci == 55)
		{
			return true;
		}

	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

																// UP DIRECTION

	else if (S.dir == UP)
	{
		if (S.Sp->ci == 20)
		{
			if (S.Sp[0].ri - 1 == 7 + 10)
			{
				return true;
			}

			else if (S.Sp[0].ri - 1 == 43 + 10)
			{
				return true;
			}
		}

		else if (S.Sp->ci == 80)
		{
			if (S.Sp[0].ri - 1 == 7 + 10)
			{
				return true;
			}

			else if (S.Sp[0].ri - 1 == 43 + 10)
			{
				return true;
			}

		}

		else if (S.Sp->ri-1==30)
		{
			for (int i = 0; i < 5; i++)
			{
				if (S.Sp[0].ri - 1 == 30 && S.Sp[0].ci == 50 + i && S.dir == UP)
				{
					return true;
				}
			}

			for (int i = 0; i < 5; i++)
			{
				if (S.Sp[0].ri - 1 == 30 && S.Sp[0].ci == 50 - i && S.dir == UP)
				{
					return true;
				}
			}
		}
		
		else if (S.Sp[0].ri + 1 == 36 && S.Sp->ci == 20)
		{
			return true;
		}
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
																// DOWN DIRECTION

	else if (S.dir == DOWN)
	{
		if (S.Sp->ci == 20)
		{
			if (S.Sp[0].ri == 7)
			{
				return true;
			}

			else if (S.Sp[0].ri == 43)
			{
				return true;
			}
		}

		else if (S.Sp->ci == 80)
		{

			if (S.Sp[0].ri == 7)
			{
				return true;
			}


			else if (S.Sp[0].ri == 43)
			{
				return true;
			}


		}
		
		else if (S.Sp->ri + 1 == 30)
		{
			for (int i = 0; i < 5; i++)
			{
				if (S.Sp[0].ri + 1 == 30 && S.Sp[0].ci == 50 + i && S.dir == DOWN)
				{
					return true;
				}
			}

			for (int i = 0; i < 5; i++)
			{
				if (S.Sp[0].ri + 1 == 30 && S.Sp[0].ci == 50 - i && S.dir == DOWN)
				{
					return true;
				}
			}
		}
				
		else if (S.Sp[0].ri - 1 == 24 && S.Sp[0].ci == 50)
		{
			return true;
		}

		

	}



	return false;
}

void BonusInit(Food& B,Snake S,Food F,int height,int width)
{
	GenerateBonusFood(B, S,F,height, width);
}
void BonusInit2(Food& B, Snake *S, Food F, int height, int width,int NOS)
{
	BonusMultipleSnake(B, F, S, height, width,NOS);
}



int main1()
{

	int height = 60, x = 0;
	int width = 100;
	bool IsAlive = false;
	int BonusCount = 0;
	char ch = 0;
	Snake S;
	Food F;
	Food B;
	srand(time(0));
	init(S, F, height, width);
	BonusInit(B, S, F, height, width);
	DisplayFood(F);
	DrawBox(height, width);
	int t = 60;
	int tc = 0;
	gotoRowCol(14, 111);
	cout << "Time";
	gotoRowCol(14, 127);
	cout << S.Pnames << "'s Score";
	GBox(15, 105, 10, 15, t);
	GBox(15, 125, 10, 15, S.score);
	while (true)
	{

		DisplaySnake(S);
		SetClr(15, 0);
		if (_kbhit())
		{
			ch = _getch();
			if (int(ch) == -32)
			{
				ch = _getch();
				ChangeDirection(ch, S);
			}
		}

		Sleep(40);
		RemoveSnake(S);
		MoveSnake(S, height, width);
		if (IsKill(S))
		{
			system("cls");
			gotoRowCol(40, 60);
			cout << "Game Ended";
			break;
		}
		if (IsFoodEaten(F, S))
		{

			GenerateFood(F, S, height, width);
			DisplayFood(F);
			ExpandSnake(S);
			S.score++;
			SetClr(0, 2);
			gotoRowCol(20, 132);
			cout << S.score;
		}

		if (x == 120)
		{
			DisplayBonus(B);
			BonusCount = 0;
			IsAlive = true;
		}

		if (IsBonusEaten(B, S))
		{
			GenerateBonusFood(B, S, F, height, width);
			ExpandSnakeBonus(S);
			S.score += 2;
			SetClr(15, 0);
			SetClr(0, 2);
			gotoRowCol(20, 132);
			cout << S.score;
			IsAlive = false;

			BonusCount = 0;
			x = 0;
		}

		if (BonusCount == 100)
		{
			RemoveBonus(B);
			GenerateBonusFood(B, S, F, height, width);
			IsAlive = false;
			BonusCount = 0;
			x = 0;
		}
		if (IsAlive == true)
		{
			BonusCount++;
		}



		if (tc == 50)
		{
			t--;
			SetClr(0, 2);
			//GBox(15, 105, 10, 15, t);
			gotoRowCol(20, 112);
			cout << t;
			tc = 0;
		}
		if (t == 0 || S.score >= 30)
		{
			SetClr(15, 0);
			system("cls");
			gotoRowCol(40, 60);
			cout << "Game Ended";
			break;
		}
		x++;
		tc++;
	}
	return _getch();
}
int main12()
{
	int height = 60;
	int width = 100,x=0,BonusCount=0;
	char ch = 0;
	Snake S;
	Food F;
	Food B;
	bool IsAlive = false;
	srand(time(0));
	init(S, F, height, width);
	BonusInit(B, S, F, height, width);
	DisplayFood(F);
	DrawBox(height, width);
	int t = 60;
	int tc = 0;
	gotoRowCol(14, 111);
	cout << "Time";
	gotoRowCol(14, 127);
	cout << S.Pnames << "'s Score";
	GBox(15, 105, 10, 15, t);
	GBox(15, 125, 10, 15, S.score);

	while (true)
	{

		DisplaySnake(S);
		SetClr(15, 0);
		if (_kbhit())
		{
			ch = _getch();
			if (int(ch) == -32)
			{
				ch = _getch();
				ChangeDirection(ch, S);
			}
		}

		Sleep(40);
		RemoveSnake(S);
		if (BoundaryCheck(S, height, width))
		{
			system("cls");
			gotoRowCol(40, 60);
			cout << "Game Ended";
			break;
		}
		MoveSnake(S, height, width);
		if (IsKill(S))
		{
			system("cls");
			gotoRowCol(40, 60);
			cout << "Game Ended";
			break;
		}
		if (IsFoodEaten(F, S))
		{

			GenerateFood(F, S, height, width);
			DisplayFood(F);
			ExpandSnake(S);
			S.score++;
			SetClr(0,2);
			gotoRowCol(20, 132);
			cout << S.score;
		}

		if (x == 120)
		{
			DisplayBonus(B);
			BonusCount = 0;
			IsAlive = true;
		}

		if (IsBonusEaten(B, S))
		{
			GenerateBonusFood(B, S, F, height, width);
			ExpandSnakeBonus(S);
			S.score += 2;
			SetClr(0, 2);
			gotoRowCol(20, 132);
			cout << S.score;
			IsAlive = false;

			BonusCount = 0;
			x = 0;
		}

		if (BonusCount == 100)
		{
			RemoveBonus(B);
			GenerateBonusFood(B, S, F, height, width);
			IsAlive = false;
			BonusCount = 0;
			x = 0;
		}
		if (IsAlive == true)
		{
			BonusCount++;
		}
		if (tc == 50)
		{
			t--;
			SetClr(0, 2);
			//GBox(15, 105, 10, 15, t);
			gotoRowCol(20, 112);
			cout << t;
			tc = 0;
		}
		if (t == 0 || S.score >= 30)
		{
			SetClr(15, 0);
			system("cls");
			gotoRowCol(40, 60);
			cout << "Game Ended";
			break;
		}
		x++;
		tc++;
	}
	return _getch();


}
int main13()
{

	int height = 60;
	int width = 100,x=0,BonusCount=0;
	bool IsAlive = false;
	char ch = 0;
	Snake S;
	Food B;
	Food F;
	srand(time(0));
	init(S, F, height, width);
	BonusInit(B, S, F, height, width);
	DisplayFood(F);
	DrawBoxH(height, width);
	int t = 60;
	int tc = 0;
	SetClr(4, 0);
	gotoRowCol(14, 111);
	cout << "Time";
	gotoRowCol(14, 127);
	cout << S.Pnames << "'s Score";
	GBox(15, 105, 10, 15, t);
	GBox(15, 125, 10, 15, S.score);

	while (true)
	{

		DisplaySnake(S);
		SetClr(15, 0);
		if (_kbhit())
		{
			ch = _getch();
			if (int(ch) == -32)
			{
				ch = _getch();
				ChangeDirection(ch, S);
			}
		}

		Sleep(70);
		RemoveSnake(S);
		if (HurdleCheck(S, height, width))
		{
			system("cls");
			gotoRowCol(40, 60);
			PlaySound(TEXT("end.wav"), NULL, SND_ASYNC);
			cout << "Game Ended";
			break;
		}
		else if (BoundaryCheck(S, height, width))
		{
			system("cls");
			gotoRowCol(40, 60);
			cout << "Game Ended";
			break;
		}
		MoveSnake(S, height, width);
		if (IsKill(S))
		{
			system("cls");
			gotoRowCol(40, 60);
			cout << "Game Ended";
			break;
		}
		if (IsFoodEaten(F, S))
		{

			GenerateFoodSH(F, S, height, width);
			DisplayFood(F);
			ExpandSnake(S);
			S.score++;
			SetClr(0, 2);
			gotoRowCol(20, 132);
			cout << S.score;
		}

		if (x == 120)
		{
			DisplayBonus(B);
			BonusCount = 0;
			IsAlive = true;
		}

		if (IsBonusEaten(B, S))
		{
			GenerateBonusFoodSH(B, S, F, height, width);
			ExpandSnakeBonus(S);
			S.score += 2;
			SetClr(0, 2);
			gotoRowCol(20, 132);
			cout << S.score;
			IsAlive = false;

			BonusCount = 0;
			x = 0;
		}

		if (BonusCount == 100)
		{
			RemoveBonus(B);
			GenerateBonusFood(B, S, F, height, width);
			IsAlive = false;
			BonusCount = 0;
			x = 0;
		}
		if (IsAlive == true)
		{
			BonusCount++;
		}

		if (tc == 50)
		{
			t--;
			SetClr(0, 2);
			//GBox(15, 105, 10, 15, t);
			gotoRowCol(20, 112);
			cout << t;
			tc = 0;
		}
		if (t == 0 || S.score >= 30)
		{
			SetClr(15, 0);
			system("cls");
			gotoRowCol(40, 60);
			cout << "Game Ended";
			break;
		}
		x++;
		tc++;
	}
	return _getch();


}
int main2()
{
	int height = 60;
	int width = 100,x=0,BonusCount=0;
	char ch = 0;
	int NOS = 2;
	bool IsAlive = false;
	Snake* Sarray = new Snake[2];
	Food F;
	Food B;
	srand(time(0));
	initM1(Sarray[0], F, height, width);
	initM2(Sarray[1], height, width);
	BonusInit2(B, Sarray, F, height, width,NOS);
	DisplayFood(F);
	DrawBox(height, width);
	int t = 60;
	int tc = 0;
	SetClr(4, 0);
	gotoRowCol(4, 111);
	cout << "Time";
	gotoRowCol(19, 107);
	cout << Sarray[0].Pnames << "'s Score";
	gotoRowCol(34, 107);
	cout << Sarray[1].Pnames << "'s Score";

	GBox(5, 105, 10, 15, t);
	GBox(20, 105, 10, 15, Sarray[0].score);
	GBox(35, 105, 10, 15, Sarray[1].score);

	while (true)
	{
		DisplaySnake(Sarray[0]);
		DisplaySnakeM2(Sarray[1]);
		SetClr(15, 0);
		if (_kbhit())
		{
			ch = _getch();
			if (int(ch) == -32)
			{
				ch = _getch();
				ChangeDirection(ch, Sarray[0]);
			}
			else if (int(ch) == 119 || int(ch) == 100 || int(ch) == 115 || int(ch) == 97)
			{
				ChangeDirection(ch, Sarray[1]);
			}
		}

		Sleep(40);
		RemoveSnake(Sarray[0]);
		RemoveSnake(Sarray[1]);
		MoveSnake(Sarray[0], height, width);
		if (IsKill(Sarray[0]))
		{
			system("cls");
			gotoRowCol(40, 60);
			cout << "Game Ended";
			break;
		}
		MoveSnake(Sarray[1], height, width);
		if (IsKill(Sarray[1]))
		{
			system("cls");
			gotoRowCol(40, 60);
			cout << "Game Ended";
			break;
		}
		if (IsSnakeKill(Sarray))
		{
			system("cls");
			gotoRowCol(40, 60);
			cout << "Game Ended";
			break;
		}

		if (IsFoodEaten(F, Sarray[0]))
		{
			FoodMultipleSnake(F, Sarray, height, width,NOS);
			DisplayFood(F);
			ExpandSnake(Sarray[0]);
			Sarray[0].score++;
			SetClr(0, 2);
			gotoRowCol(25, 112);
			cout << Sarray[0].score;
		}
		else if (IsFoodEaten(F, Sarray[1]))
		{
			FoodMultipleSnake(F, Sarray, height, width, NOS);
			DisplayFood(F);
			ExpandSnake(Sarray[1]);
			Sarray[1].score++;
			SetClr(0, 2);
			gotoRowCol(40, 112);
			cout << Sarray[1].score;
		}

		if (x == 120)
		{
			DisplayBonus(B);
			BonusCount = 0;
			IsAlive = true;
		}

		if (IsBonusEaten(B, Sarray[0]))
		{
			BonusMultipleSnake(B,  F, Sarray, height, width,NOS);
			ExpandSnakeBonus(Sarray[0]);
			Sarray[0].score += 2;
			SetClr(0, 2);
			gotoRowCol(25, 112);
			cout << Sarray[0].score;
			IsAlive = false;

			BonusCount = 0;
			x = 0;
		}
		else if (IsBonusEaten(B, Sarray[1]))
		{
			BonusMultipleSnake(B, F, Sarray, height, width, NOS);
			ExpandSnakeBonus(Sarray[1]);
			Sarray[1].score += 2;
			SetClr(0, 2);
			gotoRowCol(40, 112);
			cout << Sarray[1].score;
			IsAlive = false;

			BonusCount = 0;
			x = 0;
		}

		if (BonusCount == 100)
		{
			RemoveBonus(B);
			BonusMultipleSnake(B, F, Sarray, height, width, NOS);
			IsAlive = false;
			BonusCount = 0;
			x = 0;
		}
		if (IsAlive == true)
		{
			BonusCount++;
		}

		if (tc == 50)
		{
			t--;
			SetClr(0, 2);
			gotoRowCol(10, 112);
			//GBox(5, 105, 10, 15, t);
			cout << t;
			tc = 0;
		}
		if (t == 0 || Sarray[0].score >= 15 || Sarray[1].score >= 15)
		{
			if (Sarray[0].score >= 15)
			{
				SetClr(15, 0);
				system("cls");
				gotoRowCol(39, 60);
				cout << Sarray[0].Pnames<<" Win the game!!";
				gotoRowCol(41, 63);
				cout << "Game Ended";
				break;
			}
			else if(Sarray[1].score >= 15)
			{
				SetClr(15, 0);
				system("cls");
				gotoRowCol(39, 60);
				cout << Sarray[1].Pnames << " Win the game!!";
				gotoRowCol(41, 63);
				cout << "Game Ended";
				break;
			}
			
		}
		x++;
		tc++;
	}
	return _getch();
}
int main22()
{

	int height = 60;
	int width = 100,x=0,BonusCount=0;
	char ch = 0;
	int NOS = 2;
	Snake* Sarray = new Snake[2];
	Food F;
	Food B;
	bool IsAlive = false;
	srand(time(0));
	initM1(Sarray[0], F, height, width);
	initM2(Sarray[1], height, width);
	BonusInit2(B, Sarray, F, height, width, NOS);
	DisplayFood(F);
	DrawBox(height, width);
	int t = 60;
	int tc = 0;
	SetClr(4, 0);
	gotoRowCol(4, 111);
	cout << "Time";
	gotoRowCol(19, 107);
	cout << Sarray[0].Pnames << "'s Score";
	gotoRowCol(34, 107);
	cout << Sarray[1].Pnames << "'s Score";

	GBox(5, 105, 10, 15, t);
	GBox(20, 105, 10, 15, Sarray[0].score);
	GBox(35, 105, 10, 15, Sarray[1].score);
	while (true)
	{
		DisplaySnake(Sarray[0]);
		DisplaySnakeM2(Sarray[1]);
		SetClr(15, 0);
		if (_kbhit())
		{
			ch = _getch();
			if (int(ch) == -32)
			{
				ch = _getch();
				ChangeDirection(ch, Sarray[0]);
			}
			else if (int(ch) == 119 || int(ch) == 100 || int(ch) == 115 || int(ch) == 97)
			{
				ChangeDirection(ch, Sarray[1]);
			}
		}

		Sleep(70);
		RemoveSnake(Sarray[0]);
		if (BoundaryCheck(Sarray[0], height, width))
		{
			system("cls");
			gotoRowCol(40, 60);
			cout << "Game Ended";
			break;
		}
		RemoveSnake(Sarray[1]);
		if (BoundaryCheck(Sarray[1], height, width))
		{
			system("cls");
			gotoRowCol(40, 60);
			cout << "Game Ended";
			break;
		}
		MoveSnake(Sarray[0], height, width);
		if (IsKill(Sarray[0]))
		{
			system("cls");
			gotoRowCol(40, 60);
			cout << "Game Ended";
			break;
		}
		MoveSnake(Sarray[1], height, width);
		if (IsKill(Sarray[1]))
		{
			system("cls");
			gotoRowCol(40, 60);
			cout << "Game Ended";
			break;
		}
		if (IsSnakeKill(Sarray))
		{
			system("cls");
			gotoRowCol(40, 60);
			cout << "Game Ended";
			break;
		}

		if (IsFoodEaten(F, Sarray[0]))
		{
			FoodMultipleSnake(F, Sarray, height, width, NOS);
			DisplayFood(F);
			ExpandSnake(Sarray[0]);
			Sarray[0].score++;
			SetClr(0, 2);
			gotoRowCol(25, 112);
			cout << Sarray[0].score;
		}
		else if (IsFoodEaten(F, Sarray[1]))
		{
			FoodMultipleSnake(F, Sarray, height, width, NOS);
			DisplayFood(F);
			ExpandSnake(Sarray[1]);
			Sarray[1].score++;
			SetClr(0, 2);
			gotoRowCol(40, 112);
			cout << Sarray[1].score;
		}

		if (x == 120)
		{
			DisplayBonus(B);
			BonusCount = 0;
			IsAlive = true;
		}

		if (IsBonusEaten(B, Sarray[0]))
		{
			BonusMultipleSnake(B, F, Sarray, height, width, NOS);
			ExpandSnakeBonus(Sarray[0]);
			Sarray[0].score += 2;
			SetClr(0, 2);
			gotoRowCol(25, 112);
			cout << Sarray[0].score;
			IsAlive = false;

			BonusCount = 0;
			x = 0;
		}
		else if (IsBonusEaten(B, Sarray[1]))
		{
			BonusMultipleSnake(B, F, Sarray, height, width, NOS);
			ExpandSnakeBonus(Sarray[1]);
			Sarray[1].score += 2;
			SetClr(0, 2);
			gotoRowCol(40, 112);
			cout << Sarray[1].score;
			IsAlive = false;

			BonusCount = 0;
			x = 0;
		}

		if (BonusCount == 100)
		{
			RemoveBonus(B);
			BonusMultipleSnake(B, F, Sarray, height, width, NOS);
			IsAlive = false;
			BonusCount = 0;
			x = 0;
		}
		if (IsAlive == true)
		{
			BonusCount++;
		}

		if (tc == 50)
		{
			t--;
			SetClr(0, 2);
			gotoRowCol(10, 112);
			//GBox(5, 105, 10, 15, t);
			cout << t;
			tc = 0;
		}
		if (t == 0 || Sarray[0].score >= 1 || Sarray[1].score >= 1)
		{
			if (Sarray[0].score >= 1)
			{
				SetClr(15, 0);
				system("cls");
				gotoRowCol(39, 60);
				cout << Sarray[0].Pnames << " Win the game!!";
				gotoRowCol(41, 63);
				cout << "Game Ended";
				break;
			}
			else if(Sarray[1].score >= 1)
			{
				SetClr(15, 0);
				system("cls");
				gotoRowCol(39, 60);
				cout << Sarray[1].Pnames << " Win the game!!";
				gotoRowCol(41, 63);
				cout << "Game Ended";
				break;
			}

		}
		x++;
		tc++;
	}
	return _getch();

}
int main23()
{


	int height = 60;
	int width = 100,x=0,BonusCount=0;
	char ch = 0;
	int NOS=2;
	Snake* Sarray = new Snake[2];
	Food F;
	Food B;
	bool IsAlive = true;
	srand(time(0));
	initM1(Sarray[0], F, height, width);
	initM2(Sarray[1], height, width);
	BonusInit2(B, Sarray, F, height, width, NOS);
	DisplayFood(F);
	DrawBoxH(height, width);
	int t = 60;
	int tc = 0;
	SetClr(4, 0);
	gotoRowCol(4, 111);
	cout << "Time";
	gotoRowCol(19, 107);
	cout << Sarray[0].Pnames << "'s Score";
	gotoRowCol(34, 107);
	cout << Sarray[1].Pnames << "'s Score";

	GBox(5, 105, 10, 15, t);
	GBox(20, 105, 10, 15, Sarray[0].score);
	GBox(35, 105, 10, 15, Sarray[1].score);

	while (true)
	{
		DisplaySnake(Sarray[0]);
		DisplaySnakeM2(Sarray[1]);
		SetClr(15, 0);
		if (_kbhit())
		{
			ch = _getch();
			if (int(ch) == -32)
			{
				ch = _getch();
				ChangeDirection(ch, Sarray[0]);
			}
			else if (int(ch) == 119 || int(ch) == 100 || int(ch) == 115 || int(ch) == 97)
			{
				ChangeDirection(ch, Sarray[1]);
			}
		}

		Sleep(70);
		RemoveSnake(Sarray[0]);
		if (HurdleCheck(Sarray[0], height, width))
		{
			system("cls");
			gotoRowCol(40, 60);
			PlaySound(TEXT("end.wav"), NULL, SND_ASYNC);
			cout << "Game Ended";
			break;
		}
		else if (BoundaryCheck(Sarray[0], height, width))
		{
			system("cls");
			gotoRowCol(40, 60);
			cout << "Game Ended";
			break;
		}
		RemoveSnake(Sarray[1]);
		if (HurdleCheck(Sarray[1], height, width))
		{
			system("cls");
			gotoRowCol(40, 60);
			PlaySound(TEXT("end.wav"), NULL, SND_ASYNC);
			cout << "Game Ended";
			break;
		}
		else if (BoundaryCheck(Sarray[1], height, width))
		{
			system("cls");
			gotoRowCol(40, 60);
			cout << "Game Ended";
			break;
		}
		MoveSnake(Sarray[0], height, width);
		if (IsKill(Sarray[0]))
		{
			system("cls");
			gotoRowCol(40, 60);
			cout << "Game Ended";
			break;
		}
		MoveSnake(Sarray[1], height, width);
		if (IsKill(Sarray[1]))
		{
			system("cls");
			gotoRowCol(40, 60);
			cout << "Game Ended";
			break;
		}
		if (IsSnakeKill(Sarray))
		{
			system("cls");
			gotoRowCol(40, 60);
			cout << "Game Ended";
			break;
		}
		if (IsFoodEaten(F, Sarray[0]))
		{
			FoodMultipleSnakeMH(F, Sarray,height,width,NOS);
			DisplayFood(F);
			ExpandSnake(Sarray[0]);
			Sarray[0].score++;
			SetClr(0, 2);
			gotoRowCol(25, 112);
			cout << Sarray[0].score;
		}
		else if (IsFoodEaten(F, Sarray[1]))
		{
			FoodMultipleSnakeMH(F, Sarray, height, width, NOS);
			DisplayFood(F);
			ExpandSnake(Sarray[1]);
			Sarray[1].score++;
			SetClr(0, 2);
			gotoRowCol(40, 112);
			cout << Sarray[1].score;
		}

		if (x == 120)
		{
			DisplayBonus(B);
			BonusCount = 0;
			IsAlive = true;
		}

		if (IsBonusEaten(B, Sarray[0]))
		{
			BonusMultipleSnakeMH(B, F, Sarray, height, width, NOS);
			ExpandSnakeBonus(Sarray[0]);
			Sarray[0].score += 2;
			SetClr(0, 2);
			gotoRowCol(25, 112);
			cout << Sarray[0].score;
			IsAlive = false;

			BonusCount = 0;
			x = 0;
		}
		else if (IsBonusEaten(B, Sarray[1]))
		{
			BonusMultipleSnakeMH(B, F, Sarray, height, width, NOS);
			ExpandSnakeBonus(Sarray[1]);
			Sarray[1].score += 2;
			SetClr(0, 2);
			gotoRowCol(40, 112);
			cout << Sarray[1].score;
			IsAlive = false;

			BonusCount = 0;
			x = 0;
		}

		if (BonusCount == 100)
		{
			RemoveBonus(B);
			BonusMultipleSnakeMH(B, F, Sarray, height, width, NOS);
			IsAlive = false;
			BonusCount = 0;
			x = 0;
		}
		if (IsAlive == true)
		{
			BonusCount++;
		}

		if (tc == 50)
		{
			t--;
			SetClr(0, 2);
			gotoRowCol(10, 112);
			//GBox(5, 105, 10, 15, t);
			cout << t;
			tc = 0;
		}
		if (t == 0 || Sarray[0].score >= 15 || Sarray[1].score >= 15)
		{
			if (Sarray[0].score >= 15)
			{
				SetClr(15, 0);
				system("cls");
				gotoRowCol(39, 60);
				cout << Sarray[0].Pnames << " Win the game!!";
				gotoRowCol(41, 63);
				cout << "Game Ended";
				break;
			}
			else if (Sarray[1].score >= 15)
			{
				SetClr(15, 0);
				system("cls");
				gotoRowCol(39, 60);
				cout << Sarray[1].Pnames << " Win the game!!";
				gotoRowCol(41, 63);
				cout << "Game Ended";
				break;
			}

		}
		x++;
		tc++;
	}

	return _getch();
}
int main3()
{

	int height = 60;
	int width = 100;
	char ch = 0;
	int NOS = 3;
	Snake* Sarray = new Snake[3];
	Food F;
	srand(time(0));
	initM1(Sarray[0], F, height, width);
	initM2(Sarray[1], height, width);
	initM3(Sarray[2], height, width);
	DisplayFood(F);
	DrawBox(60, 100);
	Food B;
	int x = 0, BonusCount = 0;
	BonusInit2(B, Sarray, F, height, width, NOS);
	bool IsAlive = false;
	int t = 60;
	int tc = 0;
	SetClr(4, 0);
	gotoRowCol(4, 111);
	cout << "Time";
	gotoRowCol(19, 107);
	cout << Sarray[0].Pnames << "'s Score";
	gotoRowCol(34, 107);
	cout << Sarray[1].Pnames << "'s Score";
	gotoRowCol(49, 107);
	cout << Sarray[2].Pnames << "'s Score";

	GBox(5, 105, 10, 15, t);
	GBox(20, 105, 10, 15, Sarray[0].score);
	GBox(35, 105, 10, 15, Sarray[1].score);
	GBox(50, 105, 10, 15, Sarray[2].score);
	while (true)
	{
		DisplaySnake(Sarray[0]);
		DisplaySnakeM2(Sarray[1]);
		DisplaySnakeM3(Sarray[2]);
		SetClr(15, 0);
		if (_kbhit())
		{
			ch = _getch();
			if (int(ch) == -32)
			{
				ch = _getch();
				ChangeDirection(ch, Sarray[0]);
			}
			else if (int(ch) == 119 || int(ch) == 100 || int(ch) == 115 || int(ch) == 97)
			{
				ChangeDirection(ch, Sarray[1]);
			}
			else if (int(ch) == 56 || int(ch) == 54 || int(ch) == 52 || int(ch) == 53)
			{
				ChangeDirection(ch, Sarray[2]);
			}
		}
		Sleep(40);
		RemoveSnake(Sarray[0]);
		RemoveSnake(Sarray[1]);
		RemoveSnake(Sarray[2]);
		MoveSnake(Sarray[0], height, width);
		if (IsKill(Sarray[0]))
		{
			system("cls");
			gotoRowCol(40, 60);
			cout << "Game Ended";
			break;
		}
		MoveSnake(Sarray[1], height, width);
		if (IsKill(Sarray[1]))
		{
			system("cls");
			gotoRowCol(40, 60);
			cout << "Game Ended";
			break;
		}
		MoveSnake(Sarray[2], height, width);
		if (IsKill(Sarray[2]))
		{
			system("cls");
			gotoRowCol(40, 60);
			cout << "Game Ended";
			break;
		}
		if (IsSnakeKillM3(Sarray))
		{
			system("cls");
			gotoRowCol(40, 60);
			cout << "Game Ended";
			break;
		}

		if (IsFoodEaten(F, Sarray[0]))
		{
			FoodMultipleSnake(F, Sarray, height, width, NOS);
			DisplayFood(F);
			ExpandSnake(Sarray[0]);
			Sarray[0].score++;
			SetClr(0, 2);
			gotoRowCol(25, 112);
			cout << Sarray[0].score;
		}
		else if (IsFoodEaten(F, Sarray[1]))
		{
			FoodMultipleSnake(F, Sarray, height, width, NOS);
			DisplayFood(F);
			ExpandSnake(Sarray[1]);
			Sarray[1].score++;
			SetClr(0, 2);
			gotoRowCol(40, 112);
			cout << Sarray[1].score;
		}
		else if (IsFoodEaten(F, Sarray[2]))
		{
			FoodMultipleSnake(F, Sarray, height, width, NOS);
			DisplayFood(F);
			ExpandSnake(Sarray[2]);
			Sarray[2].score++;
			SetClr(0, 2);
			gotoRowCol(55, 112);
			cout << Sarray[2].score;
		}

		if (x == 120)
		{
			DisplayBonus(B);
			BonusCount = 0;
			IsAlive = true;
		}

		if (IsBonusEaten(B, Sarray[0]))
		{
			BonusMultipleSnake(B, F, Sarray, height, width, NOS);
			ExpandSnakeBonus(Sarray[0]);
			Sarray[0].score += 2;
			SetClr(0, 2);
			gotoRowCol(25, 112);
			cout << Sarray[0].score;
			IsAlive = false;

			BonusCount = 0;
			x = 0;
		}
		else if (IsBonusEaten(B, Sarray[1]))
		{
			BonusMultipleSnake(B, F, Sarray, height, width, NOS);
			ExpandSnakeBonus(Sarray[1]);
			Sarray[1].score += 2;
			SetClr(0, 2);
			gotoRowCol(40, 112);
			cout << Sarray[1].score;
			IsAlive = false;

			BonusCount = 0;
			x = 0;
		}

		else if (IsBonusEaten(B, Sarray[2]))
		{
			BonusMultipleSnake(B, F, Sarray, height, width, NOS);
			ExpandSnakeBonus(Sarray[2]);
			Sarray[2].score += 2;
			SetClr(0, 2);
			gotoRowCol(55, 112);
			cout << Sarray[2].score;
			IsAlive = false;

			BonusCount = 0;
			x = 0;
		}

		if (BonusCount == 100)
		{
			RemoveBonus(B);
			BonusMultipleSnake(B, F, Sarray, height, width, NOS);
			IsAlive = false;
			BonusCount = 0;
			x = 0;
		}
		if (IsAlive == true)
		{
			BonusCount++;
		}

		if (tc == 50)
		{
			t--;
			SetClr(0, 2);
			gotoRowCol(10, 112);
			//GBox(5, 105, 10, 15, t);
			cout << t;
			tc = 0;
		}
		if (t == 0 || Sarray[0].score >= 15 || Sarray[1].score >= 15 || Sarray[2].score >= 15)
		{
			if (Sarray[0].score >= 15)
			{
				SetClr(15, 0);
				system("cls");
				gotoRowCol(39, 60);
				cout << Sarray[0].Pnames << " Win the game!!";
				gotoRowCol(41, 63);
				cout << "Game Ended";
				break;
			}
			else if (Sarray[1].score >= 15)
			{
				SetClr(15, 0);
				system("cls");
				gotoRowCol(39, 60);
				cout << Sarray[1].Pnames << " Win the game!!";
				gotoRowCol(41, 63);
				cout << "Game Ended";
				break;
			}

			else if (Sarray[2].score >= 15)
			{
				SetClr(15, 0);
				system("cls");
				gotoRowCol(39, 60);
				cout << Sarray[2].Pnames << " Win the game!!";
				gotoRowCol(41, 63);
				cout << "Game Ended";
				break;
			}

			else if (t == 0)
			{
				SetClr(15, 0);
				system("cls");
				gotoRowCol(41, 63);
				cout << "Game Ended";
				break;
			}

		}
		x++;
		tc++;
	}

	return _getch();
}
int main32()
{
	int height = 60;
	int width = 100;
	char ch = 0;
	int NOS = 3;
	Snake* Sarray = new Snake[3];
	Food F;
	srand(time(0));
	initM1(Sarray[0], F, height, width);
	initM2(Sarray[1], height, width);
	initM3(Sarray[2], height, width);
	DisplayFood(F);
	DrawBox(60, 100);
	Food B;
	int x = 0, BonusCount = 0;
	BonusInit2(B, Sarray, F, height, width, NOS);
	bool IsAlive = false;
	int t = 60;
	int tc = 0;
	SetClr(4, 0);
	gotoRowCol(4, 111);
	cout << "Time";
	gotoRowCol(19, 107);
	cout << Sarray[0].Pnames << "'s Score";
	gotoRowCol(34, 107);
	cout << Sarray[1].Pnames << "'s Score";
	gotoRowCol(49, 107);
	cout << Sarray[2].Pnames << "'s Score";

	GBox(5, 105, 10, 15, t);
	GBox(20, 105, 10, 15, Sarray[0].score);
	GBox(35, 105, 10, 15, Sarray[1].score);
	GBox(50, 105, 10, 15, Sarray[2].score);

	while (true)
	{
		DisplaySnake(Sarray[0]);
		DisplaySnakeM2(Sarray[1]);
		DisplaySnakeM3(Sarray[2]);
		SetClr(15, 0);
		if (_kbhit())
		{
			ch = _getch();
			if (int(ch) == -32)
			{
				ch = _getch();
				ChangeDirection(ch, Sarray[0]);
			}
			else if (int(ch) == 119 || int(ch) == 100 || int(ch) == 115 || int(ch) == 97)
			{
				ChangeDirection(ch, Sarray[1]);
			}
			else if (int(ch) == 56 || int(ch) == 54 || int(ch) == 52 || int(ch) == 53)
			{
				ChangeDirection(ch, Sarray[2]);
			}
		}
		Sleep(40);
		RemoveSnake(Sarray[0]);
		if (BoundaryCheck(Sarray[0], height, width))
		{
			system("cls");
			gotoRowCol(40, 60);
			cout << "Game Ended";
			break;
		}
		RemoveSnake(Sarray[1]);
		if (BoundaryCheck(Sarray[1], height, width))
		{
			system("cls");
			gotoRowCol(40, 60);
			cout << "Game Ended";
			break;
		}
		RemoveSnake(Sarray[2]);
		if (BoundaryCheck(Sarray[2], height, width))
		{
			system("cls");
			gotoRowCol(40, 60);
			cout << "Game Ended";
			break;
		}
		MoveSnake(Sarray[0], height, width);
		if (IsKill(Sarray[0]))
		{
			system("cls");
			gotoRowCol(40, 60);
			cout << "Game Ended";
			break;
		}
		MoveSnake(Sarray[1], height, width);
		if (IsKill(Sarray[1]))
		{
			system("cls");
			gotoRowCol(40, 60);
			cout << "Game Ended";
			break;
		}
		MoveSnake(Sarray[2], height, width);
		if (IsKill(Sarray[2]))
		{
			system("cls");
			gotoRowCol(40, 60);
			cout << "Game Ended";
			break;
		}
		if (IsSnakeKillM3(Sarray))
		{
			system("cls");
			gotoRowCol(40, 60);
			cout << "Game Ended";
			break;
		}

		if (IsFoodEaten(F, Sarray[0]))
		{
			FoodMultipleSnake(F, Sarray, height, width, NOS);
			DisplayFood(F);
			ExpandSnake(Sarray[0]);
			Sarray[0].score++;
			SetClr(0, 2);
			gotoRowCol(25, 112);
			cout << Sarray[0].score;
		}
		else if (IsFoodEaten(F, Sarray[1]))
		{
			FoodMultipleSnake(F, Sarray, height, width, NOS);
			DisplayFood(F);
			ExpandSnake(Sarray[1]);
			Sarray[1].score++;
			SetClr(0, 2);
			gotoRowCol(40, 112);
			cout << Sarray[1].score;
		}
		else if (IsFoodEaten(F, Sarray[2]))
		{
			FoodMultipleSnake(F, Sarray, height, width, NOS);
			DisplayFood(F);
			ExpandSnake(Sarray[2]);
			Sarray[2].score++;
			SetClr(0, 2);
			gotoRowCol(55, 112);
			cout << Sarray[2].score;
		}

		if (x == 120)
		{
			DisplayBonus(B);
			BonusCount = 0;
			IsAlive = true;
		}

		if (IsBonusEaten(B, Sarray[0]))
		{
			BonusMultipleSnake(B, F, Sarray, height, width, NOS);
			ExpandSnakeBonus(Sarray[0]);
			Sarray[0].score += 2;
			SetClr(0, 2);
			gotoRowCol(25, 112);
			cout << Sarray[0].score;
			IsAlive = false;

			BonusCount = 0;
			x = 0;
		}
		else if (IsBonusEaten(B, Sarray[1]))
		{
			BonusMultipleSnake(B, F, Sarray, height, width, NOS);
			ExpandSnakeBonus(Sarray[1]);
			Sarray[1].score += 2;
			SetClr(0, 2);
			gotoRowCol(40, 112);
			cout << Sarray[1].score;
			IsAlive = false;

			BonusCount = 0;
			x = 0;
		}

		else if (IsBonusEaten(B, Sarray[2]))
		{
			BonusMultipleSnake(B, F, Sarray, height, width, NOS);
			ExpandSnakeBonus(Sarray[2]);
			Sarray[2].score += 2;
			SetClr(0, 2);
			gotoRowCol(55, 112);
			cout << Sarray[2].score;
			IsAlive = false;

			BonusCount = 0;
			x = 0;
		}

		if (BonusCount == 100)
		{
			RemoveBonus(B);
			BonusMultipleSnake(B, F, Sarray, height, width, NOS);
			IsAlive = false;
			BonusCount = 0;
			x = 0;
		}
		if (IsAlive == true)
		{
			BonusCount++;
		}

		if (tc == 50)
		{
			t--;
			SetClr(0, 2);
			gotoRowCol(10, 112);
			//GBox(5, 105, 10, 15, t);
			cout << t;
			tc = 0;
		}
		if (t == 0 || Sarray[0].score >= 15 || Sarray[1].score >= 15 || Sarray[2].score >= 15)
		{
			if (Sarray[0].score >= 15)
			{
				SetClr(15, 0);
				system("cls");
				gotoRowCol(39, 60);
				cout << Sarray[0].Pnames << " Win the game!!";
				gotoRowCol(41, 63);
				cout << "Game Ended";
				break;
			}
			else if (Sarray[1].score >= 15)
			{
				SetClr(15, 0);
				system("cls");
				gotoRowCol(39, 60);
				cout << Sarray[1].Pnames << " Win the game!!";
				gotoRowCol(41, 63);
				cout << "Game Ended";
				break;
			}

			else if (Sarray[2].score >= 15)
			{
				SetClr(15, 0);
				system("cls");
				gotoRowCol(39, 60);
				cout << Sarray[2].Pnames << " Win the game!!";
				gotoRowCol(41, 63);
				cout << "Game Ended";
				break;
			}

			else if (t == 0)
			{
				SetClr(15, 0);
				system("cls");
				gotoRowCol(41, 63);
				cout << "Game Ended";
				break;
			}

		}
		x++;
		tc++;
	}

	return _getch();
}
int main33()
{
	int height = 60;
	int width = 100;
	char ch = 0;
	int NOS = 3;
	Snake* Sarray = new Snake[3];
	Food F;
	srand(time(0));
	initM1(Sarray[0], F, height, width);
	initM2(Sarray[1], height, width);
	initM3(Sarray[2], height, width);
	DisplayFood(F);
	DrawBoxH(height, width);
	Food B;
	int x = 0, BonusCount = 0;
	BonusInit2(B, Sarray, F, height, width, NOS);
	bool IsAlive = false;
	int t = 60;
	int tc = 0;
	SetClr(4, 0);
	gotoRowCol(4, 111);
	cout << "Time";
	gotoRowCol(19, 107);
	cout << Sarray[0].Pnames << "'s Score";
	gotoRowCol(34, 107);
	cout << Sarray[1].Pnames << "'s Score";
	gotoRowCol(49, 107);
	cout << Sarray[2].Pnames << "'s Score";

	GBox(5, 105, 10, 15, t);
	GBox(20, 105, 10, 15, Sarray[0].score);
	GBox(35, 105, 10, 15, Sarray[1].score);
	GBox(50, 105, 10, 15, Sarray[2].score);

	while (true)
	{
		DisplaySnake(Sarray[0]);
		DisplaySnakeM2(Sarray[1]);
		DisplaySnakeM3(Sarray[2]);
		SetClr(15, 0);
		if (_kbhit())
		{
			ch = _getch();
			if (int(ch) == -32)
			{
				ch = _getch();
				ChangeDirection(ch, Sarray[0]);
			}
			else if (int(ch) == 119 || int(ch) == 100 || int(ch) == 115 || int(ch) == 97)
			{
				ChangeDirection(ch, Sarray[1]);
			}
			else if (int(ch) == 56 || int(ch) == 54 || int(ch) == 52 || int(ch) == 53)
			{
				ChangeDirection(ch, Sarray[2]);
			}
		}
		Sleep(40);
		RemoveSnake(Sarray[0]);
		if (HurdleCheck(Sarray[0], height, width))
		{
			system("cls");
			gotoRowCol(40, 60);
			PlaySound(TEXT("end.wav"), NULL, SND_ASYNC);
			cout << "Game Ended";
			break;
		}
		if (BoundaryCheck(Sarray[0], height, width))
		{
			system("cls");
			gotoRowCol(40, 60);
			cout << "Game Ended";
			break;
		}
		RemoveSnake(Sarray[1]);
		if (HurdleCheck(Sarray[1], height, width))
		{
			system("cls");
			gotoRowCol(40, 60);
			PlaySound(TEXT("end.wav"), NULL, SND_ASYNC);
			cout << "Game Ended";
			break;
		}
		if (BoundaryCheck(Sarray[1], height, width))
		{
			system("cls");
			gotoRowCol(40, 60);
			cout << "Game Ended";
			break;
		}
		RemoveSnake(Sarray[2]);
		if (HurdleCheck(Sarray[2], height, width))
		{
			system("cls");
			gotoRowCol(40, 60);
			PlaySound(TEXT("end.wav"), NULL, SND_ASYNC);
			cout << "Game Ended";
			break;
		}
		if (BoundaryCheck(Sarray[2], height, width))
		{
			system("cls");
			gotoRowCol(40, 60);
			cout << "Game Ended";
			break;
		}
		MoveSnake(Sarray[0], height, width);
		if (IsKill(Sarray[0]))
		{
			system("cls");
			gotoRowCol(40, 60);
			cout << "Game Ended";
			break;
		}
		MoveSnake(Sarray[1], height, width);
		if (IsKill(Sarray[1]))
		{
			system("cls");
			gotoRowCol(40, 60);
			cout << "Game Ended";
			break;
		}
		MoveSnake(Sarray[2], height, width);
		if (IsKill(Sarray[2]))
		{
			system("cls");
			gotoRowCol(40, 60);
			cout << "Game Ended";
			break;
		}
		if (IsSnakeKillM3(Sarray))
		{
			system("cls");
			gotoRowCol(40, 60);
			cout << "Game Ended";
			break;
		}

		if (IsFoodEaten(F, Sarray[0]))
		{
			FoodMultipleSnakeMH(F, Sarray, height, width, NOS);
			DisplayFood(F);
			ExpandSnake(Sarray[0]);
			Sarray[0].score++;
			SetClr(0, 2);
			gotoRowCol(25, 112);
			cout << Sarray[0].score;
		}
		else if (IsFoodEaten(F, Sarray[1]))
		{
			FoodMultipleSnakeMH(F, Sarray, height, width, NOS);
			DisplayFood(F);
			ExpandSnake(Sarray[1]);
			Sarray[1].score++;
			SetClr(0, 2);
			gotoRowCol(40, 112);
			cout << Sarray[1].score;
		}
		else if (IsFoodEaten(F, Sarray[2]))
		{
			FoodMultipleSnakeMH(F, Sarray, height, width, NOS);
			DisplayFood(F);
			ExpandSnake(Sarray[2]);
			Sarray[2].score++;
			SetClr(0, 2);
			gotoRowCol(55, 112);
			cout << Sarray[2].score;
		}

		if (x == 120)
		{
			DisplayBonus(B);
			BonusCount = 0;
			IsAlive = true;
		}

		if (IsBonusEaten(B, Sarray[0]))
		{
			BonusMultipleSnakeMH(B, F, Sarray, height, width, NOS);
			ExpandSnakeBonus(Sarray[0]);
			Sarray[0].score += 2;
			SetClr(0, 2);
			gotoRowCol(25, 112);
			cout << Sarray[0].score;
			IsAlive = false;

			BonusCount = 0;
			x = 0;
		}
		else if (IsBonusEaten(B, Sarray[1]))
		{
			BonusMultipleSnakeMH(B, F, Sarray, height, width, NOS);
			ExpandSnakeBonus(Sarray[1]);
			Sarray[1].score += 2;
			SetClr(0, 2);
			gotoRowCol(40, 112);
			cout << Sarray[1].score;
			IsAlive = false;

			BonusCount = 0;
			x = 0;
		}

		else if (IsBonusEaten(B, Sarray[2]))
		{
			BonusMultipleSnakeMH(B, F, Sarray, height, width, NOS);
			ExpandSnakeBonus(Sarray[2]);
			Sarray[2].score += 2;
			SetClr(0, 2);
			gotoRowCol(55, 112);
			cout << Sarray[2].score;
			IsAlive = false;

			BonusCount = 0;
			x = 0;
		}

		if (BonusCount == 100)
		{
			RemoveBonus(B);
			BonusMultipleSnakeMH(B, F, Sarray, height, width, NOS);
			IsAlive = false;
			BonusCount = 0;
			x = 0;
		}
		if (IsAlive == true)
		{
			BonusCount++;
		}

		if (tc == 50)
		{
			t--;
			SetClr(0, 2);
			gotoRowCol(10, 112);
			//GBox(5, 105, 10, 15, t);
			cout << t;
			tc = 0;
		}
		if (t == 0 || Sarray[0].score >= 15 || Sarray[1].score >= 15 || Sarray[2].score >= 15)
		{
			if (Sarray[0].score >= 15)
			{
				SetClr(15, 0);
				system("cls");
				gotoRowCol(39, 60);
				cout << Sarray[0].Pnames << " Win the game!!";
				gotoRowCol(41, 63);
				cout << "Game Ended";
				break;
			}
			else if (Sarray[1].score >= 15)
			{
				SetClr(15, 0);
				system("cls");
				gotoRowCol(39, 60);
				cout << Sarray[1].Pnames << " Win the game!!";
				gotoRowCol(41, 63);
				cout << "Game Ended";
				break;
			}

			else if (Sarray[2].score >= 15)
			{
				SetClr(15, 0);
				system("cls");
				gotoRowCol(39, 60);
				cout << Sarray[2].Pnames << " Win the game!!";
				gotoRowCol(41, 63);
				cout << "Game Ended";
				break;
			}

			else if (t == 0)
			{
				SetClr(15, 0);
				system("cls");
				gotoRowCol(41, 63);
				cout << "Game Ended";
				break;
			}

		}
		x++;
		tc++;
	}

	return _getch();
}
int main4()
{

	int height = 60;
	int width = 100;
	char ch = 0;
	int NOS = 4;
	Snake* Sarray = new Snake[4];
	Food F;
	srand(time(0));
	initM1(Sarray[0], F, height, width);
	initM2(Sarray[1], height, width);
	initM3(Sarray[2], height, width);
	initM4(Sarray[3], height, width);
	DisplayFood(F);
	DrawBox(60, 100);
	Food B;
	int x = 0, BonusCount = 0;
	BonusInit2(B, Sarray, F, height, width, NOS);
	bool IsAlive = false;
	int t = 60;
	int tc = 0;
	SetClr(4, 0);
	gotoRowCol(4, 111);
	cout << "Time";
	gotoRowCol(19, 107);
	cout << Sarray[0].Pnames << "'s Score";
	gotoRowCol(34, 107);
	cout << Sarray[1].Pnames << "'s Score";
	gotoRowCol(49, 107);
	cout << Sarray[2].Pnames << "'s Score";
	gotoRowCol(64, 107);
	cout << Sarray[3].Pnames << "'s Score";

	GBox(5, 105, 10, 15, t);
	GBox(20, 105, 10, 15, Sarray[0].score);
	GBox(35, 105, 10, 15, Sarray[1].score);
	GBox(50, 105, 10, 15, Sarray[2].score);
	GBox(65, 105, 10, 15, Sarray[3].score);

	while (true)
	{
		DisplaySnake(Sarray[0]);
		DisplaySnakeM2(Sarray[1]);
		DisplaySnakeM3(Sarray[2]);
		DisplaySnakeM4(Sarray[3]);
		SetClr(15, 0);
		if (_kbhit())
		{
			ch = _getch();
			if (int(ch) == -32)
			{
				ch = _getch();
				ChangeDirection(ch, Sarray[0]);
			}
			else if (int(ch) == 119 || int(ch) == 100 || int(ch) == 115 || int(ch) == 97)
			{
				ChangeDirection(ch, Sarray[1]);
			}
			else if (int(ch) == 56 || int(ch) == 54 || int(ch) == 52 || int(ch) == 53)
			{
				ChangeDirection(ch, Sarray[2]);
			}
			else if (int(ch) == 105 || int(ch) == 108 || int(ch) == 107 || int(ch) == 106)
			{
				ChangeDirection(ch, Sarray[3]);
			}
		}

		Sleep(40);
		RemoveSnake(Sarray[0]);
		RemoveSnake(Sarray[1]);
		RemoveSnake(Sarray[2]);
		RemoveSnake(Sarray[3]);
		MoveSnake(Sarray[0], height, width);
		if (IsKill(Sarray[0]))
		{
			system("cls");
			gotoRowCol(40, 60);
			cout << "Game Ended";
			break;
		}
		MoveSnake(Sarray[1], height, width);
		if (IsKill(Sarray[1]))
		{
			system("cls");
			gotoRowCol(40, 60);
			cout << "Game Ended";
			break;
		}
		MoveSnake(Sarray[2], height, width);
		if (IsKill(Sarray[2]))
		{
			system("cls");
			gotoRowCol(40, 60);
			cout << "Game Ended";
			break;
		}
		MoveSnake(Sarray[3], height, width);
		if (IsKill(Sarray[3]))
		{
			system("cls");
			gotoRowCol(40, 60);
			cout << "Game Ended";
			break;
		}
		if (IsSnakeKillM4(Sarray))
		{
			system("cls");
			gotoRowCol(40, 60);
			cout << "Game Ended";
			break;
		}

		if (IsFoodEaten(F, Sarray[0]))
		{
			FoodMultipleSnake(F, Sarray, height, width, NOS);
			DisplayFood(F);
			ExpandSnake(Sarray[0]);
			Sarray[0].score++;
			SetClr(0, 2);
			gotoRowCol(25, 112);
			cout << Sarray[0].score;
		}
		else if (IsFoodEaten(F, Sarray[1]))
		{
			FoodMultipleSnake(F, Sarray, height, width, NOS);
			DisplayFood(F);
			ExpandSnake(Sarray[1]);
			Sarray[1].score++;
			SetClr(0, 2);
			gotoRowCol(40, 112);
			cout << Sarray[1].score;
		}
		else if (IsFoodEaten(F, Sarray[2]))
		{
			FoodMultipleSnake(F, Sarray, height, width, NOS);
			DisplayFood(F);
			ExpandSnake(Sarray[2]);
			Sarray[2].score++;
			SetClr(0, 2);
			gotoRowCol(55, 112);
			cout << Sarray[2].score;
		}
		else if (IsFoodEaten(F, Sarray[3]))
		{
			FoodMultipleSnake(F, Sarray, height, width, NOS);
			DisplayFood(F);
			ExpandSnake(Sarray[3]);
			Sarray[3].score++;
			SetClr(0, 2);
			gotoRowCol(70, 112);
			cout << Sarray[3].score;
		}

		if (x == 120)
		{
			DisplayBonus(B);
			BonusCount = 0;
			IsAlive = true;
		}

		if (IsBonusEaten(B, Sarray[0]))
		{
			BonusMultipleSnake(B, F, Sarray, height, width, NOS);
			ExpandSnakeBonus(Sarray[0]);
			Sarray[0].score += 2;
			SetClr(0, 2);
			gotoRowCol(25, 112);
			cout << Sarray[0].score;
			IsAlive = false;

			BonusCount = 0;
			x = 0;
		}
		else if (IsBonusEaten(B, Sarray[1]))
		{
			BonusMultipleSnake(B, F, Sarray, height, width, NOS);
			ExpandSnakeBonus(Sarray[1]);
			Sarray[1].score += 2;
			SetClr(0, 2);
			gotoRowCol(40, 112);
			cout << Sarray[1].score;
			IsAlive = false;

			BonusCount = 0;
			x = 0;
		}

		else if (IsBonusEaten(B, Sarray[2]))
		{
			BonusMultipleSnake(B, F, Sarray, height, width, NOS);
			ExpandSnakeBonus(Sarray[2]);
			Sarray[2].score += 2;
			SetClr(0, 2);
			gotoRowCol(55, 112);
			cout << Sarray[2].score;
			IsAlive = false;

			BonusCount = 0;
			x = 0;
		}

		else if (IsBonusEaten(B, Sarray[3]))
		{
			BonusMultipleSnake(B, F, Sarray, height, width, NOS);
			ExpandSnakeBonus(Sarray[3]);
			Sarray[3].score += 2;
			SetClr(0, 2);
			gotoRowCol(70, 112);
			cout << Sarray[3].score;
			IsAlive = false;

			BonusCount = 0;
			x = 0;
		}

		if (BonusCount == 100)
		{
			RemoveBonus(B);
			BonusMultipleSnake(B, F, Sarray, height, width, NOS);
			IsAlive = false;
			BonusCount = 0;
			x = 0;
		}
		if (IsAlive == true)
		{
			BonusCount++;
		}

		if (tc == 50)
		{
			t--;
			SetClr(0, 2);
			gotoRowCol(10, 112);
			//GBox(5, 105, 10, 15, t);
			cout << t;
			tc = 0;
		}
		if (t == 0 || Sarray[0].score >= 15 || Sarray[1].score >= 15 || Sarray[2].score >= 15 || Sarray[3].score >= 15)
		{
			if (Sarray[0].score >= 15)
			{
				SetClr(15, 0);
				system("cls");
				gotoRowCol(39, 60);
				cout << Sarray[0].Pnames << " Win the game!!";
				gotoRowCol(41, 63);
				cout << "Game Ended";
				break;
			}
			else if (Sarray[1].score >= 15)
			{
				SetClr(15, 0);
				system("cls");
				gotoRowCol(39, 60);
				cout << Sarray[1].Pnames << " Win the game!!";
				gotoRowCol(41, 63);
				cout << "Game Ended";
				break;
			}

			else if (Sarray[2].score >= 15)
			{
				SetClr(15, 0);
				system("cls");
				gotoRowCol(39, 60);
				cout << Sarray[2].Pnames << " Win the game!!";
				gotoRowCol(41, 63);
				cout << "Game Ended";
				break;
			}

			else if (Sarray[3].score >= 15)
			{
				SetClr(15, 0);
				system("cls");
				gotoRowCol(39, 60);
				cout << Sarray[3].Pnames << " Win the game!!";
				gotoRowCol(41, 63);
				cout << "Game Ended";
				break;
			}

			else if (t == 0)
			{
				SetClr(15, 0);
				system("cls");
				gotoRowCol(41, 63);
				cout << "Game Ended";
				break;
			}
		}
		x++;
		tc++;
	}

	return _getch();
}
int main42()
{

	int height = 60;
	int width = 100;
	char ch = 0;
	int NOS = 4;
	Snake* Sarray = new Snake[4];
	Food F;
	srand(time(0));
	initM1(Sarray[0], F, height, width);
	initM2(Sarray[1], height, width);
	initM3(Sarray[2], height, width);
	initM4(Sarray[3], height, width);
	DisplayFood(F);
	DrawBox(height,width);
	Food B;
	int x = 0, BonusCount = 0;
	BonusInit2(B, Sarray, F, height, width, NOS);
	bool IsAlive = false;
	int t = 60;
	int tc = 0;
	SetClr(4, 0);
	gotoRowCol(4, 111);
	cout << "Time";
	gotoRowCol(19, 107);
	cout << Sarray[0].Pnames << "'s Score";
	gotoRowCol(34, 107);
	cout << Sarray[1].Pnames << "'s Score";
	gotoRowCol(49, 107);
	cout << Sarray[2].Pnames << "'s Score";
	gotoRowCol(64, 107);
	cout << Sarray[3].Pnames << "'s Score";

	GBox(5, 105, 10, 15, t);
	GBox(20, 105, 10, 15, Sarray[0].score);
	GBox(35, 105, 10, 15, Sarray[1].score);
	GBox(50, 105, 10, 15, Sarray[2].score);
	GBox(65, 105, 10, 15, Sarray[3].score);
	while (true)
	{
		DisplaySnake(Sarray[0]);
		DisplaySnakeM2(Sarray[1]);
		DisplaySnakeM3(Sarray[2]);
		DisplaySnakeM4(Sarray[3]);
		SetClr(15, 0);
		if (_kbhit())
		{
			ch = _getch();
			if (int(ch) == -32)
			{
				ch = _getch();
				ChangeDirection(ch, Sarray[0]);
			}
			else if (int(ch) == 119 || int(ch) == 100 || int(ch) == 115 || int(ch) == 97)
			{
				ChangeDirection(ch, Sarray[1]);
			}
			else if (int(ch) == 56 || int(ch) == 54 || int(ch) == 52 || int(ch) == 53)
			{
				ChangeDirection(ch, Sarray[2]);
			}
			else if (int(ch) == 105 || int(ch) == 108 || int(ch) == 107 || int(ch) == 106)
			{
				ChangeDirection(ch, Sarray[3]);
			}
		}

		Sleep(40);
		RemoveSnake(Sarray[0]);
		if (BoundaryCheck(Sarray[0], height, width))
		{
			system("cls");
			gotoRowCol(40, 60);
			cout << "Game Ended";
			break;
		}
		RemoveSnake(Sarray[1]);
		if (BoundaryCheck(Sarray[1], height, width))
		{
			system("cls");
			gotoRowCol(40, 60);
			cout << "Game Ended";
			break;
		}
		RemoveSnake(Sarray[2]);
		if (BoundaryCheck(Sarray[2], height, width))
		{
			system("cls");
			gotoRowCol(40, 60);
			cout << "Game Ended";
			break;
		}
		RemoveSnake(Sarray[3]);
		if (BoundaryCheck(Sarray[3], height, width))
		{
			system("cls");
			gotoRowCol(40, 60);
			cout << "Game Ended";
			break;
		}
		MoveSnake(Sarray[0], height, width);
		if (IsKill(Sarray[0]))
		{
			system("cls");
			gotoRowCol(40, 60);
			cout << "Game Ended";
			break;
		}
		MoveSnake(Sarray[1], height, width);
		if (IsKill(Sarray[1]))
		{
			system("cls");
			gotoRowCol(40, 60);
			cout << "Game Ended";
			break;
		}
		MoveSnake(Sarray[2], height, width);
		if (IsKill(Sarray[2]))
		{
			system("cls");
			gotoRowCol(40, 60);
			cout << "Game Ended";
			break;
		}
		MoveSnake(Sarray[3], height, width);
		if (IsKill(Sarray[3]))
		{
			system("cls");
			gotoRowCol(40, 60);
			cout << "Game Ended";
			break;
		}
		if (IsSnakeKillM4(Sarray))
		{
			system("cls");
			gotoRowCol(40, 60);
			cout << "Game Ended";
			break;
		}

		if (IsFoodEaten(F, Sarray[0]))
		{
			FoodMultipleSnake(F, Sarray, height, width, NOS);
			DisplayFood(F);
			ExpandSnake(Sarray[0]);
			Sarray[0].score++;
			SetClr(0, 2);
			gotoRowCol(25, 112);
			cout << Sarray[0].score;
		}
		else if (IsFoodEaten(F, Sarray[1]))
		{
			FoodMultipleSnake(F, Sarray, height, width, NOS);
			DisplayFood(F);
			ExpandSnake(Sarray[1]);
			Sarray[1].score++;
			SetClr(0, 2);
			gotoRowCol(40, 112);
			cout << Sarray[1].score;
		}
		else if (IsFoodEaten(F, Sarray[2]))
		{
			FoodMultipleSnake(F, Sarray, height, width, NOS);
			DisplayFood(F);
			ExpandSnake(Sarray[2]);
			Sarray[2].score++;
			SetClr(0, 2);
			gotoRowCol(55, 112);
			cout << Sarray[2].score;
		}
		else if (IsFoodEaten(F, Sarray[3]))
		{
			FoodMultipleSnake(F, Sarray, height, width, NOS);
			DisplayFood(F);
			ExpandSnake(Sarray[3]);
			Sarray[3].score++;
			SetClr(0, 2);
			gotoRowCol(70, 112);
			cout << Sarray[3].score;

		}

		if (x == 120)
		{
			DisplayBonus(B);
			BonusCount = 0;
			IsAlive = true;
		}

		if (IsBonusEaten(B, Sarray[0]))
		{
			BonusMultipleSnake(B, F, Sarray, height, width, NOS);
			ExpandSnakeBonus(Sarray[0]);
			Sarray[0].score += 2;
			SetClr(0, 2);
			gotoRowCol(25, 112);
			cout << Sarray[0].score;
			IsAlive = false;

			BonusCount = 0;
			x = 0;
		}
		else if (IsBonusEaten(B, Sarray[1]))
		{
			BonusMultipleSnake(B, F, Sarray, height, width, NOS);
			ExpandSnakeBonus(Sarray[1]);
			Sarray[1].score += 2;
			SetClr(0, 2);
			gotoRowCol(40, 112);
			cout << Sarray[1].score;
			IsAlive = false;

			BonusCount = 0;
			x = 0;
		}

		else if (IsBonusEaten(B, Sarray[2]))
		{
			BonusMultipleSnake(B, F, Sarray, height, width, NOS);
			ExpandSnakeBonus(Sarray[2]);
			Sarray[2].score += 2;
			SetClr(0, 2);
			gotoRowCol(55, 112);
			cout << Sarray[2].score;
			IsAlive = false;

			BonusCount = 0;
			x = 0;
		}

		else if (IsBonusEaten(B, Sarray[3]))
		{
			BonusMultipleSnake(B, F, Sarray, height, width, NOS);
			ExpandSnakeBonus(Sarray[3]);
			Sarray[3].score += 2;
			SetClr(0, 2);
			gotoRowCol(70, 112);
			cout << Sarray[3].score;
			IsAlive = false;

			BonusCount = 0;
			x = 0;
		}

		if (BonusCount == 100)
		{
			RemoveBonus(B);
			BonusMultipleSnake(B, F, Sarray, height, width, NOS);
			IsAlive = false;
			BonusCount = 0;
			x = 0;
		}
		if (IsAlive == true)
		{
			BonusCount++;
		}

		if (tc == 50)
		{
			t--;
			SetClr(0, 2);
			gotoRowCol(10, 112);
			//GBox(5, 105, 10, 15, t);
			cout << t;
			tc = 0;
		}
		if (t == 0 || Sarray[0].score >= 15 || Sarray[1].score >= 15 || Sarray[2].score >= 15 || Sarray[3].score >= 15)
		{
			if (Sarray[0].score >= 15)
			{
				SetClr(15, 0);
				system("cls");
				gotoRowCol(39, 60);
				cout << Sarray[0].Pnames << " Win the game!!";
				gotoRowCol(41, 63);
				cout << "Game Ended";
				break;
			}
			else if (Sarray[1].score >= 15)
			{
				SetClr(15, 0);
				system("cls");
				gotoRowCol(39, 60);
				cout << Sarray[1].Pnames << " Win the game!!";
				gotoRowCol(41, 63);
				cout << "Game Ended";
				break;
			}

			else if (Sarray[2].score >= 15)
			{
				SetClr(15, 0);
				system("cls");
				gotoRowCol(39, 60);
				cout << Sarray[2].Pnames << " Win the game!!";
				gotoRowCol(41, 63);
				cout << "Game Ended";
				break;
			}

			else if (Sarray[3].score >= 15)
			{
				SetClr(15, 0);
				system("cls");
				gotoRowCol(39, 60);
				cout << Sarray[3].Pnames << " Win the game!!";
				gotoRowCol(41, 63);
				cout << "Game Ended";
				break;
			}

			else if (t == 0)
			{
				SetClr(15, 0);
				system("cls");
				gotoRowCol(41, 63);
				cout << "Game Ended";
				break;
			}
		}
		x++;
		tc++;
	}



	return _getch();


}
int main43()
{



	int height = 60;
	int width = 100;
	char ch = 0;
	int NOS = 4;
	Snake* Sarray = new Snake[4];
	Food F;
	srand(time(0));
	initM1(Sarray[0], F, height, width);
	initM2(Sarray[1], height, width);
	initM3(Sarray[2], height, width);
	initM4(Sarray[3], height, width);
	DisplayFood(F);
	DrawBoxH(height, width);
	Food B;
	int x = 0, BonusCount = 0;
	BonusInit2(B, Sarray, F, height, width, NOS);
	bool IsAlive = false;
	int t = 60;
	int tc = 0;
	SetClr(4, 0);
	gotoRowCol(4, 111);
	cout << "Time";
	gotoRowCol(19, 107);
	cout << Sarray[0].Pnames << "'s Score";
	gotoRowCol(34, 107);
	cout << Sarray[1].Pnames << "'s Score";
	gotoRowCol(49, 107);
	cout << Sarray[2].Pnames << "'s Score";
	gotoRowCol(64, 107);
	cout << Sarray[3].Pnames << "'s Score";

	GBox(5, 105, 10, 15, t);
	GBox(20, 105, 10, 15, Sarray[0].score);
	GBox(35, 105, 10, 15, Sarray[1].score);
	GBox(50, 105, 10, 15, Sarray[2].score);
	GBox(65, 105, 10, 15, Sarray[3].score);

	while (true)
	{
		DisplaySnake(Sarray[0]);
		DisplaySnakeM2(Sarray[1]);
		DisplaySnakeM3(Sarray[2]);
		DisplaySnakeM4(Sarray[3]);
		SetClr(15, 0);
		if (_kbhit())
		{
			ch = _getch();
			if (int(ch) == -32)
			{
				ch = _getch();
				ChangeDirection(ch, Sarray[0]);
			}
			else if (int(ch) == 119 || int(ch) == 100 || int(ch) == 115 || int(ch) == 97)
			{
				ChangeDirection(ch, Sarray[1]);
			}
			else if (int(ch) == 56 || int(ch) == 54 || int(ch) == 52 || int(ch) == 53)
			{
				ChangeDirection(ch, Sarray[2]);
			}
			else if (int(ch) == 105 || int(ch) == 108 || int(ch) == 107 || int(ch) == 106)
			{
				ChangeDirection(ch, Sarray[3]);
			}
		}

		Sleep(40);
		RemoveSnake(Sarray[0]);
		if (HurdleCheck(Sarray[0], height, width))
		{
			system("cls");
			gotoRowCol(40, 60);
			PlaySound(TEXT("end.wav"), NULL, SND_ASYNC);
			cout << "Game Ended";
			break;
		}
		if (BoundaryCheck(Sarray[0], height, width))
		{
			system("cls");
			gotoRowCol(40, 60);
			cout << "Game Ended";
			break;
		}
		RemoveSnake(Sarray[1]);
		if (HurdleCheck(Sarray[1], height, width))
		{
			system("cls");
			gotoRowCol(40, 60);
			PlaySound(TEXT("end.wav"), NULL, SND_ASYNC);
			cout << "Game Ended";
			break;
		}
		if (BoundaryCheck(Sarray[1], height, width))
		{
			system("cls");
			gotoRowCol(40, 60);
			cout << "Game Ended";
			break;
		}
		RemoveSnake(Sarray[2]);
		if (HurdleCheck(Sarray[2], height, width))
		{
			system("cls");
			gotoRowCol(40, 60);
			PlaySound(TEXT("end.wav"), NULL, SND_ASYNC);
			cout << "Game Ended";
			break;
		}
		if (BoundaryCheck(Sarray[2], height, width))
		{
			system("cls");
			gotoRowCol(40, 60);
			cout << "Game Ended";
			break;
		}
		RemoveSnake(Sarray[3]);
		if (HurdleCheck(Sarray[3], height, width))
		{
			system("cls");
			gotoRowCol(40, 60);
			PlaySound(TEXT("end.wav"), NULL, SND_ASYNC);
			cout << "Game Ended";
			break;
		}
		if (BoundaryCheck(Sarray[3], height, width))
		{
			system("cls");
			gotoRowCol(40, 60);
			cout << "Game Ended";
			break;
		}
		MoveSnake(Sarray[0], height, width);
		if (IsKill(Sarray[0]))
		{
			system("cls");
			gotoRowCol(40, 60);
			cout << "Game Ended";
			break;
		}
		MoveSnake(Sarray[1], height, width);
		if (IsKill(Sarray[1]))
		{
			system("cls");
			gotoRowCol(40, 60);
			cout << "Game Ended";
			break;
		}
		MoveSnake(Sarray[2], height, width);
		if (IsKill(Sarray[2]))
		{
			system("cls");
			gotoRowCol(40, 60);
			cout << "Game Ended";
			break;
		}
		MoveSnake(Sarray[3], height, width);
		if (IsKill(Sarray[3]))
		{
			system("cls");
			gotoRowCol(40, 60);
			cout << "Game Ended";
			break;
		}
		if (IsSnakeKillM4(Sarray))
		{
			system("cls");
			gotoRowCol(40, 60);
			cout << "Game Ended";
			break;
		}

		if (IsFoodEaten(F, Sarray[0]))
		{
			FoodMultipleSnakeMH(F, Sarray, height, width, NOS);
			DisplayFood(F);
			ExpandSnake(Sarray[0]);
			Sarray[0].score++;
			SetClr(0, 2);
			gotoRowCol(25, 112);
			cout << Sarray[0].score;
		}
		else if (IsFoodEaten(F, Sarray[1]))
		{
			FoodMultipleSnakeMH(F, Sarray, height, width, NOS);
			DisplayFood(F);
			ExpandSnake(Sarray[1]);
			Sarray[1].score++;
			SetClr(0, 2);
			gotoRowCol(40, 112);
			cout << Sarray[1].score;
		}
		else if (IsFoodEaten(F, Sarray[2]))
		{
			FoodMultipleSnakeMH(F, Sarray, height, width, NOS);
			DisplayFood(F);
			ExpandSnake(Sarray[2]);
			Sarray[2].score++;
			SetClr(0, 2);
			gotoRowCol(55, 112);
			cout << Sarray[2].score;
		}
		else if (IsFoodEaten(F, Sarray[3]))
		{
			FoodMultipleSnakeMH(F, Sarray, height, width, NOS);
			DisplayFood(F);
			ExpandSnake(Sarray[3]);
			Sarray[3].score++;
			SetClr(0, 2);
			gotoRowCol(70, 112);
			cout << Sarray[3].score;
		}

		if (x == 120)
		{
			DisplayBonus(B);
			BonusCount = 0;
			IsAlive = true;
		}

		if (IsBonusEaten(B, Sarray[0]))
		{
			BonusMultipleSnake(B, F, Sarray, height, width, NOS);
			ExpandSnakeBonus(Sarray[0]);
			Sarray[0].score += 2;
			SetClr(0, 2);
			gotoRowCol(25, 112);
			cout << Sarray[0].score;
			IsAlive = false;

			BonusCount = 0;
			x = 0;
		}
		else if (IsBonusEaten(B, Sarray[1]))
		{
			BonusMultipleSnake(B, F, Sarray, height, width, NOS);
			ExpandSnakeBonus(Sarray[1]);
			Sarray[1].score += 2;
			SetClr(0, 2);
			gotoRowCol(40, 112);
			cout << Sarray[1].score;
			IsAlive = false;

			BonusCount = 0;
			x = 0;
		}

		else if (IsBonusEaten(B, Sarray[2]))
		{
			BonusMultipleSnake(B, F, Sarray, height, width, NOS);
			ExpandSnakeBonus(Sarray[2]);
			Sarray[2].score += 2;
			SetClr(0, 2);
			gotoRowCol(55, 112);
			cout << Sarray[2].score;
			IsAlive = false;

			BonusCount = 0;
			x = 0;
		}

		else if (IsBonusEaten(B, Sarray[3]))
		{
			BonusMultipleSnake(B, F, Sarray, height, width, NOS);
			ExpandSnakeBonus(Sarray[3]);
			Sarray[3].score += 2;
			SetClr(0, 2);
			gotoRowCol(70, 112);
			cout << Sarray[3].score;
			IsAlive = false;

			BonusCount = 0;
			x = 0;
		}

		if (BonusCount == 100)
		{
			RemoveBonus(B);
			BonusMultipleSnake(B, F, Sarray, height, width, NOS);
			IsAlive = false;
			BonusCount = 0;
			x = 0;
		}
		if (IsAlive == true)
		{
			BonusCount++;
		}

		if (tc == 50)
		{
			t--;
			SetClr(0, 2);
			gotoRowCol(10, 112);
			//GBox(5, 105, 10, 15, t);
			cout << t;
			tc = 0;
		}
		if (t == 0 || Sarray[0].score >= 15 || Sarray[1].score >= 15 || Sarray[2].score >= 15 || Sarray[3].score >= 15)
		{
			if (Sarray[0].score >= 15)
			{
				SetClr(15, 0);
				system("cls");
				gotoRowCol(39, 60);
				cout << Sarray[0].Pnames << " Win the game!!";
				gotoRowCol(41, 63);
				cout << "Game Ended";
				break;
			}
			else if (Sarray[1].score >= 15)
			{
				SetClr(15, 0);
				system("cls");
				gotoRowCol(39, 60);
				cout << Sarray[1].Pnames << " Win the game!!";
				gotoRowCol(41, 63);
				cout << "Game Ended";
				break;
			}

			else if (Sarray[2].score >= 15)
			{
				SetClr(15, 0);
				system("cls");
				gotoRowCol(39, 60);
				cout << Sarray[2].Pnames << " Win the game!!";
				gotoRowCol(41, 63);
				cout << "Game Ended";
				break;
			}

			else if (Sarray[3].score >= 15)
			{
				SetClr(15, 0);
				system("cls");
				gotoRowCol(39, 60);
				cout << Sarray[3].Pnames << " Win the game!!";
				gotoRowCol(41, 63);
				cout << "Game Ended";
				break;
			}

			else if (t == 0)
			{
				SetClr(15, 0);
				system("cls");
				gotoRowCol(41, 63);
				cout << "Game Ended";
				break;
			}
		}
		x++;
		tc++;
	}



	return _getch();













}
int main()
{
	_getch();
	int height = 100, width = 169, row = 0, col = 0;
	char c = -37;
	int x = 0, count = 0;

	
		SCHAR(30, 56);
		NCHAR(30, 62);
		ACHAR(30, 80);
		KCHAR(30, 90);
		ECHAR(30, 97);
		GCHAR(42, 60);
		ACHAR2(42, 73);
		MCHAR(42, 83);
		ECHAR2(42, 95);

	Snake S1;
	Snake S2;
	init2(S1, height, width);
	init3(S2, height, width);
	PlaySound(TEXT("music.wav"), NULL, SND_ASYNC);
	while (true)
	{

		DisplaySnake(S1);
		DisplaySnake(S2);
		Sleep(0.01);
		RemoveSnake(S1);
		RemoveSnake(S2);
		MoveSnake2(S1, height, width);
		MoveSnake3(S2, height, width);


		if (x % 2 == 0)
		{
			SetClr(2, 0);
			gotoRowCol(80, x);
			cout << c;

		}
		else
		{
			SetClr(4, 0);
			gotoRowCol(80, x);
			cout << c;
		}
		if (count == 4)
		{
			x += 1;
		}
		count++;
		if (count % 5 == 0)
		{
			count = 0;
		}


		if (x == width)
		{
			break;
		}

	}

	system("cls");
	Box(20, 60, 15, 25);
	Box1(40, 60, 15, 25);

	while (true)
	{
		getRowColbyLeftClick(row, col);
		if (row >= 20 && row <= 35 && col >= 60 && col <= 85)
		{
			PlaySound(TEXT("tabclick.wav"), NULL, SND_SYNC);
			Sleep(80);
			break;;
		}
		else if (row >= 40 && row <= 55 && col >= 60 && col <= 85)
		{
			PlaySound(TEXT("tabclick.wav"), NULL, SND_SYNC);
			Sleep(80);
			break;
		}
	}

	PlaySound(TEXT("music.wav"), NULL, SND_ASYNC);
	if (row >= 20 && row <= 35 && col >= 60 && col <= 85)
	{
		SetClr(15, 0);
		system("cls");
		Box5(20, 60, 15, 25);
		Box6(40, 60, 15, 25);
		Box7(60, 60, 15, 25);
		while (true)
		{
			getRowColbyLeftClick(row, col);
			if (row >= 20 && row <= 35 && col >= 60 && col <= 85)
			{
				PlaySound(TEXT("tabclick.wav"), NULL, SND_SYNC);
				break;;
				
			}
			else if (row >= 40 && row <= 55 && col >= 60 && col <= 85)
			{
				PlaySound(TEXT("tabclick.wav"), NULL, SND_SYNC);
				break;
			}
			else if (row >= 60 && row <= 75 && col >= 60 && col <= 85)
			{
				PlaySound(TEXT("tabclick.wav"), NULL, SND_SYNC);
				break;
			}

		}

		if (row >= 20 && row <= 35 && col >= 60 && col <= 85)
		{
			PlaySound(TEXT("start.wav"), NULL, SND_ASYNC);
			Sleep(100);
			SetClr(15, 0);
			system("cls");
			main1();
		}
		else if (row >= 40 && row <= 55 && col >= 60 && col <= 85)
		{
			PlaySound(TEXT("start.wav"), NULL, SND_ASYNC);
			Sleep(100);
			SetClr(15, 0);
			system("cls");
			main12();
		}
		else if (row >= 60 && row <= 75 && col >= 60 && col <= 85)
		{
			PlaySound(TEXT("start.wav"), NULL, SND_ASYNC);
			Sleep(100);
			SetClr(15, 0);
			system("cls");
			main13();
		}
		
	}
	else if (row >= 40 && row <= 55 && col >= 60 && col <= 85)
	{
		SetClr(15, 0);
		system("cls");
		Box2(20, 60, 15, 25);
		Box3(40, 60, 15, 25);
		Box4(60, 60, 15, 25);
		while (true)
		{
			getRowColbyLeftClick(row, col);
			if (row >= 20 && row <= 35 && col >= 60 && col <= 85)
			{
				PlaySound(TEXT("tabclick.wav"), NULL, SND_SYNC);
				break;
			}
			else if (row >= 40 && row <= 55 && col >= 60 && col <= 85)
			{
				PlaySound(TEXT("tabclick.wav"), NULL, SND_SYNC);
				break;
			}
			else if (row >= 60 && row <= 75 && col >= 60 && col <= 85)
			{
				PlaySound(TEXT("tabclick.wav"), NULL, SND_SYNC);
				break;
			}
		}

		if (row >= 20 && row <= 35 && col >= 60 && col <= 85)
		{
			SetClr(15, 0);
			system("cls");
			Box5(20, 60, 15, 25);
			Box6(40, 60, 15, 25);
			Box7(60, 60, 15, 25);
			while (true)
			{
				getRowColbyLeftClick(row, col);
				if (row >= 20 && row <= 35 && col >= 60 && col <= 85)
				{
					PlaySound(TEXT("tabclick.wav"), NULL, SND_SYNC);
					break;;

				}
				else if (row >= 40 && row <= 55 && col >= 60 && col <= 85)
				{
					PlaySound(TEXT("tabclick.wav"), NULL, SND_SYNC);
					break;
				}
				else if (row >= 60 && row <= 75 && col >= 60 && col <= 85)
				{
					PlaySound(TEXT("tabclick.wav"), NULL, SND_SYNC);
					break;
				}

			}
			if (row >= 20 && row <= 35 && col >= 60 && col <= 85)
			{
				PlaySound(TEXT("start.wav"), NULL, SND_ASYNC);
				Sleep(80);
				SetClr(15, 0);
				system("cls");
				main2();
			}
			else if (row >= 40 && row <= 55 && col >= 60 && col <= 85)
			{
				PlaySound(TEXT("start.wav"), NULL, SND_ASYNC);
				Sleep(80);
				SetClr(15, 0);
				system("cls");
				main22();
			}
			else if (row >= 60 && row <= 75 && col >= 60 && col <= 85)
			{
				PlaySound(TEXT("start.wav"), NULL, SND_ASYNC);
				Sleep(80);
				SetClr(15, 0);
				system("cls");
				main23();
			}
		}
		else if (row >= 40 && row <= 55 && col >= 60 && col <= 85)
		{
			SetClr(15, 0);
			system("cls");
			Box5(20, 60, 15, 25);
			Box6(40, 60, 15, 25);
			Box7(60, 60, 15, 25);
			while (true)
			{

				getRowColbyLeftClick(row, col);
				if (row >= 20 && row <= 35 && col >= 60 && col <= 85)
				{
					PlaySound(TEXT("tabclick.wav"), NULL, SND_SYNC);
					break;
				}
				else if (row >= 40 && row <= 55 && col >= 60 && col <= 85)
				{
					PlaySound(TEXT("tabclick.wav"), NULL, SND_SYNC);
					break;
				}
				else if (row >= 60 && row <= 75 && col >= 60 && col <= 85)
				{
					PlaySound(TEXT("tabclick.wav"), NULL, SND_SYNC);
					break;
				}
			}

			if (row >= 20 && row <= 35 && col >= 60 && col <= 85)
			{
				PlaySound(TEXT("start.wav"), NULL, SND_ASYNC);
				Sleep(80);
				SetClr(15, 0);
				system("cls");
				main3();
			}
			else if (row >= 40 && row <= 55 && col >= 60 && col <= 85)
			{
				PlaySound(TEXT("start.wav"), NULL, SND_ASYNC);
				Sleep(80);
				SetClr(15, 0);
				system("cls");
				main32();
			}
			else if (row >= 60 && row <= 75 && col >= 60 && col <= 85)
			{
				PlaySound(TEXT("start.wav"), NULL, SND_ASYNC);
				Sleep(80);
				SetClr(15, 0);
				system("cls");
				main33();
			}
			
		}
		else if (row >= 60 && row <= 75 && col >= 60 && col <= 85)
		{
			SetClr(15, 0);
			system("cls");
			Box5(20, 60, 15, 25);
			Box6(40, 60, 15, 25);
			Box7(60, 60, 15, 25);
			while (true)
			{
				getRowColbyLeftClick(row, col);
				if (row >= 20 && row <= 35 && col >= 60 && col <= 85)
				{
					PlaySound(TEXT("tabclick.wav"), NULL, SND_SYNC);
					break;
				}
				else if (row >= 40 && row <= 55 && col >= 60 && col <= 85)
				{
					PlaySound(TEXT("tabclick.wav"), NULL, SND_SYNC);
					break;
				}
				else if (row >= 60 && row <= 75 && col >= 60 && col <= 85)
				{
					PlaySound(TEXT("tabclick.wav"), NULL, SND_SYNC);
					break;
				}
			}
			if (row >= 20 && row <= 35 && col >= 60 && col <= 85)
			{
				PlaySound(TEXT("start.wav"), NULL, SND_ASYNC);
				Sleep(80);
				SetClr(15, 0);
				system("cls");
				main4();
			}
			else if (row >= 40 && row <= 55 && col >= 60 && col <= 85)
			{
				PlaySound(TEXT("start.wav"), NULL, SND_ASYNC);
				Sleep(80);
				SetClr(15, 0);
				system("cls");
				main42();
			}
			else if (row >= 60 && row <= 75 && col >= 60 && col <= 85)
			{
				PlaySound(TEXT("start.wav"), NULL, SND_ASYNC);
				Sleep(80);
				SetClr(15, 0);
				system("cls");
				main43();
			}
		}
	}

	return _getch();
}





// yahi hai


