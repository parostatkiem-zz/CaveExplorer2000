#include "gameEngine.h"
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <math.h>

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
				map[y][x] = blok_zwykly; // wype�nianie mapy blokami do rozwalenia
		}
	}

	//generowanie jaski�
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

	//generowanie przeciwnik�w===================
	struct Enemy e;
	e.position.X = 0;
	e.position.Y = 0;
	for (i = 0; i < MaxEnemyNum; i++) //czyszczenie tablicy przeciwnikow
	{
		enemies[i] = e; //resetowanie pozycji kazdego przeciwnika na (0,0) - oznacza to, �e nie on istnieje
	}


	e.damage = EnemyStartDamage + (EnemyMultiplier*level);
	e.hp = EnemyStartHp + (EnemyMultiplier*level);
	for (i = 0; i < EnemyAmount+(EnemyMultiplier*level)-2; i++)
	{
		int a = EnemyAmount + (EnemyMultiplier*level);
		COORD tmp;
		tmp.X = RandomInt(1, MapMaxX - 1);
		tmp.Y = RandomInt(1, MapMaxX - 1);

		if (map[tmp.Y][tmp.X] == blok_pusty)
		{
			COORD tmp2;
			tmp2.X = tmp.Y;
			tmp2.Y = tmp.X;
			e.position = tmp;
			//wylosowana pozycja jest pusta. Stawianie przeciwnika
			enemies[i] = e;
			map[tmp.Y][tmp.X] = blok_przeciwnik;
		}
		else
			i--;

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
	 if (player.position.X - viewport.X <= DTETR || player.position.X - viewport.X >= ViewportW - DTETR || player.position.Y - viewport.Y <= DTETR || player.position.Y - viewport.Y >= ViewportH - DTETR)
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


		//generowanie segment�w dla s�siednich 4 p�l
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
		player.position = tmp;
	
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
			if(znak==72|| znak == 80 || znak == 77 || znak == 75)
			{
				TryMove(znak);
				MoveEnemies();
				CheckRefresh();
				RefreshGui();
			}
			if (znak == 27) //escape pressed
			{
				ShowMenu();
			}
	

	} while (1);


}

void TryMove(char direction)
{
	COORD tmp = player.position;
	setColor(kolor_gracz);
	switch (direction)
	{ 
	case 72: //gora
		if ( map[player.position.Y - 1][player.position.X ]==blok_pusty|| map[player.position.Y - 1][player.position.X] == blok_zwykly)
		{
			player.position.Y--;
			putCharXY(player.position.X - viewport.X, player.position.Y - viewport.Y, blok_gracz);
			putCharXY(player.position.X - viewport.X, player.position.Y - viewport.Y + 1, blok_pusty);
		}
		break;
	case 80:  //dol
		if (map[player.position.Y + 1][player.position.X] == blok_pusty || map[player.position.Y + 1][player.position.X] == blok_zwykly)
		{
			player.position.Y++;
			putCharXY(player.position.X - viewport.X, player.position.Y - viewport.Y, blok_gracz);
			putCharXY(player.position.X - viewport.X , player.position.Y - viewport.Y - 1, blok_pusty);
		}
		break;
	case 77: //prawo
		if (map[player.position.Y ][player.position.X+1 ] == blok_pusty || map[player.position.Y][player.position.X + 1] == blok_zwykly)
		{
			player.position.X++;
			putCharXY(player.position.X - viewport.X, player.position.Y - viewport.Y, blok_gracz);
			putCharXY(player.position.X - viewport.X - 1, player.position.Y - viewport.Y , blok_pusty);
		}
		break;
	case 75: //lewo
		if (map[player.position.Y][player.position.X - 1] == blok_pusty || map[player.position.Y][player.position.X - 1] == blok_zwykly)
		{
			player.position.X--;
			putCharXY(player.position.X - viewport.X, player.position.Y - viewport.Y, blok_gracz);
			putCharXY(player.position.X - viewport.X + 1, player.position.Y - viewport.Y , blok_pusty);
			
		}
		break;
	}
	map[player.position.Y][player.position.X] = blok_pusty;

	setColor(0x0F);

	//dfvbdfRefreshMap();
//	putCharXY(30, 30, direction);
	return 1;
}

COORD GetOnScreenPos(COORD p)
{
	COORD out;
	out.X = p.X - viewport.X;
	out.Y = p.Y - viewport.Y;
	return out;
}

