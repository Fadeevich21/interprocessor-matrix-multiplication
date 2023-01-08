#ifndef _MESSAGES_TO_CONSOLE_H
#define _MESSAGES_TO_CONSOLE_H 1

#include <stdio.h>
#include "../color_print/color_print.h"

#define COLOR_DBG COLOR_CYAN
#define COLOR_ERROR COLOR_RED
#define COLOR_WARNING COLOR_MAGENTA

#define PRINT_MESSAGE(who_name, color, format, args...) {\
    PRINT_COLOR(who_name "> ", color);\
    printf(format, ##args);\
}

#define PRINT_DBG(format, args...)\
    PRINT_MESSAGE("DBG", COLOR_DBG, format "\n", ##args)

#define PRINT_ERROR(format, args...)\
    PRINT_MESSAGE("ERROR", COLOR_ERROR, format "\n", ##args)

#define PRINT_WARNING(format, args...)\
    PRINT_MESSAGE("WARNING", COLOR_WARNING, format "\n", ##args)

#endif // _MESSAGES_TO_CONSOLE_H