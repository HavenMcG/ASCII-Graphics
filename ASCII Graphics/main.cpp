
#include "Controller.h"
#include "GBase.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
#include <string>
#include "RenderSystem.h"

using hcon::ConhostController;
using hecs::ConsoleRenderer;
using namespace std::this_thread;
using namespace std::chrono_literals;
using hecs::Entity;

PixelData read_image_data(std::string filepath);
void move_in_orbit(Entity e, int gap, hecs::SpriteComponentManager& spcm, hecs::Transform2dComponentManager& tfcm);

int main() {

    ConhostController cc;
    ConsoleRenderer rr{ &cc };
    //cc.maximize();
    //cc.set_resolution(600, 300+8);

    PixelData background_img = read_image_data("../seasidegarden.bmp");
    PixelData smiley_img = read_image_data("../test01.bmp");

    hecs::SpriteComponentManager spcm;
    hecs::Transform2dComponentManager tfcm;

    hecs::SpriteComponent* spcomp;
    hecs::Transform2dComponent* tfcomp;
    Entity smiley1 = 1;
    spcomp = spcm.add_component(smiley1,smiley_img);
    tfcomp = tfcm.add_component(smiley1);

    cc.write("hello!");

    //rr.render(&spcm, &tfcm);
    //cc.move_cursor_to(0, 0);
    std::cin.get();
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

void move_in_orbit(Entity e, int gap, hecs::SpriteComponentManager& spcm, hecs::Transform2dComponentManager& tfcm) {
    Coord current_pos = tfcm.get_component(e)->local;

    Entity parent = tfcm.get_entity_by_component_index(tfcm.get_component(e)->parent);

    short speed = 1;
    short w_self = spcm.get_component(e)->pixel_data.width;
    short h_self = spcm.get_component(e)->pixel_data.height;
    short w_parent = spcm.get_component(parent)->pixel_data.width;
    short h_parent = spcm.get_component(parent)->pixel_data.height;

    Coord top_right = Coord{ w_parent + gap, -h_self - gap };
    Coord bottom_right{ w_parent + gap, h_parent + gap };
    Coord bottom_left{ -w_self - gap, h_parent + gap };
    Coord top_left{ -w_self - gap, -h_self - gap };

    if (current_pos.x < top_right.x && current_pos.y == top_right.y) {
        if (current_pos.x + speed > top_right.x) {
            tfcm.move(e, { top_right.x - current_pos.x, 0 });
        }
        else tfcm.move(e, { speed, 0 });
    }
    else if (current_pos.x == bottom_right.x && current_pos.y < bottom_right.y) {
        if (current_pos.y + speed > bottom_right.y) {
            tfcm.move(e, { 0, bottom_right.y - current_pos.y });
        }
        else tfcm.move(e, { 0,speed });
    }
    else if (current_pos.x > bottom_left.x && current_pos.y == bottom_left.y) {
        if (current_pos.x - speed < bottom_left.x) {
            tfcm.move(e, { bottom_left.x - current_pos.x, 0 });
        }
        else tfcm.move(e, { -speed, 0 });
    }
    else if (current_pos.x == top_left.x && current_pos.y > top_left.y) {
        if (current_pos.y - speed < top_left.y) {
            tfcm.move(e, { 0, top_left.y - current_pos.y });
        }
        else tfcm.move(e, { 0,-speed });
    }
}