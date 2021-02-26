#ifndef			__HPP__BASEWEAPON__
#define			__HPP__BASEWEAPON__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "engine/Interfaces.hpp"
#include "engine/Utility.hpp"
#include "engine/Sprite.hpp"
#include "engine/Scene.hpp"

enum Direction {
	Up,
	Down,
	Left,
	Right
};

class BaseWeapon : UGameObject {
	public:
		BaseWeapon(Scene* scene);
		void update(double delta);
		virtual void shoot(Direction dir, int x, int y);
	protected:
		double shootSpeed = 500;
		double fireRate = .3;
		double timeSinceShot = 0;
		Scene* currentScene;
};

#endif
