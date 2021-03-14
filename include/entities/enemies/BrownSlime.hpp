#ifndef			__HPP__BrownSlime__
#define			__HPP__BrownSlime__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "entities/weapons/BaseWeapon.hpp"
#include "entities/enemies/BaseEnemy.hpp"

class BrownSlime : public BaseEnemy {
	public:
		BrownSlime(Scene* scene, int x, int y);
		~BrownSlime();
		void update(double delta);
	private:
		double timeSinceAction = 0;
		
		Vector2 playerLocation = Vector2(0, 0);

		int shootFrame = 0;
};

#endif
