#pragma once
#include <string>
#include <memory>
#include "GBase.h"

namespace hcon {

	class BufferImpl;

	class Buffer {
	public:
		enum HandleType {
			std_output_handle,
			new_handle
		};
		Buffer();
		Buffer(HandleType ht);
		Buffer(const Buffer&) = delete;
		Buffer(Buffer&&) = default;
		~Buffer();

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
		void* handle() const;
		Coord cursor_pos() const;
		Coord buffer_size() const;
		Rect bufferwindow_corners() const;
		Coord font_size() const;
		Coord max_bufferwindow_size() const;

	private:
		BufferImpl* pimpl;
	};
}