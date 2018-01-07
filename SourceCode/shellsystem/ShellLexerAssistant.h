#ifndef SHELL_LEXER_ASSISTANT_H_
#define SHELL_LEXER_ASSISTANT_H_

#ifdef WIN32
#include <windows.h>
HANDLE cmdColorHandle;
#endif

/*
 *  改变控制台(windows)/终端(linux)字体颜色
 */
void setCmdColor(int c) {
    if (c == 0) {
        //默认颜色
#ifdef WIN32
        SetConsoleTextAttribute(cmdColorHandle, FOREGROUND_INTENSITY);
#else
        printf("\033[0m");
#endif // WIN32
    } else if (c == 1) {
        //黄色
#ifdef WIN32
        SetConsoleTextAttribute(cmdColorHandle, FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN);
#else
        printf("\033[33m");
#endif // WIN321
    }
}

#endif // SHELL_LEXER_ASSISTANT_H_
