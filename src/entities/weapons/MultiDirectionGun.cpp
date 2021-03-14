#include "entities/weapons/MultiDirectionGun.hpp"
#include "entities/Bullet.hpp"

MultiDirectionGun::MultiDirectionGun(Scene* scene, bool enemy) : BaseWeapon(scene, enemy){
    weaponName = "Multi-direction Gun";
}

void MultiDirectionGun::shoot(Direction dir, int x, int y){
    if(timeSinceShot > fireRate){
        if(dir == Up || dir == Down){
            auto bullet1 = new Bullet(currentScene, x, y, 0, -shootSpeed, damage, enemy);
            auto bullet2 = new Bullet(currentScene, x, y, 0, shootSpeed, damage, enemy);
            currentScene->createObject(bullet1);
            currentScene->createObject(bullet2);
        }
        else if(dir == Left || dir == Right){
            auto bullet1 = new Bullet(currentScene, x, y, -shootSpeed, 0, damage, enemy);
            auto bullet2 = new Bullet(currentScene, x, y, shootSpeed, 0, damage, enemy);
            currentScene->createObject(bullet1);
            currentScene->createObject(bullet2);
        }
        timeSinceShot = 0;
    }
}