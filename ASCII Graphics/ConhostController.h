#pragma once
#include "GBase.h"
//#include <sstream>

// temp?
using RenderCode = std::vector<std::string>;

class ConhostController {

public:
	//std::ostringstream m_log;

	ConhostController();

	void switch_target_buffer();
	void switch_display_buffer();
	void write(std::string s);
	void write(char ch);

	void set_fcolor(Color c);
	void set_fcolor(int r, int g, int b) { set_fcolor(Color{ r,g,b }); }
	void set_bcolor(Color c);
	void set_bcolor(int r, int g, int b) { set_bcolor(Color{ r,g,b }); }
	void reset_colors();
	
	Coord cursor_position();
	void move_cursor_to(Coord new_pos);
	void move_cursor_to(short x, short y) { move_cursor_to(Coord{ x,y }); }

	void maximize();
	Coord canvas_size();
	short canvas_width();
	short canvas_height();
	Coord font_size();
	void set_resolution(short width, short height);
	void set_buffer_size(short width, short height);
	void set_bufferwindow_size(short width, short height);
	void set_font_size(short width, short height);

	void log_debug_info();
	

private:
	int enable_virtual_terminal(); // p
};

std::string to_ansi_fcolor(Color c);
std::string to_ansi_fcolor(int r, int g, int b);
std::string to_ansi_bcolor(Color c);
std::string to_ansi_bcolor(int r, int g, int b);