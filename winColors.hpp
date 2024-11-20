#include <iostream>
#include <windows.h>
#include <string>
#pragma once

void setTerminalColor(unsigned short int color){
    unsigned short systemColor;
    HANDLE handleTerminal = GetStdHandle(STD_OUTPUT_HANDLE);
    switch (color)
    {
    case 0:
        systemColor = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
        break;
    case 1:
        systemColor = FOREGROUND_RED;
        break;
    case 2:
        systemColor = FOREGROUND_GREEN;
        break;  
    case 3:
        systemColor = FOREGROUND_BLUE;
        break;  
    default:
        break;
    }
    SetConsoleTextAttribute(handleTerminal, systemColor);
}