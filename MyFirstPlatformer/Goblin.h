#pragma once
#include "Player.h"

using namespace sf;

class Goblin : public Player {
public:
	Goblin();
	void Update(float time);
	void Move();

protected:
	float ground = 420;

private:
	std::vector <Texture> anim;
	enum anim {
		run = 0,
		idle = 1,
		attack1 = 2
	};
};