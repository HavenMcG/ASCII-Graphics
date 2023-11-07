
#include "WinController.h"
#include "Factory.h"

#include <iostream>
#include <windows.h>

#include <string>

void print_screen_border();
void print_buffer_debug_grid();
int enable_virtual_terminal();

int main() {
    // get HWND to console window
    HWND console = GetConsoleWindow();
    // get handle to console window
    Factory fac;
    std::unique_ptr<WinController> winCon = fac.create_winController();

    // maximize
    winCon->maximize();

    //set_font_size(8,8);
    //set_up_buffer();
    winCon->set_resolution(284, 67);

    // retrieve buffer info
    /*CONSOLE_SCREEN_BUFFER_INFO scrBufferInfo;
    GetConsoleScreenBufferInfo(hOut, &scrBufferInfo);*/
    
    // print info
    //std::cout << std::endl;
    //std::cout << "(main) Buffer Size : " << scrBufferInfo.dwSize.X << " x " << scrBufferInfo.dwSize.Y << std::endl;

    //print_buffer_debug_grid();

    /*CHAR_INFO ci;
    ci.Char.UnicodeChar = 'H';
    ci.Attributes = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;

    CHAR_INFO screen[] = { ci };
    int x = 0;
    int y = 0;
    SMALL_RECT r{ x,y,screen_size().X-1-x,screen_size().Y-1-y };
    WriteConsoleOutput(
        hOut,
        screen,
        COORD{1,1},
        COORD{0,0},
        &r
    );*/


    enable_virtual_terminal();

    std::cout << "\033[1;31mred text\033[0m \033[1;32mgreen text\033[0m \033[38;2;255;82;197mpink text\033[0m" << std::endl;
    std::cout << "\033[38;2;255;100;0mTRUECOLOR\x1b[0m" << std::endl;
    

    std::string s = "\\/\\/\\/\\/\\/\\/\\/\\/";
    s += s + s + s + s + s + s + s;

    for (int colnum = 0; colnum < 77; colnum++) {
        int r = 255 - (colnum * 255 / 76);
        int g = (colnum * 510 / 76);
        int b = (colnum * 255 / 76);

        if (g > 255) g = 510 - g;

        // Set background color
        std::cout << "\033[48;2;" << r << ";" << g << ";" << b << "m";

        // Set foreground color
        std::cout << "\033[38;2;" << 255 - r << ";" << 255 - g << ";" << 255 - b << "m";

        // Print the character from the 's' string
        std::cout << s[colnum];

        // Reset the colors
        std::cout << "\033[0m";
    }

    std::cout << "\n";

    std::cin.get();
}

void print_screen_border() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    // retrieve buffer info
    CONSOLE_SCREEN_BUFFER_INFO scrBufferInfo;
    GetConsoleScreenBufferInfo(hOut, &scrBufferInfo);

    int screenHeight = scrBufferInfo.dwSize.Y - 2;
    int screenWidth = scrBufferInfo.dwSize.X;

    for (int row = 0; row < screenHeight; ++row) {
        for (int col = 0; col < screenWidth; ++col) {
            if (row == 0
                || row == screenHeight - 1
                || col == 0
                || col == screenWidth - 1
                ) {
                std::cout << 'X';
            }
            else std::cout << ' ';
            //std::cout << (row + 1) << ", " << (col + 1) << std::endl;
        }
    }
}

void print_buffer_debug_grid() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    // retrieve buffer info
    CONSOLE_SCREEN_BUFFER_INFO scrBufferInfo;
    GetConsoleScreenBufferInfo(hOut, &scrBufferInfo);

    int screenHeight = scrBufferInfo.dwSize.Y - 2;
    int screenWidth = scrBufferInfo.dwSize.X;

    for (int row = 0; row < screenHeight; ++row) {
        for (int col = 0; col < screenWidth; ++col) {
            if (row == 0
                || row == screenHeight - 1
                || col == 0
                || col == screenWidth - 1
                ) {
                char ch = '0' + ((row + 1) * (col + 1)) % 10;
                if (ch == '0') ch = (char)219;
                std::cout << ch;
            }
            else std::cout << ' ';
        }
    }
}

int enable_virtual_terminal() {
    // Set output mode to handle virtual terminal sequences
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE)
    {
        return false;
    }
    HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
    if (hIn == INVALID_HANDLE_VALUE)
    {
        return false;
    }

    DWORD dwOriginalOutMode = 0;
    DWORD dwOriginalInMode = 0;
    if (!GetConsoleMode(hOut, &dwOriginalOutMode))
    {
        return false;
    }
    if (!GetConsoleMode(hIn, &dwOriginalInMode))
    {
        return false;
    }

    DWORD dwRequestedOutModes = ENABLE_VIRTUAL_TERMINAL_PROCESSING | DISABLE_NEWLINE_AUTO_RETURN;
    DWORD dwRequestedInModes = ENABLE_VIRTUAL_TERMINAL_INPUT;

    DWORD dwOutMode = dwOriginalOutMode | dwRequestedOutModes;
    if (!SetConsoleMode(hOut, dwOutMode))
    {
        // we failed to set both modes, try to step down mode gracefully.
        dwRequestedOutModes = ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        dwOutMode = dwOriginalOutMode | dwRequestedOutModes;
        if (!SetConsoleMode(hOut, dwOutMode))
        {
            // Failed to set any VT mode, can't do anything here.
            return -1;
        }
    }

    DWORD dwInMode = dwOriginalInMode | dwRequestedInModes;
    if (!SetConsoleMode(hIn, dwInMode))
    {
        // Failed to set VT input mode, can't do anything here.
        return -1;
    }
}