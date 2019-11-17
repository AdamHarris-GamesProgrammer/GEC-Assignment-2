#pragma once

struct Vector2D { //the vector2 struct is used to represent 2d coordinates in the game world
	float x;
	float y;

	Vector2D() { //constructor which takes no values will set x and y to 0
		x = 0.0f;
		y = 0.0f;
	}

	Vector2D(float xValue, float yValue) { //constructor that takes 2 values and sets x and y accordingly
		x = xValue;
		y = yValue;
	}
};

struct Rect2D {
	float x;
	float y;

	float width;
	float height;

	Rect2D(float xValue, float yValue, float widthValue, float heightValue) {
		x = xValue;
		y = yValue;
		width = widthValue;
		height = heightValue;
	}
};

struct Circle2D {
	Vector2D position;

	float radius;

	Circle2D(Vector2D vec, float radiusValue) {
		position = vec;
		radius = radiusValue;
	}
};
 
enum SCREENS { //this enum holds a list of the screens available in the game //a screen is a game level
	SCREEN_INTRO = 0,
	SCREEN_MENU,
	SCREEN_LEVEL1,
	SCREEN_LEVEL2,
	SCREEN_GAMEOVER,
	SCREEN_HIGHSCORES
};

enum FACING {
	FACING_LEFT = 0,
	FACING_RIGHT
};

enum CHARACTER_STATE {
	ALIVE = 0,
	DEAD
};

const int MovementSpeed = 3;

