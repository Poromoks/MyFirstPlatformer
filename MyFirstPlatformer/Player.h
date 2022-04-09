#pragma once
#include "SFML/Graphics.hpp"
#include "Map.h"

using namespace sf;

class Player {
public:
	Player();
	virtual void Move();
	virtual void Move(Event& event, Clock& playerAttackClock);
	virtual void Update(float time);
	void Collision(int num);
	Sprite sprite;
	FloatRect rect;
	bool isAttacking = false;

	float dx = 0, dy = 0, currentFrame = 0, attackFrame = 0;
	bool onGround = false, left = false, firstAttack = true;

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