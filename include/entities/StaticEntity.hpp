#ifndef			__HPP__STATICENTITY__
#define			__HPP__STATICENTITY__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "engine/Interfaces.hpp"
#include "engine/Utility.hpp"
#include "engine/Sprite.hpp"
#include "engine/Scene.hpp"

class StaticEntity : public Sprite {
	public:
		StaticEntity(Scene* scene, SDL_Rect* sourceRect, int x, int y, int w, int h, bool collision = true);
	private:
		SDL_Rect* sourceRect;
		Scene* currentScene;

};

#endif
