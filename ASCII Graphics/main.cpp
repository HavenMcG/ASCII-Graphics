
#include "ConhostController.h"
#include "Factory.h"

#include <iostream>
//#include <windows.h>

#include <string>

void print_screen_border();
void print_buffer_debug_grid();

int main() {
    ConhostController::maximize();
    ConhostController::set_resolution(284, 67);
    ConhostController::enable_virtual_terminal();

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
    std::cout << "\033[38;2;255;82;197m";
    std::cout << "test" << std::endl;

    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD written;
    WriteConsoleOutputCharacter(hOut, L"test2", 5, COORD{ 0,0 }, &written);
    std::cout << "xx\n";

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

