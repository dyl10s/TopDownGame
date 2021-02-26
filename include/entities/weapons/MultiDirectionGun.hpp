#ifndef			__HPP__MULTIDIRECTIONGUN__
#define			__HPP__MULTIDIRECTIONGUN__

#include "entities/weapons/BaseWeapon.hpp"
#include "engine/Scene.hpp"

class MultiDirectionGun : BaseWeapon {
    public:
        MultiDirectionGun(Scene* scene);
        void shoot(Direction dir, int x, int y);
};

#endif
