#include "entities/weapons/MachineGun.hpp"

MachineGun::MachineGun(Scene* scene, bool enemy) : BaseWeapon(scene, enemy){
    // Make the adjustments relative to the base gun
    fireRate = fireRate / 2;
    shootSpeed = shootSpeed * 1.2;
    damage = 1;
}