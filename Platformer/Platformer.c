#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <Windows.h>

#pragma warning(disable : 4996)
#pragma warning(disable : 6308) 


#define MapWeight 120
#define MapHeight 50

typedef struct {
	float x, y;
	float VertSpeed;
	float weight, height;
	BOOL IsFly;
	char Type;
}OBJECT;

OBJECT Player;
int BrickLenght = 1;
OBJECT *Brick = NULL;

char Map[MapHeight][MapWeight + 1];

void Init() {
	for (int i = 0;i < MapWeight;i++)
		Map[0][i] = ' ';
	Map[0][MapWeight] = '\0';

	for (int i = 1;i < MapHeight;i++) {
		sprintf(Map[i], Map[0]);
	}
}

void ObjectSetPos(OBJECT* obj, float x, float y)
{
	(*obj).x = x;
	(*obj).y = y;
}


BOOL IsPosInMap(int x, int y) {
	return (x >= 0) && (x < MapWeight) && (y >= 0) && (y < MapHeight);
}
BOOL Collision(OBJECT obj, OBJECT obj2) {
	return ((obj2.x < (obj.x + obj.weight)) && (obj.x < (obj2.x + obj2.weight)) && (obj2.y < (obj.y + obj.height)) && (obj.y < (obj2.y + obj2.height)));
}

void PutObject(OBJECT obj) {
	int ix = (int)round(obj.x);
	int iy = (int)round(obj.y);
	int iWeight = (int)round(obj.weight);
	int iHeight = (int)round(obj.height);
	for (int i = iy;i < iy + iHeight;i++)
		for (int j = ix;j < ix + iWeight;j++)
			if (IsPosInMap(j, i))
				Map[i][j] = obj.Type;
}

void InitObject(OBJECT* obj, float x, float y, float weight, float height,char Type) {
	ObjectSetPos(obj, x, y);
	(*obj).weight = weight;
	(*obj).height = height;
	(*obj).VertSpeed = 0;
	(*obj).Type = Type;
}
void CreateLevel() 
{
	InitObject(&Player, 20, 30, 5, 2.5,'#');
	BrickLenght = 3;
	Brick = realloc(Brick,sizeof(Brick) * BrickLenght);
	InitObject(Brick, 0, 44, 50, 6,'#');
	InitObject(Brick+1, 53, 40, 35, 6,'#');
	InitObject(Brick+2, 90, 38, 35, 6,'+');
}

void VertMoveObject(OBJECT* obj) {
	(*obj).IsFly = TRUE;
	(*obj).y += (*obj).VertSpeed;
	(*obj).VertSpeed += 0.05f;
	for(int i=0;i<BrickLenght;i++)
		if (Collision(Player, Brick[i])) {
			if (Brick[i].Type == '+')
			{
				system("cls");
				printf("\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\tWIN!!!!!!!!\n");
				Sleep(1000);
				CreateLevel();
			}
			(*obj).y -= (*obj).VertSpeed;
			(*obj).VertSpeed = 0;
			(*obj).IsFly = FALSE;
			break;
		}
}

void MoveMap(int dx) {
	Player.x -= dx;
	for(int i=0;i<BrickLenght;i++)
		if (Collision(Player, Brick[i]))
		{
			Player.x += dx;
			return;
		}
	Player.x += dx;
	for(int i=0;i<BrickLenght;i++)
		Brick[i].x += dx;
}

void Show() {
	for (int i = 0;i < MapHeight;i++)
		printf("%s\n", Map[i]);
}

void SetCur(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int main()
{
	CreateLevel();
	do {
		Init();
		if (GetKeyState(VK_SPACE) < 0 && Player.IsFly == FALSE)
			Player.VertSpeed = -1;
		if (GetKeyState('A')<0) MoveMap(1);
		if (GetKeyState('D')<0) MoveMap(-1);

		if (Player.y > MapHeight) CreateLevel();
		VertMoveObject(&Player);
		PutObject(Player);
		for(int i=0;i<BrickLenght;i++)
			PutObject(Brick[i]);
		SetCur(0, 0);
		Show();
		Sleep(10);
	} while (GetKeyState(VK_ESCAPE) >= 0);
}