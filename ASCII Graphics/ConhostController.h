#pragma once
#include "Frame.h"
#include <string>
#include <sstream>

struct Coord {
	short x;
	short y;
};

class ConhostController {
public:
	static void display(Frame f) { instance().display_impl(f); }

	static void set_fcolor(Color c) { set_fcolor_impl(c); }
	static void set_fcolor(int r, int g, int b) { set_fcolor(Color{ r, g, b }); }
	static void set_bcolor(Color c) { set_bcolor_impl(c); }
	static void set_bcolor(int r, int g, int b) { set_bcolor(Color{ r, g, b }); }
	static void reset_colors();

	static void move_cursor_to(Coord c) { move_cursor_to_impl(c); }

	static void maximize() { instance().maximize_impl(); }
	static short canvas_width() { return instance().canvas_width_impl(); }
	static short canvas_height() { return instance().canvas_width_impl(); }
	static void set_up_buffer() { instance().set_up_buffer_impl(); }
	static void set_font_size(short width, short height) { instance().set_font_size_impl(width, height); }
	static void set_resolution(short width, short height) { instance().set_resolution_impl(width, height); }

	static void print_debug_info() { instance().print_debug_info_impl(); }
	static Coord font_size() { return instance().font_size_impl(); }
	static Coord canvas_size() { return instance().canvas_size_impl(); }
	//static int enable_virtual_terminal() { return instance().enable_virtual_terminal_impl(); }

	static std::string log() { return instance().m_log.str(); }

	ConhostController(const ConhostController&) = delete;

private:
	std::ostringstream m_log;

	void display_impl(Frame);

	static void set_fcolor_impl(Color c);
	static void set_bcolor_impl(Color c);
	static void move_cursor_to_impl(Coord new_pos);

	void maximize_impl();
	short canvas_width_impl();
	short canvas_height_impl();
	void set_up_buffer_impl();
	void set_font_size_impl(short width, short height);
	void set_resolution_impl(short width, short height);

	void print_debug_info_impl();
	Coord font_size_impl();
	Coord canvas_size_impl();
	int enable_virtual_terminal_impl();

	ConhostController();
	static ConhostController& instance() {
		static ConhostController instance;
		return instance;
	}
};