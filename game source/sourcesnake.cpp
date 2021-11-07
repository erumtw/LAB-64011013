#include <iostream>
#include <stdlib.h>
#include <string>
#include <windows.h>
#include <time.h>
#include <conio.h>
using namespace std;

//setcosole
#define screen_x 60
#define screen_y 25
const int width = 30;
const int height = 25;
#define lenght 100
const int wx = 30, hy = 25;

HANDLE wHnd;
COORD bufferSize = { screen_x,screen_y };
SMALL_RECT windowSize = { 0,0,screen_x - 1,screen_y - 1 };
COORD characterPos = { 0,0 };

//double buffer
CHAR_INFO consoleBuffer[screen_x * screen_y];

//event buffers
HANDLE rHnd;
DWORD fdwMode;
DWORD numEvents = 0;
DWORD numEventsRead = 0;

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
void game_setup();
void control_setting();
void myname();
void scorecount();
void normalModegame();
void asciiart();

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
int dir; // w.1, s.2 , a.3, d.4 , 0 stop
int Tlenght;

bool GameOn = true, mainmenu, normalMode, play;
int speed;
int score;
int mainpy = 5;

int main()
{
	game_setup();
	while (GameOn)
	{
		while (mainmenu == true)
		{
			//Oji snake game
			//Start
			//LeaderBoard
			//How to play
			//Exit
			control_setting();
			clear_buffer(); // clear
			asciiart();
			//consoleBuffer[30 + screen_x * 5].Char.AsciiChar = 'G';
			//consoleBuffer[30 + screen_x * 5].Attributes = 4;
			//consoleBuffer[30 + screen_x * 6].Char.AsciiChar = 'E';
			//consoleBuffer[30 + screen_x * 6].Attributes = 4;
			//consoleBuffer[31 + screen_x * mainpy].Char.AsciiChar = '{';
			//consoleBuffer[31 + screen_x * mainpy].Attributes = 7;
			fill_buffer_to_console();
			Sleep(100);
		}
		while(normalMode == true)
		{	
			normalModegame();
		}
	}
	return 0;
}

void normalModegame()
{
	control_setting(); // w a s d f
	clear_buffer(); // clear
	scorecount();
	myname();
	addbody();
	oji_move();
	eatcheck();
	selfhits();
	board();
	fill_oji();
	fill_food();
	fill_lemon();
	fill_buffer_to_console(); // fill
	Sleep(speed);
}
void game_setup()
{
	setcursor(0);
	srand(time(NULL));
	mainmenu = true;
	play = false;
	setConsole(screen_x, screen_y);
	setMode();
	initfood();
	initlemon();
	init_oji();
	Tlenght = 1;
	dir = 0;
	speed = 80;
	score = 0;
}

