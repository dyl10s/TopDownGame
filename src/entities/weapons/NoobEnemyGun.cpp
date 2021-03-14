#include "entities/weapons/NoobEnemyGun.hpp"

NoobEnemyGun::NoobEnemyGun(Scene* scene, bool enemy) : BaseWeapon(scene, enemy){
    // Make the adjustments relative to the base gun
    fireRate = fireRate * 3;
    shootSpeed = shootSpeed * .8;
    damage = 1;
    weaponName = "Noob Gun";
}