
#include "WinController.h"
#include <iostream>
#include <windows.h>

void ConhostController::maximize() {
    ShowWindow(m_consoleWin, SW_MAXIMIZE);
}

short ConhostController::canvas_width()
{
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(m_hOut, &info);
    return info.dwSize.X;
}

short ConhostController::canvas_height()
{
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(m_hOut, &info);
    return info.dwSize.Y;
}


void ConhostController::set_up_buffer() {

    // new buffer size
    COORD newBufferSize;
    newBufferSize.X = GetLargestConsoleWindowSize(m_hOut).X;
    newBufferSize.Y = GetLargestConsoleWindowSize(m_hOut).Y;

    // shrink the window to prevent error
    SMALL_RECT rect = { 0,0,0,0 };
    if (!SetConsoleWindowInfo(m_hOut, TRUE, &rect)) {
        std::cout << "shrinking window size failed: " << GetLastError() << std::endl;
        std::cin.get(); // pause
        exit(0);
    }

    // set new buffer size
    if (!SetConsoleScreenBufferSize(m_hOut, newBufferSize)) {
        std::cout << "SetConsoleScreenBufferSize() failed: " << GetLastError() << std::endl;
        std::cin.get(); // pause
        exit(0);
    }

    // now restore the window again
    CONSOLE_SCREEN_BUFFER_INFO scrBufferInfo;
    GetConsoleScreenBufferInfo(m_hOut, &scrBufferInfo);
    SHORT maxWindowX = scrBufferInfo.dwMaximumWindowSize.X - 1;
    SHORT maxWindowY = scrBufferInfo.dwMaximumWindowSize.Y - 1;
    //std::cout << "Restore dimensions: " << maxWindowX << " x " << maxWindowY << std::endl; // why 67??
    rect = { 0,0,maxWindowX,maxWindowY };
    if (!SetConsoleWindowInfo(m_hOut, TRUE, &rect)) {
        std::cout << "restoring window size failed: " << GetLastError() << std::endl;
        std::cin.get(); // pause
        exit(0);
    }
}

void ConhostController::set_resolution(SHORT width, SHORT height) {

    // get Win info
    RECT clientRect;
    GetClientRect(m_consoleWin, &clientRect);
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

    if (!SetConsoleWindowInfo(m_hOut, TRUE, &rect)) {
        std::cout << "shrinking window size failed: " << GetLastError() << std::endl;
        std::cin.get(); // pause
        exit(0);
    }

    // set new buffer size
    COORD newBufferSize = { width, height };
    if (!SetConsoleScreenBufferSize(m_hOut, newBufferSize)) {
        std::cout << "SetConsoleScreenBufferSize() failed: " << GetLastError() << std::endl;
        std::cin.get(); // pause
        exit(0);
    }
    // retrieve buffer info
    CONSOLE_SCREEN_BUFFER_INFO scrBufferInfo;
    GetConsoleScreenBufferInfo(m_hOut, &scrBufferInfo);
    std::cout << "Desired buffer size: " << width << " x " << height << std::endl;
    std::cout << "Actual buffer size: " << scrBufferInfo.dwSize.X << " x " << scrBufferInfo.dwSize.Y << std::endl;

    // now restore the window again
    SHORT maxWindowX = scrBufferInfo.dwMaximumWindowSize.X - 1;
    SHORT maxWindowY = scrBufferInfo.dwMaximumWindowSize.Y - 1;
    //std::cout << "Restore dimensions: " << maxWindowX << " x " << maxWindowY << std::endl; // why 67??
    rect = { 0,0,maxWindowX,maxWindowY };
    if (!SetConsoleWindowInfo(m_hOut, TRUE, &rect)) {
        std::cout << "restoring window size failed: " << GetLastError() << std::endl;
        std::cin.get(); // pause
        exit(0);
    }

    // print extra debug info

    std::cout << "Window: " << clientWidth << " x " << clientHeight << std::endl;
    std::cout << "Char size * buffer size: " << charWidth * scrBufferInfo.dwSize.X << " x " << charHeight * scrBufferInfo.dwSize.Y << std::endl;

    // hide scroll bars
    ShowScrollBar(m_consoleWin, SB_BOTH, FALSE);
}

void ConhostController::set_font_size(SHORT newWidth, SHORT newHeight) {

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

    SetCurrentConsoleFontEx(m_hOut, FALSE, &cfi);
}



COORD ConhostController::font_size() {
    CONSOLE_FONT_INFO currentFont;
    GetCurrentConsoleFont(m_hOut, FALSE, &currentFont);
    COORD currentFontSize = GetConsoleFontSize(m_hOut, currentFont.nFont);
    return currentFontSize;
}

void ConhostController::print_debug_info() {

    // retrieve buffer info
    CONSOLE_SCREEN_BUFFER_INFO scrBufferInfo;
    GetConsoleScreenBufferInfo(m_hOut, &scrBufferInfo);

    // get Win info
    RECT r;
    GetWindowRect(m_consoleWin, &r);
    int winWidth = r.right - r.left;
    int winHeight = r.bottom - r.top;

    // get font info
    CONSOLE_FONT_INFO currentFont;
    GetCurrentConsoleFont(m_hOut, FALSE, &currentFont);
    COORD currentFontSize = GetConsoleFontSize(m_hOut, currentFont.nFont);
    int currentFontWidth = currentFontSize.X;
    int currentFontHeight = currentFontSize.Y;

    std::cout << "Window: " << winWidth << " x " << winHeight << std::endl;
    std::cout << "Font: " << currentFontWidth << " x " << currentFontHeight << std::endl;
    std::cout << "Current buffer size: " << scrBufferInfo.dwSize.X << " x " << scrBufferInfo.dwSize.Y << std::endl;
    std::cout << "Largest buffer size: " << scrBufferInfo.dwMaximumWindowSize.X << " x " << scrBufferInfo.dwMaximumWindowSize.Y << std::endl;
}

COORD ConhostController::screen_size() {
    CONSOLE_SCREEN_BUFFER_INFO scrBufferInfo;
    GetConsoleScreenBufferInfo(m_hOut, &scrBufferInfo);
    return scrBufferInfo.dwSize;
}