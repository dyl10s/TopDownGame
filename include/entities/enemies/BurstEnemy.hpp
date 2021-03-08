#ifndef			__HPP__WALLRIDEENEMY__
#define			__HPP__WALLRIDEENEMY__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "entities/weapons/BaseWeapon.hpp"
#include "entities/enemies/BaseEnemy.hpp"

class BurstEnemy : public BaseEnemy {
	public:
		BurstEnemy(Scene* scene, int x, int y);
		~BurstEnemy();
		void update(double delta);
	private:
		double timeSinceAction = 0;
		
		Vector2 playerLocation = Vector2(0, 0);

		float waitTime = 3;
		float chaseTime = .2;

		enum State {
			Chase,
			Burst,
			Wait
		};

		State currentState = Wait;
};

#endif
