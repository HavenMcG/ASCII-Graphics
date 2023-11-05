
#include "WinControl.h"
#include <iostream>
#include <windows.h>

void set_up_buffer() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    // new buffer size
    COORD newBufferSize;
    newBufferSize.X = GetLargestConsoleWindowSize(hOut).X;
    newBufferSize.Y = GetLargestConsoleWindowSize(hOut).Y;

    // shrink the window to prevent error
    SMALL_RECT rect = { 0,0,0,0 };
    if (!SetConsoleWindowInfo(hOut, TRUE, &rect)) {
        std::cout << "shrinking window size failed: " << GetLastError() << std::endl;
        std::cin.get(); // pause
        exit(0);
    }

    // set new buffer size
    if (!SetConsoleScreenBufferSize(hOut, newBufferSize)) {
        std::cout << "SetConsoleScreenBufferSize() failed: " << GetLastError() << std::endl;
        std::cin.get(); // pause
        exit(0);
    }

    // now restore the window again
    CONSOLE_SCREEN_BUFFER_INFO scrBufferInfo;
    GetConsoleScreenBufferInfo(hOut, &scrBufferInfo);
    SHORT maxWindowX = scrBufferInfo.dwMaximumWindowSize.X - 1;
    SHORT maxWindowY = scrBufferInfo.dwMaximumWindowSize.Y - 1;
    //std::cout << "Restore dimensions: " << maxWindowX << " x " << maxWindowY << std::endl; // why 67??
    rect = { 0,0,maxWindowX,maxWindowY };
    if (!SetConsoleWindowInfo(hOut, TRUE, &rect)) {
        std::cout << "restoring window size failed: " << GetLastError() << std::endl;
        std::cin.get(); // pause
        exit(0);
    }
}

void set_resolution(SHORT width, SHORT height) {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    HWND console = GetConsoleWindow();

    // get Win info
    RECT clientRect;
    GetClientRect(console, &clientRect);
    int clientWidth = clientRect.right - clientRect.left;
    int clientHeight = clientRect.bottom - clientRect.top;

    // set char size
    SHORT charWidth = clientWidth / width;
    SHORT charHeight = clientHeight / height;
    std::cout << "Desired char size: " << charWidth << " x " << charHeight << std::endl;
    set_font_size(charWidth, charHeight);

    // verify that it worked
    std::cout << "Actual font size: " << font_size().X << " x " << font_size().Y << std::endl;

    // shrink the window to prevent error
    SMALL_RECT rect = { 0,0,0,0 };

    if (!SetConsoleWindowInfo(hOut, TRUE, &rect)) {
        std::cout << "shrinking window size failed: " << GetLastError() << std::endl;
        std::cin.get(); // pause
        exit(0);
    }

    // set new buffer size
    COORD newBufferSize = { width, height };
    if (!SetConsoleScreenBufferSize(hOut, newBufferSize)) {
        std::cout << "SetConsoleScreenBufferSize() failed: " << GetLastError() << std::endl;
        std::cin.get(); // pause
        exit(0);
    }
    // retrieve buffer info
    CONSOLE_SCREEN_BUFFER_INFO scrBufferInfo;
    GetConsoleScreenBufferInfo(hOut, &scrBufferInfo);
    std::cout << "Desired buffer size: " << width << " x " << height << std::endl;
    std::cout << "Actual buffer size: " << scrBufferInfo.dwSize.X << " x " << scrBufferInfo.dwSize.Y << std::endl;

    // now restore the window again
    SHORT maxWindowX = scrBufferInfo.dwMaximumWindowSize.X - 1;
    SHORT maxWindowY = scrBufferInfo.dwMaximumWindowSize.Y - 1;
    //std::cout << "Restore dimensions: " << maxWindowX << " x " << maxWindowY << std::endl; // why 67??
    rect = { 0,0,maxWindowX,maxWindowY };
    if (!SetConsoleWindowInfo(hOut, TRUE, &rect)) {
        std::cout << "restoring window size failed: " << GetLastError() << std::endl;
        std::cin.get(); // pause
        exit(0);
    }

    // print extra debug info

    std::cout << "Window: " << clientWidth << " x " << clientHeight << std::endl;
    std::cout << "Char size * buffer size: " << charWidth * scrBufferInfo.dwSize.X << " x " << charHeight * scrBufferInfo.dwSize.Y << std::endl;

    // hide scroll bars
    ShowScrollBar(console, SB_BOTH, FALSE);
}

void set_font_size(SHORT newWidth, SHORT newHeight) {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    // ---------------------------
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = newWidth;        // Width of each character in the font
    cfi.dwFontSize.Y = newHeight;       // Height
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    wcscpy_s(cfi.FaceName, L"Consolas"); // Choose your font
    // ---------------------------

    SetCurrentConsoleFontEx(hOut, FALSE, &cfi);
}



COORD font_size() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_FONT_INFO currentFont;
    GetCurrentConsoleFont(hOut, FALSE, &currentFont);
    COORD currentFontSize = GetConsoleFontSize(hOut, currentFont.nFont);
    return currentFontSize;
}

void print_console_debug_info() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    // retrieve buffer info
    CONSOLE_SCREEN_BUFFER_INFO scrBufferInfo;
    GetConsoleScreenBufferInfo(hOut, &scrBufferInfo);

    // get Win info
    RECT r;
    GetWindowRect(GetConsoleWindow(), &r);
    int winWidth = r.right - r.left;
    int winHeight = r.bottom - r.top;

    // get font info
    CONSOLE_FONT_INFO currentFont;
    GetCurrentConsoleFont(hOut, FALSE, &currentFont);
    COORD currentFontSize = GetConsoleFontSize(hOut, currentFont.nFont);
    int currentFontWidth = currentFontSize.X;
    int currentFontHeight = currentFontSize.Y;

    std::cout << "Window: " << winWidth << " x " << winHeight << std::endl;
    std::cout << "Font: " << currentFontWidth << " x " << currentFontHeight << std::endl;
    std::cout << "Current buffer size: " << scrBufferInfo.dwSize.X << " x " << scrBufferInfo.dwSize.Y << std::endl;
    std::cout << "Largest buffer size: " << scrBufferInfo.dwMaximumWindowSize.X << " x " << scrBufferInfo.dwMaximumWindowSize.Y << std::endl;
}

COORD screen_size() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO scrBufferInfo;
    GetConsoleScreenBufferInfo(hOut, &scrBufferInfo);
    return scrBufferInfo.dwSize;
}