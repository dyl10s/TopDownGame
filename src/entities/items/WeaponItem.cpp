#include "entities/items/WeaponItem.hpp"
#include "engine/AssetLoader.hpp"
#include "entities/weapons/BaseWeapon.hpp"

WeaponItem::WeaponItem(Scene* scene, int x, int y, BaseWeapon* weapon) : Item(scene, x, y, &AssetLoader::weapon) {
  position.setX(x);
  position.setY(y);
  currentScene = scene;
  this->weapon = weapon;
}

void WeaponItem::activate(Player* player) {
  player->setWeapon(weapon);
  currentScene->removeObject(this);
}
