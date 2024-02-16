#pragma once
#include "Scene.h"

void Scene::add(Sprite entity, Coord position) {
	SpritePosition ep{entity,position};
	/*ep.entity = &entity;
	ep.position = position;*/
	contents.push_back(ep);
}


