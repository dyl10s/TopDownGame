#include "entities/weapons/BaseWeapon.hpp"
#include "entities/Bullet.hpp"

BaseWeapon::BaseWeapon(Scene* scene){
    currentScene = scene;
    scene->createUpdateable(this);
}

void BaseWeapon::update(double delta){
    timeSinceShot += delta;
}

void BaseWeapon::shoot(Direction dir, int x, int y){
    if(timeSinceShot > fireRate){
        if(dir == Up){
            auto bullet = new Bullet(currentScene, x, y, 0, -shootSpeed);
            currentScene->createObject(bullet);
        }
        else if(dir == Down){
            auto bullet = new Bullet(currentScene, x, y, 0, shootSpeed);
            currentScene->createObject(bullet);
        }
        else if(dir == Left){
            auto bullet = new Bullet(currentScene, x, y, -shootSpeed, 0);
            currentScene->createObject(bullet);
        }
        else if(dir == Right){
            auto bullet = new Bullet(currentScene, x, y, shootSpeed, 0);
            currentScene->createObject(bullet);
        }
        timeSinceShot = 0;
    }
}
