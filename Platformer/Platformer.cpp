#include <stdio.h>
#include <stdlib.h>

#define MapWeight 120
#define MapHeight 50

char Map[MapHeight][MapWeight+1];

void Init() {
	for (int i = 0;i < MapWeight;i++)
		Map[0][i] = '#';
	Map[0][MapWeight] = '\0';

	for (int i = 1;i < MapHeight;i++) {
		sprintf(Map[i], Map[0]);
	}
}

void Show() {
	for (int i = 0;i < MapHeight;i++)
		printf("%s\n", Map[i]);
}

int main()
{
	Init();
	Show();
}

