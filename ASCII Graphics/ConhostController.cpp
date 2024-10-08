
#include "ConhostController.h"
#include <iostream>
#include <windows.h>

// temp
#include <chrono>
#include <thread>
using namespace std::chrono_literals;

static HANDLE s_hOut;
static HANDLE s_hIn;
static HWND s_consoleWin;

std::string to_ansi_fcolor(Color c) {
    return "\033[38;2;" + std::to_string(c.r) + ";" + std::to_string(c.g) + ";" + std::to_string(c.b) + "m";
}

std::string to_ansi_fcolor(int r, int g, int b) {
    return to_ansi_fcolor(Color{ r,g,b });
}

std::string to_ansi_bcolor(Color c) {
    return "\033[48;2;" + std::to_string(c.r) + ";" + std::to_string(c.g) + ";" + std::to_string(c.b) + "m";
}

std::string to_ansi_bcolor(int r, int g, int b) {
    return to_ansi_bcolor(Color{ r,g,b });
}

Coord to_coord(COORD c) {
    return Coord{ c.X, c.Y };
}

COORD to_wincoord(Coord c) {
    return COORD{ c.x, c.y };
}

ConhostController::ConhostController() {
    s_hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    s_hIn = GetStdHandle(STD_INPUT_HANDLE);
    s_consoleWin = GetConsoleWindow();
    if (s_hOut == INVALID_HANDLE_VALUE) {
        // TODO: throw suitable exception
    }
    if (s_hIn == INVALID_HANDLE_VALUE) {
        // TODO: throw suitable exception
    }

    enable_virtual_terminal_impl(); // should this be here?
}

void ConhostController::maximize_impl() {
    ShowWindow(s_consoleWin, SW_MAXIMIZE);
}

Coord ConhostController::canvas_size_impl() {
    CONSOLE_SCREEN_BUFFER_INFO scrBufferInfo;
    GetConsoleScreenBufferInfo(s_hOut, &scrBufferInfo);
    return to_coord(scrBufferInfo.dwSize);
}

short ConhostController::canvas_width_impl()
{
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(s_hOut, &info);
    return info.dwSize.X;
}

short ConhostController::canvas_height_impl()
{
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(s_hOut, &info);
    return info.dwSize.Y;
}


void ConhostController::set_resolution_impl(short width, short height) {

    // get Win info
    RECT clientRect;
    GetClientRect(s_consoleWin, &clientRect);
    int clientWidth = clientRect.right - clientRect.left;
    int clientHeight = clientRect.bottom - clientRect.top;

    // set char size
    SHORT charWidth = clientWidth / width;
    if (charWidth < 2) charWidth = 2; // 2 is the minimum height of a character, therefore 2x2 is the smallest possible square character
    SHORT charHeight = clientHeight / height;
    if (charHeight < 2) charHeight = 2;
    if (charHeight > charWidth) charWidth = charHeight;
    else if (charWidth > charHeight) charHeight = charWidth;
    m_log << "Desired char size: " << charWidth << " x " << charHeight << std::endl;
    set_font_size(charWidth, charHeight);

    // verify that it worked
    m_log << "Actual font size: " << font_size().x << " x " << font_size().y << std::endl;

    // shrink the window to prevent error
    SMALL_RECT rect = { 0,0,0,0 };

    if (!SetConsoleWindowInfo(s_hOut, TRUE, &rect)) {
        m_log << "shrinking window size failed: " << GetLastError() << std::endl;
        std::cin.get(); // pause
        exit(0);
    }

    // set new buffer size
    set_buffer_size(width, height);

    // retrieve buffer info
    CONSOLE_SCREEN_BUFFER_INFO scrBufferInfo;
    GetConsoleScreenBufferInfo(s_hOut, &scrBufferInfo);

    // now restore the window again
    SHORT maxWindowX = scrBufferInfo.dwMaximumWindowSize.X - 1;
    SHORT maxWindowY = scrBufferInfo.dwMaximumWindowSize.Y - 1;
     //m_log << "Restore dimensions: " << maxWindowX << " x " << maxWindowY << std::endl; // why 67??
    set_bufferwindow_size(maxWindowX, maxWindowY);

    // print extra debug info

    m_log << "Window: " << clientWidth << " x " << clientHeight << std::endl;
    m_log << "Char size * buffer size: " << charWidth * scrBufferInfo.dwSize.X << " x " << charHeight * scrBufferInfo.dwSize.Y << std::endl;

    // hide scroll bars
    ShowScrollBar(s_consoleWin, SB_BOTH, FALSE);
}


void ConhostController::set_buffer_size_impl(short width, short height) {
    COORD newBufferSize = { width, height };
    if (!SetConsoleScreenBufferSize(s_hOut, newBufferSize)) {
        m_log << "SetConsoleScreenBufferSize() failed: " << GetLastError() << std::endl;
        exit(0);
    }

    // retrieve buffer info
    CONSOLE_SCREEN_BUFFER_INFO scrBufferInfo;
    GetConsoleScreenBufferInfo(s_hOut, &scrBufferInfo);
    m_log << "Desired buffer size: " << width << " x " << height << std::endl;
    m_log << "Actual buffer size: " << scrBufferInfo.dwSize.X << " x " << scrBufferInfo.dwSize.Y << std::endl;
}


