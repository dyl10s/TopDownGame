#include "engine/Engine.hpp"
#include "entities/Player.hpp"
#include "entities/Bullet.hpp"
#include "entities/weapons/MachineGun.hpp"
#include "entities/weapons/MultiDirectionGun.hpp"
#include <SDL2/SDL.h>

Player::Player(Scene* scene) : Sprite("./assets/player.png", 0, 32, 40) {
	velocity.setX(0);
	velocity.setY(0);
	velocity.setZ(0);
	currentScene = scene;

	// Give the player a basic gun
	currentWeapon = new BaseWeapon(scene);
}

Player::~Player(){
	delete currentWeapon;
}

void Player::update(double delta){
	/* 
		This meathod of keyboard input is much quicker and responsive then 
		the way the engine has it implimented
	*/
	auto keystate = SDL_GetKeyboardState(NULL);

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
		currentWeapon = (BaseWeapon*)new MachineGun(currentScene);
	}
	if(keystate[SDL_SCANCODE_2]){
		currentWeapon = (BaseWeapon*)new MultiDirectionGun(currentScene);
	}
	if(keystate[SDL_SCANCODE_0]){
		currentWeapon = new BaseWeapon(currentScene);
	}

	//Shooting
	if(keystate[SDL_SCANCODE_UP]){
		currentWeapon->shoot(Up, position.getX() + 16, position.getY() + 20);
	}else if(keystate[SDL_SCANCODE_DOWN]){
		currentWeapon->shoot(Down, position.getX() + 16, position.getY() + 20);
	}else if(keystate[SDL_SCANCODE_LEFT]){
		currentWeapon->shoot(Left, position.getX() + 16, position.getY() + 20);
	}else if(keystate[SDL_SCANCODE_RIGHT]){
		currentWeapon->shoot(Right, position.getX() + 16, position.getY() + 20);
	}

	position.setX(position.getX() + velocity.getX() * delta);
	position.setY(position.getY() + velocity.getY() * delta);

	// normalize the velocities so we cant move fast on diagonals 
	double totalVelocity = abs(velocity.getX()) + abs(velocity.getY());
	if(totalVelocity != 0){
		velocity.setX((abs(velocity.getX()) / totalVelocity) * velocity.getX());
		velocity.setY((abs(velocity.getY()) / totalVelocity) * velocity.getY());
	}

	// update the player position
	if(position.getX() > 1024-rect->w || position.getX() < 0){
		velocity.setX(- velocity.getX());
	}

	if(position.getY() > 768-rect->h || position.getY() < 0){
		velocity.setY(- velocity.getY());
	}


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

	// Slow down the player
	if(velocity.getX() > 0) {
		velocity.setX(velocity.getX() - std::min(friction, abs(velocity.getX())));
	}else if(velocity.getX() < 0){
		velocity.setX(velocity.getX() + std::min(friction, abs(velocity.getX())));
	}

	if(velocity.getY() > 0) {
		velocity.setY(velocity.getY() - std::min(friction, abs(velocity.getY())));
	}else if(velocity.getY() < 0){
		velocity.setY(velocity.getY() + std::min(friction, abs(velocity.getY())));
	}
}

void Player::left(double delta){
	if(velocity.getX() > -maxSpeed){
		velocity.setX(std::max(velocity.getX() - acceleration, -maxSpeed));
	}
}
void Player::right(double delta){
	if(velocity.getX() < maxSpeed){
		velocity.setX(std::min(velocity.getX() + acceleration, maxSpeed));
	}
}
void Player::up(double delta){
	if(velocity.getY() > -maxSpeed ){
		velocity.setY(std::max(velocity.getY() - acceleration, -maxSpeed));
	}
}
void Player::down(double delta){
	if(velocity.getY() < maxSpeed ){
		velocity.setY(std::min(velocity.getY() + acceleration, maxSpeed));
	}
}
