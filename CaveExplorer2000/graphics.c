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

	for (y = viewport.Y; y < viewport.Y+ViewportH; y++)
	{
		for (x = viewport.X; x < viewport.X+ViewportW; x++)
		{
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
				case blok_gracz:
					setColor(kolor_gracz);
				break;

				case blok_zwykly:
					setColor(kolor_blok_zwykly);
				break;

				case blok_staly:
					setColor(kolor_blok_staly);
					break;
			}
			printf("%c",c );
			setColor(0x0F);
			
		}
		printf("\n");
	}
	setColor(0x0B);
	putCharXY( player.X-viewport.X, player.Y - viewport.Y, blok_gracz);
	setColor(0x0F);
}