void control_setting()
{
	GetNumberOfConsoleInputEvents(rHnd, &numEvents);
	if (numEvents != 0) {
		INPUT_RECORD* eventBuffer = new INPUT_RECORD[numEvents];
		ReadConsoleInput(rHnd, eventBuffer, numEvents, &numEventsRead);
		for (DWORD i = 0; i < numEventsRead; ++i) {
			if (eventBuffer[i].EventType == KEY_EVENT && eventBuffer[i].Event.KeyEvent.bKeyDown == true) {
				if (play == true)
				{
					if (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE) {
						normalMode = false;
						mainmenu = true;
						game_setup();
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
					else if (eventBuffer[i].Event.KeyEvent.uChar.AsciiChar == 'd' && dir != 3) {
						dir = 4;
					}
					else if (eventBuffer[i].Event.KeyEvent.uChar.AsciiChar == 'f')
					{
						dir = 0;
					}
				}
				else if (mainmenu == true)
				{
					if (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode == VK_UP)
					{
						if (mainpy != 5)
							mainpy--;
					}
					else if (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode == VK_DOWN)
					{
						if (mainpy != 8)
							mainpy++;
					}
					else if (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode == VK_RETURN)
					{
						if (mainpy == 5)
						{
							mainmenu = false;
							play = true;
							normalMode = true;
						}
						else if (mainpy == 6)
						{
							exit(0);
						}
					}
				}
			}
		}
		delete[] eventBuffer;
	}
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
		SHORT x = 1 + (rand() % (wx - 2));
		SHORT y = 1 + (rand() % (hy - 2));
		food[i] = { x, y };
		for (int j = 0; i < Tlenght; i++)
		{
			if (food[i].X == oji[j].X && food[i].Y == oji[j].Y)
			{
				SHORT x = 1 + (rand() % (wx - 2));
				SHORT y = 1 + (rand() % (hy - 2));
				food[i] = { x, y };
			}
		}
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
	SHORT x = 10 + (rand() % (wx - 15));
	SHORT y = 5 + (rand() % (hy - 10));
	oji[0] = { x, y };
}

void fill_oji()
{
	for (int i = 0; i < Tlenght; i++)
	{
		consoleBuffer[oji[i].X + screen_x * oji[i].Y].Char.AsciiChar = '@';
		if(i == 0)
			consoleBuffer[oji[i].X + screen_x * oji[i].Y].Attributes = 7;
		else
			consoleBuffer[oji[i].X + screen_x * oji[i].Y].Attributes = 8;
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
			else {
				mainmenu = true;
				normalMode = false;
				game_setup();
			}
		}
		else if (dir == 2) {
			if (oji[0].Y < height - 2)
			{
				oji[0] = { oji[0].X, oji[0].Y + 1 };
				Sleep(speed/2);
			}
			else {
				normalMode = false;
				mainmenu = true;
				game_setup();
			}
			
		}
		else if (dir == 3) {
			if (oji[0].X > 1)
				oji[0] = { oji[0].X - 1, oji[0].Y };
			else {
				normalMode = false;
				mainmenu = true;
				game_setup();
			}

		}
		else if (dir == 4) {
			if (oji[0].X < width - 2)
				oji[0] = { oji[0].X + 1, oji[0].Y };
			else {
				normalMode = false;
				mainmenu = true;
				game_setup();
			}
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
			score += 10;

		}
	}
	for (size_t i = 0; i < lemoncount; i++)
	{
		if (oji[0].X == lemon[i].X && oji[0].Y == lemon[i].Y)
		{
			initlemon();
			score -= 10;
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

int fposX, fposY, sposX, sposY;
void addbody()
{
	if (dir != 0)
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
}


void myname()
{
	COORD name;
	const char* nametext = "64011013 AMREE THAOWAN";
	SHORT px = 35;
	SHORT py = 24;
	for (size_t i = 0; i < 22; i++)
	{
		consoleBuffer[(px + i) + screen_x * py].Char.AsciiChar = nametext[i];
		consoleBuffer[(px + i) + screen_x * py].Attributes = 7;
	}
}

void scorecount()
{	

	const char* scoretext = "SCORE = ";
	SHORT px = 40;
	SHORT py = 18;
	for (size_t i = 0; i < strlen(scoretext); i++)
	{
		consoleBuffer[(px + i) + screen_x * py].Char.AsciiChar = scoretext[i];
		consoleBuffer[(px + i) + screen_x * py].Attributes = 7;
	}

	string s = to_string(score);
	const char* nchar = s.c_str();
	for (size_t i = 0; i < 3; i++)
	{
		consoleBuffer[(48 + i) + screen_x * 18].Char.AsciiChar = nchar[i];
		consoleBuffer[(48 + i) + screen_x * 18].Attributes = 7;
	}
}


void asciiart()
{
	const char* ftext = "             ____";
	SHORT px = 20;
	for (size_t i = 0; i < strlen(ftext); i++)
	{
		consoleBuffer[(px + i) + screen_x * 3].Char.AsciiChar = ftext[i];
		consoleBuffer[(px + i) + screen_x * 3].Attributes = 7;
	}
	const char* stext = "            / . .\\";
	for (size_t i = 0; i < strlen(stext); i++)
	{
		consoleBuffer[(px + i) + screen_x * 4].Char.AsciiChar = stext[i];
		consoleBuffer[(px + i) + screen_x * 4].Attributes = 7;
	}
	const char* dtext = "            \\  ---<";
	for (size_t i = 0; i < strlen(dtext); i++)
	{
		consoleBuffer[(px + i) + screen_x * 5].Char.AsciiChar = dtext[i];
		consoleBuffer[(px + i) + screen_x * 5].Attributes = 7;
	}
	const char* gtext = "             \\  /";
	for (size_t i = 0; i < strlen(gtext); i++)
	{
		consoleBuffer[(px + i) + screen_x * 6].Char.AsciiChar = gtext[i];
		consoleBuffer[(px + i) + screen_x * 6].Attributes = 7;
	}
	const char* htext = "   __________/ /";
	for (size_t i = 0; i < strlen(htext); i++)
	{
		consoleBuffer[(px + i) + screen_x * 7].Char.AsciiChar = htext[i];
		consoleBuffer[(px + i) + screen_x * 7].Attributes = 7;
	}
	const char* jtext = "-=:___________/";
	for (size_t i = 0; i < strlen(jtext); i++)
	{
		consoleBuffer[(px + i) + screen_x * 8].Char.AsciiChar = jtext[i];
		consoleBuffer[(px + i) + screen_x * 8].Attributes = 7;
	}

	/*
	       _ _ 
      (_|_)
  ___  _ _ 
 / _ \| | |
| (_) | | |
 \___/| |_|
     _/ |  
    |__/   */
}
