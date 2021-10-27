#include <iostream>
#include <windows.h>
#include <time.h>
#include <conio.h>
using namespace std;

//setcosole
#define screen_x 70
#define screen_y 25
const int width = 40;
const int height = 25;
#define lenght 100
const int wx = 40, hy = 25;

HANDLE wHnd;
COORD bufferSize = { screen_x,screen_y };
SMALL_RECT windowSize = { 0,0,screen_x - 1,screen_y - 1 };
COORD characterPos = { 0,0 };

//double buffer
CHAR_INFO consoleBuffer[screen_x * screen_y];

//event buffers
HANDLE rHnd;
DWORD fdwMode;


//function
int setConsole(int, int);
int setMode();
void fill_buffer_to_console();
void fill_food();
void clear_buffer();
void initfood();
void initlemon();
void fill_lemon();
void init_oji();
void fill_oji();
void oji_move();
void board();
void eatcheck();
void addbody();
void setcursor(bool);
void selfhits();

//food
#define count 100
bool foodstat = false;
COORD food[count];
int atefood = 0;
//lemon
bool lemonstat = false;
COORD lemon[count];
int atelemon = 0;
//Oji
COORD oji[lenght];
int dir = 4; // w.1, s.2 , a.3, d.4 , 5 stop
int Tlenght = 1;

bool play;
int speed = 70;

int main()
{
	setcursor(0);
	play = true;
	DWORD numEvents = 0;
	DWORD numEventsRead = 0;
	srand(time(NULL));
	setConsole(screen_x, screen_y);
	setMode();
	initfood();
	initlemon();
	init_oji();

	while(play)
	{	
		GetNumberOfConsoleInputEvents(rHnd, &numEvents);
		if (numEvents != 0) {
			INPUT_RECORD* eventBuffer = new INPUT_RECORD[numEvents];
			ReadConsoleInput(rHnd, eventBuffer, numEvents, &numEventsRead);
			for (DWORD i = 0; i < numEventsRead; ++i) {
				if (eventBuffer[i].EventType == KEY_EVENT && eventBuffer[i].Event.KeyEvent.bKeyDown == true) {
					if (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE) {
						play = false;
					}
					else if (eventBuffer[i].Event.KeyEvent.uChar.AsciiChar == 'w' && dir != 2) {
						dir = 1;
					}
					else if (eventBuffer[i].Event.KeyEvent.uChar.AsciiChar == 's' && dir != 1) {
						dir = 2;
					}
					else if (eventBuffer[i].Event.KeyEvent.uChar.AsciiChar == 'a' && dir != 4) {
						dir = 3;
					}
					else if (eventBuffer[i].Event.KeyEvent.uChar.AsciiChar == 'd' && dir !=3) {
						dir = 4;
					}
					else if (eventBuffer[i].Event.KeyEvent.uChar.AsciiChar == 'x')
					{
						dir = 5;
					}
				}
			}
			delete[] eventBuffer;
		}
		clear_buffer();
		addbody(); 
		oji_move();
		eatcheck();
		selfhits();
		board();
		fill_oji();
		fill_food();
		fill_lemon();
		fill_buffer_to_console();
		Sleep(speed);
	}
	return 0;
}


void setcursor(bool visible)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
}
int setConsole(int x, int y)
{
	wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleWindowInfo(wHnd, TRUE, &windowSize);
	SetConsoleScreenBufferSize(wHnd, bufferSize);
	return 0;
}

void fill_buffer_to_console()
{
	WriteConsoleOutputA(wHnd, consoleBuffer, bufferSize, characterPos,
		&windowSize);
}

void clear_buffer()
{
	for (int y = 0; y < screen_y; ++y) {
		for (int x = 0; x < screen_x; ++x) {
			consoleBuffer[x + screen_x * y].Char.AsciiChar = ' ';
			consoleBuffer[x + screen_x * y].Attributes = 0;
		}
	}
}

int setMode()
{
	rHnd = GetStdHandle(STD_INPUT_HANDLE);
	fdwMode = ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT |
		ENABLE_MOUSE_INPUT;
	SetConsoleMode(rHnd, fdwMode);
	return 0;
}

int foodcount = 1;
void fill_food()
{
	for (int i = 0; i < foodcount; i++)
	{
		consoleBuffer[food[i].X + screen_x * food[i].Y].Char.AsciiChar = '*';
		consoleBuffer[food[i].X + screen_x * food[i].Y].Attributes = 4;
	}
}

