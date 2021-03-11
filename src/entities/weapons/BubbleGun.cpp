#include "entities/weapons/BubbleGun.hpp"
#include "entities/Bullet.hpp"

BubbleGun::BubbleGun(Scene* scene, bool enemy) : BaseWeapon(scene, enemy){
    fireRate = 2.5;
    shootSpeed = 100;
    damage = 1;
}

void BubbleGun::shoot(Direction dir, int x, int y){
    if(canShoot()){

        auto bullets = 50;

        for(int i = 0; i < bullets; i++){
            auto shootX = 1 * cos(2 * M_PI * i / bullets);
            auto shootY = 1 * sin(2 * M_PI * i / bullets);

            auto bullet = new Bullet(currentScene, x, y, shootX * shootSpeed, shootY * shootSpeed, damage, enemy);
            currentScene->createObject(bullet);
        }
        timeSinceShot = 0;
    }
}