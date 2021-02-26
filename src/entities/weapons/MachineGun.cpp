#include "entities/weapons/MachineGun.hpp"

MachineGun::MachineGun(Scene* scene) : BaseWeapon(scene){
    fireRate = .1;
    shootSpeed = 900;
}