void MoveEnemies()
{
	int i;
	int xDist = 0;
	int yDist = 0;
	for (i = 0; i < MaxEnemyNum; i++) //p�tla po wszystkich przeciwnikach
	{
		if (enemies[i].position.X == 0 && enemies[i].position.Y == 0)
			break; //koniec p�tli je�li przeciwnik nie istnieje
		
		int tmp = CalculateDistance(enemies[i].position, player.position);
		if (CalculateDistance(enemies[i].position, player.position) <= SeeDistance) //je�li przeciwnik widzi gracza
		{
			setColor(kolor_blok_przeciwnik);
			if (CalculateDistance(enemies[i].position, player.position) <= 1) //przeciwnik stoi ko�o gracza
			{

			}
			else //przeciwnik idzie w kierunku gracza
			{
				xDist = enemies[i].position.X - player.position.X;
				yDist = enemies[i].position.Y - player.position.Y;
				if (abs(xDist) > abs(yDist)) //przeciwnik porusza si� w osi poziomej
				{
					if (xDist > 0) //w lewo
					{
						if (map[enemies[i].position.Y][enemies[i].position.X - 1] == blok_pusty || map[enemies[i].position.Y ][enemies[i].position.X - 1] == blok_gracz)
						{
							//mo�e si� normalnie poruszy� w wyznaczonym kierunku
							enemies[i].position.X--;
							putCharXY(GetOnScreenPos(enemies[i].position).X, GetOnScreenPos(enemies[i].position).Y, blok_przeciwnik);
							putCharXY(GetOnScreenPos(enemies[i].position).X+1, GetOnScreenPos(enemies[i].position).Y, blok_pusty);
							map[enemies[i].position.Y][enemies[i].position.X + 1] = blok_pusty;
						}
						else
						{
							if (yDist > 0) //w gore
							{
								if (map[enemies[i].position.Y - 1][enemies[i].position.X] == blok_pusty || map[enemies[i].position.Y - 1][enemies[i].position.X] == blok_gracz)
								{
									//nie m�g� si� normalnie poruszy�, wi�c rusza wed�ug innej osi
									enemies[i].position.Y--;
									putCharXY(GetOnScreenPos(enemies[i].position).X, GetOnScreenPos(enemies[i].position).Y, blok_przeciwnik);
									putCharXY(GetOnScreenPos(enemies[i].position).X, GetOnScreenPos(enemies[i].position).Y + 1, blok_pusty);
									map[enemies[i].position.Y + 1][enemies[i].position.X] = blok_pusty;
								}
							}
							else //w dol
							{
								if (map[enemies[i].position.Y + 1][enemies[i].position.X] == blok_pusty || map[enemies[i].position.Y + 1][enemies[i].position.X] == blok_pusty)
								{
									//nie m�g� si� normalnie poruszy�, wi�c rusza wed�ug innej osi
									enemies[i].position.Y++;
									putCharXY(GetOnScreenPos(enemies[i].position).X, GetOnScreenPos(enemies[i].position).Y, blok_przeciwnik);
									putCharXY(GetOnScreenPos(enemies[i].position).X, GetOnScreenPos(enemies[i].position).Y - 1, blok_pusty);
									map[enemies[i].position.Y - 1][enemies[i].position.X] = blok_pusty;
								}
							}
						}
					}
					else //w prawo
					{
						if (map[enemies[i].position.Y ][enemies[i].position.X + 1] == blok_pusty ||map[enemies[i].position.Y ][enemies[i].position.X + 1] == blok_gracz)
						{
							//mo�e si� normalnie poruszy� w wyznaczonym kierunku
							enemies[i].position.X++;
							putCharXY(GetOnScreenPos(enemies[i].position).X, GetOnScreenPos(enemies[i].position).Y, blok_przeciwnik);
							putCharXY(GetOnScreenPos(enemies[i].position).X - 1, GetOnScreenPos(enemies[i].position).Y, blok_pusty);
							map[enemies[i].position.Y][enemies[i].position.X - 1] = blok_pusty;
						}
						else
						{
							if (yDist > 0) //w gore
							{
								if (map[enemies[i].position.Y - 1][enemies[i].position.X] == blok_pusty || map[enemies[i].position.Y - 1][enemies[i].position.X] == blok_gracz)
								{
									//nie m�g� si� normalnie poruszy�, wi�c rusza wed�ug innej osi
									enemies[i].position.Y--;
									putCharXY(GetOnScreenPos(enemies[i].position).X, GetOnScreenPos(enemies[i].position).Y, blok_przeciwnik);
									putCharXY(GetOnScreenPos(enemies[i].position).X, GetOnScreenPos(enemies[i].position).Y + 1, blok_pusty);
									map[enemies[i].position.Y + 1][enemies[i].position.X] = blok_pusty;
								}
							}
							else //w dol
							{
								if (map[enemies[i].position.Y + 1][enemies[i].position.X] == blok_pusty || map[enemies[i].position.Y + 1][enemies[i].position.X] == blok_pusty)
								{
									//nie m�g� si� normalnie poruszy�, wi�c rusza wed�ug innej osi
									enemies[i].position.Y++;
									putCharXY(GetOnScreenPos(enemies[i].position).X, GetOnScreenPos(enemies[i].position).Y, blok_przeciwnik);
									putCharXY(GetOnScreenPos(enemies[i].position).X, GetOnScreenPos(enemies[i].position).Y - 1, blok_pusty);
									map[enemies[i].position.Y - 1][enemies[i].position.X] = blok_pusty;
								}
							}
						}
					}
				}
				else //przeciwnik porusza si� w osi pionowej
				{
					if (yDist > 0) //w gore
					{
						if (map[enemies[i].position.Y - 1][enemies[i].position.X ] == blok_pusty || map[enemies[i].position.Y-1][enemies[i].position.X ] == blok_gracz)
						{
							//mo�e si� normalnie poruszy� w wyznaczonym kierunku
							enemies[i].position.Y--;
							putCharXY(GetOnScreenPos(enemies[i].position).X, GetOnScreenPos(enemies[i].position).Y, blok_przeciwnik);
							putCharXY(GetOnScreenPos(enemies[i].position).X , GetOnScreenPos(enemies[i].position).Y + 1, blok_pusty);
							map[enemies[i].position.Y + 1][enemies[i].position.X] = blok_pusty;
						}
						else
						{
							if (xDist > 0) //w lewo
							{
								if (map[enemies[i].position.Y][enemies[i].position.X - 1] == blok_pusty || map[enemies[i].position.Y][enemies[i].position.X - 1] == blok_gracz)
								{
									//nie m�g� si� normalnie poruszy�, wi�c rusza wed�ug innej osi
									enemies[i].position.X--;
									putCharXY(GetOnScreenPos(enemies[i].position).X, GetOnScreenPos(enemies[i].position).Y, blok_przeciwnik);
									putCharXY(GetOnScreenPos(enemies[i].position).X + 1, GetOnScreenPos(enemies[i].position).Y, blok_pusty);
									map[enemies[i].position.Y][enemies[i].position.X + 1] = blok_pusty;
								}
								
							}
							else //w prawo
							{
								if (map[enemies[i].position.Y][enemies[i].position.X + 1] == blok_pusty || map[enemies[i].position.Y][enemies[i].position.X + 1] == blok_gracz)
								{
									//nie m�g� si� normalnie poruszy�, wi�c rusza wed�ug innej osi
									enemies[i].position.X++;
									putCharXY(GetOnScreenPos(enemies[i].position).X, GetOnScreenPos(enemies[i].position).Y, blok_przeciwnik);
									putCharXY(GetOnScreenPos(enemies[i].position).X - 1, GetOnScreenPos(enemies[i].position).Y, blok_pusty);
									map[enemies[i].position.Y][enemies[i].position.X - 1] = blok_pusty;
								}
								
							}
						}
					}
					else //w dol
					{
						if (map[enemies[i].position.Y+1][enemies[i].position.X] == blok_pusty|| map[enemies[i].position.Y+1][enemies[i].position.X] == blok_pusty)
						{
							//mo�e si� normalnie poruszy� w wyznaczonym kierunku
							enemies[i].position.Y++;
							putCharXY(GetOnScreenPos(enemies[i].position).X, GetOnScreenPos(enemies[i].position).Y, blok_przeciwnik);
							putCharXY(GetOnScreenPos(enemies[i].position).X, GetOnScreenPos(enemies[i].position).Y - 1, blok_pusty);
							map[enemies[i].position.Y - 1][enemies[i].position.X] = blok_pusty;
						}
						else
						{
							if (xDist > 0) //w lewo
							{
								if (map[enemies[i].position.Y][enemies[i].position.X - 1] == blok_pusty || map[enemies[i].position.Y][enemies[i].position.X - 1] == blok_gracz)
								{
									//nie m�g� si� normalnie poruszy�, wi�c rusza wed�ug innej osi
									enemies[i].position.X--;
									putCharXY(GetOnScreenPos(enemies[i].position).X, GetOnScreenPos(enemies[i].position).Y, blok_przeciwnik);
									putCharXY(GetOnScreenPos(enemies[i].position).X + 1, GetOnScreenPos(enemies[i].position).Y, blok_pusty);
									map[enemies[i].position.Y][enemies[i].position.X + 1] = blok_pusty;
								}

							}
							else //w prawo
							{
								if (map[enemies[i].position.Y][enemies[i].position.X + 1] == blok_pusty || map[enemies[i].position.Y][enemies[i].position.X + 1] == blok_gracz)
								{
									//nie m�g� si� normalnie poruszy�, wi�c rusza wed�ug innej osi
									enemies[i].position.X++;
									putCharXY(GetOnScreenPos(enemies[i].position).X, GetOnScreenPos(enemies[i].position).Y, blok_przeciwnik);
									putCharXY(GetOnScreenPos(enemies[i].position).X - 1, GetOnScreenPos(enemies[i].position).Y, blok_pusty);
									map[enemies[i].position.Y][enemies[i].position.X - 1] = blok_pusty;
								}

							}
						}
					}
				}
			}
			//koniec ruchu
			map[enemies[i].position.Y][enemies[i].position.X] = blok_przeciwnik;

			setColor(0x0F);

			//char buf[50];
			//snprintf(buf, sizeof buf, "Enemy on map: (%d,%d)", player.position.X, player.position.Y);
			//putStrXY(ViewportW + 5, 10, buf);
		}
	}
}

