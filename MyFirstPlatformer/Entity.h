#pragma once
#include "SFML/Graphics.hpp"
#include "Map.h"

using namespace sf;

class Entity {
public:
	Entity() = default;
	void Animation(float& currentFrame);
	void Collision(int num);
	Texture texture;
	Sprite sprite;
	FloatRect rect;

protected:
	int x = 0, y = 0, step = 0;
	float dx = 0, dy = 0, currentFrame = 0, attackFrame = 0;
	bool onGround = false, left = false, firstAttack = true, isAttacking = false;
};