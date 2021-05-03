#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <Windows.h>

#define ROWS 170
#define COLS 631
#define DENSITY 8

int field[COLS][ROWS];

void StartLife()
{
    for (int x = 0; x < COLS; x++)
        for (int y = 0; y < ROWS; y++)
            field[x][y] = ( rand() % DENSITY ) == 0;
}



int CountNeighbours(int x, int y)
{
    int count = 0;
    for (int i = -1; i < 2; i++)
    {
        for (int j = -1; j < 2; j++)
        {
            int col = (x + i + COLS) % COLS;
            int row = (y + j + ROWS) % ROWS;
            int self = col == x && row == y;
            int hasLife = field[col][row];

            if (hasLife && !self)
                count++;
        }
    }
    return count;
}

void NextGeneration()
{
    int newField[COLS][ROWS];
    for (int x = 0; x < COLS; x++)
    {
        for (int y = 0; y < ROWS; y++)
        {
            int neighboursCount = CountNeighbours(x, y);
            int hasLife = field[x][y];
            if (!hasLife && neighboursCount == 3)
                newField[x][y] = 1;
            else if (hasLife && (neighboursCount < 2 || neighboursCount > 3))
                newField[x][y] = 0;
            else
                newField[x][y] = field[x][y];

        }
    }

    for (int x = 0; x < COLS; x++)
        for (int y = 0; y < ROWS; y++)
            field[x][y] = newField[x][y];
}


void main(void){
    // Console screen
    COORD position;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    HWND hWnd = GetForegroundWindow();
    CONSOLE_CURSOR_INFO info;
    ShowWindow(hWnd, SW_MAXIMIZE);
    info.dwSize = 100;
    info.bVisible = 0;
    SetConsoleCursorInfo(hConsole, &info);
    position.X = position.Y = 0;
    // /Console screen


    StartLife();
    char str[COLS];

    // Draw
    while(1){
        for (int y = 0; y < ROWS; y++) {
            for (int x = 0; x < COLS; x++) {
                if (field[x][y])
                    str[x] = '#';
                else
                    str[x] = ' ';
            }
            printf("%s\n", str);
        }
        SetConsoleCursorPosition(hConsole, position);
        NextGeneration();
    }

}
