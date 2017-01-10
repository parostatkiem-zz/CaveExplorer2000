//CAVE EXPLORER 2000
#include "config.h"
#include "console.h"
#include "gameEngine.h"
#include "gameSave.h" 



unsigned char map[200][200];
unsigned int GameState = 0;
unsigned int LogLevel = 0;
unsigned int Turns = 0;
unsigned int CurrentLevel = 0;
unsigned int EnemiesKilled = 0;

struct playerClass player;
COORD viewport;
COORD portal;



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