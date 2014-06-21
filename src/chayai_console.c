
#include "chayai_console.h"


// Windows
#if defined(_WIN32) && !defined(CHAYAI_NO_COLOR)


#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>


inline static WORD chayai_get_console_attributes() {
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleInfo);
    return consoleInfo.wAttributes;
}

int chayai_console_change_color(FILE* stream, CHayaiConsoleColor color)
{
    static const WORD defaultConsoleAttributes =
        getConsoleAttributes();
    WORD newColor;
    switch(color) {
        case CHAYAI_TEXT_DEFAULT: 
            newColor = defaultConsoleAttributes; 
            break;
        case CHAYAI_TEXT_BLACK: 
            newColor = 0; 
            break;
        case CHAYAI_TEXT_BLUE: 
            newColor = FOREGROUND_BLUE; 
            break;
        case CHAYAI_TEXT_GREEN: 
            newColor = FOREGROUND_GREEN; 
            break;
        case CHAYAI_TEXT_CYAN: 
            newColor = FOREGROUND_GREEN | FOREGROUND_BLUE; 
            break;
        case CHAYAI_TEXT_RED: 
            newColor = FOREGROUND_RED; 
            break;
        case CHAYAI_TEXT_PURPLE: 
            newColor = FOREGROUND_RED | FOREGROUND_BLUE;
            break;
        case CHAYAI_TEXT_YELLOW: 
            newColor = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY; 
            break;
        case CHAYAI_TEXT_WHITE: 
            newColor = FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_INTENSITY; 
            break;
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), newColor);
    return 0;
}


// Linux or others
#elif !defined(CHAYAI_NO_COLOR) 


int chayai_console_change_color(FILE* stream, CHayaiConsoleColor color)
{
    const char* value;
    switch(color) {
        case CHAYAI_TEXT_DEFAULT: 
            value = "\033[m"; break;
        case CHAYAI_TEXT_BLACK: 
            value = "\033[0;30m"; break;
        case CHAYAI_TEXT_BLUE: 
            value = "\033[0;34m"; break;
        case CHAYAI_TEXT_GREEN: 
            value = "\033[0;32m"; break;
        case CHAYAI_TEXT_CYAN: 
            value = "\033[0;36m"; break;
        case CHAYAI_TEXT_RED: 
            value = "\033[0;31m"; break;
        case CHAYAI_TEXT_PURPLE: 
            value = "\033[0;35m"; break;
        case CHAYAI_TEXT_YELLOW: 
            value = "\033[0;33m"; break;
        case CHAYAI_TEXT_WHITE: 
            value = "\033[0;37m"; break;
        default:
            value = "";
    }
    return fputs(value, stream);
}


#endif