void ConhostController::set_bufferwindow_size_impl(short width, short height) {
    SMALL_RECT rect = { 0,0,width,height };
    if (!SetConsoleWindowInfo(s_hOut, TRUE, &rect)) {
        m_log << "SetConsoleWindowInfo() failed: " << GetLastError() << std::endl;
        exit(0);
    }
}


void ConhostController::set_font_size_impl(short newWidth, short newHeight) {
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

    SetCurrentConsoleFontEx(s_hOut, FALSE, &cfi);
}


Coord ConhostController::font_size_impl() {
    CONSOLE_FONT_INFO currentFont;
    GetCurrentConsoleFont(s_hOut, FALSE, &currentFont);
    COORD currentFontSize = GetConsoleFontSize(s_hOut, currentFont.nFont);
    return to_coord(currentFontSize);
}


void ConhostController::log_debug_info_impl() {
    // retrieve buffer info
    CONSOLE_SCREEN_BUFFER_INFO scrBufferInfo;
    GetConsoleScreenBufferInfo(s_hOut, &scrBufferInfo);

    // get Win info
    RECT r;
    GetWindowRect(s_consoleWin, &r);
    int winWidth = r.right - r.left;
    int winHeight = r.bottom - r.top;

    // get font info
    CONSOLE_FONT_INFO currentFont;
    GetCurrentConsoleFont(s_hOut, FALSE, &currentFont);
    COORD currentFontSize = GetConsoleFontSize(s_hOut, currentFont.nFont);
    int currentFontWidth = currentFontSize.X;
    int currentFontHeight = currentFontSize.Y;

    m_log << "Window: " << winWidth << " x " << winHeight << std::endl;
    m_log << "Font: " << currentFontWidth << " x " << currentFontHeight << std::endl;
    m_log << "Current buffer size: " << scrBufferInfo.dwSize.X << " x " << scrBufferInfo.dwSize.Y << std::endl;
    m_log << "Largest buffer size: " << scrBufferInfo.dwMaximumWindowSize.X << " x " << scrBufferInfo.dwMaximumWindowSize.Y << std::endl;
}


int ConhostController::enable_virtual_terminal_impl() {
    // Set output mode to handle virtual terminal sequences
    

    DWORD dwOriginalOutMode = 0;
    DWORD dwOriginalInMode = 0;
    if (!GetConsoleMode(s_hOut, &dwOriginalOutMode))
    {
        return false;
    }
    if (!GetConsoleMode(s_hIn, &dwOriginalInMode))
    {
        return false;
    }

    DWORD dwRequestedOutModes = ENABLE_VIRTUAL_TERMINAL_PROCESSING | DISABLE_NEWLINE_AUTO_RETURN;
    DWORD dwRequestedInModes = ENABLE_VIRTUAL_TERMINAL_INPUT;

    DWORD dwOutMode = dwOriginalOutMode | dwRequestedOutModes;
    if (!SetConsoleMode(s_hOut, dwOutMode))
    {
        // we failed to set both modes, try to step down mode gracefully.
        dwRequestedOutModes = ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        dwOutMode = dwOriginalOutMode | dwRequestedOutModes;
        if (!SetConsoleMode(s_hOut, dwOutMode))
        {
            // Failed to set any VT mode, can't do anything here.
            return -1;
        }
    }

    DWORD dwInMode = dwOriginalInMode | dwRequestedInModes;
    if (!SetConsoleMode(s_hIn, dwInMode))
    {
        // Failed to set VT input mode, can't do anything here.
        return -1;
    }
}


void ConhostController::reset_colors()
{
    write("\033[0m");
}


//void ConhostController::display_impl(Frame f) {
//    move_cursor_to({ 0,0 });
//    write(create_frame_code(f));
//}

//void ConhostController::display_impl(Scene s) {
//    for (int i = 0; i < s.contents.size(); ++i) {
//        EntityPosition ep = s.contents[0];
//        move_cursor_to(ep.position);
//        write(create_frame_code(ep.entity));
//    }
//}


void ConhostController::write_impl(FrameCode fcode) {
    Coord start_pos = cursor_position();
    for (int i = 0; i < fcode.size(); ++i) {
        move_cursor_to(start_pos.x, start_pos.y + i);
        write(fcode[i]);
    }
}

void ConhostController::write_impl(std::string s) {
    DWORD charsWritten;
    WriteConsoleA(s_hOut, s.c_str(), s.size(), &charsWritten, NULL);
    //std::this_thread::sleep_for(10ms);
}

void ConhostController::write_impl(char ch) {
    DWORD charsWritten;
    WriteConsoleA(s_hOut, &ch, 1, &charsWritten, NULL);
    //std::this_thread::sleep_for(3ms);
}


void ConhostController::set_fcolor_impl(Color c) {
    write(to_ansi_fcolor(c));
}


void ConhostController::set_bcolor_impl(Color c) {
    write(to_ansi_bcolor(c));
}


Coord ConhostController::cursor_position_impl() {
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(s_hOut, &info);
    return to_coord(info.dwCursorPosition);
}

void ConhostController::move_cursor_to_impl(Coord new_pos) {
    SetConsoleCursorPosition(s_hOut,to_wincoord(new_pos));
}

