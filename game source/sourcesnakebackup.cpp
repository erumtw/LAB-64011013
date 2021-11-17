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
void initwall();
void fill_wall();
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
void menuascii();
void modepage();
void gameoverpage();
void howtoplaypage();
//food
#define count 100
COORD food[count];
int atefood;
int foodcount;
//wall
bool wallstat;
COORD wall[count];
int wallcount;
//Oji
COORD oji[lenght];
int dir; // w.1, s.2 , a.3, d.4 , 0 stop
int Tlenght;

bool GameOn = true, mainmenu, modemenu, normalMode, obstructMode, play, Gameover = false, howtoplay;
float speed;
int score;
int mainpy = 15, modepy = 11, gameoverpy = 17;

int main()
{
	game_setup();
	while (GameOn)
	{
		while (howtoplay == true)
		{
			control_setting();
			clear_buffer();
			howtoplaypage();
			fill_buffer_to_console();
			Sleep(160);
		}
		while (Gameover == true)
		{
			control_setting();
			clear_buffer();
			gameoverpage();
			consoleBuffer[40 + screen_x * gameoverpy].Char.AsciiChar = '<';
			consoleBuffer[40 + screen_x * gameoverpy].Attributes = 3;
			fill_buffer_to_console();
			Sleep(160);
		}
		while (mainmenu == true)
		{
			control_setting();
			clear_buffer(); // clear
			menuascii();
			consoleBuffer[37 + screen_x * mainpy].Char.AsciiChar = '<';
			consoleBuffer[37 + screen_x * mainpy].Attributes = 3;
			fill_buffer_to_console();
			Sleep(160);
		}
		while (modemenu == true)
		{
			control_setting();
			clear_buffer();
			modepage();
			consoleBuffer[37 + screen_x * modepy].Char.AsciiChar = '<';
			consoleBuffer[37 + screen_x * modepy].Attributes = 3;
			fill_buffer_to_console();
			Sleep(160);
		}
		while(normalMode == true)
		{	
			normalModegame();
		}
	}
	return 0;
}


void game_setup()
{
	setcursor(0);
	srand(time(NULL));
	mainmenu = true;
	play = false;
	modemenu = false;
	normalMode = false;
	obstructMode = false;
	wallstat = false;
	foodcount = 1;
	wallcount = 0;
	atefood = 3;
	setConsole(screen_x, screen_y);
	setMode();
	init_oji();
	initfood();
	initwall();
	Tlenght = 1;
	dir = 0;
	speed = 90;
	score = 0;
}

