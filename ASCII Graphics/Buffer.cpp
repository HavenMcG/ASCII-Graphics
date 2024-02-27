#include "Buffer.h"
#include <exception>

namespace hcon {

	Buffer::Buffer() {
		m_handle = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_WRITE | FILE_SHARE_READ, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
		if (m_handle == INVALID_HANDLE_VALUE) {
			throw std::exception{ "CreateConsoleScreenBuffer() failed: " + GetLastError() };
		}
		update_buffer_info();
		update_font_info();
	}

	Buffer Buffer::create_from_std() {
		HANDLE h_stdout = GetStdHandle(STD_OUTPUT_HANDLE);
		if (h_stdout == INVALID_HANDLE_VALUE) {
			throw std::exception{ "GetStdHandle() failed: " + GetLastError() };
		}
		return Buffer(h_stdout);
	}

	Buffer::Buffer(HANDLE h) {
		m_handle = h;
		update_buffer_info();
		update_font_info();
	}

	void Buffer::write(const std::string& s) {
		DWORD chars_written = 0;
		if (!WriteConsoleA(m_handle, s.c_str(), s.size(), &chars_written, NULL)) {
			throw std::exception{ "WriteConsoleA() failed: " + GetLastError() };
		}
	}

	void Buffer::set_buffer_size(short width, short height) {
		COORD new_size = { width, height };
		if (!SetConsoleScreenBufferSize(m_handle, new_size)) {
			throw std::exception{ "SetConsoleScreenBufferSize() failed: " + GetLastError() };
		}
	}

	void Buffer::set_bufferwindow_size(short width, short height) {
		SMALL_RECT new_corners = { 0, 0, width, height };
		if (!SetConsoleWindowInfo(m_handle, TRUE, &new_corners)) {
			throw std::exception{ "SetConsoleWindowInfo() failed: " + GetLastError() };
		}
	}

	void Buffer::set_font_size(short width, short height) {
		CONSOLE_FONT_INFOEX new_font = m_font_info;
		new_font.dwFontSize = COORD{ width, height };
		if (!SetCurrentConsoleFontEx(m_handle, FALSE, &new_font)) {
			throw std::exception{ "SetCurrentConsoleFontEx() failed: " + GetLastError() };
		}
	}

	void Buffer::set_cursor_pos(short x, short y) {
		if (!SetConsoleCursorPosition(m_handle, COORD{ x,y })) {
			throw std::exception{ "SetConsoleCursorPosition() failed: " + GetLastError() };
		}
	}

	void Buffer::set_fcolor(Color c) {
		write(to_ansi_fcolor(c));
	}

	void Buffer::set_bcolor(Color c) {
		write(to_ansi_bcolor(c));
	}

	void Buffer::reset_colors() {
		write("\033[0m");
	}

	void Buffer::update_buffer_info() {
		if (!GetConsoleScreenBufferInfo(m_handle, &m_buffer_info)) {
			throw std::exception{ "GetConsoleScreenBufferInfo() failed: " + GetLastError() };
		}
	}

	void Buffer::update_font_info() {
		if (!GetCurrentConsoleFontEx(m_handle, FALSE, &m_font_info)) {
			throw std::exception{ "GetCurrentConsoleFontEx() failed: " + GetLastError() };
		}
	}
}