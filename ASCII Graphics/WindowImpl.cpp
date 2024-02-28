#include "WindowImpl.h"

namespace hcon {

	WindowImpl::WindowImpl() {
		window = GetConsoleWindow();
	}

	void WindowImpl::display_buffer(const Buffer& buf) {
		SetConsoleActiveScreenBuffer(buf.handle());
	}

	void WindowImpl::maximize() {
		ShowWindow(window, SW_MAXIMIZE);
	}
}