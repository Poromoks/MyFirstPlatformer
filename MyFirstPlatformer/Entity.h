#pragma once
#include "SFML/Graphics.hpp"
#include "Map.h"

using namespace sf;

class Entity {
public:
	Entity() = default;
	virtual void Animation(float& currentFrame) = 0;
	virtual void Collision(int num) = 0;
	Texture texture;
	Sprite sprite;
	FloatRect rect;

protected:
	int x = 0, y = 0, step = 0;
	float dx = 0, dy = 0, currentFrame = 0, attackFrame = 0;
	bool onGround = false, left = false, isAttacking = false, firstAttack = true;
};