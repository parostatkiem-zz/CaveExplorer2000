#include "console.h"

#include <windows.h>
#include <stdio.h>
#include <conio.h>

//test
void initScreen( void )
{
   // Wymaga: windows.h
   // wy³¹czenie mrugania kursora - dzia³a od windowsa XP
   CONSOLE_CURSOR_INFO cciInfo;
   cciInfo.dwSize = 1;
   cciInfo.bVisible = 0;   
   SetConsoleCursorInfo( GetStdHandle(STD_OUTPUT_HANDLE), &cciInfo );   

   system( "chcp 852" );
   system( "cls" );
}

void putCharXY( int x, int y, unsigned char z )
{
   COORD a;
   a.X = x;
   a.Y = y;
   SetConsoleCursorPosition( GetStdHandle(STD_OUTPUT_HANDLE), a );
   printf("%c", z );
   a.X = 0;
   a.Y = 0;
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), a);
}

void putStrXY( int x, int y, const char *s )
{
   while( *s )
      putCharXY( x++, y, *s++ );
}

void setColor( unsigned short id )
{
   SetConsoleTextAttribute( GetStdHandle(STD_OUTPUT_HANDLE), id );
}

char getKey( void )
{
   return getch();
}
