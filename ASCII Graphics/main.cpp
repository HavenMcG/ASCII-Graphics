
#include "ConhostController.h"
#include "Renderer.h"
#include "GBase.h"
#include "Scene.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <string>

using ConArt::ConsoleRenderer;
using namespace std::this_thread;
using namespace std::chrono_literals;

Sprite read_image_data(std::string filepath);

int main() {
    ConhostController cc;
    ConsoleRenderer rr{ &cc };
    cc.maximize();
    cc.set_resolution(600, 400);


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
    rr.draw(&my_scene);

    while (true) {
        // South East
        for (int i = 0; i < hop_count; ++i) {
            sleep_for(delay);
            x_pos += hop_distance;
            y_pos += hop_distance;
            rr.move(&my_scene, 1, Coord{ x_pos,y_pos });
        }
        // Back to start
        for (int i = 0; i < hop_count; ++i) {
            sleep_for(delay);
            x_pos -= hop_distance;
            y_pos -= hop_distance;
            rr.move(&my_scene, 1, Coord{ x_pos,y_pos });
        }

        // East
        for (int i = 0; i < hop_count; ++i) {
            sleep_for(delay);
            x_pos += hop_distance;
            rr.move(&my_scene, 1, Coord{ x_pos,y_pos });
        }
        // Back to start
        for (int i = 0; i < hop_count; ++i) {
            sleep_for(delay);
            x_pos -= hop_distance;
            rr.move(&my_scene, 1, Coord{ x_pos,y_pos });
        }

        // North East
        for (int i = 0; i < hop_count; ++i) {
            sleep_for(delay);
            x_pos += hop_distance;
            y_pos -= hop_distance;
            rr.move(&my_scene, 1, Coord{ x_pos,y_pos });
        }
        // Back to start
        for (int i = 0; i < hop_count; ++i) {
            sleep_for(delay);
            x_pos -= hop_distance;
            y_pos += hop_distance;
            rr.move(&my_scene, 1, Coord{ x_pos,y_pos });
        }

        // North
        for (int i = 0; i < hop_count; ++i) {
            sleep_for(delay);
            y_pos -= hop_distance;
            rr.move(&my_scene, 1, Coord{ x_pos,y_pos });
        }
        // Back to start
        for (int i = 0; i < hop_count; ++i) {
            sleep_for(delay);
            y_pos += hop_distance;
            rr.move(&my_scene, 1, Coord{ x_pos,y_pos });
        }

        // North West
        for (int i = 0; i < hop_count; ++i) {
            sleep_for(delay);
            x_pos -= hop_distance;
            y_pos -= hop_distance;
            rr.move(&my_scene, 1, Coord{ x_pos,y_pos });
        }
        // Back to start
        for (int i = 0; i < hop_count; ++i) {
            sleep_for(delay);
            x_pos += hop_distance;
            y_pos += hop_distance;
            rr.move(&my_scene, 1, Coord{ x_pos,y_pos });
        }

        // West
        for (int i = 0; i < hop_count; ++i) {
            sleep_for(delay);
            x_pos -= hop_distance;
            rr.move(&my_scene, 1, Coord{ x_pos,y_pos });
        }
        // Back to start
        for (int i = 0; i < hop_count; ++i) {
            sleep_for(delay);
            x_pos += hop_distance;
            rr.move(&my_scene, 1, Coord{ x_pos,y_pos });
        }

        // South West
        for (int i = 0; i < hop_count; ++i) {
            sleep_for(delay);
            x_pos -= hop_distance;
            y_pos += hop_distance;
            rr.move(&my_scene, 1, Coord{ x_pos,y_pos });
        }
        // Back to start
        for (int i = 0; i < hop_count; ++i) {
            sleep_for(delay);
            x_pos += hop_distance;
            y_pos -= hop_distance;
            rr.move(&my_scene, 1, Coord{ x_pos,y_pos });
        }

        // South
        for (int i = 0; i < hop_count; ++i) {
            sleep_for(delay);
            y_pos += hop_distance;
            rr.move(&my_scene, 1, Coord{ x_pos,y_pos });
        }
        // Back to start
        for (int i = 0; i < hop_count; ++i) {
            sleep_for(delay);
            y_pos -= hop_distance;
            rr.move(&my_scene, 1, Coord{ x_pos,y_pos });
        }
    }


    cc.move_cursor_to(cc.canvas_width() - 1, cc.canvas_height() - 1);
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