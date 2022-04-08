#pragma once
#include "SFML/Graphics.hpp"
#include "Map.h"

using namespace sf;

class Player {
public:
	Player();
	void Move();
	void Update(float time);
	/*void Collision(int dir); */
	Sprite sprite;
	FloatRect rect;
	bool isAttacking = false;

	float dx = 0.1, dy = 0.1, currentFrame = 0, attackFrame = 0, ground = 400;
	bool onGround = false, left = false;

private:
	std::vector <Texture> anim;
	enum anim {
		run = 0,
		jump = 1,
		fall = 2,
		idle = 3,
		attack1 = 4,
		attack2 = 5
	};
};