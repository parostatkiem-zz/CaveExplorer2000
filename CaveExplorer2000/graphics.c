#include "graphics.h"
#include "gameEngine.h"

#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>

int lastI = 0;
char buf[256];

void RefreshMap()
{

	if (GameState != 1)
		return;

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


	//czy portal jest w zasi�gu mapy
	tmp= GetOnScreenPos(portal);
	if(tmp.X>=0 && tmp.X<=ViewportW &&tmp.Y >= 0 && tmp.Y <= ViewportH)
	{ 
		setColor(kolor_portal);
		putCharXY(portal.X - viewport.X, portal.Y - viewport.Y, blok_portal);
	}
	setColor(0x0F);
}

void RefreshGui()
{

	if (GameState != 1)
		return;
	int hpPercent = player.hp * 15 /player.maxhp;
		int i;


	
		

		///==========HP=========
	
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
	
		setColor(0x04);

		snprintf(buf, sizeof buf, "%d", player.hp);
		putStrXY(ViewportW + 6+15+2, 1, buf);  //current level number
		
		///==========LVL=========
		int lvlPercent = player.exp * 15 / ExpToNextLevel;
	

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
		putStrXY(ViewportW + 7, 4, buf);  //current level number
		setColor(0x08);


		snprintf(buf, sizeof buf, "%d", player.level+1);
		putStrXY(ViewportW + 7+15-1, 4, buf); //next level number


		
		setColor(kolor_menu_aktywny);
		snprintf(buf, sizeof buf, "%d - %d", (int)(player.damage * MinDamageMultiplier), player.damage);
		putStrXY(ViewportW + 7, 6, buf); //player min and max damage number

	/*	///==========Portal=========
		

		float maxDist = sqrt(pow(MapMaxX,2)+ pow(MapMaxY, 2));
		float dist = CalculateDistance(player.position, portal);
		float tmp = (float)(dist / maxDist);
		float val = tmp*13;
	
	
		setColor(0x0F);
		putStrXY(ViewportW + 2, 8, "Portal: ");
		
			
			setColor(0x08);
			c = 176;
			for (int i = 1; i <= 13; i++)
			{

				if (i > val)
				{
					setColor(kolor_portal);
			
					c = 178;
				}

				putCharXY(ViewportW + 9 + 13- i, 8, c);
			}

	*/


		//==============DEBUG============
		//snprintf(buf, sizeof buf, "Player: %d,%d", player.position.X,player.position.Y);
		//putStrXY(ViewportW + 7 , 8, buf); //next level number

		//snprintf(buf, sizeof buf, "Portal: %d,%d", portal.X, portal.Y);
		//putStrXY(ViewportW + 7 , 9, buf); //next level number




	
		
}

void InitGui()
{
	setColor(0x0f);
	putStrXY(ViewportW + 2, 1, "HP: ");
	setColor(0x0F);
	putStrXY(ViewportW + 2, 3, "LVL: ");
	setColor(0x0F);
	putStrXY(ViewportW + 2, 6, "DMG: ");
	setColor(0x0F);
	putStrXY(ViewportW + 2, 8, "Portal: ");
}

void Log(char* text, int num)
{
	


//	putStrXY(ViewportW + 7, 4, buf);  //current level number

	
	if (num <0)
	{
		//gracz przyjal obrazenia
		setColor(0x04);
		snprintf(buf, sizeof buf, "%s: %d", text, -num);
	}
	else if (num > 0)
	{
		//gracz zadal obrazenia
		setColor(0x0A);
		snprintf(buf, sizeof buf, "%s: %d", text, num);

	}
	else
	{
		//inna wiadomosc
		setColor(0x08);
		snprintf(buf, sizeof buf, "%s", text);
	}
	putStrXY(ViewportW + 1, ViewportH - 1 - LogLevel, buf);  
	LogLevel++;
}

void ClearLog()
{
	LogLevel = 0;
	int i = 0;
	for (i = 8; i < ViewportH; i++)
	{
		putStrXY(ViewportW + 1,i , "                                      ");
	}
}

void ShowDeathScreen()
{
	system("cls");
	setColor(kolor_logo);
	printf("                                     ____\n");
	printf("                              __,---'     `--.__\n");
	printf("                           ,-'                ; `.\n");
	printf("                          ,'                  `--.`--.\n");
	printf("                         ,'                       `._ `-.\n");
	printf("                         ;                     ;     `-- ;\n");
	printf("                       ,-'-_       _,-~~-.      ,--      `.\n");
	printf("                       ;;   `-,;    ,'~`.__    ,;;;    ;  ;\n");
	printf("                       ;;    ;,'  ,;;      `,  ;;;     `. ;\n");
	printf("                       `:   ,'    `:;     __/  `.;      ; ;\n");
	printf("                        ;~~^.   `.   `---'~~    ;;      ; ;\n");
	printf("                        `,' `.   `.            .;;;     ;'\n");
	printf("                        ,',^. `.  `._    __    `:;     ,'\n");
	printf("                        `-' `--'    ~`--'~~`--.  ~    ,'\n");
	printf("                       /;`-;_ ; ;. /. /   ; ~~`-.     ;\n");
	printf("-._                   ; ;  ; `,;`-;__;---;      `----'\n");
	printf("   `--.__             ``-`-;__;:  ;  ;__;\n");
	printf(" ...     `--.__                `-- `-'\n");
	printf("`--.:::...     `--.__                ____\n");
	printf("    `--:::::--.      `--.__    __,--'    `.\n");
	printf("        `--:::`;....       `--'       ___  `.\n");
	printf("            `--`-:::...     __           )  ;\n");
	printf("                  ~`-:::...   `---.      ( ,'\n");
	printf("                      ~`-:::::::::`--.   `-.\n");
	printf("                          ~`-::::::::`.    ;\n");
	printf("                              ~`--:::,'   ,'\n");
	printf("                                   ~~`--'~\n");


	//przezyles xxx itd.

}

