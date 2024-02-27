
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
void move_in_orbit(Entity e, int gap, hecs::SpriteComponentManager& spcm, hecs::Transform2dComponentManager& tfcm);

int main() {

    auto delay = 0ms;

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

    hecs::SpriteComponent* spcomp;
    hecs::Transform2dComponent* tfcomp;

    Entity background = 0;
    spcomp = spcm.add_component(background,background_img);
    tfcomp = tfcm.add_component(background,0,0);

    //Entity smiley2 = 2;
    //spcomp = spcm.add_component(smiley2, smiley_img);
    //tfcomp = tfcm.add_component(smiley2, background, 150, 100);

    //Entity smiley1 = 1;
    //spcomp = spcm.add_component(smiley1,smiley_img);
    //tfcomp = tfcm.add_component(smiley1,smiley2);

    //int smiley1_gap = 50;
    //tfcm.set_local(smiley1, Coord{ -smiley_img.width - smiley1_gap, -smiley_img.height - smiley1_gap });

    //Entity minion1 = 3;
    //spcomp = spcm.add_component(minion1, green_minion_img);
    //tfcomp = tfcm.add_component(minion1, smiley1);

    //int minion1_gap = 16;
    //tfcm.set_local(minion1, Coord{ -green_minion_img.width - minion1_gap, -green_minion_img.height - minion1_gap });

    //Entity minion2 = 4;
    //spcomp = spcm.add_component(minion2, green_minion_img);
    //tfcomp = tfcm.add_component(minion2, smiley1, smiley_img.width + 1, smiley_img.height + 1);

    //Entity subminion1 = 5;
    //spcomp = spcm.add_component(subminion1, pink_minion_img);
    //tfcomp = tfcm.add_component(subminion1, minion1);

    //int subminion1_gap = 3;
    //tfcm.set_local(subminion1, Coord{ -pink_minion_img.width - subminion1_gap, -pink_minion_img.height - subminion1_gap });

    rr.render(&spcm, &tfcm);
    cc.move_cursor_to(0, 0);
    std::cin.get();

    //rr.draw(smiley_img, Coord{0,0});
    
    /*int count = 0;
    while (true) {
        sleep_for(delay);
        if (count == 4) {
            move_in_orbit(smiley1, smiley1_gap, spcm, tfcm);
            count = 0;
        }
        if (count % 2 == 0) {
            move_in_orbit(minion1, minion1_gap, spcm, tfcm);
        }
        move_in_orbit(subminion1, subminion1_gap, spcm, tfcm);
        rr.render(&spcm, &tfcm);
        ++count;
    }
    cc.move_cursor_to(0, cc.canvas_height() - 1 - 6);*/
    //std::cin.get();
    //sleep_for(delay);

    //tfcm.move(1, Coord{ 170,0 });
    //rr.render(&spcm, &tfcm);
    ////cc.move_cursor_to(0, cc.canvas_height() - 1 - 6);

    //sleep_for(delay);

    //tfcm.move(3, Coord{ 0,smiley_img.height + 1 + green_minion_img.height + 1 });
    //rr.render(&spcm, &tfcm);

    /*Coord current_pos = tfcm.get_component(minion1)->local;
    short speed1 = 1;
    short speed2 = 3;
    
    Coord north{ 0,-speed1 };
    Coord south{ 0,speed1 };
    Coord east{ speed1, 0 };
    Coord west{ -speed1, 0 };

    Entity parent = tfcm.get_entity_by_component_index(tfcm.get_component(minion1)->parent);

    int gap = 1;
    short w_self = spcm.get_component(minion1)->pixel_data.width;
    short h_self = spcm.get_component(minion1)->pixel_data.height;
    short w_parent = spcm.get_component(parent)->pixel_data.width;
    short h_parent = spcm.get_component(parent)->pixel_data.height;

    Coord top_right = Coord{ w_parent + gap, -h_self - gap };
    Coord bottom_right{ w_parent + gap, h_parent + gap };
    Coord bottom_left{ -w_self - gap, h_parent + gap };
    Coord top_left{ -w_self - gap, -h_self - gap };

    tfcm.set_local(minion1, top_left);

    while (true) {
        while (current_pos.x < top_right.x) {
            if (current_pos.x + speed2 > top_right.x) {
                tfcm.move(minion1, { top_right.x - current_pos.x, 0 });
            }
            else tfcm.move(minion1, { speed2, 0 });
            current_pos = tfcm.get_component(minion1)->local;
            tfcm.move(smiley1, { speed1, 0 });

            rr.render(&spcm, &tfcm);
            sleep_for(delay);
        }
        while (current_pos.y < bottom_right.y) {
            if (current_pos.y + speed2 > bottom_right.y) {
                tfcm.move(minion1, { 0, bottom_right.y - current_pos.y });
            }
            else tfcm.move(minion1, { 0,speed2 });
            current_pos = tfcm.get_component(minion1)->local;
            tfcm.move(smiley1, { speed1, 0 });

            rr.render(&spcm, &tfcm);
            sleep_for(delay);
        }
        while (current_pos.x > bottom_left.x) {
            if (current_pos.x - speed2 < bottom_left.x) {
                tfcm.move(minion1, { bottom_left.x - current_pos.x, 0 });
            }
            else tfcm.move(minion1, { -speed2, 0 });
            current_pos = tfcm.get_component(minion1)->local;
            tfcm.move(smiley1, { speed1, 0 });

            rr.render(&spcm, &tfcm);
            sleep_for(delay);
        }
        while (current_pos.y > top_left.y) {
            if (current_pos.y - speed2 < top_left.y) {
                tfcm.move(minion1, { 0, top_left.y - current_pos.y });
            }
            else tfcm.move(minion1, { 0,-speed2 });
            current_pos = tfcm.get_component(minion1)->local;
            tfcm.move(smiley1, { speed1, 0 });

            rr.render(&spcm, &tfcm);
            sleep_for(delay);
        }
    }
*/

    //cc.move_cursor_to(0, cc.canvas_height() - 1 - 6);
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