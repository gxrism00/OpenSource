// 2048 GAME V7
// BY BTS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#ifdef _WIN32 //Linux platform
#include <conio.h>
#include <windows.h>
#else  
#include <termios.h>
#include <unistd.h>
#endif

#define Left 75
#define Right 77
#define Up 72
#define Down 80


int num[4][4];
int num_v[4][4];//comparation
char direct;
int check();
int signal;
int score;
int express_row;
int express_column;

char get1char(void)
{
#ifdef _WIN32
	// Do nothing
#else   
	struct termios stored_settings;
	struct termios new_settings;
	tcgetattr(0, &stored_settings);
	new_settings = stored_settings;
	new_settings.c_lflag &= (~ICANON);
	new_settings.c_cc[VTIME] = 0;
	new_settings.c_cc[VMIN] = 1;
	tcsetattr(0, TCSANOW, &new_settings);
#endif
	int ret = 0;
	char c;

#ifdef _WIN32
	c = _getch();
	if (c == -32) {
		c = _getch();
		switch (c) {
		case Left: c = 'h'; break; 
		case Down: c = 'j'; break; 
		case Up: c = 'k'; break; 
		case Right: c = 'l'; break; 
		default: break;
		}
	}
#else 
	//c = getchar();
	putchar('\b');
#endif
	printf("[%c]\n", c);
	//system("sleep 0.2");

#ifdef _WIN32  
	// Do nothing  
#else  
	tcsetattr(0, TCSANOW, &stored_settings);
#endif
	return c;
}


int rnd(int x)
{
	int judge;
	int k, j;
	k = x / 4;
	j = (x % 4);
	judge = rand() % 10 + 1;
	if (judge < 8) num[k][j] = 2;
	if (judge >= 8) num[k][j] = 4;
	return 0;
}

void color_printf(int x)
{
	express_column=0;
	do
	{
		if (num[express_row][express_column] == 0) printf("      |", num[express_row][express_column]);
		else if (num[express_row][express_column] == 2) printf(" \033[m%4d\033[0;33m |", num[express_row][express_column]);
		else if (num[express_row][express_column] == 4) printf(" \033[0;32;32m%4d\033[0;33m |", num[express_row][express_column]);
		else if (num[express_row][express_column] == 8) printf(" \033[1;32m%4d\033[0;33m |", num[express_row][express_column]);
		else if (num[express_row][express_column] == 16) printf(" \033[0;32;34m%4d\033[0;33m |", num[express_row][express_column]);
		else if (num[express_row][express_column] == 32) printf(" \033[0;35m%4d\033[0;33m |", num[express_row][express_column]);
		else if (num[express_row][express_column] == 64) printf(" \033[1;35m%4d\033[0;33m |", num[express_row][express_column]);
		else if (num[express_row][express_column] == 128) printf(" \033[0;32;31m%4d\033[0;33m |", num[express_row][express_column]);
		else if (num[express_row][express_column] == 256) printf(" \033[1;31m%4d\033[0;33m |", num[express_row][express_column]);
		else if (num[express_row][express_column] == 512) printf(" \033[0;33m%4d\033[0;33m |", num[express_row][express_column]);
		else if (num[express_row][express_column] == 1024) printf(" \033[1;30m%4d\033[0;33m |", num[express_row][express_column]);
		else if (num[express_row][express_column] == 2048) printf(" \033[0;37m%4d\033[0;33m |", num[express_row][express_column]);
		else if (num[express_row][express_column] == 4096) printf(" \033[1;34m%4d\033[0;33m |", num[express_row][express_column]);
		
		express_column++;
	} while (express_column < x);
}

void draw_canvas()
{
#ifdef _WIN32
	system("cls");//clear sreen
#else
	system("clear");//clear screen
#endif
	express_row = 0;
	express_column = 0;
	printf("\033[m");
	printf("2048 CLI V7\n");
	printf("Built by Coder-BTS\n\n");
	printf("Use <HJKL> | E-Exit | R-Reset\n");
	printf("\033[0;33m");
	printf("-----------------------------\n");
	printf("|      |      |      |      |\n");
	printf("|");
	color_printf(4);
	express_row++;
	printf("\n|      |      |      |      |\n");
	printf("-----------------------------\n");
	printf("|      |      |      |      |\n");
	printf("|");
	color_printf(4);
	express_row++;
	printf("\n|      |      |      |      |\n");
	printf("-----------------------------\n");
	printf("|      |      |      |      |\n");
	printf("|");
	color_printf(4);
	express_row++;
	printf("\n|      |      |      |      |\n");
	printf("-----------------------------\n");
	printf("|      |      |      |      |\n");
	printf("|");
	color_printf(4);
	express_row++;
	printf("\n|      |      |      |      |\n");
	printf("-----------------------------\n");
	printf(">>> Score:   %d <<<\033[m\n", score);
	printf(">>> TEST_VER\n");
	if (check() == 1)
	{
		printf("\n\033[1;32mCan you make a forward move?\n");
	}
	printf("\033[m");
}

