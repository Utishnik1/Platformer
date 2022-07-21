#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <Windows.h>

#pragma warning(disable : 4996)
#pragma warning(disable : 6308) 

int level = 0;

#define MapWeight 120
#define MapHeight 50

typedef struct {
	float x, y;
	float VertSpeed;
	float weight, height;
	BOOL IsFly;
	char Type;
	float horizontalspeed;
	int Coints;
}OBJECT;

OBJECT* moving = NULL;
int lenMoving = 1;

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
BOOL Collision(OBJECT obj, OBJECT obj2,float *fy) {
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

void initObject(OBJECT* obj, float x, float y, float weight, float height,char Type) {
	ObjectSetPos(obj, x, y);
	(*obj).weight = weight;
	(*obj).height = height;
	(*obj).VertSpeed = 0;
	(*obj).Type = Type;
	(*obj).horizontalspeed = 0.5;
	(*obj).Coints = 0;
}


void CreateLevel(int level);

void DeleteMoving(int i) {
	//lenMoving--;//3
	//moving[lenMoving] = moving[i];
	//moving = realloc(moving, sizeof(*moving) * lenMoving); при этом коде если допустим прыгнуть на 0 движущийся обьект то умрут все остальные и он сам
	lenMoving--;
	moving[i] = moving[lenMoving];
	moving = realloc(moving, sizeof(*moving) * lenMoving);
}

void PlayerCollision() {
	for(int i=0;i<lenMoving;i++)
		if (Collision(Player, *(moving+i),&Player.y)) {
			if ((Player.IsFly==TRUE)&&(Player.VertSpeed>0)&&(Player.y+Player.height<moving[i].y+moving[i].height*0.5))
			{
				DeleteMoving(i);
				i--;
				continue;
			}
			else {
				if((moving[i].Type=='0')||(moving[i].Type=='o'))
					CreateLevel(level);
				else
				{
					DeleteMoving(i);
					i--;
					Player.Coints++;
					continue;
				}
			}
		}
}

void VertMoveObject(OBJECT* obj);


void HorizontalObjectMove(OBJECT* obj) {
	(*obj).x += (*obj).horizontalspeed;

	for (int i = 0;i < BrickLenght;i++) {
		if (Collision((*obj), Brick[i],&((*obj).y)))
		{
			(*obj).x -= (*obj).horizontalspeed;
			(*obj).horizontalspeed = (*obj).horizontalspeed * (-1);
		}
	}
	if((*obj).Type!='$'){
		OBJECT Tobj = *obj;
		VertMoveObject(&Tobj);
		if (Tobj.IsFly == TRUE) {
			(*obj).x -= (*obj).horizontalspeed;
			(*obj).horizontalspeed = (-1) * (*obj).horizontalspeed;
		}
	}
}

OBJECT* getNewBrick()
{
	BrickLenght++;
	Brick = realloc(Brick,sizeof(*Brick)*BrickLenght);
	return Brick+ BrickLenght-1;
}

OBJECT* getNewMoving()
{
	lenMoving++;
	moving = realloc(moving, sizeof(*moving) * lenMoving);
	return moving + lenMoving-1;
}
void CreateLevel(int level) 
{
	system("color A");
	BrickLenght = 0;
	lenMoving = 0;
	if (level == 0) {
		initObject(&Player, 20, 30, 5, 2.5, '#');
		initObject(getNewBrick(), 0, 44, 50, 6, '@');
		initObject(getNewBrick(), 53, 40, 35, 6, '@');
		initObject(getNewBrick(), 90, 41, 35, 6, '@');
		initObject(getNewBrick(), 128, 42, 35, 6, '@');
		initObject(getNewBrick(), 166, 39, 35, 6, '+');

		initObject(getNewMoving(), 0, 36, 4, 2, '0');
		initObject(getNewMoving(), 2, 38, 5, 2.5, '0');
		initObject(getNewMoving(), 55, 34, 5, 2.5, '0');
		initObject(getNewMoving(), 91, 30, 5, 2.5, '0');
		initObject(getNewMoving(), 130, 35, 5, 2.5, '0');
	}
	else if (level == 1) {

			ObjectSetPos(&Player, 0, 0);
			initObject(getNewBrick(), 0, 21, 207, 4, '#');

			initObject(getNewBrick(), 48, 13, 3, 2, '?');
			initObject(getNewBrick(), 60, 13, 3, 2, '#');
			initObject(getNewBrick(), 63, 13, 3, 2, '?');
			initObject(getNewBrick(), 66, 13, 3, 2, '#');
			initObject(getNewBrick(), 69, 13, 3, 2, '?');
			initObject(getNewBrick(), 72, 13, 3, 2, '#');
			initObject(getNewBrick(), 66, 5, 3, 2, '?');

			initObject(getNewBrick(), 84, 17, 6, 2, '#');
			initObject(getNewBrick(), 85, 19, 4, 2, '#');

			initObject(getNewBrick(), 114, 15, 6, 2, '#');
			initObject(getNewBrick(), 115, 17, 4, 4, '#');

			initObject(getNewBrick(), 138, 13, 6, 2, '#');
			initObject(getNewBrick(), 139, 15, 4, 6, '#');

			initObject(getNewBrick(), 171, 13, 6, 2, '#');
			initObject(getNewBrick(), 172, 15, 4, 6, '#');
			// --
			initObject(getNewBrick(), 213, 21, 45, 4, '#');
			initObject(getNewBrick(), 231, 13, 3, 2, '#');
			initObject(getNewBrick(), 234, 13, 3, 2, '?');
			initObject(getNewBrick(), 237, 13, 3, 2, '#');
			initObject(getNewBrick(), 240, 5, 24, 2, '#');
			// --
			initObject(getNewBrick(), 267, 21, 192, 4, '#');
			initObject(getNewBrick(), 273, 5, 9, 2, '#');
			initObject(getNewBrick(), 282, 5, 3, 2, '?');
			initObject(getNewBrick(), 282, 13, 3, 2, '?');
			initObject(getNewBrick(), 300, 13, 6, 2, '#');
			initObject(getNewBrick(), 318, 13, 3, 2, '?');
			initObject(getNewBrick(), 327, 13, 3, 2, '?');
			initObject(getNewBrick(), 327, 5, 3, 2, '?');
			initObject(getNewBrick(), 336, 13, 3, 2, '?');
			initObject(getNewBrick(), 354, 13, 3, 2, '#');
			initObject(getNewBrick(), 363, 5, 9, 2, '#');
			initObject(getNewBrick(), 384, 5, 3, 2, '#');
			initObject(getNewBrick(), 387, 5, 3, 2, '?');
			initObject(getNewBrick(), 390, 5, 3, 2, '?');
			initObject(getNewBrick(), 393, 5, 3, 2, '#');
			initObject(getNewBrick(), 387, 13, 6, 2, '#');
			//лестница
			initObject(getNewBrick(), 402, 19, 12, 2, '#');
			initObject(getNewBrick(), 405, 17, 9, 2, '#');
			initObject(getNewBrick(), 408, 15, 6, 2, '#');
			initObject(getNewBrick(), 411, 13, 3, 2, '#');

			initObject(getNewBrick(), 420, 13, 3, 2, '#');
			initObject(getNewBrick(), 420, 15, 6, 2, '#');
			initObject(getNewBrick(), 420, 17, 9, 2, '#');
			initObject(getNewBrick(), 420, 19, 12, 2, '#');

			initObject(getNewBrick(), 444, 19, 15, 2, '#');
			initObject(getNewBrick(), 447, 17, 12, 2, '#');
			initObject(getNewBrick(), 450, 15, 9, 2, '#');
			initObject(getNewBrick(), 453, 13, 6, 2, '#');
			// --
			initObject(getNewBrick(), 465, 21, 165, 4, '#');
			initObject(getNewBrick(), 465, 13, 3, 2, '#');
			initObject(getNewBrick(), 465, 15, 6, 2, '#');
			initObject(getNewBrick(), 465, 17, 9, 2, '#');
			initObject(getNewBrick(), 465, 19, 12, 2, '#');

			initObject(getNewBrick(), 489, 17, 6, 2, '#');
			initObject(getNewBrick(), 490, 19, 4, 2, '#');

			initObject(getNewBrick(), 504, 13, 6, 2, '#');
			initObject(getNewBrick(), 510, 13, 3, 2, '?');
			initObject(getNewBrick(), 513, 13, 3, 2, '#');

			initObject(getNewBrick(), 537, 17, 6, 2, '#');
			initObject(getNewBrick(), 538, 19, 4, 2, '#');
			// лестница большая
			initObject(getNewBrick(), 543, 19, 27, 2, '#');
			initObject(getNewBrick(), 546, 17, 24, 2, '#');
			initObject(getNewBrick(), 549, 15, 21, 2, '#');
			initObject(getNewBrick(), 552, 13, 18, 2, '#');
			initObject(getNewBrick(), 555, 11, 15, 2, '#');
			initObject(getNewBrick(), 558, 9, 12, 2, '#');
			initObject(getNewBrick(), 561, 7, 9, 2, '#');
			initObject(getNewBrick(), 564, 5, 6, 2, '#');

			// замок
			initObject(getNewBrick(), 600, 16, 10, 5, '+');
			initObject(getNewBrick(), 600, 15, 1, 1, '+');
			initObject(getNewBrick(), 609, 15, 1, 1, '+');
			initObject(getNewBrick(), 604, 17, 2, 4, '-');
			initObject(getNewBrick(), 602, 12, 6, 4, '+');
			initObject(getNewBrick(), 602, 11, 1, 1, '+');
			initObject(getNewBrick(), 604, 11, 2, 1, '+');
			initObject(getNewBrick(), 607, 11, 1, 1, '+');
			initObject(getNewBrick(), 603, 13, 1, 2, '-');
			initObject(getNewBrick(), 606, 13, 1, 2, '-');

			initObject(getNewMoving(), 66, 16, 3, 2, 'o');
			initObject(getNewMoving(), 121, 16, 3, 2, 'o');
			initObject(getNewMoving(), 153, 16, 3, 2, 'o');
			initObject(getNewMoving(), 159, 16, 3, 2, 'o');

			initObject(getNewMoving(), 238, 1, 3, 2, 'o');
			initObject(getNewMoving(), 246, 1, 3, 2, 'o');
			initObject(getNewMoving(), 288, 16, 3, 2, 'o');
			initObject(getNewMoving(), 294, 16, 3, 2, 'o');
			initObject(getNewMoving(), 321, 16, 3, 2, 'o');
			initObject(getNewMoving(), 342, 16, 3, 2, 'o');
			initObject(getNewMoving(), 348, 16, 3, 2, 'o');
			initObject(getNewMoving(), 370, 16, 3, 2, 'o');
			initObject(getNewMoving(), 376, 16, 3, 2, 'o');
			initObject(getNewMoving(), 385, 16, 3, 2, 'o');
			initObject(getNewMoving(), 391, 16, 3, 2, 'o');

			initObject(getNewMoving(), 522, 16, 3, 2, 'o');
			initObject(getNewMoving(), 526, 16, 3, 2, 'o');
	}

}

void VertMoveObject(OBJECT* obj) {
	(*obj).IsFly = TRUE;
	(*obj).VertSpeed += 0.05f;
	(*obj).y += (*obj).VertSpeed;
	for (int i = 0;i < BrickLenght;i++)
		if (Collision(*obj, Brick[i],&((*obj).y))) {
			if((*obj).VertSpeed>0)
				(*obj).IsFly = FALSE;
			if ((Brick[i].Type == '?') && ((*obj).VertSpeed<0) && (obj == &Player)) {
				Brick[i].Type = '-';
				initObject(getNewMoving(), Brick[i].x, Brick[i].y - 5, 3, 1.5, '$');
			}
			(*obj).y -= (*obj).VertSpeed;
			(*obj).VertSpeed = 0;
			if (Brick[i].Type == '+')
			{
				system("cls");
				printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tWIN!!!!!!!!\n");
				system("cls");
				Sleep(1000);
				if (level > 1)
					level = 0;
				else
					level++;
				Init();
				CreateLevel(level);
			}
			break;
		}
}

void MoveMap(int dx) {
	Player.x -= dx;
	for(int i=0;i<BrickLenght;i++)
		if (Collision(Player, Brick[i],&Player.y))
		{
			Player.x += dx;
			return;
		}
	Player.x += dx;
	for (int i = 0;i < BrickLenght;i++) 
		Brick[i].x += dx;
	for (int i = 0;i < lenMoving;i++)
		moving[i].x += dx;
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
	level = 0;
	CreateLevel(level);
	do {
		Init();//////////////////////////////////---
		if (GetKeyState(VK_SPACE) < 0 && Player.IsFly == FALSE)
			Player.VertSpeed = -1;
		if (GetKeyState('J') < 0)
			Player.VertSpeed = -1;
		if (GetKeyState('A')<0) MoveMap(1);
		if (GetKeyState('D')<0) MoveMap(-1);

		

		if (Player.y > MapHeight) CreateLevel(level);
   		VertMoveObject(&Player);
		//printf("\t\t\t\t\t\t\t\t\t\t%f %f %f %d", Player.x, Player.y,Player.VertSpeed,level);
		printf("\t\t\t\t\t\t\t\t\t\t%d", Player.Coints);
		PlayerCollision();
		for(int i=0;i<BrickLenght;i++)
			PutObject(Brick[i]);
		for (int i = 0;i < lenMoving;i++) {
 			VertMoveObject(moving+i);
			if (moving[i].y > MapHeight)
			{
				DeleteMoving(i);
				i--;
				continue;
			}
			HorizontalObjectMove(moving + i);
			PutObject(moving[i]);
		}
		PutObject(Player);
		SetCur(0, 0);
		Show();
 		Sleep(10);
	} while (GetKeyState(VK_ESCAPE) >= 0);

	
	/*
	float x = 0.7;
	int y=0;
	for (int i = 0;i < 20;i++)
	{
		y += (int)round(x);
		printf("%d %f %d\n", i, x, y);
		x -= 0.05;
	}
	*/

}