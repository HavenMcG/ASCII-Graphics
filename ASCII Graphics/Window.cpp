#include "Window.h"
#include "Buffer.h"
#include "WindowImpl.h"
#include <vector>

namespace hcon {

	Window::Window() {
		pimpl = new WindowImpl{};
	}
	Window::~Window() {
		delete pimpl;
	}

	void Window::display_buffer(const Buffer& buf) { pimpl->display_buffer(buf); }
	void Window::maximize() { pimpl->maximize(); }
}