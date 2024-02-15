#pragma once
#include "GBase.h"
#include <string>
#include <sstream>
#include <vector>

// temp?
using RenderCode = std::vector<std::string>;

class ConhostController {
public:
	static void write(RenderCode fcode) { instance().write_impl(fcode); }
	static void write(std::string s) { instance().write_impl(s); }
	static void write(char ch) { instance().write_impl(ch); }

	static void set_fcolor(Color c) { instance().set_fcolor_impl(c); }
	static void set_fcolor(int r, int g, int b) { set_fcolor(Color{ r, g, b }); }
	static void set_bcolor(Color c) { instance().set_bcolor_impl(c); }
	static void set_bcolor(int r, int g, int b) { set_bcolor(Color{ r, g, b }); }
	static void reset_colors();

	static Coord cursor_position() { return instance().cursor_position_impl(); }
	static void move_cursor_to(Coord c) { instance().move_cursor_to_impl(c); }
	static void move_cursor_to(short x, short y) { instance().move_cursor_to_impl(Coord{x,y}); }

	static void maximize() { instance().maximize_impl(); }
	static short canvas_width() { return instance().canvas_width_impl(); }
	static short canvas_height() { return instance().canvas_height_impl(); }
	static void set_font_size(Coord new_size) { instance().set_font_size_impl(new_size.x, new_size.y); }
	static void set_font_size(short width, short height) { instance().set_font_size_impl(width, height); }
	static void set_resolution(short width, short height) { instance().set_resolution_impl(width, height); }
	static void set_buffer_size(short width, short height) { instance().set_buffer_size_impl(width, height); } // should this be public?
	static void set_bufferwindow_size(short width, short height) { instance().set_bufferwindow_size_impl(width, height); } // should this be public?

	static void log_debug_info() { instance().log_debug_info_impl(); } // needs refactoring
	static Coord font_size() { return instance().font_size_impl(); }
	static Coord canvas_size() { return instance().canvas_size_impl(); }
	//static int enable_virtual_terminal() { return instance().enable_virtual_terminal_impl(); }

	static std::string log() { return instance().m_log.str(); }

	ConhostController(const ConhostController&) = delete;

private:
	std::ostringstream m_log;

	//void display_impl(Frame);
	//void display_impl(Scene);
	void write_impl(RenderCode fcode);
	void write_impl(std::string s);
	void write_impl(char ch);

	void set_fcolor_impl(Color c);
	void set_bcolor_impl(Color c);

	Coord cursor_position_impl();
	void move_cursor_to_impl(Coord new_pos);

	void maximize_impl();
	short canvas_width_impl();
	short canvas_height_impl();
	void set_font_size_impl(short width, short height);
	void set_resolution_impl(short width, short height);
	void set_buffer_size_impl(short width, short height);
	void set_bufferwindow_size_impl(short width, short height);

	void log_debug_info_impl();
	Coord font_size_impl();
	Coord canvas_size_impl();
	int enable_virtual_terminal_impl();

	ConhostController();
	static ConhostController& instance() {
		static ConhostController instance;
		return instance;
	}
};