int lemoncount = 1;
void fill_lemon()
{
	for (int i = 0; i < lemoncount; i++)
	{
		consoleBuffer[lemon[i].X + screen_x * lemon[i].Y].Char.AsciiChar = 'o';
		consoleBuffer[lemon[i].X + screen_x * lemon[i].Y].Attributes = 2;
	}
}

void initfood()
{
	for (int i = 0; i < foodcount; i++)
	{
		SHORT x = 1 + (rand() % (wx- 2));
		SHORT y = 1 + (rand() % (hy - 2));
		food[i] = { x, y };
	}
}

void initlemon()
{
	for (int i = 0; i < lemoncount; i++)
	{
		SHORT x = 1 + (rand() % (wx - 2));
		SHORT y = 1 + (rand() % (hy - 2));
		lemon[i] = { x, y };
	}
}

void init_oji()
{
	int findx, findy;
	SHORT x, y;

	for (int i = 0; i != food[0].X; i++)
	{
		findx = 10 + (rand() % (wx - 15));
		findy = 5 + (rand() % (hy - 10));
		if (findx != food[0].X)
			x = findx;
		if (findy != food[0].Y)
			y = findy;
	}
	oji[0] = { x, y };
}

void fill_oji()
{
	for (int i = 0; i < Tlenght; i++)
	{
		consoleBuffer[oji[i].X + screen_x * oji[i].Y].Char.AsciiChar = '@';
		consoleBuffer[oji[i].X + screen_x * oji[i].Y].Attributes = 7;
	}
}

void oji_move()
{

		if(dir == 1){
			if (oji[0].Y > 1)
			{
				oji[0] = { oji[0].X, oji[0].Y - 1 };
				Sleep(speed/2);
			}
			else
				play = false;
			
		}
		else if (dir == 2) {
			if (oji[0].Y < height - 2)
			{
				oji[0] = { oji[0].X, oji[0].Y + 1 };
				Sleep(speed/2);
			}
			else
				play = false;
			
		}
		else if (dir == 3) {
			if (oji[0].X > 1)
				oji[0] = { oji[0].X - 1, oji[0].Y };
			else
				play = false;

		}
		else if (dir == 4) {
			if (oji[0].X < width - 2)
				oji[0] = { oji[0].X + 1, oji[0].Y };
			else
				play = false;
		}
}

void board()
{
	for (int i = 0; i < height; i++) //row
	{
		for (int j = 0; j < width; j++) // column
		{
			if (i == 0 || i == height - 1  || j == 0 || j == width - 1 )
			{
				consoleBuffer[j + screen_x * i].Char.AsciiChar = '#';
				consoleBuffer[j + screen_x * i].Attributes = 10;
			}
			else
				consoleBuffer[j + screen_x * i].Char.AsciiChar = ' ';
		}
	}
}

void eatcheck()
{
	for (size_t i = 0; i < foodcount; i++)
	{
		if (oji[0].X == food[i].X && oji[0].Y == food[i].Y)
		{
			Tlenght++;
			//atefood++;
			initfood();
			if (atefood ==  5)
			{
				foodcount+=2;
			}
		}
	}
	for (size_t i = 0; i < lemoncount; i++)
	{
		if (oji[0].X == lemon[i].X && oji[0].Y == lemon[i].Y)
		{
			initlemon();
			Tlenght--;
			//atelemon++;
			if (atelemon == atelemon + 5)
			{
				lemoncount+=2;
			}
			if (Tlenght == 0)
			{
				play = false;
			}
		}
	}
}
void selfhits()
{
	for (int i = 1; i <= Tlenght; i++)
	{
		if (oji[0].X == oji[i].X && oji[0].Y == oji[i].Y)
		{
			play = false;
		}
	}

}
//bug
int fposX, fposY, sposX, sposY;

void addbody()
{
	fposX = oji[1].X;
	fposY = oji[1].Y;
	oji[1].X = oji[0].X;
	oji[1].Y = oji[0].Y;
	for (int i = 2; i < Tlenght; i++)
	{
		sposX = oji[i].X;
		sposY = oji[i].Y;
		oji[i].X = fposX;
		oji[i].Y = fposY;
		fposX = sposX;
		fposY = sposY;
	}
}
/*
COORD name;
const char* nametext = "64011010 AMREE"
void myname()
{
	for (size_t i = 0; i < 14; i++)
	{
		consoleBuffer[name[i].X + screen_x * name[i].Y].Char.AsciiChar = nametext;
		consoleBuffer[name[i].X + screen_x * name[i].Y].Attributes = 7;
	}
}
*/
