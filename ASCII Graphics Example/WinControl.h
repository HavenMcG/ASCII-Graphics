#pragma once
#include <Windows.h>

void set_up_buffer();
void set_font_size(SHORT width, SHORT height);
/* Sets the console buffer to the specified dimensions and sets font dimensions to attempt to fill the current window */ 
void set_resolution(SHORT width, SHORT height);
void print_console_debug_info();
COORD font_size();
COORD screen_size();