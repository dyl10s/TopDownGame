#include "entities/weapons/MultiDirectionGun.hpp"
#include "entities/Bullet.hpp"

MultiDirectionGun::MultiDirectionGun(Scene* scene) : BaseWeapon(scene){
}

void MultiDirectionGun::shoot(Direction dir, int x, int y){
    if(timeSinceShot > fireRate){
        if(dir == Up || dir == Down){
            auto bullet1 = new Bullet(currentScene, x, y, 0, -shootSpeed);
            auto bullet2 = new Bullet(currentScene, x, y, 0, shootSpeed);
            currentScene->createObject(bullet1);
            currentScene->createObject(bullet2);
        }
        else if(dir == Left || dir == Right){
            auto bullet1 = new Bullet(currentScene, x, y, -shootSpeed, 0);
            auto bullet2 = new Bullet(currentScene, x, y, shootSpeed, 0);
            currentScene->createObject(bullet1);
            currentScene->createObject(bullet2);
        }
        timeSinceShot = 0;
    }
}