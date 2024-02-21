
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
#include "RenderSystem.h"

using ConArt::ConsoleRenderer;
using namespace std::this_thread;
using namespace std::chrono_literals;
using hecs::Entity;

Sprite read_image_data(std::string filepath);

int main() {
    ConhostController cc;
    ConsoleRenderer rr{ &cc };
    cc.maximize();
    cc.set_resolution(600, 400);

    Sprite background = read_image_data("../seasidegarden.bmp");
    //cc.set_resolution(background.width(), background.height());
    Sprite img = read_image_data("../test01.bmp");

    hecs::RenderSystem rsys;
    hecs::SpriteComponentManager spcm;
    hecs::Transform2dComponentManager tfcm;

    std::vector<Entity> Entities;

    Entity e_background = 0;
    spcm.add_component(e_background);
    hecs::SpriteComponent* spcomp = spcm.get_component(e_background);
    spcomp->pixel_data = background.pixel_data;
    tfcm.add_component(e_background);
    hecs::Transform2dComponent* tfcomp = tfcm.get_component(e_background);
    tfcomp->x = 0;
    tfcomp->y = 0;

    Entity e_1 = 1;
    spcm.add_component(e_1);
    spcomp = spcm.get_component(e_1);
    spcomp->pixel_data = img.pixel_data;
    tfcm.add_component(e_1);
    tfcomp = tfcm.get_component(e_1);
    tfcomp->x = 200;
    tfcomp->y = 50;

    Entity e_2 = 2;
    spcm.add_component(e_2);
    spcomp = spcm.get_component(e_2);
    spcomp->pixel_data = img.pixel_data;
    tfcm.add_component(e_2);
    tfcomp = tfcm.get_component(e_2);
    tfcomp->x = 300;
    tfcomp->y = 100;

    rsys.render(rr, spcm, tfcm);

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