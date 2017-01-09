#pragma once
#include <windows.h>
// Wymiary planszy
#define  MapMaxX   200
#define  MapMaxY	200

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




#define CaveSize 49 //prawdopodobienstwo w % generacji s¥siedniego segmentu jaskini (im wieksze, tym wi©ksze s¥ jaskinie)
#define MinCaveSize 10 //minimalna ilo˜† segment¢w jednej jaskini 
#define CavesPerLevel 10 //ilosc jaskiä na ka¾dy poziom - dostosowa† do rozmiaru planszy!
#define DTETR 2 //min. dystans do kraw©dzi potrzebny do od˜wie¾enia widoku - RACZEJ NIE ZMIENIA†

#define EnemyAmount 22 //ilosc przeciwnikow na lvl 0
#define EnemyMultiplier 1.5 //mno¾nik zwi©kszania siˆy oraz ilo˜ci przeciwnik¢w na kolejnym lvl
#define EnemyStartHp 20
#define EnemyStartDamage 4
#define MaxEnemyNum 100		//maksymalna przewidziana ilosc przeciwnikow (ustawiona na sztywno bo tak.)

#define PlayerStartHp 50
#define PlayerStartDamage 7
#define ExpToNextLevel 10
#define PlayerDamageMultiplier 1.3 //mno¾nik zwi©kszenia obra¾eä gracza na ka¾dy level
#define HPregenRate 7 //uzdrawia gracza o 1hp co X ruch¢w -> im mniejsza wartosc, tym szybciej ro˜nie HP


#define MinDamageMultiplier 0.6 //mno¾lik minimalnych obra¾en wzgl©dem peˆnych obra¾eä
#define SeeDistance 6 //zasi©g wzroku przeciwnik¢w
#define Visibility 10 //zasi©g wzroku gracza | obecnie nieu¾ywany

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
extern unsigned char map[MapMaxX][MapMaxY];
extern unsigned int GameState;
extern unsigned int LogLevel;
extern unsigned int Turns;
extern unsigned int CurrentLevel;
extern unsigned int EnemiesKilled;

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

