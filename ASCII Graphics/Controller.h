#pragma once
#include "ANSI.h"
#include "Buffer.h"

namespace hcon {

	class ControllerImpl;

	class Controller {
	public:
		Controller();
		~Controller();
		Controller(const Controller&) = delete;

		Buffer* buffer(int i);
		void switch_target_buffer();
		void switch_display_buffer();
		void write(std::string s);
		void write(char ch);

		void set_fcolor(Color c);
		void set_fcolor(int r, int g, int b);
		void set_bcolor(Color c);
		void set_bcolor(int r, int g, int b);
		void reset_colors();

		Coord cursor_position();
		void move_cursor_to(Coord new_pos);
		void move_cursor_to(short x, short y);

		void maximize();
		Coord canvas_size();
		short canvas_width();
		short canvas_height();
		Coord font_size();
		void set_resolution(short width, short height);
		void set_buffer_size(short width, short height);
		void set_bufferwindow_size(short width, short height);
		void set_font_size(short width, short height);

	private:
		ControllerImpl* pimpl; // pimpl idiom
		//std::unique_ptr<ControllerImpl> pimpl;
	};
}