#pragma once
#include <windows.h> //do typu COORD
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <math.h>


#include "console.h"
#include "gameEngine.h"
#include "gameSave.h" 
#include "graphics.h"




// Wymiary planszy
#define MapMaxX 200
#define MapMaxY 200

// Wymiary viewporta
#define  ViewportW  80
#define  ViewportH	30 

//bloki
#define blok_staly 0xB2
#define blok_zwykly 0xB1
#define blok_zwykly_ukruszony 0xB0
#define blok_pusty ' '
#define blok_gracz 0xF5
#define blok_przeciwnik 0xFE
#define blok_item 0xCF
#define blok_portal 0xDB



//tworzenie jaskiñ
#define CaveSize 49 //prawdopodobienstwo w % generacji sasiedniego segmentu jaskini (im wieksze, tym wieksze sa jaskinie)
#define MinCaveSize 10 //minimalna ilosc segmentow jednej jaskini 
#define CavesPerLevel 14 //ilosc jaskin na kazdy poziom - dostosowac do rozmiaru planszy!
#define DTETR 2 //min. dystans do krawedzi potrzebny do od˜wiezenia widoku - RACZEJ NIE ZMIENIAC

//generacja przeciwników
#define EnemyAmount 22 //ilosc przeciwnikow na lvl 0
#define EnemyMultiplier 1.5 //mnoznik zwiekszania si³ˆy oraz ilo˜ci przeciwnikow na kolejnym lvl
#define EnemyStartHp 20
#define EnemyStartDamage 4
#define MaxEnemyNum 100		//maksymalna przewidziana ilosc przeciwnikow (ustawiona na sztywno bo tak.)

//gracz, levele gracza i jego parametry
#define PlayerStartHp 50
#define PlayerStartDamage 7
#define ExpToNextLevel 10 //iloœæ EXP potrzebna do zdobycia nast. poziomu postaci
#define PlayerDamageMultiplier 1.3 //mnoznik zwiekszenia obrazen gracza na kazdy level
#define HPregenRate 8 //uzdrawia gracza o 1hp co X ruchów -> im mniejsza wartosc, tym szybciej ro˜œnie HP

//globalne ustawienia
#define MinDamageMultiplier 0.6 //mno¿lik minimalnych obra¿en wzglêdem pe³nych obra¿eñ
#define SeeDistance 6 //zasiêg wzroku przeciwników
#define Visibility 10 //zasiêg wzroku gracza | obecnie nieu¿ywany

//kolory
#define kolor_gracz 0x03
#define kolor_blok_zwykly 0x08
#define kolor_blok_staly 0x0F
#define kolor_blok_przeciwnik 0x04
#define kolor_tlo 0x00 
#define kolor_portal 0x09

#define kolor_menu_aktywny 0x0D
#define kolor_menu 0x05
#define kolor_logo 0x05


//globalna definicja zmiennych
extern unsigned char map[200][200];
extern unsigned int GameState;
extern unsigned int LogLevel;
extern unsigned int TotalTurns;
extern unsigned int CurrentLevel;
extern unsigned int EnemiesKilled;

extern unsigned int GameSaveLoad;

extern COORD viewport; 
extern COORD portal;
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

