#include "entities/weapons/BurstGun.hpp"
#include "entities/Bullet.hpp"

BurstGun::BurstGun(Scene* scene, bool enemy) : BaseWeapon(scene, enemy){
    shootSpeed = 300;
}

void BurstGun::shoot(Direction dir, int x, int y){
    if(timeSinceShot > fireRate){
        auto bullet1 = new Bullet(currentScene, x, y, 0, -shootSpeed, damage, enemy);
        auto bullet2 = new Bullet(currentScene, x, y, 0, shootSpeed, damage, enemy);
        auto bullet3 = new Bullet(currentScene, x, y, -shootSpeed, 0, damage, enemy);
        auto bullet4 = new Bullet(currentScene, x, y, shootSpeed, 0, damage, enemy);
        auto bullet5 = new Bullet(currentScene, x, y, shootSpeed, -shootSpeed, damage, enemy);
        auto bullet6 = new Bullet(currentScene, x, y, shootSpeed, shootSpeed, damage, enemy);
        auto bullet7 = new Bullet(currentScene, x, y, -shootSpeed, shootSpeed, damage, enemy);
        auto bullet8 = new Bullet(currentScene, x, y, -shootSpeed, -shootSpeed, damage, enemy);
        currentScene->createObject(bullet1);
        currentScene->createObject(bullet2);
        currentScene->createObject(bullet3);
        currentScene->createObject(bullet4);
        currentScene->createObject(bullet5);
        currentScene->createObject(bullet6);
        currentScene->createObject(bullet7);
        currentScene->createObject(bullet8);
        timeSinceShot = 0;
    }
}