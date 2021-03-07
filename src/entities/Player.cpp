#include "engine/Engine.hpp"
#include "entities/Player.hpp"
#include "entities/Bullet.hpp"
#include "engine/AssetLoader.hpp"
#include "entities/weapons/MachineGun.hpp"
#include "entities/weapons/MultiDirectionGun.hpp"
#include <SDL2/SDL.h>

Player::Player(Scene* scene) : Sprite(AssetLoader::tilesheet, AssetLoader::player, 4, .2, 0, 24, 34) {
	velocity.setX(0);
	velocity.setY(0);
	velocity.setZ(0);
	position.setX(100);
	position.setY(100);
	currentScene = scene;

	setType("Player");

	// Give the player a basic gun
	currentWeapon = new BaseWeapon(scene, false);
	auto body = currentScene->getCollision()->addObject(this, FRIENDLY, ENEMY);
    this->setBody(body);
}

Player::~Player(){
}

void Player::update(double delta){
	Sprite::update(delta);
	/* 
		This meathod of keyboard input is much quicker and responsive then 
		the way the engine has it implimented
	*/
	auto keystate = SDL_GetKeyboardState(NULL);

	velocity = Vector3(0, 0);

	// Movement
	if(keystate[SDL_SCANCODE_W]){
		up(delta);
	}
	if(keystate[SDL_SCANCODE_A]){
		left(delta);
	}
	if(keystate[SDL_SCANCODE_S]){
		down(delta);
	}
	if(keystate[SDL_SCANCODE_D]){
		right(delta);
	}

	// Testing Keys
	if(keystate[SDL_SCANCODE_1]){
		// I think this causes a memory leak because we never delete the old weapon. However the engine crashes if we do
		// change this because we are itterating over the updatables
		currentWeapon = (BaseWeapon*)new MachineGun(currentScene, false);
	}
	if(keystate[SDL_SCANCODE_2]){
		currentWeapon = (BaseWeapon*)new MultiDirectionGun(currentScene, false);
	}
	if(keystate[SDL_SCANCODE_0]){
		currentWeapon = new BaseWeapon(currentScene, false);
	}

	//Shooting
	if(keystate[SDL_SCANCODE_UP]){
		currentWeapon->shoot(Up, body->GetPosition().x * METERSTOPIXELS, body->GetPosition().y * METERSTOPIXELS);
	}else if(keystate[SDL_SCANCODE_DOWN]){
		currentWeapon->shoot(Down, body->GetPosition().x * METERSTOPIXELS, body->GetPosition().y * METERSTOPIXELS);
	}else if(keystate[SDL_SCANCODE_LEFT]){
		currentWeapon->shoot(Left, body->GetPosition().x * METERSTOPIXELS, body->GetPosition().y * METERSTOPIXELS);
	}else if(keystate[SDL_SCANCODE_RIGHT]){
		currentWeapon->shoot(Right, body->GetPosition().x * METERSTOPIXELS, body->GetPosition().y * METERSTOPIXELS);
	}

	auto moveForce = b2Vec2(velocity.getX(), velocity.getY());
	moveForce.Normalize();
	auto moveSpeed = b2Vec2((velocity.getX() * abs(moveForce.x)) * delta, (velocity.getY() * abs(moveForce.y)) * delta);
	body->SetLinearVelocity(moveSpeed);
	body->SetLinearDamping(friction);

	if(health <= 0){
		currentScene->removeObject(this);
	}
}

void Player::left(double delta){
	if(velocity.getX() > -maxSpeed){
		velocity.setX(std::max(body->GetLinearVelocity().x - acceleration, -maxSpeed));
	}
}
void Player::right(double delta){
	if(velocity.getX() < maxSpeed){
		velocity.setX(std::min(body->GetLinearVelocity().x + acceleration, maxSpeed));
	}
}
void Player::up(double delta){
	if(velocity.getY() > -maxSpeed ){
		velocity.setY(std::max(body->GetLinearVelocity().y - acceleration, -maxSpeed));
	}
}
void Player::down(double delta){
	if(velocity.getY() < maxSpeed ){
		velocity.setY(std::min(body->GetLinearVelocity().y + acceleration, maxSpeed));
	}
}

void Player::takeDamage(int damage){
	health -= damage;
}
