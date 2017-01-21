#include "console.h"

#include <windows.h> 
#include <stdio.h>
#include <conio.h>


int SetFontSize(HANDLE windowHandle, COORD size)
{
	CONSOLE_FONT_INFOEX font = { sizeof(CONSOLE_FONT_INFOEX) };

	if (!GetCurrentConsoleFontEx(windowHandle, 0, &font))
	{
		return 0;
	}

	font.dwFontSize = size;

	if (!SetCurrentConsoleFontEx(windowHandle, 0, &font))
	{
		return 0;
	}

	return 1;
}



void initScreen( void )
{
   // Wymaga: windows.h
   // wylaczenie mrugania kursora - dziala od windowsa XP

	
	COORD size;

	HANDLE wHnd;    // Handle to write to the console.
	HANDLE rHnd;
   CONSOLE_CURSOR_INFO cciInfo;

   size.X = 16;
   size.Y = 16;

   wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
   rHnd = GetStdHandle(STD_INPUT_HANDLE);


   system("Title CaveExplorer2000 by Jan Sudczak");

  SMALL_RECT windowSize = { 0, 0, 119, 29 };
   SetConsoleWindowInfo(wHnd, 1, &windowSize);

   cciInfo.dwSize = 1;
   cciInfo.bVisible = 0;   
   SetConsoleCursorInfo( GetStdHandle(STD_OUTPUT_HANDLE), &cciInfo );   
   COORD bufferSize = { 50, 4 };
   SetConsoleScreenBufferSize(wHnd, bufferSize);
   SetFontSize(wHnd, size);

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