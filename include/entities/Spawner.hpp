#ifndef			__HPP__Spawner__
#define			__HPP__Spawner__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "engine/Interfaces.hpp"
#include "engine/Utility.hpp"
#include "engine/Sprite.hpp"
#include "engine/Scene.hpp"

class Spawner : public Sprite {
	public:
		Spawner(Scene* scene);
		void update(double delta);
	private:
        Scene* currentScene;
		int currentWave = 0;
};

#endif
