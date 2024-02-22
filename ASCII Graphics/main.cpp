
#include "ConhostController.h"
#include "Renderer.h"
#include "GBase.h"
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

PixelData read_image_data(std::string filepath);

int main() {
    ConhostController cc;
    ConsoleRenderer rr{ &cc };
    cc.maximize();
    cc.set_resolution(600, 400);

    PixelData background = read_image_data("../seasidegarden.bmp");
    PixelData img = read_image_data("../test01.bmp");

    hecs::RenderSystem rsys;
    hecs::SpriteComponentManager spcm;
    hecs::Transform2dComponentManager tfcm;

    std::vector<Entity> Entities;

    hecs::SpriteComponent* spcomp;
    hecs::Transform2dComponent* tfcomp;

    Entity e_background = 0;
    spcomp = spcm.add_component(e_background,background);
    tfcomp = tfcm.add_component(e_background,0,0);

    Entity e_1 = 1;
    spcomp = spcm.add_component(e_1,img);
    tfcomp = tfcm.add_component(e_1,200,50);

    Entity e_2 = 2;
    spcomp = spcm.add_component(e_2,img);
    tfcomp = tfcm.add_component(e_2,300,100);

    rsys.render(rr, spcm, tfcm);

    cc.move_cursor_to(cc.canvas_width() - 1, cc.canvas_height() - 1);
}


PixelData read_image_data(std::string filepath) {
    std::ifstream ifs;
    ifs.open(filepath, std::ios::binary);
    if (!ifs) //do something;

    ifs.seekg(2);
    int file_size;
    ifs.read((char*)&file_size, 4);

    ifs.seekg(10);
    int pixels_beginning;
    ifs.read((char*)&pixels_beginning, 4);

    short image_width;
    ifs.seekg(18);
    ifs.read((char*)&image_width, sizeof(short));

    short image_height;
    ifs.seekg(22);
    ifs.read((char*)&image_height, sizeof(short));

    ifs.seekg(pixels_beginning);

    PixelData image{ static_cast<unsigned>(image_height),std::vector<Color>{ static_cast<unsigned>(image_width) } };

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
    return image;
}