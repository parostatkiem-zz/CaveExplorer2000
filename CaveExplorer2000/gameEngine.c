#include "gameEngine.h"

#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <math.h>

unsigned int tmp = 0;
unsigned int Turns = 0;
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
			if (x == 0 || x == MapMaxX - 1 || y == 0 || y == MapMaxY - 1)
				map[y][x] = blok_staly; //otaczanie mapy nierozbijalnymi blokami
			else
				map[y][x] = blok_zwykly; // wypelnianie mapy blokami do rozwalenia
		}
	}

	//generowanie jaskin
	int i = 0;
	for (i = 0; i <= CavesPerLevel; i++)
	{
		CaveSegments = 0;
		COORD tmp;
		tmp.X = RandomInt(1, MapMaxX - 1);
		tmp.Y = RandomInt(1, MapMaxX - 1);
		//map[tmp.X][tmp.Y] = blok_pusty;
		AddCaveSegment(tmp);

	}

	//generowanie przeciwnikow===================
	struct Enemy e;
	e.position.X = 0;
	e.position.Y = 0;
	for (i = 0; i < MaxEnemyNum; i++) //czyszczenie tablicy przeciwnikow
	{
		enemies[i] = e; //resetowanie pozycji kazdego przeciwnika na (0,0) - oznacza to,ze on nie  istnieje
	}


	e.damage = EnemyStartDamage + (EnemyMultiplier*level);
	e.hp = EnemyStartHp + (EnemyMultiplier*level);
	for (i = 0; i < EnemyAmount + (EnemyMultiplier*level) - 2; i++)
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

	PlacePortal();

	RefreshMap();
	RefreshGui();

	InitGui();

}

int RandomInt(int min, int max)
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


	if (b == blok_zwykly && a<CaveSize || CaveSegments<MinCaveSize && b == blok_zwykly)
	{
		CaveSegments++;
		map[punkt.Y][punkt.X] = blok_pusty;


		//generowanie segmentow dla sasiednich 4 pol
		COORD tmp;
		tmp.X = punkt.X + 1;
		tmp.Y = punkt.Y;
		AddCaveSegment(tmp);

		tmp.X = punkt.X;
		tmp.Y = punkt.Y + 1;
		AddCaveSegment(tmp);

		tmp.X = punkt.X - 1;
		tmp.Y = punkt.Y;
		AddCaveSegment(tmp);

		tmp.X = punkt.X;
		tmp.Y = punkt.Y - 1;
		AddCaveSegment(tmp);
	}
}

