#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define CORSUR_COLOR 15 // White
#define FRUIT_COLOR 12 // Red
#define BLOCK_COLOR 10 // Green
#define PACMAN_COLOR 14 // Yellow
#define MASAAGE_BOX_COLOR 14 //yellow
#define CHOOSE_SLEEP_TIME 300
#define MOVE_SLEEP_TIME 50
#define PRINT_SLEEP_TIME 25
#define MAX 101
#define MROW 100
#define MCOLUMN 100
#define INF (int)8e5 + 1

HANDLE hConsole;
int COLUMN;
int ROW;
int X = 50;
int Y = 0;

//1 -> fruit
//0 -> block
//-1 -> empty

typedef struct{
	short x;
	short y;
} coord;

void eraser();
void hideCursor();
void messageBox();
void Frame(int, int);
void gotoxy(int, int);
void move(coord*, short [MCOLUMN][MROW], int);
void printTable (short [MCOLUMN][MROW], int, int);
char flimentPrint(short [MCOLUMN][MROW], int, int, int);
int scanTable(coord*, short [MCOLUMN][MROW], char const*);
int getChoose(coord, short[MCOLUMN][MROW], short [MCOLUMN][MROW]);
void printWay(short [MCOLUMN][MROW], short [MCOLUMN][MROW], coord);
coord navigator(coord, short[MCOLUMN][MROW], short[MCOLUMN][MROW]);

