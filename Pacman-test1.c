#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define ROW 10
#define COLUMN 10

//2 -> pacman
//1 -> fruit
//0 -> block
//-1 -> empty

typedef struct{
	short x;
	short y;
}coord;

void move (coord*, short [COLUMN][ROW], int);
void printTable (short [COLUMN][ROW]);
void gotoxy (int, int);
int getChoose ();

int main () {
	coord pacman = {1, 1};
	
	short table [COLUMN][ROW] = {
									0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
							    	0, 2, 1, 1, 1, 1, 1, 0, 1, 0,
							    	0, 1, 0, 0, 0, 1, 0, 0, 1, 0,
							    	0, 1, 0, 1, 1, 1 ,1, 0, 1, 0,
							    	0, 1, 0, 1, 1, 1, 1, 0, 1, 0,
							    	0, 1, 0, 0, 1, 1, 1, 1, 1, 0,
							    	0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
							    	0, 1, 0, 1, 0, 1, 0, 1, 1, 0,
							    	0, 1, 1, 1, 1, 1, 1, 1, 1, 0,
							    	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
								};
	printTable (table);
	
	while (1) {
		int choose;
		
		gotoxy (pacman.x, pacman.y);
			printf ("%c", 'C');
			
		choose = getChoose ();
		
		gotoxy (pacman.x, pacman.y);
			printf (" ");
			
		if (choose)
			move (&pacman, table, choose);
			

		
	}
}
void printTable (short table[COLUMN][ROW]) {
	for (int i = 0; i < COLUMN; i++){
		for (int j = 0; j < ROW; j++) {
			char block = ' ';
			if (!table [i][j]) {
				int value = 8 * (j+1 < ROW ? !table [i][j+1] : 0) + 4 * (j > 0 ? !table [i][j-1] : 0) + 2 * (i > 0 ? !table [i-1][j] : 0) + (i+1 < COLUMN ? !table [i+1][j] : 0)  ;
				
				switch (value) {
					case 0 : block = 254; break;
					
					case 1 :
					case 2:
					case 3: block = 186; break; 
					
					case 4:
					case 8:
					case 12: block = 205; break;
					
					case 5: block = 187; break;
					case 6: block = 188; break;
					
					case 7: block = 185; break;
					case 9: block = 201; break;
					case 10: block = 200; break;
					
					case 11: block = 204; break;
					case 13: block = 203; break;
					case 14: block = 202; break;
					case 15: block = 206; break;
				}
			}//End of blocked blocks if
			else if (table [i][j] == 1)//fruits
				block = 176;
			
			printf ("%c", block);
		}
		printf ("\n");
	}
}
void move (coord* pacman, short table [COLUMN][ROW], int choose) {
	table[pacman->y][pacman->x] = -1;
	switch (choose) {
		case 1:
			if (pacman->y > 0 && table[pacman->y-1][pacman->x])
				pacman->y--;
			
			break;
				
		case 2:
			if (pacman->y + 1 < COLUMN && table[pacman->y+1][pacman->x])
				pacman->y++;
				
			break;
			
		case 3:
			if (pacman->x > 0 && table[pacman->y][pacman->x-1])
				pacman->x--;
				
			break;
			
		case 4:
			if (pacman->x + 1 < ROW && table[pacman->y][pacman->x+1])
				pacman->x++;
				
			break;
	}
	
	table[pacman->y][pacman->x] = 2;
}
void gotoxy(int x,int y){
  HANDLE hConsole;
  COORD cursorLoc;
  cursorLoc.X = x;
  cursorLoc.Y = y;
  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleCursorPosition(hConsole, cursorLoc);
}
int getChoose () {
	int choose = getch();
	
	switch(choose) {
		case 72: return 1;//printf("UP WAS PRESSED\n"); break;
		case 80: return 2;//printf("DOWN WAS PRESSED\n"); break;
		case 75: return 3;//printf("LEFT WAS PRESSED\n"); break;
		case 77: return 4;//printf("RIGHT WAS PRESSED\n"); break;
		
		default: return 0;
	}
}
