#include "console.h"

#include <windows.h> 
#include <stdio.h>
#include <conio.h>

void initScreen( void )
{
   // Wymaga: windows.h
   // wylaczenie mrugania kursora - dziala od windowsa XP
   CONSOLE_CURSOR_INFO cciInfo;
   cciInfo.dwSize = 1;
   cciInfo.bVisible = 0;   
   SetConsoleCursorInfo( GetStdHandle(STD_OUTPUT_HANDLE), &cciInfo );   

  // system( "chcp 852" );
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

void drawMenuItem(int x, int y, unsigned short c, const char *s)
{

	setColor(c);
	const char *t = s;

	unsigned int num = 0;
	int i = 0;
	putCharXY(x, y, 0xC9);
	while (*t)
	{
		num++;
		*t++;
	}


	for (i = 1; i <= num + 3; i++)
	{
		putCharXY(x + i, y, 0xCD);

	}

	putCharXY(x + num + 3, y, 0xBB);

	putCharXY(x, y + 1, 0xBA);

	putCharXY(x + num + 3, y + 1, 0xBA);
	t = s;
	for (i = 2; i <= num + 1; i++)
	{
		putStrXY(x + i, y + 1, t);
		*t++;

	}
	setColor(c);
	for (i = 0; i <= num + 5; i++)
	{
		putCharXY(x + i - 1, y + 2, 0xCD);

	}

	//putCharXY(x +num, y, 0xBA);

	setColor(0x0F);

}