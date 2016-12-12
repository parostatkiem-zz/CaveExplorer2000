#pragma once
// Funkcje obs³ugi konsoli

// Ustawienie odpowiednich parametrów konsoli
void initScreen( void );

// Drukowanie znaku z na pozycji (x,y)
void putCharXY( int x, int y, unsigned char z );

// Drukowanie ³añcucha s od pozycji (x,y)
void putStrXY( int x, int y, const char *s );

// Zmiana kolorów w konsoli
void setColor( unsigned short id );

// Pobieranie znaku z konsoli
char getKey( void );