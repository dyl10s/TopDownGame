#ifndef			__HPP__ITEM__
#define			__HPP__ITEM__

#include "engine/Sprite.hpp"
#include "engine/Scene.hpp"
#include "engine/Interfaces.hpp"
#include "engine/Utility.hpp"
#include "entities/Player.hpp"
#include <SDL2/SDL.h>

class Item : public Sprite {
	public:
		Item(Scene* scene, int x, int y);
		~Item();
		virtual void activate(Player* player) = 0;
		void spawn();
	protected:
		Scene* currentScene;
};

#endif
