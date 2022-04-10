#pragma once
#include "Player.h"

using namespace sf;

class Goblin : public Player {
public:
	Goblin();
	void Move() override;
	void Move(Event& event, Clock& goblinAttackClock) override;
	void Update(float time) override;

private:
	std::vector <Texture> anim;
	enum anim {
		run = 0,
		idle = 1,
		attack1 = 2,
		attack2 = 3
	};
};