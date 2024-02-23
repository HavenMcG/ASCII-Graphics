
#include "ConhostController.h"
#include "GBase.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <string>
#include "RenderSystem.h"

using hecs::ConsoleRenderer;
using namespace std::this_thread;
using namespace std::chrono_literals;
using hecs::Entity;

PixelData read_image_data(std::string filepath);

int main() {
    ConhostController cc;
    ConsoleRenderer rr{ &cc };
    cc.maximize();
    cc.set_resolution(600, 300+8);

    PixelData background_img = read_image_data("../seasidegarden.bmp");
    PixelData smiley_img = read_image_data("../test01.bmp");
    PixelData green_minion_img = read_image_data("../GreenMinion.bmp");
    PixelData pink_minion_img = read_image_data("../PinkMinion.bmp");

    hecs::SpriteComponentManager spcm;
    hecs::Transform2dComponentManager tfcm;

    std::vector<Entity> Entities;

    hecs::SpriteComponent* spcomp;
    hecs::Transform2dComponent* tfcomp;

    Entity background = 0;
    spcomp = spcm.add_component(background,background_img);
    tfcomp = tfcm.add_component(background,0,0);

    Entity smiley1 = 1;
    spcomp = spcm.add_component(smiley1,smiley_img);
    tfcomp = tfcm.add_component(smiley1,background,50,150);

    Entity smiley2 = 2;
    spcomp = spcm.add_component(smiley2,smiley_img);
    tfcomp = tfcm.add_component(smiley2,background,300,20);

    Entity minion1 = 3;
    spcomp = spcm.add_component(minion1, green_minion_img);
    tfcomp = tfcm.add_component(minion1, smiley1, -green_minion_img.width-1, -green_minion_img.height-1);

    Entity minion2 = 4;
    spcomp = spcm.add_component(minion2, green_minion_img);
    tfcomp = tfcm.add_component(minion2, smiley1, smiley_img.width + 1, smiley_img.height + 1);

    Entity subminion1 = 5;
    spcomp = spcm.add_component(subminion1, pink_minion_img);
    tfcomp = tfcm.add_component(subminion1, minion1, -pink_minion_img.width - 1, green_minion_img.height + 1);

    rr.render(&spcm, &tfcm);
    cc.move_cursor_to(0, cc.canvas_height() - 1 - 6);
    std::cin.get();

    tfcm.move(1, Coord{ 170,0 });
    rr.render(&spcm, &tfcm);
    cc.move_cursor_to(0, cc.canvas_height() - 1 - 6);
    std::cin.get();

    tfcm.move(3, Coord{ 0,smiley_img.height + 1 + green_minion_img.height + 1 });
    rr.render(&spcm, &tfcm);

    cc.move_cursor_to(0, cc.canvas_height() - 1 - 6);
}


PixelData read_image_data(std::string filepath) {
    std::ifstream ifs;
    ifs.open(filepath, std::ios::binary);
    if (!ifs); //do something

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

    PixelData image{ image_width,image_height };
    unsigned char R, G, B;

    // read pixel data
    for (int i = image.data.size()-1; i >= 0; --i) {
        ifs.read((char*)&B, sizeof(unsigned char));
        ifs.read((char*)&G, sizeof(unsigned char));
        ifs.read((char*)&R, sizeof(unsigned char));
        image.data[i] = Color{ R,G,B };
    }
    ifs.close();
    return image;
}