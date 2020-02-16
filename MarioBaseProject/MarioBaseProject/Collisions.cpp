#include "Collisions.h"
#include "Character.h"

Collisions* Collisions::mInstance = NULL;

Collisions::Collisions() {}

Collisions::~Collisions() {
	mInstance = NULL;
}

Collisions* Collisions::Instance() {
	if (!mInstance) {
		mInstance = new Collisions;
	}
	return mInstance;
}

bool Collisions::Circle(Circle2D circle1, Circle2D circle2)
{
	Vector2D vec = Vector2D((circle1.position.x - circle2.position.x),
		(circle1.position.y - circle2.position.y));

	double distance = sqrt((vec.x * vec.x) + (vec.y * vec.y));

	double combinedDistance = (circle1.radius + circle2.radius);

	return distance < combinedDistance;
}

bool Collisions::Circle(Character* character1, Character* character2)
{
	Vector2D vec = Vector2D((character1->GetPosition().x - character2->GetPosition().x),
							(character1->GetPosition().y - character2->GetPosition().y));

	double distance = sqrt((vec.x * vec.x) + (vec.y * vec.y));

	double combinedDistance = (character1->GetCollisionRadius() + character2->GetCollisionRadius());

	return distance < combinedDistance;
}

bool Collisions::Box(SDL_Rect& a, SDL_Rect& b) {
	int left1 = a.x;
	int right1 = a.x + a.w;
	int top1 = a.y;
	int bottom1 = a.y + a.h;

	int left2 = b.x;
	int right2 = b.x + b.w;
	int top2 = b.y;
	int bottom2 = b.y + b.h;


	if ((bottom1 > top2) && (top1 < bottom2) && (right1 > left2) && (left1 < right2)) { //if there is a overlapping side
		return true;
	}
	else {
		return false;
	}
}