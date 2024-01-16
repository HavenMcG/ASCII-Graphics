
#include "ConhostController.h"

#include <iostream>
#include <fstream>
#include <string>

void print_screen_border();
void print_buffer_debug_grid();
void color_test();
void temp_display_image(std::string filepath);

int main() {
    using CC = ConhostController;
    CC::maximize();
    //CC::set_resolution(284, 67);
    //CC::set_resolution(800, 600);
    /*CC::set_font_size(2, 2);
    CC::set_buffer_size(800, 600);
    CC::set_bufferwindow_size(799, 449);*/
    CC::set_resolution(400, 300);

    //print_screen_border();
    temp_display_image("../seasidegarden.bmp");
    //CC::write("Hello World!");
    
    // Pause
    std::cin.get();

    //Frame blank{CC::canvas_size().x, CC::canvas_size().y};
    //CC::display(blank);

    //std::cin.get();
}

void temp_display_image(std::string filepath) {
    using CC = ConhostController;
    std::ifstream ifs;
    ifs.open(filepath, std::ios::binary);
    if (!ifs) std::cout << "error\n";

    ifs.seekg(2);
    int file_size;
    ifs.read((char*)&file_size, 4);
    std::cout << file_size << std::endl;]

    ifs.seekg(10);
    int pixels_beginning;
    ifs.read((char*)&pixels_beginning, 4);
    std::cout << pixels_beginning << std::endl;

    short image_width;
    ifs.seekg(18);
    ifs.read((char*)&image_width, sizeof(short));
    std::cout << image_width << std::endl;

    short image_height;
    ifs.seekg(22);
    ifs.read((char*)&image_height, sizeof(short));
    std::cout << image_height << std::endl;

    ifs.seekg(pixels_beginning);

    std::vector<std::vector<Color>> image;
    std::vector<Color> v{ static_cast<uint64_t>(image_width) };
    for (short row = 0; row < image_height; ++row) image.push_back(v);

    unsigned char R, G, B;

    // read pixel data
    for (short row = 0; row < image_height; ++row) {
        for (short col = 0; col < image_width; ++col) {
            ifs.read((char*)&B, sizeof(unsigned char));
            ifs.read((char*)&G, sizeof(unsigned char));
            ifs.read((char*)&R, sizeof(unsigned char));

            image[image_height - row - 1][col] = Color{ R,G,B };
        }
    }
    ifs.close();

    // display image
    CC::move_cursor_to(Coord{ 0, 0 });
    Color prev_color{0,0,0};
    std::string img_code = "";
    for (short row = 0; row < image_height; ++row) {
        for (short col = 0; col < image_width; ++col) {
            //CC::set_fcolor(image[row][col]);
            // block char: 219
            Color current_color = image[row][col];
            if (current_color != prev_color) {
                img_code += to_ansi(current_color);
            }
            img_code += (char)219;
        }
    }
    CC::write(img_code);
}

void print_screen_border() {
    int screenHeight = ConhostController::canvas_size().y - 2;
    int screenWidth = ConhostController::canvas_size().x;

    for (int row = 0; row < screenHeight; ++row) {
        for (int col = 0; col < screenWidth; ++col) {
            if (row == 0
                || row == screenHeight - 1
                || col == 0
                || col == screenWidth - 1
                ) {
                std::cout << 'X';
            }
            else std::cout << ' ';
            //std::cout << (row + 1) << ", " << (col + 1) << std::endl;
        }
    }
}

void print_buffer_debug_grid() {
    int screenHeight = ConhostController::canvas_size().y - 2;
    int screenWidth = ConhostController::canvas_size().x;

    for (int row = 0; row < screenHeight; ++row) {
        for (int col = 0; col < screenWidth; ++col) {
            if (row == 0
                || row == screenHeight - 1
                || col == 0
                || col == screenWidth - 1
                ) {
                char ch = '0' + ((row + 1) * (col + 1)) % 10;
                if (ch == '0') ch = (char)219;
                std::cout << ch;
            }
            else std::cout << ' ';
        }
    }
}

void color_test() {
    using CC = ConhostController;
    std::string s = "\\/\\/\\/\\/\\/\\/\\/\\/";
    s += s + s + s + s + s + s + s;

    for (int colnum = 0; colnum < 77; colnum++) {
        int r = 255 - (colnum * 255 / 76);
        int g = (colnum * 510 / 76);
        int b = (colnum * 255 / 76);

        if (g > 255) g = 510 - g;

        CC::set_bcolor(r, g, b);
        CC::set_fcolor(255 - r, 255 - g, 255 - b);
        std::cout << s[colnum];
        CC::reset_colors();
    }
    std::cout << "\n";
}