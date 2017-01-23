#include "console.h"

#include <windows.h> 
#include <stdio.h>
#include <conio.h>


void initScreen( void )
{


	HWND wh = GetConsoleWindow();


	MoveWindow(wh, 100, 100, 920, 400, TRUE); //zmiana rozmiaru okna na odpowiedni

	//ustawianie rozmiaru bufora okna
	COORD bufferSize = { 110, 30 };
	SetConsoleScreenBufferSize(wh, bufferSize);

	system("Title CaveExplorer2000 by Jan Sudczak"); //ustawianie tytu³u okna

	//wy³¹czenie migania kursora
	CONSOLE_CURSOR_INFO cciInfo;
	cciInfo.dwSize = 1;
	cciInfo.bVisible = 0;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cciInfo);

		//Ustawianie czcionki na Terminal 8x12
	  CONSOLE_FONT_INFOEX info = { 0 };
	  info.cbSize = sizeof(info);
	  info.dwFontSize.X = 8;
	  info.dwFontSize.Y = 12;
	  info.FontWeight = FW_NORMAL;
	  wcscpy(info.FaceName, L"Terminal");
	  SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), NULL, &info);
	

	   system( "chcp 852" ); //na koniec kodowanie. Jest to raczej niepotrzebne, ale dam ¿eby by³o na wszelki wypadek :D
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