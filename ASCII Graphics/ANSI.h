#pragma once
#include <string>
#include "GBase.h"

namespace hcon {
	std::string to_ansi_fcolor(Color c);
	std::string to_ansi_fcolor(int r, int g, int b);
	std::string to_ansi_bcolor(Color c);
	std::string to_ansi_bcolor(int r, int g, int b);
}