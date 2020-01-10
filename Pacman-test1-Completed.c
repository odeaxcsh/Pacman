#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define ROW 10
#define COLUMN 10
#define INF (int)7e2 + 1

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
int getChoose (coord, short[COLUMN][ROW]);
coord dijkstra (coord, short[COLUMN][ROW], short[COLUMN][ROW]);

int main () {
	coord pacman = {8, 8};

		short table [COLUMN][ROW] = {
									0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
							    	0, 0, 1, 1, 1, 0, 1, 0, 1, 0,
							    	0, 0, 0, 0, 0, 0, 1, 0, 1, 0,
							    	0, -1, 0, 1, 0, 1 ,1, 0, 1, 0,
							    	0, -1, 0, -1, 1, 1, 1, 0, 1, 0,
							    	0, -1, 0, 0, 1, 0, 1, 1, 1, 0,
							    	0, 1, 0, 0, 1, 0, -1, 0, 1, 0,
							    	0, -1, 0, 0, 1, 0, -1, 0, 1, 0,
							    	0, -1, 1, 1, 1, -1, -1, 0, 2, 0,
	system("color 20");				    	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,						};	
	printTable (table);
	
	while (1) {
		int choose;
		
		gotoxy (pacman.x, pacman.y);
			printf ("%c", 'C');
		gotoxy (COLUMN, ROW);
		
		choose = getChoose (pacman, table);
		
		Sleep (200);
		
		gotoxy (pacman.x, pacman.y);
			printf (" ");
		
		if (choose) 
			move (&pacman, table, choose);
		
		else break;
	}
	
	gotoxy (0, 11);
	printf ("THE END");
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
coord navigator (coord pacman, short table[COLUMN][ROW], short way[COLUMN][ROW]) {
	int dist [COLUMN][ROW];
	for (int i = 0; i < COLUMN; i++)
		for (int j = 0; j < ROW; j++) {
			way [i][j] = 0;
			dist [i][j] = INF;
		}
		
	dist [pacman.y][pacman.x] = 0;
		
	int flag = 1;
	while (flag){
		flag = 0;
		for (int i = 0; i < COLUMN; i++)
			for (int j = 0; j < ROW; j++){
				int tmp = dist [i][j];
				if (table[i][j] && (j != pacman.x || i != pacman.y))
					dist [i][j] = min (min ((i > 0 ? dist [i-1][j] : INF),(i+1 < COLUMN ? dist[i+1][j] : INF)), min ((j+1 < ROW ? dist[i][j+1] : INF), (j > 0 ? dist[i][j-1] : INF))) + 1;
					
				if (dist[i][j] != tmp)
					flag = 1;
		}
	}
	
		
	coord goal = { 0 };
	for (int i = 0; i < COLUMN; i++)
		for (int j = 0; j < ROW; j++)
			if (table[i][j] == 1)
				if (dist[i][j] < dist[goal.y][goal.x]){
					goal.x = j;
					goal.y = i;
				}
	
	coord now = goal;
	
	while (now.x != pacman.x || now.y != pacman.y) {
		way [now.y][now.x] = 1;	

		if (dist[now.y][now.x-1] < dist[now.y][now.x])
			now.x--;
			
		else if (dist[now.y][now.x+1] < dist[now.y][now.x])
			now.x++;
			
		else if (dist[now.y-1][now.x] < dist[now.y][now.x])
			now.y--;
			
		else if (dist[now.y+1][now.x] < dist[now.y][now.x])
			now.y++;
			
		else 
			break;
	}
	
	return goal;
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
int getChoose (coord pacman, short table [COLUMN][ROW]) {
	static coord goal = {-1 , -1};
	static int time = 1;
	static short way [COLUMN][ROW] = { 0 };
	
	if ((goal.x == pacman.x && goal.y == pacman.y) || goal.x == -1)
		goal = navigator (pacman, table, way);
				
	way [pacman.y][pacman.x] = 0;
	return 4*(way[pacman.y][pacman.x+1]) + 3*(way[pacman.y][pacman.x-1]) + 2*(way[pacman.y+1][pacman.x]) + way[pacman.y-1][pacman.x];
}
