#include "entities/weapons/TrippleShotGun.hpp"
#include "entities/Bullet.hpp"

TrippleShotGun::TrippleShotGun(Scene* scene, bool enemy) : BaseWeapon(scene, enemy){
    shootSpeed = 600;
    damage = 2;
    fireRate = .6;
    weaponName = "Tripple Shot";
} 

void TrippleShotGun::shoot(Direction dir, int x, int y){
    if(canShoot()){

        auto spread = .7;

        if(dir == Up){
            auto bullet1 = new Bullet(currentScene, x, y, 0, -shootSpeed, damage, enemy);
            auto bullet2 = new Bullet(currentScene, x, y, shootSpeed * 1 - spread, -shootSpeed * spread, damage, enemy);
            auto bullet3 = new Bullet(currentScene, x, y, -shootSpeed * 1 - spread, -shootSpeed * spread, damage, enemy);
            currentScene->createObject(bullet1);
            currentScene->createObject(bullet2);
            currentScene->createObject(bullet3);
        }
        else if(dir == Down){
            auto bullet1 = new Bullet(currentScene, x, y, 0, shootSpeed, damage, enemy);
            auto bullet2 = new Bullet(currentScene, x, y, shootSpeed * 1 - spread, shootSpeed * spread, damage, enemy);
            auto bullet3 = new Bullet(currentScene, x, y, -shootSpeed * 1 - spread, shootSpeed * spread, damage, enemy);
            currentScene->createObject(bullet1);
            currentScene->createObject(bullet2);
            currentScene->createObject(bullet3);
        }
        else if(dir == Left){
            auto bullet1 = new Bullet(currentScene, x, y, -shootSpeed, 0, damage, enemy);
            auto bullet2 = new Bullet(currentScene, x, y, -shootSpeed * spread, -shootSpeed * 1 - spread, damage, enemy);
            auto bullet3 = new Bullet(currentScene, x, y, -shootSpeed * spread, shootSpeed * 1 - spread, damage, enemy);
            currentScene->createObject(bullet1);
            currentScene->createObject(bullet2);
            currentScene->createObject(bullet3);
        }
        else if(dir == Right){
            auto bullet1 = new Bullet(currentScene, x, y, shootSpeed, 0, damage, enemy);
            auto bullet2 = new Bullet(currentScene, x, y, shootSpeed * spread, -shootSpeed * 1 - spread, damage, enemy);
            auto bullet3 = new Bullet(currentScene, x, y, shootSpeed * spread, shootSpeed * 1 - spread, damage, enemy);
            currentScene->createObject(bullet1);
            currentScene->createObject(bullet2);
            currentScene->createObject(bullet3);
        }
        
        timeSinceShot = 0;
    }
}