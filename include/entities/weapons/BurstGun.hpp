#ifndef			__HPP__BURSTGUN__
#define			__HPP__BURSTGUN__

#include "entities/weapons/BaseWeapon.hpp"
#include "engine/Scene.hpp"

class BurstGun : BaseWeapon {
    public:
        BurstGun(Scene* scene, bool enemy);
        void shoot(Direction dir, int x, int y);
};

#endif
