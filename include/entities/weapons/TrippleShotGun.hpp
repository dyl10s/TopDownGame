#ifndef			__HPP__TrippleShotGun__
#define			__HPP__TrippleShotGun__

#include "entities/weapons/BaseWeapon.hpp"
#include "engine/Scene.hpp"

class TrippleShotGun : BaseWeapon {
    public:
        TrippleShotGun(Scene* scene, bool enemy);
        void shoot(Direction dir, int x, int y);
};

#endif
