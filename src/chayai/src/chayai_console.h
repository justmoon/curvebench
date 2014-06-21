#ifndef CHAYAI_CONSOLE_H
#define CHAYAI_CONSOLE_H

#include <stdio.h>

typedef enum CHayaiConsoleColor
{
    CHAYAI_TEXT_DEFAULT,
    CHAYAI_TEXT_BLACK, ///< Avoid using white unless it is absolutely necessary.
    CHAYAI_TEXT_BLUE,
    CHAYAI_TEXT_GREEN,
    CHAYAI_TEXT_CYAN,
    CHAYAI_TEXT_RED,
    CHAYAI_TEXT_PURPLE,
    CHAYAI_TEXT_YELLOW,
    CHAYAI_TEXT_WHITE ///< Avoid using white unless it is absolutely necessary.
} CHayaiConsoleColor;


#if defined(CHAYAI_NO_COLOR) 

inline static int chayai_console_change_color(FILE* stream, CHayaiConsoleColor color)
{
    return 0;
}

#else

# ifdef __cplusplus
extern "C" {
# endif

int chayai_console_change_color(FILE* stream, CHayaiConsoleColor color);

# ifdef __cplusplus
}
# endif

#endif


#endif // CHAYAI_CONSOLE_H
