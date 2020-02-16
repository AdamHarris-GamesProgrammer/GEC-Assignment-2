#pragma once
#ifndef _COLLISIONS_H
#define _COLLISIONS_H

#include "Commons.h"
#include "Character.h"

class Character;

class Collisions {
public:
	~Collisions();
	static Collisions* Instance();

	bool Circle(Circle2D circle1, Circle2D circle2);
	bool Circle(Character* character1, Character* character2);
	bool Box(SDL_Rect& rect1, SDL_Rect& rect2);

private:
	Collisions();

	static Collisions* mInstance;
};

#endif