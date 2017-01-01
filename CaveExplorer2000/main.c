//CAVE EXPLORER 2000
#include "config.h"
#include "console.h"
#include "gameEngine.h"
#include "init.h"

unsigned char map[MapMaxX][MapMaxY];
unsigned int GameState = 0;
struct playerClass player;
COORD viewport;



struct Enemy enemies[MaxEnemyNum];

int main()
{
	
	initScreen();


	player.hp = PlayerStartHp - 3; // -3 dla testów
	player.damage = PlayerStartDamage;
	player.maxhp = PlayerStartHp;
	player.exp =9; //start exp

	player.level = 1;

	ShowMenu();




	system("PAUSE");
   return 0;
}