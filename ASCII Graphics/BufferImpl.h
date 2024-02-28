#pragma once
#include <Windows.h>
#include <string>
#include "ANSI.h"

namespace hcon {
	class BufferImpl {
	public:
		enum HandleType {
			std_output_handle,
			new_handle
		};
		BufferImpl();
		BufferImpl(HandleType ht);
		BufferImpl(const BufferImpl&) = delete;
		BufferImpl(BufferImpl&&) = default;
		~BufferImpl();

		void write(const std::string& s);
		void set_buffer_size(short width, short height);
		void set_bufferwindow_size(short width, short height);
		void set_font_size(short width, short height);
		void set_cursor_pos(short x, short y);

		void set_fcolor(Color c);
		void set_fcolor(int r, int g, int b) { set_fcolor(Color{ r,g,b }); }
		void set_bcolor(Color c);
		void set_bcolor(int r, int g, int b) { set_bcolor(Color{ r,g,b }); }
		void reset_colors();

		// Getters
		HANDLE handle() const { return m_handle; }
		COORD cursor_pos() const { return m_buffer_info.dwCursorPosition; }
		COORD buffer_size() const { return m_buffer_info.dwSize; }
		SMALL_RECT bufferwindow_corners() const { return m_buffer_info.srWindow; }
		COORD font_size() const { return m_font_info.dwFontSize; }
		CONSOLE_SCREEN_BUFFER_INFO buffer_info() const { return m_buffer_info; }
		CONSOLE_FONT_INFOEX font_info() const { return m_font_info; }


	private:
		HANDLE m_handle;
		CONSOLE_SCREEN_BUFFER_INFO m_buffer_info;
		CONSOLE_FONT_INFOEX m_font_info;
		HandleType m_htype;
		void update_buffer_info();
		void update_font_info();
	};
}