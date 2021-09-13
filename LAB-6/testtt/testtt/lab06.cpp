#include <stdio.h>
#include <windows.h>
#include <conio.h>
// Lab 6 : Text Mode Game 02 
// 64011013
void gotoxy(int, int);
void draw_ship(int, int);
void setcursor(bool);
void setcolor(int, int);
void del_bg(int, int);
void draw_bullet(int, int);
void del_bullet(int, int);

int main()
{
	char ch = ' ';
	int x = 38, y = 20;
	//int count = 0;
	//int *c;
	//c = &count;
	
	setcursor(0);
	draw_ship(x, y);
	int dir = 0; // 0 = stop, 1 = Left, 2 = right
	int shoot = 0; // 0 = off 1 = on
	int xs[5], ys[5], count = 6;
	//int xs2, ys2;
	int i = 0;
	do
	{	
		
		// _kbgit() check if keyboard used
		if ( _kbhit() ) 
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
			if (count > 1 && count <= 6)
			{
				if (ch == 'f')
				{
					count--;
					shoot = 1;
					if (count == 5)
					{
						xs[0] = x + 2;
						ys[0] = y - 1;
					}
					if (count == 4)
					{
						xs[1] = x + 2;
						ys[1] = y - 1;
					}
					if (count == 3)
					{
						xs[2] = x + 2;
						ys[2] = y - 1;
					}
					if (count == 2)
					{
						xs[3] = x + 2;
						ys[3] = y - 1;
					}
					if (count == 1)
					{
						xs[4] = x + 2;
						ys[4] = y - 1;
					}
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

		if (shoot == 1) 
		{	
			if (count != 0)
			{
				if (count <= 5)
				{
					del_bullet(xs[0], ys[0]);
					if (ys[0] > 0) {
						setcolor(3, 5);
						draw_bullet(xs[0], --ys[0]);
					}
					else {
						if (count > 4)
							count++;
					}
				}
				if (count <= 4)
				{
					del_bullet(xs[1], ys[1]);
					if (ys[1] > 0) {
						setcolor(3, 4);
						draw_bullet(xs[1], --ys[1]);
					}
					else {
						if (count > 3)
							count++;
					}
				}
				if (count <= 3)
				{
					del_bullet(xs[2], ys[2]);
					if (ys[2] > 0) {
						setcolor(3, 3);
						draw_bullet(xs[2], --ys[2]);
					}
					else {
						if (count > 2)
						count++;
					}
				}

				if (count <= 2) 
				{
					del_bullet(xs[3], ys[3]);
					if (ys[3] > 0) {
						setcolor(2, 2);
						draw_bullet(xs[3], --ys[3]);
					}
					else {
						if(count > 1)
						count++;
					}
				}

				if (count < 2)
				{
					del_bullet(xs[4], ys[4]);
					if (ys[4] > 0) {
						setcolor(3, 1);	
						draw_bullet(xs[4], --ys[4]);
					}
					else {

						count++;
					}

				}

				else if (ys[0] < 0)
				{
					count = 1;
					shoot = 0;
				}
				
			}
		}
		Sleep(100);
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
	setcolor(0, 3);
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