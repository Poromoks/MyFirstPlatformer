#pragma once
#include "Entity.h"

using namespace sf;

class Player : public Entity {
public:
	Player();
	virtual void Move();
	virtual void Move(Event& event, Clock& playerAttackClock);
	virtual void Update(float time);

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