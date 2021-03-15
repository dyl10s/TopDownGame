#include "entities/weapons/BaseWeapon.hpp"
#include "entities/Bullet.hpp"

BaseWeapon::BaseWeapon(Scene* scene, bool enemy){
    currentScene = scene;
    this->enemy = enemy;

    scene->createUpdateable(this);
}

void BaseWeapon::update(double delta){
    timeSinceShot += delta;
}

void BaseWeapon::setFirerate(double rate) {
    fireRate = rate;
}

bool BaseWeapon::canShoot(){
    if(timeSinceShot > fireRate){
        return true;
    }

    return false;
}

bool BaseWeapon::hasRecoil(){
  return false;
}

void BaseWeapon::shoot(Direction dir, int x, int y){
    if(canShoot()){
        if(dir == Up){
            auto bullet = new Bullet(currentScene, x, y, 0, -shootSpeed, damage, enemy);
            currentScene->createObject(bullet);
        }
        else if(dir == Down){
            auto bullet = new Bullet(currentScene, x, y, 0, shootSpeed, damage, enemy);
            currentScene->createObject(bullet);
        }
        else if(dir == Left){
            auto bullet = new Bullet(currentScene, x, y, -shootSpeed, 0, damage, enemy);
            currentScene->createObject(bullet);
        }
        else if(dir == Right){
            auto bullet = new Bullet(currentScene, x, y, shootSpeed, 0, damage, enemy);
            currentScene->createObject(bullet);
        }
        timeSinceShot = 0;
    }
}

void BaseWeapon::shoot(double xDir, double yDir, int x, int y) {
    if(canShoot()){
        auto bullet = new Bullet(currentScene, x, y, xDir * shootSpeed, yDir * shootSpeed, damage, enemy);
        currentScene->createObject(bullet);
        timeSinceShot = 0;
    }
}