void PlacePlayer()
{
	COORD tmp;
	tmp.X = RandomInt(1, MapMaxX - 1);
	tmp.Y = RandomInt(1, MapMaxY - 1);

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
		if (znak == 0 || znak == 0xE0) 
			znak = getKey();  //'czyszczenie' znaku ze �mieci je�li jest enterem albo czym� takim

		if (znak == 72 || znak == 80 || znak == 77 || znak == 75)
		{
			if (GameState == 1)
			{
				ClearLog();
				RegenerateLife();
				TryMove(znak);
				CheckPortal();
				MoveEnemies();
				CheckRefresh();
				RefreshGui();
			}

		}
		if (znak == 27) //escape pressed
		{
			ShowMenu();
		}

		if (znak == 32) //space pressed
		{
			if (GameState == 1)
			{
				ClearLog();
				RegenerateLife();
				Atack();
			}
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
		if (map[player.position.Y - 1][player.position.X] == blok_pusty || map[player.position.Y - 1][player.position.X] == blok_zwykly || map[player.position.Y - 1][player.position.X] == blok_zwykly_ukruszony)
		{
			TotalTurns++;
			Turns++;
			if (map[player.position.Y - 1][player.position.X] == blok_zwykly)
			{
				//nalezy ukruszyc blok
				setColor(kolor_blok_zwykly);
				putCharXY(player.position.X - viewport.X, player.position.Y - viewport.Y - 1, blok_zwykly_ukruszony);
				map[player.position.Y - 1][player.position.X] = blok_zwykly_ukruszony;
			}
			else
			{
				//blok juz jest ukruszony, mozna go zniszczyc i sie tam przemiescic LUB pole jest puste
				player.position.Y--;
				putCharXY(player.position.X - viewport.X, player.position.Y - viewport.Y, blok_gracz);
				putCharXY(player.position.X - viewport.X, player.position.Y - viewport.Y + 1, blok_pusty);
			}
		}
		break;
	case 80:  //dol
		if (map[player.position.Y + 1][player.position.X] == blok_pusty || map[player.position.Y + 1][player.position.X] == blok_zwykly || map[player.position.Y + 1][player.position.X] == blok_zwykly_ukruszony)
		{
			TotalTurns++;
			Turns++;
			if (map[player.position.Y + 1][player.position.X] == blok_zwykly)
			{
				//nalezy ukruszyc blok
				setColor(kolor_blok_zwykly);
				putCharXY(player.position.X - viewport.X, player.position.Y - viewport.Y + 1, blok_zwykly_ukruszony);
				map[player.position.Y + 1][player.position.X] = blok_zwykly_ukruszony;
			}
			else
			{
				player.position.Y++;
				putCharXY(player.position.X - viewport.X, player.position.Y - viewport.Y, blok_gracz);
				putCharXY(player.position.X - viewport.X, player.position.Y - viewport.Y - 1, blok_pusty);
			}
		}
		break;
	case 77: //prawo
		if (map[player.position.Y][player.position.X + 1] == blok_pusty || map[player.position.Y][player.position.X + 1] == blok_zwykly || map[player.position.Y][player.position.X + 1] == blok_zwykly_ukruszony)
		{
			TotalTurns++;
			Turns++;
			if (map[player.position.Y][player.position.X + 1] == blok_zwykly)
			{
				//nalezy ukruszyc blok
				setColor(kolor_blok_zwykly);
				putCharXY(player.position.X - viewport.X + 1, player.position.Y - viewport.Y, blok_zwykly_ukruszony);
				map[player.position.Y][player.position.X + 1] = blok_zwykly_ukruszony;
			}
			else
			{
				player.position.X++;
				putCharXY(player.position.X - viewport.X, player.position.Y - viewport.Y, blok_gracz);
				putCharXY(player.position.X - viewport.X - 1, player.position.Y - viewport.Y, blok_pusty);
			}
		}
		break;
	case 75: //lewo
		if (map[player.position.Y][player.position.X - 1] == blok_pusty || map[player.position.Y][player.position.X - 1] == blok_zwykly || map[player.position.Y][player.position.X - 1] == blok_zwykly_ukruszony)
		{
			TotalTurns++;
			Turns++;
			if (map[player.position.Y][player.position.X - 1] == blok_zwykly)
			{
				//nalezy ukruszyc blok
				setColor(kolor_blok_zwykly);
				putCharXY(player.position.X - viewport.X - 1, player.position.Y - viewport.Y, blok_zwykly_ukruszony);
				map[player.position.Y][player.position.X - 1] = blok_zwykly_ukruszony;
			}
			else
			{
				player.position.X--;
				putCharXY(player.position.X - viewport.X, player.position.Y - viewport.Y, blok_gracz);
				putCharXY(player.position.X - viewport.X + 1, player.position.Y - viewport.Y, blok_pusty);
			}

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
	for (i = 0; i < MaxEnemyNum; i++) //petla po wszystkich przeciwnikach
	{
		if (enemies[i].position.X == 0 && enemies[i].position.Y == 0)
			continue; //koniec petli jesli przeciwnik nie istnieje

		int tmp = CalculateDistance(enemies[i].position, player.position);
		if (CalculateDistance(enemies[i].position, player.position) <= SeeDistance) //jesli przeciwnik widzi gracza
		{
			setColor(kolor_blok_przeciwnik);
			if (CalculateDistance(enemies[i].position, player.position) <= 1) //przeciwnik stoi kolo gracza
			{
				//przeciwnik atakuje
				int obrazenia = RandomInt(MinDamageMultiplier*enemies[i].damage, enemies[i].damage);
				if (player.hp - obrazenia > 0)
				{
					player.hp -= obrazenia; //gracz otrzymuje cios
					Log("Otrzyma�e� obra�enia", -obrazenia);
				}
				else
					Death();   //gracz umiera

			}
			else //przeciwnik idzie w kierunku gracza
			{
				xDist = enemies[i].position.X - player.position.X;
				yDist = enemies[i].position.Y - player.position.Y;
				if (abs(xDist) > abs(yDist)) //przeciwnik porusza si� w osi poziomej
				{
					if (xDist > 0) //w lewo
					{
						if (map[enemies[i].position.Y][enemies[i].position.X - 1] == blok_pusty || map[enemies[i].position.Y][enemies[i].position.X - 1] == blok_gracz)
						{
							//moze sie normalnie poruszyc w wyznaczonym kierunku
							enemies[i].position.X--;
							putCharXY(GetOnScreenPos(enemies[i].position).X, GetOnScreenPos(enemies[i].position).Y, blok_przeciwnik);
							putCharXY(GetOnScreenPos(enemies[i].position).X + 1, GetOnScreenPos(enemies[i].position).Y, blok_pusty);
							map[enemies[i].position.Y][enemies[i].position.X + 1] = blok_pusty;
						}
						else
						{
							if (yDist > 0) //w gore
							{
								if (map[enemies[i].position.Y - 1][enemies[i].position.X] == blok_pusty || map[enemies[i].position.Y - 1][enemies[i].position.X] == blok_gracz)
								{
									//nie moze sie normalnie poruszyc, wiec rusza wedlug innej osi
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
									//nie moze sie normalnie poruszyc, wiec rusza wedlug innej osi
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
						if (map[enemies[i].position.Y][enemies[i].position.X + 1] == blok_pusty || map[enemies[i].position.Y][enemies[i].position.X + 1] == blok_gracz)
						{
							//moze sie normalnie poruszyc w wyznaczonym kierunku
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
									//nie moze sie normalnie poruszyc, wiec rusza wedlug innej osi
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
									//nie moze sie normalnie poruszyc, wiec rusza wedlug innej osi
									enemies[i].position.Y++;
									putCharXY(GetOnScreenPos(enemies[i].position).X, GetOnScreenPos(enemies[i].position).Y, blok_przeciwnik);
									putCharXY(GetOnScreenPos(enemies[i].position).X, GetOnScreenPos(enemies[i].position).Y - 1, blok_pusty);
									map[enemies[i].position.Y - 1][enemies[i].position.X] = blok_pusty;
								}
							}
						}
					}
				}
				else //przeciwnik porusza sie w osi pionowej
				{
					if (yDist > 0) //w gore
					{
						if (map[enemies[i].position.Y - 1][enemies[i].position.X] == blok_pusty || map[enemies[i].position.Y - 1][enemies[i].position.X] == blok_gracz)
						{
							//moze sie normalnie poruszyc w wyznaczonym kierunku
							enemies[i].position.Y--;
							putCharXY(GetOnScreenPos(enemies[i].position).X, GetOnScreenPos(enemies[i].position).Y, blok_przeciwnik);
							putCharXY(GetOnScreenPos(enemies[i].position).X, GetOnScreenPos(enemies[i].position).Y + 1, blok_pusty);
							map[enemies[i].position.Y + 1][enemies[i].position.X] = blok_pusty;
						}
						else
						{
							if (xDist > 0) //w lewo
							{
								if (map[enemies[i].position.Y][enemies[i].position.X - 1] == blok_pusty || map[enemies[i].position.Y][enemies[i].position.X - 1] == blok_gracz)
								{
									//nie moze sie normalnie poruszyc, wiec rusza wedlug innej osi
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
									//nie moze sie normalnie poruszyc, wiec rusza wedlug innej osi
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
						if (map[enemies[i].position.Y + 1][enemies[i].position.X] == blok_pusty || map[enemies[i].position.Y + 1][enemies[i].position.X] == blok_pusty)
						{
							//moze sie normalnie poruszyc w wyznaczonym kierunku
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
									//nie moze sie normalnie poruszyc, wiec rusza wedlug innej osi
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
									//nie moze sie normalnie poruszyc, wiec rusza wedlug innej osi
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

		}
	}
}

int CalculateDistance(COORD a, COORD b)
{
	return sqrt(pow((a.X - b.X), 2) + pow((a.Y - b.Y), 2));
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
	putStrXY(60, 20, "by  Jan Sudczak");
	setColor(0x0F);

	do
	{
		if (GameState != 0 && GameState != 1)
			return;
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
		if (GameState != 1 && !GameSaveLoad)
		{
			colors[1] = 0x08;
		}



		drawMenuItem(17, 7, colors[0], "Rozpocznij NOW� gr�");
		if (isSaved()&&GameSaveLoad  &&  GameState == 0)
		{


			drawMenuItem(16, 12, colors[1], "Kontynuuj zapisan� gr�");
		}
		else
		{


			drawMenuItem(22, 12, colors[1], "Kontynuuj");
		}



		drawMenuItem(24, 17, colors[2], "Opcje");

		drawMenuItem(21, 22, colors[3], "Zako�cz gr�");



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

				GameState = 1;
				CurrentLevel = 0;
				Turns = 0;
				player.hp = PlayerStartHp; // 3 dla testow
				player.damage = PlayerStartDamage;
				player.maxhp = PlayerStartHp;
				player.exp = 0; //start exp
				player.level = 1;
				EnemiesKilled = 0;
				InitializeLevel(CurrentLevel);



				Move();

				return;
				break;
			case 1: //kontynuuj

				if (GameState == 1)
				{
					system("CLS");
					RefreshMap();
					RefreshGui();

				}
				else
				{
					//wczytaj gre

					loadGame();
					GameState = 1;
					system("CLS");
					RefreshMap();
					RefreshGui();
					Move();


				}



				return;
				break;
			case 2: //opcje
				tmp = GameState;
				GameState=2;
				ShowOptions(tmp);

				break;
			case 3: //wyjdz

				if (map[0][0] == blok_staly && GameSaveLoad)
					saveGame(); //zapisanie gry na wyjsciu jesli wczytana jest jakas mapa
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

void Atack()
{
	int i = 0;
	for(int i = 0; i<MaxEnemyNum ;i++)  //petla po wszystkich przeciwnikach
	{
		if (enemies[i].position.X == 0 && enemies[i].position.Y == 0)
			continue;    //pominiecie przeciwnika jesli nie istnieje

		int tmp = CalculateDistance(enemies[i].position, player.position);
		int s = CalculateDistance(enemies[i].position, player.position);
		if (CalculateDistance(enemies[i].position, player.position) <= 1) //jestli gracz jest obok przeciwnika
		{
			TotalTurns++;
			Turns++;
			int obrazenia = RandomInt(MinDamageMultiplier*player.damage, player.damage);


			Log("Zadane obra�enia", obrazenia);
			if (enemies[i].hp <= obrazenia)//cios zabija przeciwnika
			{
				EnemiesKilled++;
				COORD tmp = GetOnScreenPos(enemies[i].position);

				putCharXY(tmp.X, tmp.Y, blok_pusty); //usuniecie przeciwnika z widoku

													 //usuniecie przeciwnika z mapy
				map[enemies[i].position.Y][enemies[i].position.X] = blok_pusty;
				enemies[i].position.X = 0;
				enemies[i].position.Y = 0;//ustawienie przeciwnika jako niezywego


				Log("Zabi�e� przeciwnika!", 0);


				if (player.exp >= ExpToNextLevel)
				{
					//gracz awansuje na nowy level
					player.level++;

					player.exp = -1;

					player.damage *= PlayerDamageMultiplier;

					Log("Awansowa�e� na wy�szy poziom!!", 0);


				}

				player.exp++;
				RefreshGui();
			}
			else //cios tylko uszkadza przeciwnika
			{
				enemies[i].hp -= obrazenia;

			}


			MoveEnemies();
			RefreshGui();
		}
	}

}

void Death()
{
	GameState = 0;

	ShowDeathScreen();

}

void RegenerateLife()
{
	if (Turns >= HPregenRate)
	{
		Turns = 0;
		if (player.hp<PlayerStartHp)
			player.hp++;
	}
	else
		Turns++;
}


void PlacePortal()
{
	COORD tmp;
	tmp.X = RandomInt(1, MapMaxX - 1);
	tmp.Y = RandomInt(1, MapMaxY - 1);

	unsigned char b = map[tmp.Y][tmp.X];
	unsigned char c = blok_pusty;

	if (b == c)
	{
		//map[tmp.X][tmp.Y] = blok_gracz;
		portal = tmp;

		return;
	} 
	else
	{
		PlacePortal();
	}

}

void CheckPortal() //sprawdza, czy gracz nie  wszedl w portal
{
	if (player.position.X == portal.X && player.position.Y == portal.Y)
	{
		InitializeLevel(++CurrentLevel);
	}
}
