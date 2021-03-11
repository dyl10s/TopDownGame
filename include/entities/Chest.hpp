#ifndef			__HPP__CHEST__
#define			__HPP__CHEST__

#include "engine/Sprite.hpp"
#include "engine/Scene.hpp"
#include "engine/Interfaces.hpp"
#include "engine/Utility.hpp"
#include "entities/items/Item.hpp"
#include <SDL2/SDL.h>

class Chest : public Sprite {
	public:
		Chest(Scene* scene);
		Chest(Scene* scene, int x, int y);
		~Chest();
		void update(double delta);
		void spawnItem();
	private:
		Scene* currentScene;
		Item* item;
		bool opened;
};

#endif
