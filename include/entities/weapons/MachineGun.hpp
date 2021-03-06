#ifndef			__HPP__MACHINEGUN__
#define			__HPP__MACHINEGUN__

#include "entities/weapons/BaseWeapon.hpp"
#include "engine/Scene.hpp"

class MachineGun : BaseWeapon {
    public:
        MachineGun(Scene* scene, bool enemy);
};

#endif
