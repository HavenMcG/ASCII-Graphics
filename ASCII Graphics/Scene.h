#pragma once
#include <vector>
#include "GBase.h"
#include <string>
#include "Sprite.h"

using PixelData = std::vector<std::vector<Color>>;
using RenderCode = std::vector<std::string>;

struct SpritePosition {
	Sprite sprite;
	Coord position;
};

template <typename T>
struct SceneNode {
	T renderable_object;
	Coord position;
};

struct Scene {
	std::vector<SpritePosition> contents;
	void add(Sprite entity, Coord position);
	void draw();
	void move(int i, Coord new_pos);
};