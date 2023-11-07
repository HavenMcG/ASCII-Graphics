#pragma once

#include "WinController.h"
#include <memory>

class Factory {
public:
	std::unique_ptr<WinController> create_winController() {
		return (std::unique_ptr<WinController>{new ConhostController{}});
	}
};