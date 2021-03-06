#include "engine/Engine.hpp"
#include "entities/Player.hpp"
#include "entities/Bullet.hpp"
#include "engine/AssetLoader.hpp"
#include "entities/weapons/MachineGun.hpp"
#include "entities/weapons/MultiDirectionGun.hpp"
#include "entities/weapons/TrippleShotGun.hpp"
#include "entities/weapons/BubbleGun.hpp"
#include "entities/items/WeaponItem.hpp"
#include <SDL2/SDL.h>
#include "entities/weapons/Cannon.hpp"

Player::Player(Scene* scene) : Sprite(AssetLoader::tilesheet, AssetLoader::player, 4, .2, 0, 24, 34) {
	
	position.setX(500);
	position.setY(700);

	velocity.setX(0);
	velocity.setY(0);
	velocity.setZ(0);
	
	currentScene = scene;

	setType("Player");

	// Give the player a basic gun
	currentWeapon = new BaseWeapon(scene, false);
	auto body = currentScene->getCollision()->addObject(this, FRIENDLY, ENEMY);
    this->setBody(body);

	//heartIcons = new Sprite*[maxHealth % 2];
	for(int i = 0; i < maxHealth / 2; i++){
		heartIcons.push_back(new Sprite(AssetLoader::tilesheet, AssetLoader::hearts, 3, 0, 0, 26, 20));
		heartIcons[i]->setPosition(35 * i + 20, 20);
	}

	curWeaponName = new Sprite(currentWeapon->weaponName, "./assets/stick.ttf", 0, 30);
	curWeaponName->setPosition(20, 725);
}

void Player::addHeart() {
	maxHealth += 2;
	health += 2;
	auto newHeart = new Sprite(AssetLoader::tilesheet, AssetLoader::hearts, 3, 0, 0, 26, 20);
	newHeart->setPosition((maxHealth / 2 - 1) * 35 + 20, 20);
	heartIcons.push_back(newHeart);
}

Player::~Player(){
}

void Player::setWeapon(BaseWeapon* weapon) {
  	// Drop the old one
	if(currentWeapon != nullptr) {
		auto item = new WeaponItem(currentScene, position.getX() + width / 2, position.getY() + height / 2, currentWeapon);
		((Item*)item)->spawn();
	}

	currentWeapon = weapon;
}

void Player::update(double delta){

	if(hitDoor){
		body->SetTransform(b2Vec2(500 / METERSTOPIXELS, 700 / METERSTOPIXELS), body->GetAngle());
		hitDoor = false;
		return;
	}

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
		setWeapon((BaseWeapon*)new MachineGun(currentScene, false));
	}
	if(keystate[SDL_SCANCODE_2]){
		setWeapon(currentWeapon = (BaseWeapon*)new MultiDirectionGun(currentScene, false));
	}
	if(keystate[SDL_SCANCODE_3]){
		setWeapon(currentWeapon = (BaseWeapon*)new TrippleShotGun(currentScene, false));
	}
	if(keystate[SDL_SCANCODE_4]){
		setWeapon(currentWeapon = (BaseWeapon*)new BubbleGun(currentScene, false));
	}
	if(keystate[SDL_SCANCODE_5]){
		setWeapon(currentWeapon = (BaseWeapon*)new Cannon(currentScene, false));
	}
	if(keystate[SDL_SCANCODE_KP_PLUS]){
		currentScene->spawner->currentWave = 20;
	}
	if(keystate[SDL_SCANCODE_0]){
		setWeapon(currentWeapon = new BaseWeapon(currentScene, false));
	}

	//Shooting
	if(keystate[SDL_SCANCODE_UP]){
		if(currentWeapon->hasRecoil())
			body->ApplyForceToCenter(b2Vec2(0, maxSpeed * 12), true);
		currentWeapon->shoot(Up, body->GetPosition().x * METERSTOPIXELS, body->GetPosition().y * METERSTOPIXELS);
	}else if(keystate[SDL_SCANCODE_DOWN]){
		if(currentWeapon->hasRecoil())
			body->ApplyForceToCenter(b2Vec2(0, -maxSpeed * 12), true);
		currentWeapon->shoot(Down, body->GetPosition().x * METERSTOPIXELS, body->GetPosition().y * METERSTOPIXELS);
	}else if(keystate[SDL_SCANCODE_LEFT]){
		if(currentWeapon->hasRecoil())
			body->ApplyForceToCenter(b2Vec2(maxSpeed * 12, 0), true);
		currentWeapon->shoot(Left, body->GetPosition().x * METERSTOPIXELS, body->GetPosition().y * METERSTOPIXELS);
	}else if(keystate[SDL_SCANCODE_RIGHT]){
		if(currentWeapon->hasRecoil())
			body->ApplyForceToCenter(b2Vec2(-maxSpeed * 12, 0), true);
		currentWeapon->shoot(Right, body->GetPosition().x * METERSTOPIXELS, body->GetPosition().y * METERSTOPIXELS);
	}

	auto moveForce = b2Vec2(velocity.getX(), velocity.getY());
	moveForce.Normalize();
	auto moveSpeed = b2Vec2((velocity.getX() * abs(moveForce.x)) * delta, (velocity.getY() * abs(moveForce.y)) * delta);
	body->SetLinearVelocity(moveSpeed);
	body->SetLinearDamping(friction);

	if(health <= 0){
		// Death Code
		currentScene->spawner->resetGame();
		resetToDefaults();
		currentScene->timer->stop();
		return;
	}

	currentScene->SetPlayerLocation(position.getX(), position.getY());

	// Update the HUD
	auto allocatedHp = 0;
	for(int i = 0; i < maxHealth / 2; i++){
		// Set frame based on HP
		auto hpLeftToAllocate = health - allocatedHp;
		if(hpLeftToAllocate == 0){
			heartIcons[i]->setAnimationFrame(2);
		}else if(hpLeftToAllocate == 1){
			heartIcons[i]->setAnimationFrame(1);
			allocatedHp += 1;
		}else{
			heartIcons[i]->setAnimationFrame(0);
			allocatedHp += 2;
		}

		heartIcons[i]->update(delta);
	}

	curWeaponName->setText(currentWeapon->weaponName);
	curWeaponName->update(delta);
}

void Player::draw() {
	Sprite::draw();

	// Draw the HUD
	for(int i = 0; i < maxHealth / 2; i++){
		heartIcons[i]->draw();
	}

	curWeaponName->draw();
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

void Player::giveHealth(int hp){
	health += hp;
	if(health > maxHealth){
		health = maxHealth;
	}
}

void Player::playerHitDoor() {
	hitDoor = true;
}

void Player::resetToDefaults() {
	currentWeapon = new BaseWeapon(currentScene, false);
	body->SetTransform(b2Vec2(500 / METERSTOPIXELS, 700 / METERSTOPIXELS), body->GetAngle());
	maxHealth = 6;
	health = maxHealth;
}
