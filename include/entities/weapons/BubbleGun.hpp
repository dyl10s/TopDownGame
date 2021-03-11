#ifndef			__HPP__BubbleGun__
#define			__HPP__BubbleGun__

#include "entities/weapons/BaseWeapon.hpp"
#include "engine/Scene.hpp"

class BubbleGun : BaseWeapon {
    public:
        BubbleGun(Scene* scene, bool enemy);
        void shoot(Direction dir, int x, int y);
};

#endif