int main () {
	int err;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	coord pacman;
	char fileAddress [MAX];
	short table [MCOLUMN][MROW] = { 0 };
	short way [MCOLUMN][MROW] = { 0 };

	do {
		printf ("ENTER SOURCE FILE ADDRESS : ");
		gets (fileAddress);

		system ("cls");

		err = scanTable (&pacman, table, fileAddress);
	}while(!err);

	hideCursor();
	if (ROW > 6 && COLUMN > 6){
        for (int i = 0; i < 3; i++) Frame(1, 1);
        printTable (table, PRINT_SLEEP_TIME, 1);
        Sleep (1000);
        printTable(table, 0, 0);
        Sleep(1000);
        messageBox("START");
        Sleep(1000);
	}
	else printf("Map is too small to show message boxes \n");
    printTable(table, 0, 0);
	while (1) {
		int choice;
		SetConsoleTextAttribute(hConsole, PACMAN_COLOR);
		gotoxy (pacman.x + X, pacman.y + Y);
        printf ("%c", 'C');

		choice = getChoose (pacman, table, way);

		Sleep (MOVE_SLEEP_TIME);

		gotoxy (pacman.x + X, pacman.y + Y);
			printf (" ");

		if (choice)
			move(&pacman, table, choice);

		else  break;
	}

	Sleep (1000);
	eraser ();
	for (int i = 0; i < 4; i++) Frame(0, 0);
	ROW = 0; COLUMN = 6;
	messageBox("FINISH \\[^-^]/ THANKS");
}
void Frame (int m, int mode) {
	gotoxy (X, Y);
	for (int i = 1; i <= COLUMN; i++) {

		gotoxy (X + ROW + 1, Y + i);
		printf ("%c", m ? 186 : ' ');

		gotoxy (X, Y + i);
		printf ("%c", m ? 186 : ' ');

		Sleep (PRINT_SLEEP_TIME);
	}

	gotoxy (X, COLUMN + Y + 1);
	printf ("%c", m ? 200 : ' ');
	gotoxy (X, Y);
	printf ("%c", m ? 201 : ' ');

	for (int i = 0; i < ROW; i++) {
		gotoxy (X + i + 1, Y);
		printf ("%c", m ? 205 : ' ');

		gotoxy (X + i + 1, Y + COLUMN + 1);
		printf ("%c", m ? 205 : ' ');

		Sleep (PRINT_SLEEP_TIME);
	}

	printf ("%c", m ? 188 : ' ');
	gotoxy (X + ROW + 1, Y);
	printf ("%c", m ? 187 : ' ');

	if (mode) {
        X++;
        Y++;
	}

	else {
        X--;
        Y--;
	}
}
void printWay (short way[MCOLUMN][MROW], short table[MCOLUMN][MROW], coord pacman) {
	int Way [MCOLUMN][MROW] = { 0 };
	for (int i = 0; i < COLUMN; i++)
		for (int j = 0;j < ROW; j++)
			Way [i][j] = way [i][j];

	SetConsoleTextAttribute(hConsole, 15);

	while (table [pacman.y][pacman.x] != 1) {
		Way [pacman.y][pacman.x] = 0;

		if (Way[pacman.y][pacman.x-1] && pacman.x > 0)
			pacman.x--;

		else if (Way[pacman.y-1][pacman.x] && pacman.y > 0)
			pacman.y--;

		else if (Way[pacman.y+1][pacman.x] && pacman.y+1 < COLUMN)
			pacman.y++;


		else if (Way[pacman.y][pacman.x+1] && pacman.x+1 < ROW)
			pacman.x++;

		else break;

		char block = ' ';

		block = flimentPrint(way, pacman.y, pacman.x, 1);

		gotoxy (pacman.x + X, pacman.y + Y);
		if (table[pacman.y][pacman.x] != 1)
			printf ("%c", block);

		Sleep (PRINT_SLEEP_TIME);
	}
}
void printTable (short table[MCOLUMN][MROW], int sleep, int mod) {
	for (int i = 0; i < COLUMN; i++)
		for (int j = 0; j < ROW; j++) {
			char block = ' ';
			int reap = 2;

            SetConsoleTextAttribute(hConsole, CORSUR_COLOR);
            gotoxy (j + X, i + Y);
            printf ("%c", 219);
            Sleep (sleep);

            if (!table [i][j]) {
                block = flimentPrint(table, i, j, 0);
                SetConsoleTextAttribute(hConsole, BLOCK_COLOR);
            }
            else if (table [i][j] == 1){
                block = 254;
                SetConsoleTextAttribute(hConsole, FRUIT_COLOR);
            }
            else if (table [i][j] == 2) {
                block = 'C';
                SetConsoleTextAttribute(hConsole, PACMAN_COLOR);
            }

            gotoxy (j + X, i + Y);
            printf ("%c", block);
                if(mod)
        	messageBox("PRINTING");
        }
}
coord navigator (coord pacman, short table[MCOLUMN][MROW], short way[MCOLUMN][MROW]) {
	int dist [MCOLUMN][MROW];
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

	dist [COLUMN][ROW] = INF;
	coord goal = {ROW, COLUMN};
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

		if (dist[now.y][now.x-1] < dist[now.y][now.x] && now.x > 0)
			now.x--;

		else if (dist[now.y][now.x+1] < dist[now.y][now.x] && now.x+1 < ROW)
			now.x++;

		else if (dist[now.y-1][now.x] < dist[now.y][now.x] && now.y > 0)
			now.y--;

		else if (dist[now.y+1][now.x] < dist[now.y][now.x] && now.y+1 < COLUMN)
			now.y++;

		else
			break;
	}

	return goal;
}
void move (coord* pacman, short table [MCOLUMN][MROW], int choice) {
	table[pacman->y][pacman->x] = -1;

	switch (choice) {
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
int getChoose (coord pacman, short table [MCOLUMN][MROW], short way[MCOLUMN][MROW]) {
	static coord goal = {-1 , -1};

	if ((goal.x == pacman.x && goal.y == pacman.y) || goal.x == -1){
		Sleep(CHOOSE_SLEEP_TIME);
		goal = navigator(pacman, table, way);
		printWay(way, table, pacman);
	}

	way [pacman.y][pacman.x] = 0;

	return 4*(pacman.x+1 < ROW ? way[pacman.y][pacman.x+1] : 0) + 3*(pacman.x > 0 ? way[pacman.y][pacman.x-1] : 0) + 2*(pacman.y+1 < COLUMN ? way[pacman.y+1][pacman.x] : 0) + (pacman.y > 0 ? way[pacman.y-1][pacman.x] : 0);
}
int scanTable (coord* pacman, short table[MCOLUMN][MROW], char const* fileAddress){
	FILE* source = fopen (fileAddress, "r");
	int i = 0, j = 0;

	if (source == NULL){
		SetConsoleTextAttribute(hConsole, 76);
		printf ("File Does NOT exist (Oskol) [#_#] Try again \n");
		SetConsoleTextAttribute(hConsole, CORSUR_COLOR);
		return 0;
	}

	while (!feof (source)){
		char bfr = getc (source);
		if (bfr == '*') table [i][j++] = 1;
		if (bfr == '#') table [i][j++] = 0;
		if (bfr == '1') table [i][j++] = -1;
		if (bfr == '0'){
			table [i][j++] = 2;
			pacman->x = j-1;
			pacman->y = i;
		}

		else if (bfr == '\n') {
			i++;
			if (j > ROW) ROW = j; j = 0;
		}
	}
	COLUMN = i+1;
	return 1;
}
void hideCursor(){//Hides cursor :)
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(hConsole, &info);
}
void eraser(){
	SetConsoleTextAttribute(hConsole, CORSUR_COLOR);//CHANGE COLOR

	for (int i = 0; i < COLUMN; i++)
		for (int j = i; j < ROW; j++){
			if (j < ROW && i < COLUMN){//Print cursor (HORIZENTAL)
				gotoxy (j + X, i + Y);
				printf ("%c", 219);
			}
			if (j < COLUMN && i < ROW) {//Print cursor (VERTICAL)
				gotoxy (i + X, j + Y);
				printf ("%c", 219);
			}

			Sleep (PRINT_SLEEP_TIME);

			if (j < ROW && i < COLUMN){//Erase map (HORIZENTAL)
				gotoxy (j + X, i + Y);
				printf (" ");
			}
			if (j < COLUMN && i < ROW) {//Erase map (VERTICAL)
				gotoxy (i + X, j + Y);
				printf (" ");
			}
		}
}
char flimentPrint (short table[MCOLUMN][MROW], int i, int j, int p){
    char block = 0;
    int value = 8 * (j+1 < ROW ? table [i][j+1] == p : 0) + 4 * (j > 0 ? table [i][j-1] == p : 0) + 2 * (i > 0 ? table [i-1][j] == p : 0) + (i+1 < COLUMN ? table [i+1][j] == p : 0);
				switch (value) {//ADDING COMMENT TO THIS PARTS IS TOO COMPLEX
					case 0 : block = 254; break;

					case 1:
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
    return block;
}
void messageBox (char* s){
	int len = strlen (s);
    SetConsoleTextAttribute(hConsole, MASAAGE_BOX_COLOR);

	gotoxy (X + ROW/2  - len/2 , Y + COLUMN/2 -1);
	printf("%c", 201);
	for (int i = 0; i < len; i++) printf("%c", 205);
	printf ("%c", 187);

	gotoxy (X + ROW/2 - len/2 , Y + COLUMN/2);
    printf ("%c%s%c", 186, s, 186);

    gotoxy (X + ROW/2 - len/2 , Y + COLUMN/2 +1);
    printf("%c", 200);
    for (int i = 0; i < len; i++) printf("%c", 205);
	printf ("%c", 188);
}