void normalModegame()
{
	control_setting(); // w a s d f
	clear_buffer(); // clear
	scorecount();
	board();
	addbody();
	oji_move();
	eatcheck();
	selfhits();
	fill_oji();
	fill_food();
	fill_wall();
	fill_buffer_to_console(); // fill
	Sleep(speed);
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
						Sleep(300);
						normalMode = false;
						mainmenu = true;
						play = false;
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
					else if (eventBuffer[i].Event.KeyEvent.uChar.AsciiChar == 'f'){
						dir = 0;
					}
				}
				else if (mainmenu == true)
				{
					if (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode == VK_UP)
					{
						if (mainpy != 15)
							mainpy -= 2;
					}
					else if (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode == VK_DOWN)
					{
						if (mainpy != 21)
							mainpy += 2;
					}
					else if (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode == VK_RETURN)
					{
						if (mainpy == 15)
						{
							game_setup();
							mainmenu = false;
							modemenu = true;
						}
						//else if (mainpy == 17)
						else if (mainpy == 19)
						{
							mainmenu = false;
							howtoplay = true;
						}
						else if (mainpy == 21)
						{
							exit(0);
						}
					}
				}
				else if (modemenu == true)
				{
					if (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode == VK_UP)
					{
						if (modepy != 11)
							modepy -= 2;
					}
					else if (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode == VK_DOWN)
					{
						if (modepy != 15)
							modepy += 2;
					}
					else if (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode == VK_RETURN)
					{
						if (modepy == 11)
						{
							//game_setup();
							modemenu = false;
							play = true;
							normalMode = true;
						}
						else if (modepy == 13)
						{
							//game_setup();
							wallstat = true;
							modemenu = false;
							play = true;
							normalMode = true;
						}
						else if (modepy == 15)
						{
							modemenu = false;
							mainmenu = true;
						}
					}
				}
				else if (Gameover == true)
				{
					if (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode == VK_RETURN)
					{
							mainmenu = true;
							Gameover = false;
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
	WriteConsoleOutputA(wHnd, consoleBuffer, bufferSize, characterPos, &windowSize);
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

void fill_food()
{
	for (int i = 0; i < foodcount; i++)
	{
		consoleBuffer[food[i].X + screen_x * food[i].Y].Char.AsciiChar = '*';
		consoleBuffer[food[i].X + screen_x * food[i].Y].Attributes = 4;
	}
}


void fill_wall()
{
	if (wallstat == true)
	{
		for (int i = 0; i < wallcount; i++)
		{
			consoleBuffer[wall[i].X + screen_x * wall[i].Y].Char.AsciiChar = '#';
			consoleBuffer[wall[i].X + screen_x * wall[i].Y].Attributes = 10;
		}
	}
}

void initfood()
{
	for (int i = 0; i < foodcount; i++)
	{
		SHORT x = 1 + (rand() % (wx - 2));
		SHORT y = 1 + (rand() % (hy - 2));
		for (int j = 0; j < Tlenght; j++)
		{
			while (x == oji[j].X && y == oji[j].Y)
			{
				SHORT x = 1 + (rand() % (wx - 2));
				SHORT y = 1 + (rand() % (hy - 2));
			}
		}
		food[i] = { x, y };
	}

	/*
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
	*/
}

void initwall()
{
	if (wallstat == true)
	{
		for (int i = wallcount; i <= wallcount; i++)
		{
			SHORT x = 2 + (rand() % (wx - 3));
			SHORT y = 2 + (rand() % (hy - 4));
			wall[i] = { x, y };
		}
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
				Sleep(250);
				Gameover = true;
				normalMode = false;
				play = false;
				//game_setup();
			}
		}
		else if (dir == 2) {
			if (oji[0].Y < height - 2)
			{
				oji[0] = { oji[0].X, oji[0].Y + 1 };
				Sleep(speed/2);
			}
			else {
				Sleep(250);
				Gameover = true;
				normalMode = false;
				play = false;
				//game_setup();
			}
		}

		else if (dir == 3) {
			if (oji[0].X > 1)
				oji[0] = { oji[0].X - 1, oji[0].Y };
			else {
				Sleep(250);
				Gameover = true;
				normalMode = false;
				play = false;
				//game_setup();
			}
		}

		else if (dir == 4) {
			if (oji[0].X < width - 2)
				oji[0] = { oji[0].X + 1, oji[0].Y };
			else {
				Sleep(250);
				Gameover = true;
				normalMode = false;
				play = false;
				//game_setup();
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
			initfood();
			score += 10;
			if (speed != 50)
				speed -= 0.5;
			if (wallstat == true)
			{
				atefood--;
				if (atefood < 1)
				{
					initwall();
					wallcount++;
					atefood = 3;
				}
			}
		}
	}

	for (size_t i = 0; i < wallcount; i++)
	{
		if (oji[0].X == wall[i].X && oji[0].Y == wall[i].Y)
		{
			play = false;
			normalMode = false;
			Gameover = true;
			//game_setup();
		}
	}
}
void selfhits()
{
	for (int i = 1; i <= Tlenght; i++)
	{
		if (oji[0].X == oji[i].X && oji[0].Y == oji[i].Y)
		{
			Sleep(250);
			normalMode = false;
			play = false;
			Gameover = true;
			//game_setup();
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


void menuascii()
{
	SHORT px = 20, py = 3;
	const char* ftext = "             ____";
	const char* stext = "            / . .\\";
	const char* dtext = "            \\  ---<";
	const char* gtext = "             \\  /";
	const char* htext = "   __________/ /";
	const char* jtext = "-=:___________/";

	for (size_t i = 0; i < strlen(ftext); i++)
	{
		consoleBuffer[(px + i) + screen_x * py].Char.AsciiChar = ftext[i];
		consoleBuffer[(px + i) + screen_x * py].Attributes = 10;
	}
	for (size_t i = 0; i < strlen(stext); i++)
	{
		consoleBuffer[(px + i) + screen_x * (py+1)].Char.AsciiChar = stext[i];
		consoleBuffer[(px + i) + screen_x * (py+1)].Attributes = 10;
	}
	for (size_t i = 0; i < strlen(dtext); i++)
	{
		consoleBuffer[(px + i) + screen_x * (py+2)].Char.AsciiChar = dtext[i];
		consoleBuffer[(px + i) + screen_x * (py+2)].Attributes = 10;
	}
	for (size_t i = 0; i < strlen(gtext); i++)
	{
		consoleBuffer[(px + i) + screen_x * (py+3)].Char.AsciiChar = gtext[i];
		consoleBuffer[(px + i) + screen_x * (py+3)].Attributes = 10;
	}
	for (size_t i = 0; i < strlen(htext); i++)
	{
		consoleBuffer[(px + i) + screen_x * (py+4)].Char.AsciiChar = htext[i];
		consoleBuffer[(px + i) + screen_x * (py+4)].Attributes = 10;
	}
	for (size_t i = 0; i < strlen(jtext); i++)
	{
		consoleBuffer[(px + i) + screen_x * (py+5)].Char.AsciiChar = jtext[i];
		consoleBuffer[(px + i) + screen_x * (py+5)].Attributes = 10;
	}

	const char* a1 = "OJI's";
	const char* start = "Start";
	const char* leader = "Leaderboard";
	const char* how = "How to play";
	const char* Exits = "Exits";

	for (size_t i = 0; i < strlen(a1); i++)
	{
		consoleBuffer[(28 + i) + screen_x * (py + 8)].Char.AsciiChar = a1[i];
		consoleBuffer[(28 + i) + screen_x * (py + 8)].Attributes = 7;
	}

	for (size_t i = 0; i < strlen(start); i++)
	{
		consoleBuffer[(28 + i) + screen_x * (py + 12)].Char.AsciiChar = start[i];
		consoleBuffer[(28 + i) + screen_x * (py + 12)].Attributes = 7;
	}

	for (size_t i = 0; i < strlen(leader); i++)
	{
		consoleBuffer[(25 + i) + screen_x * (py + 14)].Char.AsciiChar = leader[i];
		consoleBuffer[(25 + i) + screen_x * (py + 14)].Attributes = 7;
	}

	for (size_t i = 0; i < strlen(how); i++)
	{
		consoleBuffer[(25 + i) + screen_x * (py + 16)].Char.AsciiChar = how[i];
		consoleBuffer[(25 + i) + screen_x * (py + 16)].Attributes = 7;
	}

	for (size_t i = 0; i < strlen(Exits); i++)
	{
		consoleBuffer[(28 + i) + screen_x * (py + 18)].Char.AsciiChar = Exits[i];
		consoleBuffer[(28 + i) + screen_x * (py + 18)].Attributes = 7;
	}

	const char* nametext = "By 64011013/T. AMREE";
	SHORT tx = 35;
	SHORT ty = 24;
	for (size_t i = 0; i < 22; i++)
	{
		consoleBuffer[(tx + i) + screen_x * ty].Char.AsciiChar = nametext[i];
		consoleBuffer[(tx + i) + screen_x * ty].Attributes = 7;
	}
}

void modepage()
{
	const char* b1 = "MODES";
	const char* b2 = "Challenge";
	const char* b3 = "Obstructions";
	const char* b4 = "Return";
	int py = 8;

	for (size_t i = 0; i < strlen(b1); i++)
	{
		consoleBuffer[(27 + i) + screen_x * py].Char.AsciiChar = b1[i];
		consoleBuffer[(27 + i) + screen_x * py].Attributes = 7;
	}

	for (size_t i = 0; i < strlen(b2); i++)
	{
		consoleBuffer[(25 + i) + screen_x * (py + 3)].Char.AsciiChar = b2[i];
		consoleBuffer[(25 + i) + screen_x * (py + 3)].Attributes = 7;
	}

	for (size_t i = 0; i < strlen(b3); i++)
	{
		consoleBuffer[(24 + i) + screen_x * (py + 5)].Char.AsciiChar = b3[i];
		consoleBuffer[(24 + i) + screen_x * (py + 5)].Attributes = 7;
	}

	for (size_t i = 0; i < strlen(b4); i++)
	{
		consoleBuffer[(27 + i) + screen_x * (py + 7)].Char.AsciiChar = b4[i];
		consoleBuffer[(27 + i) + screen_x * (py + 7)].Attributes = 7;
	}
}

void gameoverpage()
{
	SHORT py = 13;
	const char* text1 = "GAME OVER!!!!";
	const char* scoretext = " SCORE  = ";
	const char* text3 = "BACK TO MAIN MENU";
	for (size_t i = 0; i < strlen(text1); i++)
	{
		consoleBuffer[(24 + i) + screen_x * (py - 4)].Char.AsciiChar = text1[i];
		consoleBuffer[(24 + i) + screen_x * (py - 4)].Attributes = 4;
	}

	for (size_t i = 0; i < strlen(scoretext); i++)
	{
		consoleBuffer[(24 + i) + screen_x * (py + 0)].Char.AsciiChar = scoretext[i];
		consoleBuffer[(24 + i) + screen_x * (py + 0)].Attributes = 7;
	}

	string s = to_string(score);
	const char* nchar = s.c_str();
	for (size_t i = 0; i < 3; i++)
	{
		consoleBuffer[(34 + i) + screen_x * (py + 0)].Char.AsciiChar = nchar[i];
		consoleBuffer[(34 + i) + screen_x * (py + 0)].Attributes = 7;
	}

	for (size_t i = 0; i < strlen(text3); i++)
	{
		consoleBuffer[(22 + i) + screen_x * (py + 4)].Char.AsciiChar = text3[i];
		consoleBuffer[(22 + i) + screen_x * (py + 4)].Attributes = 7;
	}
}


void howtoplaypage()
{
	int py = 3;
	const char* topic = "HOW TO PLAY";
	const char* line1 = "KEY                         DETAIL";
	const char* line2 = " w                          go up";
	const char* line3 = " s                         go down";
	const char* line4 = " a                         go left";
	const char* line5 = "  d                         go right";
	const char* line6 = " f                          pause";
	for (size_t i = 0; i < strlen(topic); i++)
	{
		consoleBuffer[(((60 - strlen(topic))/2)+i) + screen_x * (py + 0)].Char.AsciiChar = topic[i];
		consoleBuffer[(((60 - strlen(topic)) / 2) + i) + screen_x * (py + 0)].Attributes = 7;
	}

	for (size_t i = 0; i < strlen(line1); i++)
	{
		consoleBuffer[(((60 - strlen(line1)) / 2) + i) + screen_x * (py + 3)].Char.AsciiChar = line1[i];
		consoleBuffer[(((60 - strlen(line1)) / 2) + i) + screen_x * (py + 3)].Attributes = 7;
	}

	for (size_t i = 0; i < strlen(line2); i++)
	{
		consoleBuffer[(((60 - strlen(line2)) / 2) + i) + screen_x * (py + 5)].Char.AsciiChar = line2[i];
		consoleBuffer[(((60 - strlen(line2)) / 2) + i) + screen_x * (py + 5)].Attributes = 7;
	}

	for (size_t i = 0; i < strlen(line3); i++)
	{
		consoleBuffer[(((60 - strlen(line3)) / 2) + i) + screen_x * (py + 7)].Char.AsciiChar = line3[i];
		consoleBuffer[(((60 - strlen(line3)) / 2) + i) + screen_x * (py + 7)].Attributes = 7;
	}

	for (size_t i = 0; i < strlen(line4); i++)
	{
		consoleBuffer[(((60 - strlen(line4)) / 2) + i) + screen_x * (py + 9)].Char.AsciiChar = line4[i];
		consoleBuffer[(((60 - strlen(line4)) / 2) + i) + screen_x * (py + 9)].Attributes = 7;
	}

	for (size_t i = 0; i < strlen(line5); i++)
	{
		consoleBuffer[(((60 - strlen(line5)) / 2) + i) + screen_x * (py + 11)].Char.AsciiChar = line5[i];
		consoleBuffer[(((60 - strlen(line5)) / 2) + i) + screen_x * (py + 11)].Attributes = 7;
	}

	for (size_t i = 0; i < strlen(line6); i++)
	{
		consoleBuffer[(((60 - strlen(line6)) / 2) + i) + screen_x * (py + 13)].Char.AsciiChar = line6[i];
		consoleBuffer[(((60 - strlen(line6)) / 2) + i) + screen_x * (py + 13)].Attributes = 7;
	}
}