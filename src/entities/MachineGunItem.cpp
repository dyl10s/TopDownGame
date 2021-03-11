#include "entities/MachineGunItem.hpp"
#include "entities/weapons/MachineGun.hpp"

MachineGunItem::MachineGunItem(Scene* scene, int x, int y) : Item(scene, x, y) {
  setType("MachineGunItem");
  position.setX(x);
  position.setY(y);
  currentScene = scene;
}

void MachineGunItem::activate(Player* player) {
  player->setWeapon(((BaseWeapon*)new MachineGun(currentScene, false)));
  currentScene->removeObject(this);
}
