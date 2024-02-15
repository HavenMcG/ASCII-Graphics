
#include "ConhostController.h"
#include "GBase.h"
#include "Scene.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>

using namespace std::this_thread;
using namespace std::chrono_literals;
using ImageCodeRows = std::vector<std::string>;

void print_screen_border();
void print_buffer_debug_grid();
void color_test();
void play_intro();
Sprite read_image_data(std::string filepath);

int main() {
    using CC = ConhostController;
    CC::maximize();
    CC::set_resolution(600, 400);

    //Frame background{600,300};
    Sprite background = read_image_data("../seasidegarden.bmp");
    Sprite img = read_image_data("../test01.bmp");

    short x_pos = 170;
    short y_pos = 90;
    std::chrono::milliseconds delay = 20ms;
    short hop_distance = 1;
    short hop_count = 20;

    Scene my_scene{};
    my_scene.add(background, Coord{ 0,0 });
    my_scene.add(img, Coord{ x_pos, y_pos });
    my_scene.draw();

    while (true) {
        // South East
        for (int i = 0; i < hop_count; ++i) {
            sleep_for(delay);
            x_pos += hop_distance;
            y_pos += hop_distance;
            my_scene.move(1, Coord{ x_pos,y_pos });
        }
        // Back to start
        for (int i = 0; i < hop_count; ++i) {
            sleep_for(delay);
            x_pos -= hop_distance;
            y_pos -= hop_distance;
            my_scene.move(1, Coord{ x_pos,y_pos });
        }

        // East
        for (int i = 0; i < hop_count; ++i) {
            sleep_for(delay);
            x_pos += hop_distance;
            my_scene.move(1, Coord{ x_pos,y_pos });
        }
        // Back to start
        for (int i = 0; i < hop_count; ++i) {
            sleep_for(delay);
            x_pos -= hop_distance;
            my_scene.move(1, Coord{ x_pos,y_pos });
        }

        // North East
        for (int i = 0; i < hop_count; ++i) {
            sleep_for(delay);
            x_pos += hop_distance;
            y_pos -= hop_distance;
            my_scene.move(1, Coord{ x_pos,y_pos });
        }
        // Back to start
        for (int i = 0; i < hop_count; ++i) {
            sleep_for(delay);
            x_pos -= hop_distance;
            y_pos += hop_distance;
            my_scene.move(1, Coord{ x_pos,y_pos });
        }

        // North
        for (int i = 0; i < hop_count; ++i) {
            sleep_for(delay);
            y_pos -= hop_distance;
            my_scene.move(1, Coord{ x_pos,y_pos });
        }
        // Back to start
        for (int i = 0; i < hop_count; ++i) {
            sleep_for(delay);
            y_pos += hop_distance;
            my_scene.move(1, Coord{ x_pos,y_pos });
        }

        // North West
        for (int i = 0; i < hop_count; ++i) {
            sleep_for(delay);
            x_pos -= hop_distance;
            y_pos -= hop_distance;
            my_scene.move(1, Coord{ x_pos,y_pos });
        }
        // Back to start
        for (int i = 0; i < hop_count; ++i) {
            sleep_for(delay);
            x_pos += hop_distance;
            y_pos += hop_distance;
            my_scene.move(1, Coord{ x_pos,y_pos });
        }

        // West
        for (int i = 0; i < hop_count; ++i) {
            sleep_for(delay);
            x_pos -= hop_distance;
            my_scene.move(1, Coord{ x_pos,y_pos });
        }
        // Back to start
        for (int i = 0; i < hop_count; ++i) {
            sleep_for(delay);
            x_pos += hop_distance;
            my_scene.move(1, Coord{ x_pos,y_pos });
        }

        // South West
        for (int i = 0; i < hop_count; ++i) {
            sleep_for(delay);
            x_pos -= hop_distance;
            y_pos += hop_distance;
            my_scene.move(1, Coord{ x_pos,y_pos });
        }
        // Back to start
        for (int i = 0; i < hop_count; ++i) {
            sleep_for(delay);
            x_pos += hop_distance;
            y_pos -= hop_distance;
            my_scene.move(1, Coord{ x_pos,y_pos });
        }

        // South
        for (int i = 0; i < hop_count; ++i) {
            sleep_for(delay);
            y_pos += hop_distance;
            my_scene.move(1, Coord{ x_pos,y_pos });
        }
        // Back to start
        for (int i = 0; i < hop_count; ++i) {
            sleep_for(delay);
            y_pos -= hop_distance;
            my_scene.move(1, Coord{ x_pos,y_pos });
        }
    }

    CC::move_cursor_to(CC::canvas_width() - 1, CC::canvas_height() - 1);
}

void play_intro() {
    using CC = ConhostController;
    std::cout << "Hello, this is a console window!\n";
    std::cin.get();

    CC::set_fcolor(9, 179, 94);
    std::cout << "The windows console now supports ";
    CC::set_fcolor(250, 215, 40);
    std::cout << "24 bit rgb color!\n";
    std::cin.get();

    CC::set_fcolor(196, 156, 10);
    std::cout << "These are block characters:\n";
    color_test();
    std::cin.get();

    CC::set_fcolor(196, 10, 112);
    std::cout << "I wonder if we could use block characters to paint a picture...\n";
    std::cin.get();

    CC::set_fcolor(47, 97, 0);
    std::cout << "It would be easier if we could make the font square, like pixels.\n";
    std::cin.get();
    CC::set_fcolor(130, 7, 224);
    std::cout << "That was easy!\n";

    Coord font_size = CC::font_size();
    CC::set_font_size(font_size.y, font_size.y);
    std::cin.get();

    CC::set_fcolor(37, 101, 179);
    std::cout << "Lets make it smaller too.\n";
    std::cin.get();
    CC::set_fcolor(255, 89, 225);
    std::cout << "Wow, it's getting hard to read now...\n";

    CC::set_font_size(font_size.y / 2, font_size.y / 2);
    std::cin.get();

    CC::set_fcolor(40, 181, 150);
    std::cout << "Now we have the tools needed to render images in the console!\n";
    std::cin.get();

    CC::set_fcolor(189, 166, 36);
    std::cout << "For example, here's some art I found online:\n";
    std::cin.get();
}

Sprite read_image_data(std::string filepath) {
    std::ifstream ifs;
    ifs.open(filepath, std::ios::binary);
    if (!ifs) std::cout << "error\n";

    ifs.seekg(2);
    int file_size;
    ifs.read((char*)&file_size, 4);
    std::cout << file_size << std::endl;

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

    Sprite image{ image_width,image_height };

    unsigned char R, G, B;

    // read pixel data
    for (short row = 0; row < image_height; ++row) {
        for (short col = 0; col < image_width; ++col) {
            ifs.read((char*)&B, sizeof(unsigned char));
            ifs.read((char*)&G, sizeof(unsigned char));
            ifs.read((char*)&R, sizeof(unsigned char));

            image.pixel_data[image_height - row - 1][col] = Color{ R,G,B };
        }
    }
    ifs.close();
    return image;
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

    for (int colnum = 0; colnum < 77; colnum++) {
        int r = 255 - (colnum * 255 / 76);
        int g = (colnum * 510 / 76);
        int b = (colnum * 255 / 76);

        if (g > 255) g = 510 - g;

        CC::set_fcolor(r, g, b);
        //CC::set_fcolor(255 - r, 255 - g, 255 - b);
        std::cout << (char)219 << ' ';
        CC::reset_colors();
    }
    std::cout << "\n";
}