#ifndef			__HPP__BULLET__
#define			__HPP__BULLET__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "engine/Interfaces.hpp"
#include "engine/Utility.hpp"
#include "engine/Sprite.hpp"
#include "engine/Scene.hpp"

class Bullet : public Sprite {
	public:
		Bullet(Scene* scene, int x, int y, int xVel, int yVel, int damage = 1, bool enemy = false);
		~Bullet();
		void update(double delta);
		int getDamage();
	private:
        Scene* currentScene;
		Vector3 velocity;
		int damage;
};

#endif
