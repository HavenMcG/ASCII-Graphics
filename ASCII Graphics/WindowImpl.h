#pragma once
#include "GBase.h"
#include "Buffer.h"
#include <Windows.h>

namespace hcon {

	class WindowImpl {
	public:
		WindowImpl();

		void display_buffer(const Buffer& buf);
		void maximize();

	private:
		HWND window;
	};
}