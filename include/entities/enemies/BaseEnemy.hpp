#ifndef			__HPP__ENEMY__
#define			__HPP__ENEMY__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "engine/Interfaces.hpp"
#include "engine/Utility.hpp"
#include "engine/Sprite.hpp"
#include "engine/Scene.hpp"
#include "entities/weapons/BaseWeapon.hpp"

class BaseEnemy : public Sprite {
	public:
		BaseEnemy(Scene* scene, int x, int y);
		BaseEnemy(Scene* scene, int x, int y, int w, int h, SDL_Rect** sprites, int frames = 3);
		~BaseEnemy();
		virtual void update(double delta);
		virtual void takeDamage(int damage);
	private:
		void setupEnemy(Scene* scene, int x, int y);
		double timeSinceAction = 0;
		Direction moveDir = Up;
	protected:
		Scene* currentScene;
		void standardUpdate(double delta);
		Vector3 velocity;
		double maxSpeed = 200;
		double acceleration = 200;
		double friction = 100;
		int health = 4;
		BaseWeapon* currentWeapon = nullptr;

};

#endif
