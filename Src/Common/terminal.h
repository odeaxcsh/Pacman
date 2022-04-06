#ifndef _TERMINAL_H_
#define _TERMINAL_H_

#include "platform.h"
#include "defines.h"

#include <windows.h>
#include <stdio.h>

HANDLE hConsole;

void InitTerminal()
{
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
}

void ChangeColor(WORD color)
{
    SetConsoleTextAttribute(hConsole, color);
}

void HideCursor()
{
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = 0;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void ShowCursorIcon()
{
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = 1;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void GotoXY(int x, int y)
{
    COORD coord = { x, y };
    SetConsoleCursorPosition(hConsole, coord);
}

coord GetXY()
{
    coord coord;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    coord.x = csbi.dwCursorPosition.X;
    coord.y = csbi.dwCursorPosition.Y;
    return coord;
}

void Pause(int ms)
{
    if(ms > 0) {
        Sleep(ms);
    } else if(ms < 0) {
        scanf("%*c");
    }
}

void ClearScreen()
{
    system("cls");    
}

#endif