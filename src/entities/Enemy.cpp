#include "engine/Engine.hpp"
#include "entities/Enemy.hpp"
#include "entities/Bullet.hpp"
#include <SDL2/SDL.h>

Enemy::Enemy(Scene* scene, int x, int y) : Sprite("./assets/enemy.png", 0, 32, 40) {
	position.setX(x);
	position.setY(y);
	currentScene = scene;
}

void Enemy::update(double delta){

	timeSinceShot += delta;

	// limit the characters movement to the screen
	if(position.getX() < 0){
		position.setX(0);
	}

	if(position.getY() < 0){
		position.setY(0);
	}

	if(position.getX() + 32 > 1024){
		position.setX(1024 - 32);
	}

	if(position.getY() + 40 > 768){
		position.setY(768 - 40);
	}
}

void Enemy::createBullet(int velX, int velY){
	// Shoot the gun
	if(timeSinceShot > fireRate){
		Bullet* b = new Bullet(currentScene, position.getX() + (rect->w / 2), position.getY() + (rect->h / 2), velX, velY);
		currentScene->createUpdateable(b);
		currentScene->createDrawable(b);
		timeSinceShot = 0;
	}
}
