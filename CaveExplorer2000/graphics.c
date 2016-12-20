#include "graphics.h"
#include "gameEngine.h"

#include <stdlib.h>
#include <stdio.h>
#include <conio.h>




void RefreshMap()
{
	int x = 0;
	int y = 0;


	viewport.X = player.X - ViewportW / 2;
	viewport.Y = player.Y - ViewportH / 2;

	
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
	putCharXY( player.X-viewport.X, player.Y - viewport.Y, blok_gracz);
	setColor(0x0F);
}

void RefreshGui()
{
	char buf[256];
	//setColor
	//int hpPercent = player


	snprintf(buf, sizeof buf, "Enemy: (%d,%d)", enemies[0].position.X, enemies[0].position.Y);
	putStrXY(ViewportW + 5, 13, buf);
}