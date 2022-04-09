#include "Player.h"

Player::Player() {
	rect = FloatRect(75, 70, 40, 53);

	Texture texture;
	texture.loadFromFile("textures/Martial Hero/Sprites/Run.png");
	anim.push_back(texture);
	texture.loadFromFile("textures/Martial Hero/Sprites/Jump.png");
	anim.push_back(texture);
	texture.loadFromFile("textures/Martial Hero/Sprites/Fall.png");
	anim.push_back(texture);
	texture.loadFromFile("textures/Martial Hero/Sprites/Idle.png");
	anim.push_back(texture);
	texture.loadFromFile("textures/Martial Hero/Sprites/Attack1.png");
	anim.push_back(texture);
	texture.loadFromFile("textures/Martial Hero/Sprites/Attack2.png");
	anim.push_back(texture);
}

/*void Player::Collision(int dir) {
	for (int i = rect.top / 32; i < (rect.top + rect.height) / 32; i++)
		for (int j = rect.left / 32; j < (rect.left + rect.width) / 32; j++)
			if (TileMap[i][j] == 'B') {
				if (dx > 0 && dir == 0)
					rect.left = j * 32 - rect.width;
				if (dx < 0 && dir == 0)
					rect.left = j * 32 + 32;
				if (dy > 0 && dir == 0) {
					rect.top = i * 32 - rect.height;
					dy = 0;
					onGround = true;
				}
				if (dy < 0 && dir == 0) {
					rect.top = i * 32 + 32;
					dy = 0;
				}
			}
}*/

void Player::Move() {
	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		dx = -0.2;
		left = true;
	}

	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		dx = 0.2;
		left = false;
	}

	if (Keyboard::isKeyPressed(Keyboard::Up)) {
		if (onGround) {
			dy = -0.4;
			onGround = false;
		}
	}
}

void Player::Move(Event& event, Clock& playerAttackClock) {
	if (event.type == Event::KeyReleased) {
		if (event.key.code == Keyboard::Z) {
			playerAttackClock.restart();
			isAttacking = true;
		}
	}
}

void Player::Collision(int num) {

	for (int i = rect.top / 32; i < (rect.top + rect.height) / 32; i++)
		for (int j = rect.left / 32; j < (rect.left + rect.width) / 32; j++) {
			if (TileMap[i][j] == 'B') {
				if (dy > 0 && num == 1) {
					rect.top = i * 32 - rect.height;
					dy = 0;
					onGround = true;
				}
				if (dy < 0 && num == 1) {
					rect.top = i * 32 + 32;
					dy = 0;
				}
				if (dx > 0 && num == 0) {
					rect.left = j * 32 - rect.width;
				}
				if (dx < 0 && num == 0) {
					rect.left = j * 32 + 32;
				}
			}
		}

}

void Player::Update(float time) {
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
			if (attackFrame > 6) {
				attackFrame = 0;
				firstAttack = false;
			}
		}

		if (!firstAttack) {
			sprite.setTexture(anim[anim::attack2]);
			if (attackFrame > 6) {
				attackFrame = 0;
				isAttacking = false;
				firstAttack = true;
			}
		}

		if (left == false)
		sprite.setTextureRect(IntRect(200 * int(attackFrame), 0, 200, 200));
		else if (left == true)
			sprite.setTextureRect(IntRect(200 * int(attackFrame) + 200, 0, -200, 200));
	}

	if (dx == 0 && dy == 0 && !isAttacking) {
		sprite.setTexture(anim[anim::idle]);
		if (currentFrame > 8)
			currentFrame = 0;
		if (left == false)
		sprite.setTextureRect(IntRect(200 * int(currentFrame), 0, 200, 200));
		else if (left == true)
			sprite.setTextureRect(IntRect(200 * int(currentFrame) + 200, 0, -200, 200));
	}

	if (dx > 0 || dx < 0) {
		sprite.setTexture(anim[anim::run]);
		if (currentFrame > 8)
			currentFrame = 0;
		if (left == false)
		sprite.setTextureRect(IntRect(200 * int(currentFrame), 0, 200, 200));
		else if (left == true)
			sprite.setTextureRect(IntRect(200 * int(currentFrame) + 200, 0, -200, 200));
	}

	/*if (rect.top + rect.height >= ground) {
		rect.top = ground - rect.height;
		dy = 0;
		onGround = true;
	}*/

	if (!onGround) {
		if (dy < 0) {
			sprite.setTexture(anim[anim::jump]);
			if (dx > 0 || dx < 0 || dx == 0) {
				if (currentFrame > 2)
					currentFrame = 0;
				if (left == false)
					sprite.setTextureRect(IntRect(200 * int(currentFrame), 0, 200, 200));
				else if (left == true)
					sprite.setTextureRect(IntRect(200 * int(currentFrame) + 200, 0, -200, 200));
			}
		}
		else if (dy > 0) {
			sprite.setTexture(anim[anim::fall]);
			if (dx > 0 || dx < 0 || dx == 0) {
				if (currentFrame > 2)
					currentFrame = 0;
				if (left == false)
					sprite.setTextureRect(IntRect(200 * int(currentFrame), 0, 200, 200));
				else if (left == true)
					sprite.setTextureRect(IntRect(200 * int(currentFrame) + 200, 0, -200, 200));
			}
		}
		dy += 0.0005 * time;
	}
	sprite.setPosition(rect.left - 75, rect.top - 70);
	dx = 0;
}