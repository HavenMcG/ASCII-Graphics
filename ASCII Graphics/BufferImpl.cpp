#include "BufferImpl.h"
#include <exception>

namespace hcon {

	BufferImpl::BufferImpl() : BufferImpl::BufferImpl(new_handle) {}

	BufferImpl::BufferImpl(HandleType ht) {
		switch (ht) {
			case std_output_handle: {
				m_handle = GetStdHandle(STD_OUTPUT_HANDLE);
				if (m_handle == INVALID_HANDLE_VALUE) {
					throw std::exception{ "GetStdHandle() failed: " + GetLastError() };
				}
				m_font_info.cbSize = sizeof(CONSOLE_FONT_INFOEX); // required as per msdn documentation
				update_buffer_info();
				update_font_info();
				m_htype = ht;
				break;
			}
			default: {
				m_handle = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_WRITE | FILE_SHARE_READ, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
				if (m_handle == INVALID_HANDLE_VALUE) {
					throw std::exception{ "CreateConsoleScreenBufferImpl() failed: " + GetLastError() };
				}
				m_font_info.cbSize = sizeof(CONSOLE_FONT_INFOEX); // required as per msdn documentation
				update_buffer_info();
				update_font_info();
				m_htype = new_handle;
				break;
			}
		}
	}

	BufferImpl::~BufferImpl() {
		if (m_htype != std_output_handle) {
			if (!CloseHandle(m_handle)) {
				throw std::exception{ "CloseHandle() failed: " + GetLastError() };
			}
		}
	}

	void BufferImpl::write(const std::string& s) {
		DWORD chars_written = 0;
		if (!WriteConsoleA(m_handle, s.c_str(), s.size(), &chars_written, NULL)) {
			throw std::exception{ "WriteConsoleA() failed: " + GetLastError() };
		}
	}

	void BufferImpl::set_buffer_size(short width, short height) {
		COORD new_size = { width, height };
		if (!SetConsoleScreenBufferSize(m_handle, new_size)) {
			throw std::exception{ "SetConsoleScreenBufferImplSize() failed: " + GetLastError() };
		}
		update_buffer_info();
	}

	void BufferImpl::set_bufferwindow_size(short width, short height) {
		SMALL_RECT new_corners = { 0, 0, width, height };
		if (!SetConsoleWindowInfo(m_handle, TRUE, &new_corners)) {
			throw std::exception{ "SetConsoleWindowInfo() failed: " + GetLastError() };
		}
		update_buffer_info();
	}

	void BufferImpl::set_font_size(short width, short height) {
		// ---------------------------
		CONSOLE_FONT_INFOEX cfi;
		cfi.cbSize = sizeof(cfi);
		cfi.nFont = 0;
		cfi.dwFontSize.X = width;        // Width of each character in the font
		cfi.dwFontSize.Y = height;       // Height
		cfi.FontFamily = FF_DONTCARE;
		cfi.FontWeight = FW_NORMAL;
		wcscpy_s(cfi.FaceName, L"Consolas"); // Choose your font
		// ---------------------------
		if (!SetCurrentConsoleFontEx(m_handle, FALSE, &cfi)) {
			throw std::exception{ "SetCurrentConsoleFontEx() failed: " + GetLastError() };
		}
		update_font_info();
	}

	void BufferImpl::set_cursor_pos(short x, short y) {
		if (!SetConsoleCursorPosition(m_handle, COORD{ x,y })) {
			throw std::exception{ "SetConsoleCursorPosition() failed: " + GetLastError() };
		}
		update_buffer_info();
	}

	void BufferImpl::set_fcolor(Color c) {
		write(to_ansi_fcolor(c));
	}

	void BufferImpl::set_bcolor(Color c) {
		write(to_ansi_bcolor(c));
	}

	void BufferImpl::reset_colors() {
		write("\033[0m");
	}

	void BufferImpl::copy(HANDLE h_source, SMALL_RECT source_rect, SMALL_RECT destination_rect) {
		int block_width = source_rect.Right - source_rect.Left+1;
		int block_height = source_rect.Bottom - source_rect.Top+1;
		CHAR_INFO* chiBuffer = new CHAR_INFO[block_width * block_height];
		COORD block_size{ block_width-1,block_height-1 };
		COORD chiBuffer_top_left{ 0,0 };
		bool read_success = ReadConsoleOutputA(
			h_source,
			chiBuffer,
			block_size,
			chiBuffer_top_left,
			&source_rect
		);
		if (!read_success) {
			throw std::exception{ "ReadConsoleOutputA() failed: " + GetLastError() };
		}

		bool write_success = WriteConsoleOutputA(
			m_handle,
			chiBuffer,
			block_size,
			chiBuffer_top_left,
			&destination_rect
		);
		if (!write_success) {
			throw std::exception{ "WriteConsoleOutputA() failed: " + GetLastError() };
		}
	}

	void BufferImpl::update_buffer_info() {
		if (!GetConsoleScreenBufferInfo(m_handle, &m_buffer_info)) {
			throw std::exception{ "GetConsoleScreenBufferImplInfo() failed: " + GetLastError() };
		}
	}

	void BufferImpl::update_font_info() {
		if (!GetCurrentConsoleFontEx(m_handle, FALSE, &m_font_info)) {
			throw std::exception{ "GetCurrentConsoleFontEx() failed: " + GetLastError() };
		}
	}
}