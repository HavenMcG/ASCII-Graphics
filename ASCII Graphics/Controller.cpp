#include "Controller.h"
#include "Buffer.h"
#include <vector>

namespace hcon {

	
	class ControllerImpl {
	public:

		static Coord to_coord(COORD c) {
			return Coord{ c.X, c.Y };
		}
		static COORD to_wincoord(Coord c) {
			return COORD{ c.x, c.y };
		}

		ControllerImpl();
		Buffer* buffer(int i);
		void switch_target_buffer();
		void switch_visible_buffer();
		void write(std::string s);
		void write(char ch);

		void set_fcolor(Color c);
		void set_fcolor(int r, int g, int b);
		void set_bcolor(Color c);
		void set_bcolor(int r, int g, int b);
		void reset_colors();

		Coord cursor_position();
		void move_cursor_to(short x, short y);
		void move_cursor_to(Coord new_pos);
		
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
		std::vector<Buffer> buffers;
		int target_buffer;
		int visible_buffer;
		HWND window;
	};

	//-------------------------------------------------------------------------------------------------------------------------------------------------------------------

	ControllerImpl::ControllerImpl() {
		window = GetConsoleWindow();
		buffers = std::vector<Buffer>{};
		buffers.emplace_back(Buffer::std_output_handle);
		buffers.emplace_back();
		target_buffer = 0;
		visible_buffer = 0;
		SetConsoleActiveScreenBuffer(buffers[visible_buffer].handle());
	}

	Buffer* ControllerImpl::buffer(int i) {
		return &buffers[i];
	}

	void ControllerImpl::switch_target_buffer() {
		target_buffer += 1;
		if (target_buffer >= buffers.size()) target_buffer = 0;
	}

	void ControllerImpl::switch_visible_buffer() {
		visible_buffer += 1;
		if (visible_buffer >= buffers.size()) visible_buffer = 0;
		SetConsoleActiveScreenBuffer(buffers[visible_buffer].handle());
	}

	void ControllerImpl::write(std::string s) {
		buffers[target_buffer].write(s);
	}

	void ControllerImpl::write(char ch) {
		buffers[target_buffer].write(std::to_string(ch));
	}

	void ControllerImpl::set_fcolor(Color c) {
		buffers[target_buffer].set_fcolor(c);
	}

	void ControllerImpl::set_fcolor(int r, int g, int b) {
		set_fcolor(Color{ r,g,b });
	}

	void ControllerImpl::set_bcolor(Color c) {
		buffers[target_buffer].set_bcolor(c);
	}

	void ControllerImpl::set_bcolor(int r, int g, int b) {
		set_bcolor(Color{ r,g,b });
	}

	void ControllerImpl::reset_colors() {
		buffers[target_buffer].reset_colors();
	}

	Coord ControllerImpl::cursor_position() {
		return to_coord(buffers[target_buffer].cursor_pos());
	}

	void ControllerImpl::move_cursor_to(short x, short y) {
		buffers[target_buffer].set_cursor_pos(x, y);
	}

	void ControllerImpl::move_cursor_to(Coord new_pos) {
		move_cursor_to(new_pos.x, new_pos.y);
	}

	void ControllerImpl::maximize() {
		ShowWindow(window, SW_MAXIMIZE);
	}

	Coord ControllerImpl::canvas_size() {
		return to_coord(buffers[target_buffer].buffer_size());
	}

	short ControllerImpl::canvas_width() {
		return canvas_size().x;
	}

	short ControllerImpl::canvas_height() {
		return canvas_size().y;
	}

	Coord ControllerImpl::font_size() {
		return to_coord(buffers[target_buffer].font_size());
	}

	void ControllerImpl::set_resolution(short width, short height) {

		Buffer* buf = &buffers[target_buffer];

		// get Win info
		RECT clientRect;
		GetClientRect(window, &clientRect);
		int clientWidth = clientRect.right - clientRect.left;
		int clientHeight = clientRect.bottom - clientRect.top;

		// set char size
		SHORT charWidth = clientWidth / width;
		if (charWidth < 2) charWidth = 2; // 2 is the minimum height of a character, therefore 2x2 is the smallest possible square character
		SHORT charHeight = clientHeight / height;
		if (charHeight < 2) charHeight = 2;
		if (charHeight > charWidth) charWidth = charHeight;
		else if (charWidth > charHeight) charHeight = charWidth;
		buf->set_font_size(charWidth, charHeight);

		// shrink the window to prevent error
		buf->set_bufferwindow_size(0, 0);

		// set new buffer size
		buf->set_buffer_size(width, height);

		// now restore the window again
		SHORT maxWindowX = buf->buffer_info().dwMaximumWindowSize.X - 1;
		SHORT maxWindowY = buf->buffer_info().dwMaximumWindowSize.Y - 1;

		// hide scroll bars
		//ShowScrollBar(s_consoleWin, SB_BOTH, FALSE);
	}

	void ControllerImpl::set_buffer_size(short width, short height) {
		buffers[target_buffer].set_buffer_size(width, height);
	}

	void ControllerImpl::set_bufferwindow_size(short width, short height) {
		buffers[target_buffer].set_bufferwindow_size(width, height);
	}

	void ControllerImpl::set_font_size(short width, short height) {
		buffers[target_buffer].set_font_size(width, height);
	}

	//===================================================================================================================================================================

	Controller::Controller() {
		pimpl = new ControllerImpl{};
	}
	Controller::~Controller() {
		delete pimpl;
	}
	Buffer* hcon::Controller::buffer(int i) { return pimpl->buffer(i); }
	void Controller::switch_target_buffer() { pimpl->switch_target_buffer(); }
	void Controller::switch_display_buffer() { pimpl->switch_visible_buffer(); }
	void Controller::write(std::string s) { pimpl->write(s); }
	void Controller::write(char ch) { pimpl->write(ch); }

	void Controller::set_fcolor(Color c) { pimpl->set_fcolor(c); }
	void Controller::set_fcolor(int r, int g, int b) { pimpl->set_fcolor(r, g, b); }
	void Controller::set_bcolor(Color c) { pimpl->set_bcolor(c); }
	void Controller::set_bcolor(int r, int g, int b) { pimpl->set_bcolor(r, g, b); }
	void Controller::reset_colors() { pimpl->reset_colors(); }

	Coord Controller::cursor_position() { return pimpl->cursor_position(); }
	void Controller::move_cursor_to(Coord new_pos) { pimpl->move_cursor_to(new_pos); }
	void Controller::move_cursor_to(short x, short y) { pimpl->move_cursor_to(x, y); }

	void Controller::maximize() { pimpl->maximize(); }
	Coord Controller::canvas_size() { return pimpl->canvas_size(); }
	short Controller::canvas_width() { return pimpl->canvas_width(); }
	short Controller::canvas_height() { return pimpl->canvas_height(); }
	Coord Controller::font_size() { return pimpl->font_size(); }
	void Controller::set_resolution(short width, short height) { pimpl->set_resolution(width, height); }
	void Controller::set_buffer_size(short width, short height) { pimpl->set_buffer_size(width, height); }
	void Controller::set_bufferwindow_size(short width, short height) { pimpl->set_bufferwindow_size(width, height); }
	void Controller::set_font_size(short width, short height) { pimpl->set_font_size(width, height); }
}