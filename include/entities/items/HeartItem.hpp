#ifndef			__HPP__HEARTITEM__
#define			__HPP__HEARTITEM__

#include "entities/Player.hpp"
#include "entities/items/Item.hpp"
#include "engine/Scene.hpp"

class HeartItem : Item {
	public:
		HeartItem(Scene* scene, int x, int y);
		void activate(Player* player);
	private:
};

#endif
