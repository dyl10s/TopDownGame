#include "entities/Chest.hpp"
#include "engine/AssetLoader.hpp"
#include "entities/items/MachineGunItem.hpp"

Chest::Chest(Scene* scene) : Sprite(AssetLoader::tilesheet, AssetLoader::chest, 3, .2, 0, 16, 16) {
  currentScene = scene;
  opened = false;
  //item = new Item(scene, 100, 100);
  auto body = currentScene->getCollision()->addObject(this, ENEMY, FRIENDLY | FRIENDLYBULLET);
  this->setBody(body);
}

Chest::Chest(Scene* scene, int x, int y) : Sprite(AssetLoader::tilesheet, AssetLoader::chest, 3, .2, 0, 16, 16) {
  setType("Chest");
  opened = false;
  position.setY(y);
  position.setX(x);
  currentScene = scene;
  item = (Item*)new MachineGunItem(scene, x, y);
  auto body = currentScene->getCollision()->addObject(this, ENEMY, FRIENDLY | FRIENDLYBULLET);
  this->setBody(body);
}

Chest::~Chest() {
}

void Chest::update(double delta) {
  Sprite::update(delta);
  if(opened) {
    item->spawn();
    //setAnimationFrame(2);
    //currentScene->removeObject(this);
    opened = false;
  }
}

void Chest::spawnItem() {
  opened = true;
}
