#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <Windows.h>

#pragma warning(disable : 4996)

#define MapWeight 120
#define MapHeight 50

typedef struct {
	float x, y;
	float VertSpeed;
	float weight, height;
}OBJECT;

OBJECT Player,Brick[1];

char Map[MapHeight][MapWeight+1];

void Init() {
	for (int i = 0;i < MapWeight;i++)
		Map[0][i] = ' ';
	Map[0][MapWeight] = '\0';

	for (int i = 1;i < MapHeight;i++) {
	 sprintf(Map[i], Map[0]);
	}
}

void ObjectSetPos(OBJECT *obj,float x,float y)
{
	(*obj).x = x;
	(*obj).y = y; 
}

BOOL IsPosInMap(int x, int y) {
	return (x>=0) && (x<MapWeight) && (y>=0) && (y<MapHeight);
}
BOOL Collision(OBJECT obj,OBJECT obj2) {
	return 
}

void PutObject(OBJECT obj) {
	int ix = (int)round(obj.x);
	int iy = (int)round(obj.y);
	int iWeight = (int)round(obj.weight);
	int iHeight = (int)round(obj.height);
	for(int i=iy;i<iy+iHeight;i++)
		for(int j=ix;j<ix+iWeight;j++)
			if(IsPosInMap(j,i))
			Map[i][j] = '#';
}

void InitObject(OBJECT *obj,float x,float y,float weight,float height) {
	ObjectSetPos(obj, x, y);
	(*obj).weight = weight;
	(*obj).height = height;
	(*obj).VertSpeed = 0;
}

void VertMoveObject(OBJECT *obj) {
	(*obj).y += (*obj).VertSpeed;
	(*obj).VertSpeed += 0.05;
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
	InitObject(&Player,20,30,5,2.5);
	InitObject(&Brick[0], 0, 44, 50, 6);
	do {
		Init();
		VertMoveObject(&Player);
		PutObject(Player);
		PutObject(Brick[0]);
		SetCur(0, 0);
		Show();
		Sleep(10);
	} while (GetKeyState(VK_ESCAPE) >= 0);
}

