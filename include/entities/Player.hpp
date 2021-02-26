#ifndef			__HPP__PLAYER__
#define			__HPP__PLAYER__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "engine/Interfaces.hpp"
#include "engine/Utility.hpp"
#include "engine/Sprite.hpp"
#include "engine/Scene.hpp"
#include "entities/weapons/BaseWeapon.hpp"

class Player : public Sprite {
	public:
		Player(Scene* scene);
		~Player();
		void update(double delta);
		void left(double delta);
		void right(double delta);
		void up(double delta);
		void down(double delta);
	private:
		void createBullet(int xVel, int yVel);
		Vector3 velocity;
		double maxSpeed = 200;
		double acceleration = 200;
		double friction = 100;
		BaseWeapon* currentWeapon;
		Scene* currentScene;

};

#endif
