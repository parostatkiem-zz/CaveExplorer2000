#include "gameEngine.h"
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>

int CaveSegments = 0;

void InitializeLevel(int level)
{
	srand(time(NULL));
	int x = 0;
	int y = 0;

	
	for (x = 0; x < MapMaxX; x++)
	{
		for (y = 0; y < MapMaxY; y++)
		{
			if (x == 0 || x == MapMaxX-1 || y == 0 || y == MapMaxY-1)
				map[y][x] = blok_staly; //otaczanie mapy nierozbijalnymi blokami
			else
				map[y][x] = blok_zwykly; // wype³nianie mapy blokami do rozwalenia
		}
	}

	//generowanie jaskiñ
	int i = 0;
	for (i = 0; i <= CavesPerLevel; i++)
	{
		CaveSegments = 0;
		COORD tmp;
		tmp.X = RandomInt(1,MapMaxX-1);
		tmp.Y = RandomInt(1, MapMaxX-1);
		//map[tmp.X][tmp.Y] = blok_pusty;
		AddCaveSegment(tmp);
	
	}

	//ustawianie gracza
	PlacePlayer();



}

 int RandomInt( int min,  int max)
{
	int r;
	const unsigned int range = 1 + max - min;
	const unsigned int buckets = RAND_MAX / range;
	const unsigned int limit = buckets * range;

	
	do
	{
		r = rand();
	} while (r >= limit);

	return min + (r / buckets);
}

 void CheckRefresh()
 {
	 if (player.X - viewport.X <= DTETR || player.X - viewport.X >= ViewportW - DTETR || player.Y - viewport.Y <= DTETR || player.Y - viewport.Y >= ViewportH - DTETR)
	 {
		 RefreshMap();
	 }
 }


void AddCaveSegment(COORD punkt)
{
	int a = RandomInt(0, 100);
	unsigned char b = map[punkt.Y][punkt.X];
	unsigned char c = blok_zwykly;

	
	if ( b==blok_zwykly && a<CaveSize || CaveSegments<MinCaveSize && b == blok_zwykly) 
	{
		CaveSegments++;
		map[punkt.Y][punkt.X] = blok_pusty;


		//generowanie segmentów dla s¹siednich 4 pól
		COORD tmp;
		tmp.X = punkt.X+1;
		tmp.Y = punkt.Y;
		AddCaveSegment(tmp);

		tmp.X = punkt.X;
		tmp.Y = punkt.Y +1;
		AddCaveSegment(tmp);

		tmp.X = punkt.X - 1;
		tmp.Y = punkt.Y;
		AddCaveSegment(tmp);

		tmp.X = punkt.X ;
		tmp.Y = punkt.Y -1;
		AddCaveSegment(tmp);
	}
}

void PlacePlayer()
{
	COORD tmp;
	tmp.X = RandomInt(1, MapMaxX - 1);
	tmp.Y = RandomInt(1, MapMaxX - 1);

	unsigned char b = map[tmp.Y][tmp.X];
	unsigned char c = blok_pusty;

	if (b == c)
	{
		//map[tmp.X][tmp.Y] = blok_gracz;
		player = tmp;
	
		return;
	}
	else
	{
		PlacePlayer();
	}
	
}

void Move()
{
	unsigned char znak;
	do
	{
		znak = getKey();
				if (znak == 0 || znak == 0xE0) znak = getKey();
			switch (znak) 
			{ // the real value
			case 72:
				TryMove(72);
				CheckRefresh();
				break;
			case 80:
				TryMove(80);
				CheckRefresh();
				break;
			case 77:
				TryMove(77);
				CheckRefresh();
				break;
			case 75:
				TryMove(75);
				CheckRefresh();
				break;
			}
	

	} while (1);


}

void TryMove(char direction)
{
	COORD tmp = player;
	setColor(0x0B);
	switch (direction)
	{ 
	case 72: //gora
		if ( map[player.X][player.Y - 1]==blok_pusty|| map[player.X ][player.Y - 1] == blok_zwykly)
		{
			player.Y--;
			putCharXY(player.X - viewport.X, player.Y - viewport.Y, blok_gracz);
			putCharXY(player.X - viewport.X, player.Y - viewport.Y + 1, blok_pusty);
		}
		break;
	case 80:  //dol
		if (map[player.X][player.Y + 1] == blok_pusty || map[player.X][player.Y + 1] == blok_zwykly)
		{
			player.Y++;
			putCharXY(player.X - viewport.X, player.Y - viewport.Y, blok_gracz);
			putCharXY(player.X - viewport.X , player.Y - viewport.Y - 1, blok_pusty);
		}
		break;
	case 77: //prawo
		if (map[player.X + 1][player.Y ] == blok_pusty || map[player.X + 1][player.Y ] == blok_zwykly)
		{
			player.X++;
			putCharXY(player.X - viewport.X, player.Y - viewport.Y, blok_gracz);
			putCharXY(player.X - viewport.X - 1, player.Y - viewport.Y , blok_pusty);
		}
		break;
	case 75: //lewo
		if (map[player.X - 1][player.Y] == blok_pusty || map[player.X - 1][player.Y ] == blok_zwykly)
		{
			player.X--;
			putCharXY(player.X - viewport.X, player.Y - viewport.Y, blok_gracz);
			putCharXY(player.X - viewport.X + 1, player.Y - viewport.Y , blok_pusty);
			
		}
		break;
	}
	map[player.Y][player.X] = blok_pusty;

	setColor(0x0F);
	//RefreshMap();
//	putCharXY(30, 30, direction);
}
