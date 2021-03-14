#include "entities/weapons/Cannon.hpp"
#include "entities/Bullet.hpp"

Cannon::Cannon(Scene* scene, bool enemy) : BaseWeapon(scene, enemy) {
  shootSpeed = 195;
  damage = 2;
  fireRate = 1.65;
  weaponName = "Cannon";
}

bool Cannon::hasRecoil() {
  return canShoot();
}

void Cannon::shoot(Direction dir, int x, int y) {

  if(canShoot()) {
    if(dir == Up) {
      currentScene->createObject(new Bullet(currentScene, x, y, 0, -shootSpeed, damage, enemy, 4.0));
    }
    if(dir == Right) {
      currentScene->createObject(new Bullet(currentScene, x, y, shootSpeed, 0, damage, enemy, 4.0));
    }
    if(dir == Left) {
      currentScene->createObject(new Bullet(currentScene, x, y, -shootSpeed, 0, damage, enemy, 4.0));
    }
    if(dir == Down) {
      currentScene->createObject(new Bullet(currentScene, x, y, 0, shootSpeed, damage, enemy, 4.0));
    }
    timeSinceShot = 0;
  }

}
