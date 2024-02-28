#pragma once
#include "GBase.h"
#include "Buffer.h"

namespace hcon {

	class WindowImpl;

	class Window {
	public:
		Window();
		~Window();
		Window(const Window&) = delete;

		void display_buffer(const Buffer& buf);
		void maximize();

	private:
		WindowImpl* pimpl; // pimpl idiom
		//std::unique_ptr<ControllerImpl> pimpl;
	};
}