#include "Goblin.h"

Goblin::Goblin() {
	rect = FloatRect(55, 65, 35, 36);
	step = 150;
	x = rect.left;
	y = rect.top;

	texture.loadFromFile("textures/Monsters_Creatures_Fantasy/Goblin/Run.png");
	anim.push_back(texture);
	texture.loadFromFile("textures/Monsters_Creatures_Fantasy/Goblin/Idle.png");
	anim.push_back(texture);
	texture.loadFromFile("textures/Monsters_Creatures_Fantasy/Goblin/Attack.png");
	anim.push_back(texture);
	texture.loadFromFile("textures/Monsters_Creatures_Fantasy/Goblin/Attack2.png");
	anim.push_back(texture);
}

void Goblin::Move() {
	if (Keyboard::isKeyPressed(Keyboard::A)) {
		dx = -0.2;
		left = true;
	}

	if (Keyboard::isKeyPressed(Keyboard::D)) {
		dx = 0.2;
		left = false;
	}

	if (Keyboard::isKeyPressed(Keyboard::W)) {
		if (onGround) {
			dy = -0.4;
			onGround = false;
		}
	}
}

void Goblin::Move(Event& event, Clock& goblinAttackClock) {
	if (event.type == Event::KeyReleased) {
		if (event.key.code == Keyboard::X) {
			goblinAttackClock.restart();
			isAttacking = true;
		}
	}
}

void Goblin::Update(float time) {
	Move();
	rect.left += dx * time;
	Collision(0);
	rect.top += dy * time;
	onGround = false;
	Collision(1);
	currentFrame += 0.005 * time;

	if (isAttacking && onGround) {
		attackFrame += 0.03 * time;
		if (firstAttack) {
			sprite.setTexture(anim[anim::attack1]);
			if (attackFrame > 8) {
				attackFrame = 0;
				firstAttack = false;
			}
		}
		if (!firstAttack) {
			sprite.setTexture(anim[anim::attack2]);
			if (attackFrame > 8) {
				attackFrame = 0;
				isAttacking = false;
				firstAttack = true;
			}
		}
		Animation(attackFrame);
	}

	if (dx == 0 && dy == 0 && !isAttacking) {
		sprite.setTexture(anim[anim::idle]);
		if (currentFrame > 4)
			currentFrame = 0;
		Animation(currentFrame);
	}

	if (dx > 0 || dx < 0) {
		sprite.setTexture(anim[anim::run]);
		if (currentFrame > 8)
			currentFrame = 0;
		Animation(currentFrame);
	}

	if (!onGround) {
		dy = dy + 0.0005 * time;
	}

	sprite.setPosition(rect.left - x, rect.top - y);
	dx = 0;
}