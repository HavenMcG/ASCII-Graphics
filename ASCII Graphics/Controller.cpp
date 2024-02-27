#include "Controller.h"
#include "Buffer.h"
#include <vector>

namespace hcon {

	Coord to_coord(COORD c) {
		return Coord{ c.X, c.Y };
	}

	COORD to_wincoord(Coord c) {
		return COORD{ c.x, c.y };
	}

	class ControllerImpl {
	public:
		ControllerImpl() {
			window = GetConsoleWindow();
			buffers = std::vector<Buffer>{};
			buffers.emplace_back(Buffer::std_output_handle);
			buffers.emplace_back();
			target_buffer = 0;
			visible_buffer = 0;
			SetConsoleActiveScreenBuffer(buffers[visible_buffer].handle());
		}

		//-------------------------------------------------------------------------------------------------------------

		void switch_target_buffer() {
			target_buffer += 1;
			if (target_buffer >= buffers.size()) target_buffer = 0;
		}
		void switch_visible_buffer() {
			visible_buffer += 1;
			if (visible_buffer >= buffers.size()) visible_buffer = 0;
			SetConsoleActiveScreenBuffer(buffers[visible_buffer].handle());
		}
		void write(std::string s) {
			buffers[target_buffer].write(s);
		}
		void write(char ch) {
			buffers[target_buffer].write(std::to_string(ch));
		}


		void set_fcolor(Color c) {
			buffers[target_buffer].set_fcolor(c);
		}
		void set_fcolor(int r, int g, int b) { set_fcolor(Color{ r,g,b }); }
		void set_bcolor(Color c) {
			buffers[target_buffer].set_bcolor(c);
		}
		void set_bcolor(int r, int g, int b) { set_bcolor(Color{ r,g,b }); }
		void reset_colors() {
			buffers[target_buffer].reset_colors();
		}


		Coord cursor_position() {
			return to_coord(buffers[target_buffer].cursor_pos());
		}
		void move_cursor_to(short x, short y) {
			buffers[target_buffer].set_cursor_pos(x, y);
		}
		void move_cursor_to(Coord new_pos) { move_cursor_to(new_pos.x, new_pos.y); }
		

		void maximize() {
			ShowWindow(window, SW_MAXIMIZE);
		}
		Coord canvas_size() {
			return to_coord(buffers[target_buffer].buffer_size());
		}
		short canvas_width() { return canvas_size().x; }
		short canvas_height() { return canvas_size().y; }
		Coord font_size() { return to_coord(buffers[target_buffer].font_size()); }
		void set_resolution(short width, short height) {

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
		void set_buffer_size(short width, short height) {
			buffers[target_buffer].set_buffer_size(width, height);
		}
		void set_bufferwindow_size(short width, short height) {
			buffers[target_buffer].set_bufferwindow_size(width, height);
		}
		void set_font_size(short width, short height) {
			buffers[target_buffer].set_font_size(width, height);
		}
		//-------------------------------------------------------------------------------------------------------------

	private:
		std::vector<Buffer> buffers;
		int target_buffer;
		int visible_buffer;
		HWND window;
	};

	void ControllerImpl::write(std::string s) {
		buffers[target_buffer].write(s);
	}
	void ControllerImpl::write(char ch) {
		buffers[target_buffer].write(std::to_string(ch));
	}

	//===================================================================================================================================

	ConhostController::ConhostController() {
		pimpl = new ControllerImpl{};
	}
	ConhostController::~ConhostController() {
		delete pimpl;
	}
	void ConhostController::switch_target_buffer() { pimpl->switch_target_buffer(); }
	void ConhostController::switch_display_buffer() { pimpl->switch_visible_buffer(); }
	void ConhostController::write(std::string s) { pimpl->write(s); }
	void ConhostController::write(char ch) { pimpl->write(ch); }

	void ConhostController::set_fcolor(Color c) { pimpl->set_fcolor(c); }
	void ConhostController::set_fcolor(int r, int g, int b) { pimpl->set_fcolor(r, g, b); }
	void ConhostController::set_bcolor(Color c) { pimpl->set_bcolor(c); }
	void ConhostController::set_bcolor(int r, int g, int b) { pimpl->set_bcolor(r, g, b); }
	void ConhostController::reset_colors() { pimpl->reset_colors(); }

	Coord ConhostController::cursor_position() { return pimpl->cursor_position(); }
	void ConhostController::move_cursor_to(Coord new_pos) { pimpl->move_cursor_to(new_pos); }
	void ConhostController::move_cursor_to(short x, short y) { pimpl->move_cursor_to(x, y); }

	void ConhostController::maximize() { pimpl->maximize(); }
	Coord ConhostController::canvas_size() { return pimpl->canvas_size(); }
	short ConhostController::canvas_width() { return pimpl->canvas_width(); }
	short ConhostController::canvas_height() { return pimpl->canvas_height(); }
	Coord ConhostController::font_size() { return pimpl->font_size(); }
	void ConhostController::set_resolution(short width, short height) { pimpl->set_resolution(width, height); }
	void ConhostController::set_buffer_size(short width, short height) { pimpl->set_buffer_size(width, height); }
	void ConhostController::set_bufferwindow_size(short width, short height) { pimpl->set_bufferwindow_size(width, height); }
	void ConhostController::set_font_size(short width, short height) { pimpl->set_font_size(width, height); }
}