int CalculateDistance(COORD a, COORD b)
{
	return sqrt(pow((a.X-b.X),2)+ pow((a.Y - b.Y), 2));
}

void ShowMenu()
{
	system("CLS");
	unsigned char menuIndex = 0;
	short colors[5] = { 0 };
	int i = 0;
	unsigned char c;
	setColor(kolor_logo);


	putStrXY(1, 0, "_________                    ___________             .__              ");
	putStrXY(1, 1, "\\_   ___ \\_____ ___  __ ____ \\_   _____/__  ________ |  |   ___________  ___________ ");
	putStrXY(1, 2, "/    \\  \\/\\__  \\\\  \\/ // __ \\ |    __)_\\  \\/  |____ \\|  |  /  _ \\_  __ \\/ __ \\_  __ \\");
	putStrXY(1, 3, "\\     \\____/ __ \\\\   /\\  ___/ |        \\>    <|  |_> >  |_(  <_> )  | \\|  ___/|  | \\/");
	putStrXY(1, 4, " \\______  (____  /\\_/  \\___  >_______  /__/\\_ \\   __/|____/\\____/|__|   \\___  >__|   ");
	putStrXY(1, 5, "        \\/     \\/          \\/        \\/      \\/__|                          \\/       ");
	
	putStrXY(49, 7, "_______________  _______  _______   "); 
	putStrXY(49, 8, "\\_____  \\   _  \\ \\   _  \\ \\   _  \\ ");
	putStrXY(49, 9, " /  ____/  /_\\  \\/  /_\\  \\/  /_\\  \\ ");
	putStrXY(49, 10, "/       \\  \\_/   \\  \\_/   \\  \\_/   \\");
	putStrXY(49, 11, "\\_______ \\_____  /\\_____  /\\_____  /");
	putStrXY(49, 12, "        \\/     \\/       \\/       \\/ ");

	setColor(0x08);
	putStrXY(60, 20, "by Jan Sudczak");
	setColor(0x0F);

	do
	{
		for (i = 0; i < 5; i++)
		{
			if (menuIndex == i)
			{
				colors[i] = kolor_menu_aktywny;
			}
			else
			{
				colors[i] = kolor_menu;
			}

			
		}
		if (GameState != 1)
		{
			colors[1] = 0x08;
		}


		drawMenuItem(20, 7, colors[0], "Rozpocznij gre");

		drawMenuItem(22, 12, colors[1], "Kontynuuj");
		drawMenuItem(24, 17, colors[2], "Opcje");

		drawMenuItem(21, 22, colors[3], "Zakoncz gre");



		c = getKey();


		if (c == 72) //gora
		{
			if (menuIndex >0)
			{
				menuIndex--;
			}
		}

		if (c == 80)//dol
		{
			if (menuIndex < (4 - 1))
			{
				menuIndex++;
			}
		}




		if (c == 13)//enter
		{
			switch (menuIndex)
			{
			case 0: //nowa gra
				system("CLS");
				return;
				break;
			case 1: //kontynuuj

				if (GameState == 1)
				{
					
					RefreshMap();
					return;
				}


				break;
			case 2: //opcje

				break;
			case 3: //wyjdz
				exit(0);
				break;
			}
		}

		if (c == 27) //escape pressed
		{
			if (GameState == 1)
			{
				RefreshMap(); //kontunuuj gre
				return;
			}
		}

	} while (1);
}
