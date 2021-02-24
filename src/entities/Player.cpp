#include "engine/Engine.hpp"
#include "entities/Player.hpp"
#include "entities/Bullet.hpp"
#include <SDL2/SDL.h>

Player::Player(Scene* scene) : Sprite("./assets/player.png", 0, 32, 40) {
	velocity.setX(0);
	velocity.setY(0);
	velocity.setZ(0);
	currentScene = scene;
}

void Player::update(double delta){

	timeSinceShot += delta;

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

	//Shooting
	if(keystate[SDL_SCANCODE_UP]){
		createBullet(0, -shootSpeed);
	}else if(keystate[SDL_SCANCODE_DOWN]){
		createBullet(0, shootSpeed);
	}else if(keystate[SDL_SCANCODE_LEFT]){
		createBullet(-shootSpeed, 0);
	}else if(keystate[SDL_SCANCODE_RIGHT]){
		createBullet(shootSpeed, 0);
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

void Player::createBullet(int velX, int velY){
	// Shoot the gun
	if(timeSinceShot > fireRate){
		Bullet* b = new Bullet(currentScene, position.getX() + (rect->w / 2), position.getY() + (rect->h / 2), velX, velY);
		currentScene->createUpdateable(b);
		currentScene->createDrawable(b);
		timeSinceShot = 0;
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