void bakup()
{
	int k;
	int j;
	for (k = 0;k < 4;k++) {
		for (j = 0;j < 4;j++) {
			num_v[k][j] = num[k][j];//bakup .old data
		}
	}
}

int compare()
{
	int k;
	for (k = 0;k < 16;k++)
	{
		if (num_v[k] != num[k]) return 1;
	}
	return 0;
}

int check()
{
	int k;
	for (k = 0;k < 16;k++)
	{
		if (num[k] == 0) return 0;
	}
	return 1;
}

int main()
{
	int k;
	int j;
	int new_block;
start:
	for (k = 0;k < 4;k++) {//init void
		for (j = 0;j < 4;j++) {
			num[k][j] = 0;
		}
	}
	srand(time(NULL));
	score = 0;
	rnd(11);//init
	rnd(14);
	rnd(15);
	for (k = 0;k < 4;k++) {
		for (j = 0;j < 4;j++) {
			num_v[k][j] = num[k][j];//bakup .old data
		}
	}
	while (1) {
	get_direct:
		//system("clear");//clear screen
		draw_canvas();
		//system("stty -icanon");

		direct = get1char();

		//printf("%c\n",direct);
		signal = 0;
		bakup();
		switch (direct) {
			case 'h': case 'H':
				goto to_left; break;
			case 'j': case 'J': 
				goto to_down; break;
			case 'k': case 'K':
				goto to_up; break;
			case 'l': case 'L':
				goto to_right; break;
			case 'r': case 'R':
				goto start; break;
			//case 'X': goto cheat_x; break;
			case 'e': case 'E':
				exit(0);
		default: break;
		}
	}
	/*
to_right:
	for (k = 0;k <= 12;k += 4)
	{
		for (j = k + 3;j >= k + 1;j--)
		{
			if (num[j] == 0)
			{
				num[j] = num[j - 1];
				num[j - 1] = 0;
			}
			if (num[j] != 0)
			{
				if (num[j] == num[j - 1])
				{
					num[j] = num[j] * 2;
					score = score + num[j];
					num[j - 1] = 0;
				}
			}
		}
	}
	if (compare() == 0) goto get_wait;
	bakup();
	signal = 1;
	goto to_right;
to_left:
	for (k = 0;k <= 12;k += 4)
	{
		for (j = k;j <= k + 2;j++)
		{
			if (num[j] == 0)
			{
				num[j] = num[j + 1];
				num[j + 1] = 0;
			}
			if (num[j] != 0)
			{
				if (num[j] == num[j + 1])
				{
					num[j] = num[j] * 2;
					score = score + num[j];
					num[j + 1] = 0;
				}
			}
		}
	}
	if (compare() == 0) goto get_wait;
	bakup();
	signal = 1;
	goto to_left;
to_up:
	for (k = 0; k <= 3;k++)
	{
		for (j = k;j <= 11;j += 4)
		{
			if (num[j] == 0)
			{
				num[j] = num[j + 4];
				num[j + 4] = 0;
			}
			if (num[j] != 0)
			{
				if (num[j] == num[j + 4])
				{
					num[j] = num[j] * 2;
					score = score + num[j];
					num[j + 4] = 0;
				}
			}
		}
	}
	if (compare() == 0) goto get_wait;
	bakup();
	signal = 1;
	goto to_up;
to_down:
	for (k = 12;k <= 15;k++)
	{
		for (j = k;j >= 4;j -= 4)
		{
			if (num[j] == 0)
			{
				num[j] = num[j - 4];
				num[j - 4] = 0;
			}
			if (num[j] != 0)
			{
				if (num[j] == num[j - 4])
				{
					num[j] = num[j] * 2;
					score = score + num[j];
					num[j - 4] = 0;
				}
			}
		}
	}
	if (compare() == 0) goto get_wait;
	bakup();
	signal = 1;
	goto to_down;
	*/
get_wait:
	draw_canvas();
	if (signal == 0) goto get_direct;
	if (check() == 1) goto get_direct;
	new_block = rand() % 16;
	if (num[new_block] != 0) goto get_wait;
#ifdef _WIN32
	Sleep(100);
#else
	system("sleep 0.1");
#endif
	rnd(new_block);
	goto get_direct;
/*
cheat_x:
	num[0] = 16;
	num[1] = 128;
	num[2] = 1024;
	num[3] = 4096;
	num[4] = 0;
	num[5] = 256;
	num[6] = 0;
	num[7] = 2048;
	num[8] = 0;
	num[9] = 0;
	num[10] = 256;
	num[11] = 128;
	num[12] = 0;
	num[13] = 0;
	num[14] = 16;
	num[15] = 256;
	score = 67108864;
	*/
	goto get_wait;
	//quit_g:
	//exit(1);
	return 0;
}