#pragma once
#include <Windows.h>

class ConhostController {
public:
	static void maximize() { instance().impl_maximize(); }
	static short canvas_width() { return instance().impl_canvas_width(); }
	static short canvas_height() { return instance().impl_canvas_width(); }
	static void set_up_buffer() { instance().impl_set_up_buffer(); }
	static void set_font_size(short width, short height) { instance().impl_set_font_size(width, height); }
	static void set_resolution(short width, short height) { instance().impl_set_resolution(width, height); }
	static void print_debug_info() { instance().impl_print_debug_info(); }
	static COORD font_size() { return instance().impl_font_size(); }
	static COORD screen_size() { return instance().impl_screen_size(); }
	static int enable_virtual_terminal() { return instance().impl_enable_virtual_terminal(); }

	ConhostController(const ConhostController&) = delete;

private:
	static ConhostController& instance() {
		static ConhostController instance;
		return instance;
	}

	void impl_set_resolution(SHORT width, SHORT height);
	void impl_maximize();
	short impl_canvas_width();
	short impl_canvas_height();

	void impl_set_up_buffer();
	void impl_set_font_size(SHORT width, SHORT height);

	void impl_print_debug_info();
	COORD impl_font_size();
	COORD impl_screen_size();
	int impl_enable_virtual_terminal();

	ConhostController() {
		m_hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		m_hIn = GetStdHandle(STD_INPUT_HANDLE);
		m_consoleWin = GetConsoleWindow();
		if (m_hOut == INVALID_HANDLE_VALUE) {
			// TODO: throw suitable exception
		}
		if (m_hIn == INVALID_HANDLE_VALUE) {
			// TODO: throw suitable exception
		}
	}
	HANDLE m_hOut;
	HANDLE m_hIn;
	HWND m_consoleWin;
};