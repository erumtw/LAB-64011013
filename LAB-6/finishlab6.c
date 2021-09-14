#include <stdio.h>
#include <windows.h>
#include <conio.h>
// finish for lab6_game02
void gotoxy(int, int);
void draw_ship(int, int);
void setcursor(bool);
void setcolor(int, int);
void del_bg(int, int);
void draw_bullet(int, int);
void del_bullet(int, int);
void setBullet(int, int);
void bulletState();
// shooting set
int bullet[5] = { 0,0,0,0,0 }; // 0 = off, 1 = on
int xs[5], ys[5];
int countf = 0;

int main()
{
	char ch = ' ';
	int x = 38, y = 25;

	draw_ship(x, y);
	setcursor(0);
	int dir = 0; // 0 = stop, 1 = Left, 2 = right

	int i = 0;
	do
	{
		// _kbgit() check if keyboard used
		if (_kbhit())
		{
			//_getch() pull keyboard buffer put in ch
			ch = _getch();
			if (ch == 'a' || ch == 'A')
			{
				dir = 1;
			}
			if (ch == 'd' || ch == 'D')
			{
				dir = 2;
			}
			if (ch == 's')
			{
				dir = 0;
			}
			if (ch == 'f')
			{
				countf++;
				if (countf < 6)
				{
					setBullet(x,y);
				}
			}
			fflush(stdin);	//this command is for clear ch in keyboard 
			// check direction		
		}


		if (dir == 1 && x > 0) // to left ; dir = 1
		{
			del_bg(x, y);
			draw_ship(--x, y);
		}

		if (dir == 2 && x < 76) // to right ; dir = 2
		{
			del_bg(x, y);
			draw_ship(++x, y);
		}

		bulletState();
		
		Sleep(55);
	} while (ch != 'x');
	return 0;
}

void gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void draw_ship(int x, int y)
{
	gotoxy(x, y);
	setcolor(2, 4);
	printf("<-0->");
}

void draw_bullet(int x, int y)
{
	gotoxy(x, y);
	//setcolor(2, 4);
	printf("|");
}

void del_bullet(int x, int y)
{
	gotoxy(x, y);
	setcolor(0, 0);
	printf(" ");
}

void del_bg(int x, int y)
{
	gotoxy(x, y);
	setcolor(0, 0);
	printf("       ");
}

void setcursor(bool visible)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
}

void setcolor(int fg, int bg)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, bg * 16 + fg);
}

void bulletState()
{
	int i;
	for (i = 0; i < 6; i++)
	{
		if (bullet[i] == 1)
		{
			del_bullet(xs[i], ys[i]);
			if (ys[i] > 0)
			{
				setcolor(2, i+1);
				draw_bullet(xs[i], --ys[i]);
			}
			else
			{
				if(i == 0)
				{
				countf = 0;
				}
				bullet[i] = 0;
			}
		}
	}
}

void setBullet(int x, int y)
{
	int i;
	for (i = 0; i < 6; ++i)
	{
		if (bullet[i] == 0 && countf == i+1 )
		{
			bullet[i] = 1;
			xs[i] = x + 2;
			ys[i] = y - 1;
		
		}	
	}
}