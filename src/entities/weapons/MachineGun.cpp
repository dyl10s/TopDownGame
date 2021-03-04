#include "entities/weapons/MachineGun.hpp"

MachineGun::MachineGun(Scene* scene) : BaseWeapon(scene){
    // Make the adjustments relative to the base gun
    fireRate = fireRate / 3;
    shootSpeed = shootSpeed * 1.2;
}