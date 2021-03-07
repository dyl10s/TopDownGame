#include "engine/Engine.hpp"
#include "engine/AssetLoader.hpp"
#include "entities/enemies/BaseEnemy.hpp"
#include "entities/weapons/NoobEnemyGun.hpp"
#include "entities/Bullet.hpp"
#include <SDL2/SDL.h>
#include <time.h>
#include <stdlib.h>

BaseEnemy::BaseEnemy(Scene* scene, int x, int y) : Sprite(AssetLoader::tilesheet, AssetLoader::basicEnemy, 3, .2, 0, 22, 36) {
	position.setX(x);
	position.setY(y);
	currentScene = scene;
	if(currentWeapon == nullptr){
		currentWeapon = (BaseWeapon*)new NoobEnemyGun(scene, true);
	}
	setType("Enemy");

	auto body = currentScene->getCollision()->addObject(this, ENEMY, FRIENDLY | ENEMY);
    this->setBody(body);

	srand(time(NULL));
}

BaseEnemy::~BaseEnemy() {
}

void BaseEnemy::update(double delta){

	// Standard code for enemies
	// ----------------------------------
	Sprite::update(delta);

	body->SetLinearDamping(friction);

	if(health <= 0){
		currentScene->removeObject(this);
	}
	// ----------------------------------

	timeSinceAction += delta;

	// Randomize move direction
	if(timeSinceAction > 1) {
		auto rngMoveDir = rand() % 4 + 1;
		if(rngMoveDir == 1){
			velocity.setX(-maxSpeed);
			if(position.getX() < 100){
				velocity.setX(maxSpeed);
			}
			velocity.setY(0);
		}else if(rngMoveDir == 2){
			velocity.setX(maxSpeed);
			if(position.getX() > 1000){
				velocity.setX(-maxSpeed);
			}
			velocity.setY(0);
		}else if(rngMoveDir == 3){
			velocity.setY(-maxSpeed);
			if(position.getY() < 100){
				velocity.setY(maxSpeed);
			}
			velocity.setX(0);
		}else if(rngMoveDir == 4){
			velocity.setY(maxSpeed);
			if(position.getY() > 1000){
				velocity.setY(-maxSpeed);
			}
			velocity.setX(0);
		}

		timeSinceAction = 0;
	}

	body->SetLinearVelocity(b2Vec2(velocity.getX() * delta, velocity.getY() * delta));

	// Randomize shoot direction
	auto shootDir = rand() % 4 + 1;
	if(shootDir == 1){
		currentWeapon->shoot(Left, position.getX() + (width / 2.0), position.getY() + (height / 2.0));
	}else if(shootDir == 2){
		currentWeapon->shoot(Right, position.getX() + (width / 2.0), position.getY() + (height / 2.0));
	}else if(shootDir == 3){
		currentWeapon->shoot(Up, position.getX() + (width / 2.0), position.getY() + (height / 2.0));
	}else if(shootDir == 4){
		currentWeapon->shoot(Down, position.getX() + (width / 2.0), position.getY() + (height / 2.0));
	}
}

void BaseEnemy::takeDamage(int damage){
	health -= damage;
}
