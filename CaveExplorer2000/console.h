#pragma once
// Funkcje obs�ugi konsoli

// Ustawienie odpowiednich parametr�w konsoli
void initScreen( void );

// Drukowanie znaku z na pozycji (x,y)
void putCharXY( int x, int y, unsigned char z );

// Drukowanie �a�cucha s od pozycji (x,y)
void putStrXY( int x, int y, const char *s );

// Zmiana kolor�w w konsoli
void setColor( unsigned short id );

// Pobieranie znaku z konsoli
char getKey( void );