#pragma once
#include "GBase.h"
#include "Sprite.h"

struct SpritePosition {
	Sprite sprite;
	Coord position;
};

struct Scene {
	std::vector<SpritePosition> contents;
	void add(Sprite entity, Coord position);
};