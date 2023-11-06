#pragma once

#include "WinController.h"

class Factory {
public:
	std::unique_ptr<WinController> create_winController() {
		//return new ConhostController{};
		return (std::unique_ptr<WinController>{new ConhostController{}});
	}
};