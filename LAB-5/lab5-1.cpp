#include <stdio.h>
#include <windows.h>
#include <conio.h>

void gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void draw_ship(int x, int y)
{
	gotoxy(x, y);
	printf(" <-0-> ");
}

void erase_ship(int x, int y)
{
	gotoxy(x, y);
	printf("       ");
}

int main()
{
	char ch = ' ';
	int x = 80, y = 20;
	draw_ship(x, y);
		do
		{
			if (_kbhit()) // _kbgit() check if keyboard used
			{
				ch = _getch(); //_getch() pull keyboard buffer put in ch
				if (ch == 'a' || ch == 'A') 
				{ 
					draw_ship(--x, y); 
				}
				if (ch == 'd' || ch == 'D') 
				{ 
					draw_ship(++x, y); 
				}
				if (ch == 'w' || ch == 'W') 
				{ 
					erase_ship(x, y);
					draw_ship(x, --y);
				}
				if (ch == 's' || ch == 'S') 
				{ 
					erase_ship(x, y);
					draw_ship(x, ++y); 
				}
				fflush(stdin); //this command is for clear ch in keyboard buffer
			}
			if (x > 80) {
				erase_ship(x, y);
				x = 1;
			}
			if (x < 1) {
				erase_ship(x, y);
				x = 80;
			}
			Sleep(100);
		} while (ch != 'x' );
	return 0;
}