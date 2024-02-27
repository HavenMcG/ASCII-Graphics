#include "ANSI.h"

namespace hcon {

    std::string to_ansi_fcolor(Color c) {
        return "\033[38;2;" + std::to_string(c.r) + ";" + std::to_string(c.g) + ";" + std::to_string(c.b) + "m";
    }

    std::string to_ansi_fcolor(int r, int g, int b) {
        return to_ansi_fcolor(Color{ r,g,b });
    }

    std::string to_ansi_bcolor(Color c) {
        return "\033[48;2;" + std::to_string(c.r) + ";" + std::to_string(c.g) + ";" + std::to_string(c.b) + "m";
    }

    std::string to_ansi_bcolor(int r, int g, int b) {
        return to_ansi_bcolor(Color{ r,g,b });
    }
}