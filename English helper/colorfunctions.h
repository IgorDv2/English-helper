#ifndef COLORFUNCTIONS
#define COLORFUNCTIONS

#include <iostream>
#include <Windows.h>
enum class ColorName {
        BLACK = 0,
        BLUE,
        GREEN,
        CYAN,
        RED,
        MAGENTA,
        BROWN,
        LIGHTGRAY,
        DARKGRAY,
        LIGHTBLUE,
        LIGHTGREEN,
        LIGHTCYAN,
        LIGHTRED,
        LIGHTMAGENTA,
        YELLOW,
        WHITE
};
void setColor(int bg, int fg) {
     HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
     SetConsoleTextAttribute(hConsole, 16 * bg + fg);
}
void setColor(ColorName bg, ColorName  fg) {
     HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
     SetConsoleTextAttribute(hConsole, 16 * int(bg) + int(fg));

}
void setDefaultColor() {
     setColor(0, 7);
}

 void fillColorLine(int bg, int fg) {
     HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
     WORD  wAttributes = 16 * bg + fg;
     CONSOLE_SCREEN_BUFFER_INFO csbiScreenInfo;
     GetConsoleScreenBufferInfo(hConsole, &csbiScreenInfo);
     COORD coordStart = csbiScreenInfo.dwCursorPosition;
     DWORD dwScrSize = csbiScreenInfo.dwMaximumWindowSize.X-coordStart.X;
     DWORD dwNumWritten = 0;
     FillConsoleOutputAttribute(hConsole, wAttributes, dwScrSize, coordStart, &dwNumWritten);


}
 void setLineColor(int bg, int fg) {
     fillColorLine(bg, fg);
     setColor(bg, fg);
 }
 void setLineColor(ColorName bg, ColorName fg) {
     fillColorLine(int(bg), int(fg));
     setColor(int(bg), int(fg));
 }
 
 void printColorText(const  char *text, int bg, int fg) {
     setColor(int(bg), int(fg));
     std::cout << text;
     setDefaultColor();
 }
 void printColorLine(const char *text, int bg, int fg) {
     fillColorLine(int(bg), int(fg));
     setColor(int(bg), int(fg));
     std::cout << text;
     setDefaultColor();
 }

 void printColorText(const char* text, ColorName bg, ColorName fg)
 {
     printColorText(text, int(bg), int(fg));
 }

 void printColorLine(const char* text, ColorName bg, ColorName fg) {
     printColorLine(text, int(bg), int(fg));
 }

#endif // !COLORFUNCTIONS

