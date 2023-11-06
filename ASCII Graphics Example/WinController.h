#pragma once
#include <Windows.h>

static class WinController {
public:
	virtual void set_resolution(short width, short height) = 0;
	virtual void maximize() = 0;
	virtual short canvas_width() = 0;
	virtual short canvas_height() = 0;
};



class ConhostController : public WinController {
public:
	void set_resolution(SHORT width, SHORT height) override;
	void maximize() override;
	short canvas_width() override;
	short canvas_height() override;

	ConhostController() { m_hOut = GetStdHandle(STD_OUTPUT_HANDLE); m_consoleWin = GetConsoleWindow(); }
	ConhostController(HANDLE hOut, HWND console) : m_hOut{ hOut }, m_consoleWin{ console } {}

	void set_up_buffer();
	void set_font_size(SHORT width, SHORT height);
	/* Sets the console buffer to the specified dimensions and sets font dimensions to attempt to fill the current window */
	
	void print_console_debug_info();
	COORD font_size();
	COORD screen_size();
private:
	HANDLE m_hOut;
	HWND m_consoleWin;
};