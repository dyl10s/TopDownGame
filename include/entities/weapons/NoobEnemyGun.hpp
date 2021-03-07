#ifndef			__HPP__NOOBENEMYGUN__
#define			__HPP__NOOBENEMYGUN__

#include "entities/weapons/BaseWeapon.hpp"
#include "engine/Scene.hpp"

class NoobEnemyGun : BaseWeapon {
    public:
        NoobEnemyGun(Scene* scene, bool enemy);
};

#endif
