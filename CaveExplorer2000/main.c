//CAVE EXPLORER 2000
#include "config.h"
#include "console.h"
#include "gameEngine.h"
#include "init.h"

unsigned char map[MapMaxX][MapMaxY];
unsigned int GameState = 1;
COORD player;
COORD viewport;




int main()
{
	
	initScreen();
	InitializeLevel(1);
	
	RefreshMap();
	

	Move();

	system("PAUSE");
   return 0;
}