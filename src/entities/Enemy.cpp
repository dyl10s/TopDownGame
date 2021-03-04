#include "engine/Engine.hpp"
#include "entities/Enemy.hpp"
#include "entities/Bullet.hpp"
#include <SDL2/SDL.h>

Enemy::Enemy(Scene* scene, int x, int y) : Sprite("./assets/enemy.png", 0, 22, 36) {
	position.setX(x);
	position.setY(y);
	currentScene = scene;

	auto body = currentScene->getCollision()->addObject(this, ENEMY, FRIENDLY);
    this->setBody(body);
}

void Enemy::update(double delta){
	timeSinceShot += delta;
	body->SetLinearDamping(friction);
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
