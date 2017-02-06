#include "config.h"

void SetConsoleWindowSize(int x, int y)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);


		

	// If either dimension is greater than the largest console window we can have,
	// there is no point in attempting the change.
	
		
	


	CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
	GetConsoleScreenBufferInfo(h, &bufferInfo);
		

	SMALL_RECT winInfo = bufferInfo.srWindow;
	COORD windowSize = { winInfo.Right - winInfo.Left + 1, winInfo.Bottom - winInfo.Top + 1 };

	if (windowSize.X > x || windowSize.Y > y)
	{
		// window size needs to be adjusted before the buffer size can be reduced.
		SMALL_RECT info =
		{
			0,
			0,
			x < windowSize.X ? x - 1 : windowSize.X - 1,
			y < windowSize.Y ? y - 1 : windowSize.Y - 1
		};

		SetConsoleWindowInfo(h, TRUE, &info);
			
	}

	COORD size = { x, y };
	SetConsoleScreenBufferSize(h, size);
		


	SMALL_RECT info = { 0, 0, x - 1, y - 1 };
	SetConsoleWindowInfo(h, TRUE, &info);
		
}

void initScreen( void )
{


	
	HANDLE wh2 = GetStdHandle(STD_OUTPUT_HANDLE);



	

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
	

	  ////ustawianie rozmiaru bufora okna
	  COORD bufferSize = { 120, 31 };
	  SetConsoleScreenBufferSize(wh2, bufferSize);

	  //SMALL_RECT windowSize = { 0, 0, 120, 29 };
	  //SetConsoleWindowInfo(wh2, 1, &windowSize);

	  //ShowWindow(GetConsoleWindow(), SW_NORMAL);

	  SetConsoleWindowSize(120, 31); //ustawianie rozmiaru ekranu
	

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



	setColor(0x0F);

}