#ifndef			__HPP__CANNON__
#define			__HPP__CANNON__

#include "entities/weapons/BaseWeapon.hpp"
#include "engine/Scene.hpp"

class Cannon : BaseWeapon {
	public:
		Cannon(Scene* scene, bool enemy);
		void shoot(Direction dir, int x, int y);
		bool hasRecoil();
};

#endif
