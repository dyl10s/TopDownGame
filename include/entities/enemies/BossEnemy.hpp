#ifndef			__HPP__BossEnemy__
#define			__HPP__BossEnemy__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "entities/weapons/BaseWeapon.hpp"
#include "entities/enemies/BaseEnemy.hpp"

class BossEnemy : public BaseEnemy {
	public:
		BossEnemy(Scene* scene, int x, int y);
		~BossEnemy();
		void update(double delta);
	private:
		double timeSinceAction = 0;
		
		Vector2 playerLocation = Vector2(0, 0);

		float timer = 0;
		int shootFrame = 0;

		enum State {
			Bubble,
			Rage,
			Charge
		};

        enum SubState {
			Left,
            Right,
			Dart,
			Shoot
		};

		int targetX;
		int targetY;

		State currentState = Bubble;
		SubState currentSubState = Left;
};

#endif
