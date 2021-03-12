#ifndef			__HPP__PLAYER__
#define			__HPP__PLAYER__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "engine/Interfaces.hpp"
#include "engine/Utility.hpp"
#include "engine/Sprite.hpp"
#include "engine/Scene.hpp"
#include "entities/weapons/BaseWeapon.hpp"
#include <vector>

class Player : public Sprite {
	public:
		Player(Scene* scene);
		~Player();
		void draw();
		void update(double delta);
		void left(double delta);
		void right(double delta);
		void up(double delta);
		void down(double delta);
		void takeDamage(int damage);
		void giveHealth(int hp);
		void playerHitDoor();
		void setWeapon(BaseWeapon* weapon);
		void resetToDefaults();
		void addHeart();
	private:
		void createBullet(int xVel, int yVel);
		Vector3 velocity;
		double maxSpeed = 750;
		bool hitDoor = false;
		double acceleration = 750;
		double friction = 100;
		int health = 6;
		int maxHealth = 6;
		BaseWeapon* currentWeapon;
		Scene* currentScene;
		std::vector<Sprite*> heartIcons;

};

#endif
