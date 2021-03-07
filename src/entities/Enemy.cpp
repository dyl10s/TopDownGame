#include "engine/Engine.hpp"
#include "engine/AssetLoader.hpp"
#include "entities/Enemy.hpp"
#include "entities/Bullet.hpp"
#include <SDL2/SDL.h>

Enemy::Enemy(Scene* scene, int x, int y) : Sprite(AssetLoader::tilesheet, AssetLoader::basicEnemy, 3, .2, 0, 22, 36) {
	position.setX(x);
	position.setY(y);
	currentScene = scene;
	currentWeapon = new BaseWeapon(scene, true);
	setType("Enemy");

	auto body = currentScene->getCollision()->addObject(this, ENEMY, FRIENDLY);
    this->setBody(body);
}

Enemy::~Enemy() {
}

void Enemy::update(double delta){
	Sprite::update(delta);

	body->SetLinearDamping(friction);

	if(health <= 0){
		currentScene->removeObject(this);
	}

	currentWeapon->shoot(Left, position.getX(), position.getY());
}

void Enemy::takeDamage(int damage){
	health -= damage;
}
