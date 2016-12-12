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
#define blok_zwykly 0xB0
#define blok_pusty ' '
#define blok_gracz 0xF5
#define blok_przeciwnik 0xFE
#define blok_item 0xCF


//globalna definicja zmiennych
extern unsigned char map[MapMaxX][MapMaxY];
extern unsigned int GameState;
extern COORD player;
extern COORD viewport;

#define CaveSize 47 //prawdopodobienstwo w % generacji sąsiedniego segmentu jaskini (im wieksze, tym większe są jaskinie)
#define MinCaveSize 9 //minimalna ilość segmentów jednej jaskini 
#define CavesPerLevel 9 //ilosc jaskiń na każdy poziom - dostosować do rozmiaru planszy!
#define DTETR 2 //min. dystans do krawędzi potrzebny do odświeżenia widoku

//kolory
#define kolor_gracz 0x05
#define kolor_blok_zwykly 0x0F
#define kolor_blok_staly 0x0F
#define kolor_tlo 0x0F