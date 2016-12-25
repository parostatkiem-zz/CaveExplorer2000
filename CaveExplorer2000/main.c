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

	ShowMenu();


	player.hp = PlayerStartHp -3;
	player.damage = PlayerStartDamage;
	player.maxhp = PlayerStartHp;


	InitializeLevel(1);
	
	RefreshMap();
	RefreshGui();
	GameState = 1;

	Move();

	system("PAUSE");
   return 0;
}