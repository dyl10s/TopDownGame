#ifndef			__HPP__SpiralEnemy__
#define			__HPP__SpiralEnemy__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "entities/weapons/BaseWeapon.hpp"
#include "entities/enemies/BaseEnemy.hpp"

class SpiralEnemy : public BaseEnemy {
	public:
		SpiralEnemy(Scene* scene, int x, int y);
		~SpiralEnemy();
		void update(double delta);
	private:
		double timeSinceAction = 0;
		
		Vector2 playerLocation = Vector2(0, 0);

		int shootFrame = 0;
};

#endif
