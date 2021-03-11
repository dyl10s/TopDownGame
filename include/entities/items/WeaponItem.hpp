#ifndef			__HPP__WEAPONITEM__
#define			__HPP__WEAPONITEM__

#include "entities/Player.hpp"
#include "entities/items/Item.hpp"
#include "entities/weapons/BaseWeapon.hpp"
#include "engine/Scene.hpp"

class WeaponItem : Item {
	public:
		WeaponItem(Scene* scene, int x, int y, BaseWeapon* weapon);
		void activate(Player* player);
	private:
		BaseWeapon* weapon;
};

#endif
