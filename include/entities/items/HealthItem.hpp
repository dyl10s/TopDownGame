#ifndef			__HPP__HEALTHITEM__
#define			__HPP__HEALTHITEM__

#include "entities/Player.hpp"
#include "entities/items/Item.hpp"
#include "engine/Scene.hpp"

class HealthItem : Item {
	public:
		HealthItem(Scene* scene, int x, int y);
		void activate(Player* player);
	private:
};

#endif
