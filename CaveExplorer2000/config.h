﻿#pragma once
#include <windows.h>
// Wymiary planszy
#define  MapMaxX   200
#define  MapMaxY	200

// Wymiary viewporta
#define  ViewportW  80
#define  ViewportH	30

//bloki
#define blok_staly 0xB2
#define blok_zwykly 0xB0
#define blok_pusty ' '
#define blok_gracz 0xF5
#define blok_przeciwnik 0xFE
#define blok_item 0xCF




#define CaveSize 48 //prawdopodobienstwo w % generacji sąsiedniego segmentu jaskini (im wieksze, tym większe są jaskinie)
#define MinCaveSize 9 //minimalna ilość segmentów jednej jaskini 
#define CavesPerLevel 9 //ilosc jaskiń na każdy poziom - dostosować do rozmiaru planszy!
#define DTETR 2 //min. dystans do krawędzi potrzebny do odświeżenia widoku

#define EnemyAmount 20 //ilosc przeciwnikow na lvl 0
#define EnemyMultiplier 1.5 //mnożnik zwiększania siły oraz ilości przeciwników na kolejnym lvl
#define EnemyStartHp 20
#define EnemyStartDamage 4
#define MaxEnemyNum 100		//maksymalna przewidziana ilosc przeciwnikow (ustawiona na sztywno bo tak.)

#define PlayerStartHp 35
#define PlayerStartDamage 7
#define ExpToNextLevel 10
#define PlayerDamageMultiplier 1.3 //mnożnik zwiększenia obrażeń gracza na każdy level



#define MinDamageMultiplier 0.6 //mnożlik minimalnych obrażen względem pełnych obrażeń
#define SeeDistance 6 //zasięg wzroku przeciwników
#define Visibility 10 //zasięg wzroku gracza | obecnie nieużywany

//kolory
#define kolor_gracz 0x03
#define kolor_blok_zwykly 0x08
#define kolor_blok_staly 0x0F
#define kolor_blok_przeciwnik 0x04
#define kolor_tlo 0x0F

#define kolor_menu_aktywny 0x0D
#define kolor_menu 0x05
#define kolor_logo 0x05


//globalna definicja zmiennych
extern unsigned char map[MapMaxX][MapMaxY];
extern unsigned int GameState;

extern COORD viewport;
extern struct playerClass
{
	int hp;
	int maxhp;
	int damage;
	COORD position;
	int level;
	int exp;

};
extern struct playerClass player;
extern struct Enemy
{
	int hp;
	int damage;
	COORD position;

};
extern struct Enemy enemies[];

