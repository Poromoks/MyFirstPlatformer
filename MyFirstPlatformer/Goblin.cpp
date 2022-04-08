#include "Goblin.h"

Goblin::Goblin() {
	rect = FloatRect(0, 0, 150, 150);

	Texture texture;
	texture.loadFromFile("textures/Monsters_Creatures_Fantasy/Goblin/Run.png");
	anim.push_back(texture);
	texture.loadFromFile("textures/Monsters_Creatures_Fantasy/Goblin/Idle.png");
	anim.push_back(texture);
	texture.loadFromFile("textures/Monsters_Creatures_Fantasy/Goblin/Attack.png");
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

void Goblin::Update(float time) {
	Move();
	rect.left += dx * time;
	rect.top += dy * time;
	currentFrame += 0.005 * time;

	if (isAttacking && onGround) {
		attackFrame += 0.005 * time;
		sprite.setTexture(anim[anim::attack1]);
		if (attackFrame > 8) {
			attackFrame = 0;
			isAttacking = false;
		}
		if (left == false)
			sprite.setTextureRect(IntRect(150 * int(attackFrame), 0, 150, 150));
		else if (left == true)
			sprite.setTextureRect(IntRect(150 * int(attackFrame) + 150, 0, -150, 150));
	}

	if (dx == 0 && dy == 0 && !isAttacking) {
		sprite.setTexture(anim[anim::idle]);
		if (currentFrame > 4)
			currentFrame = 0;
		if (left == false)
			sprite.setTextureRect(IntRect(150 * int(currentFrame), 0, 150, 150));
		else if (left == true)
			sprite.setTextureRect(IntRect(150 * int(currentFrame) + 150, 0, -150, 150));
	}

	if (dx > 0 || dx < 0) {
		sprite.setTexture(anim[anim::run]);
		if (currentFrame > 8)
			currentFrame = 0;
		if (left == false)
			sprite.setTextureRect(IntRect(150 * int(currentFrame), 0, 150, 150));
		else if (left == true)
			sprite.setTextureRect(IntRect(150 * int(currentFrame) + 150, 0, -150, 150));
	}

	if (rect.top >= ground) {
		rect.top = ground;
		dy = 0;
		onGround = true;
	}

	if (!onGround) {
		dy = dy + 0.0005 * time;
	}

	sprite.setPosition(rect.left, rect.top);
	dx = 0;
}