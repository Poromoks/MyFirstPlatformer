#include "Entity.h"

void Entity::Animation(float& currentFrame) {
	if (left == false)
		sprite.setTextureRect(IntRect(step * int(currentFrame), 0, step, step));
	else if (left == true)
		sprite.setTextureRect(IntRect(step * int(currentFrame) + step, 0, -step, step));
}

void Entity::Collision(int num) {
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