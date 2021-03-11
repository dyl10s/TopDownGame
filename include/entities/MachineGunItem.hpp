#ifndef			__HPP__MACHINEGUNITEM__
#define			__HPP__MACHINEGUNITEM__

#include "entities/Player.hpp"
#include "entities/Item.hpp"
#include "engine/Scene.hpp"

class MachineGunItem : Item {
	public:
		MachineGunItem(Scene* scene, int x, int y);
		void activate(Player* player);
	private:
};

#endif
