#pragma once
#include <Windows.h>
#include "Frame.h"

class ConhostController {
public:
	static void maximize() { instance().maximize_impl(); }
	static short canvas_width() { return instance().canvas_width_impl(); }
	static short canvas_height() { return instance().canvas_width_impl(); }
	static void set_up_buffer() { instance().set_up_buffer_impl(); }
	static void set_font_size(short width, short height) { instance().set_font_size_impl(width, height); }
	static void set_resolution(short width, short height) { instance().set_resolution_impl(width, height); }
	static void print_debug_info() { instance().print_debug_info_impl(); }
	static COORD font_size() { return instance().font_size_impl(); }
	static COORD screen_size() { return instance().screen_size_impl(); }
	static int enable_virtual_terminal() { return instance().enable_virtual_terminal_impl(); }

	ConhostController(const ConhostController&) = delete;

private:
	static ConhostController& instance() {
		static ConhostController instance;
		return instance;
	}

	void set_resolution_impl(SHORT width, SHORT height);
	void maximize_impl();
	short canvas_width_impl();
	short canvas_height_impl();

	void set_up_buffer_impl();
	void set_font_size_impl(SHORT width, SHORT height);

	void print_debug_info_impl();
	COORD font_size_impl();
	COORD screen_size_impl();
	int enable_virtual_terminal_impl();

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