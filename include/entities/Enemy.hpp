#ifndef			__HPP__ENEMY__
#define			__HPP__ENEMY__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "engine/Interfaces.hpp"
#include "engine/Utility.hpp"
#include "engine/Sprite.hpp"
#include "engine/Scene.hpp"
#include "entities/weapons/BaseWeapon.hpp"

class Enemy : public Sprite {
	public:
		Enemy(Scene* scene, int x, int y);
		~Enemy();
		void update(double delta);
		void takeDamage(int damage);
	private:
		Vector3 velocity;
		double maxSpeed = 200;
		double acceleration = 200;
		double friction = 100;
		int health = 4;
		BaseWeapon* currentWeapon;
		Scene* currentScene;

};

#endif
