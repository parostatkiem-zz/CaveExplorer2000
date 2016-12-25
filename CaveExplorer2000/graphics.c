#include "graphics.h"
#include "gameEngine.h"

#include <stdlib.h>
#include <stdio.h>
#include <conio.h>




void RefreshMap()
{

	int x = 0;
	int y = 0;


	viewport.X = player.position.X - ViewportW / 2;
	viewport.Y = player.position.Y - ViewportH / 2;

	
	//system("CLS");

	char c;
	COORD tmp;
	for (y = viewport.Y; y < viewport.Y+ViewportH; y++)
	{
		for (x = viewport.X; x < viewport.X+ViewportW; x++)
		{
			tmp.X =x - ViewportH / 2;
			tmp.Y = y ;
			


			c = map[y][x];
			if (x < 0 || x >= MapMaxX || y < 0 || y >= MapMaxY)
			{
				setColor(kolor_tlo);
				printf(" ");
				setColor(0x0F);
				continue;
			}


			
			switch (c)
			{
			case (char)blok_gracz:
					setColor(kolor_gracz);
				break;

				case (char)(blok_zwykly):
					setColor(kolor_blok_zwykly);
				break;

				case (char)blok_przeciwnik:
					setColor(kolor_blok_przeciwnik);
					break;

				case (char)blok_staly:
					setColor(kolor_blok_staly);
					break;
			}
			//if (CalculateDistance(player,tmp)<=Visibility)
			printf("%c",c );

			setColor(0x0F);
			
		}
		printf("\n");
	}
	setColor(kolor_gracz);
	putCharXY( player.position.X-viewport.X, player.position.Y - viewport.Y, blok_gracz);
	setColor(0x0F);
}

void RefreshGui()
{
	char buf[256];
	//setColor
	int hpPercent = player.hp * 15 /player.maxhp;
		int i;

	//snprintf(buf, sizeof buf, "Enemy: (%d,%d)", enemies[0].position.X, enemies[0].position.Y);
	
		

		///==========HP=========
		setColor(kolor_menu);
		putStrXY(ViewportW + 2, 1, "HP: ");
		setColor(0x04);
		char c = 178;
		for (int i = 1; i <= 15; i++)
		{
		
			if (i > hpPercent)
			{
				setColor(0x08);
				c = 176;
			}

			putCharXY(ViewportW + 6+i, 1, c);
		}
		int dif = player.nextLevelAt - player.exp;
		//int lvlPercent= 15-;
		///==========HP=========
		setColor(kolor_menu);
		putStrXY(ViewportW + 2, 3, "LVL: ");
		setColor(0x0A);
		 c = 178;
		for (int i = 1; i <= 15; i++)
		{

			if (i > lvlPercent)
			{
				setColor(0x08);
				c = 176;
			}

			putCharXY(ViewportW + 6 + i, 3, c);
		}
		setColor(0x0A);

		snprintf(buf, sizeof buf, "%d", player.level);
		putStrXY(ViewportW + 7, 4, buf);
		setColor(0x08);
		snprintf(buf, sizeof buf, "%d", player.level+1);
		putStrXY(ViewportW + 7+15-1, 4, buf);
		
}