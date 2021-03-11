#include "entities/items/WeaponItem.hpp"
#include "entities/weapons/BaseWeapon.hpp"

WeaponItem::WeaponItem(Scene* scene, int x, int y, BaseWeapon* weapon) : Item(scene, x, y) {
  position.setX(x);
  position.setY(y);
  currentScene = scene;
  this->weapon = weapon;
}

void WeaponItem::activate(Player* player) {
  player->setWeapon(weapon);
  currentScene->removeObject(this);
}
