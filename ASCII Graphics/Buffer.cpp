#include "Buffer.h"
#include "BufferImpl.h"
#include "Conversion.h"
#include <exception>

namespace hcon {

	Buffer::Buffer() : Buffer::Buffer(new_handle) {}

	Buffer::Buffer(HandleType ht) {
		switch (ht) {
			case std_output_handle: {
				pimpl = new BufferImpl{ BufferImpl::std_output_handle };
				break;
			}
			case new_handle: {
				pimpl = new BufferImpl{ BufferImpl::new_handle };
				break;
			}
			default: {
				throw std::exception{ "Invalid HandleType argument to Buffer()" };
				break;
			}
		}
	}

	Buffer::~Buffer() {
		delete pimpl;
	}
	void Buffer::write(Coord c, const std::string& s) { pimpl->write(to_wincoord(c), s); }
	void Buffer::slow_write(const std::string& s) { pimpl->slow_write(s); }
	void Buffer::set_buffer_size(short width, short height) { pimpl->set_buffer_size(width, height); }
	void Buffer::set_bufferwindow_size(short width, short height) { pimpl->set_bufferwindow_size(width, height); }
	void Buffer::set_font_size(short width, short height) { pimpl->set_font_size(width, height); }
	void Buffer::set_cursor_pos(short x, short y) { pimpl->set_cursor_pos(x, y); }
	void Buffer::set_fcolor(Color c) { pimpl->set_fcolor(c); }
	void Buffer::set_bcolor(Color c) { pimpl->set_bcolor(c); }
	void Buffer::reset_colors() { pimpl->reset_colors(); }
	void Buffer::copy(const Buffer& source, Rect source_rect, Rect destination_rect) { pimpl->copy(source.handle(), to_winsmallrect(source_rect), to_winsmallrect(destination_rect)); }

	// Getters
	void* Buffer::handle() const { return pimpl->handle(); }
	Coord Buffer::cursor_pos() const { return to_coord(pimpl->cursor_pos()); }
	Coord Buffer::buffer_size() const { return to_coord(pimpl->buffer_size()); }
	Rect Buffer::bufferwindow_corners() const { return to_rect(pimpl->bufferwindow_corners()); }
	Coord Buffer::font_size() const { return to_coord(pimpl->font_size()); }
	Coord Buffer::max_bufferwindow_size() const { return to_coord(pimpl->buffer_info().dwMaximumWindowSize); }
}