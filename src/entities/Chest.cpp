#include "entities/Chest.hpp"
#include "engine/AssetLoader.hpp"
#include "entities/items/WeaponItem.hpp"
#include "entities/weapons/MachineGun.hpp"
#include "entities/weapons/TrippleShotGun.hpp"
#include "entities/weapons/MultiDirectionGun.hpp"
#include "entities/weapons/BubbleGun.hpp"
#include "entities/weapons/Cannon.hpp"
#include "entities/items/HeartItem.hpp"
#include "entities/weapons/BurstGun.hpp"
#include "entities/items/HealthItem.hpp"
#include <time.h>
#include <stdlib.h>

// create a new chest at a random location with a random item inside of it
Chest::Chest(Scene* scene) : Sprite(AssetLoader::tilesheet, AssetLoader::chest, 3, 0, 0, 32, 32) {
  position.setX(rand() % 500 + 100);
  position.setY(rand() % 500 + 100);
  initialSetup(scene);
  randomItem();
}

// create a new chest at a given location with a random item inside of it
Chest::Chest(Scene* scene, int x, int y) : Sprite(AssetLoader::tilesheet, AssetLoader::chest, 3, 0, 0, 32, 32) {
  position.setX(x);
  position.setY(y);
  initialSetup(scene);
  randomItem();
}

// create a new chest at a given location with a given item inside of it
Chest::Chest(Scene* scene, int x, int y, Item* item) : Sprite(AssetLoader::tilesheet, AssetLoader::chest, 3, 0, 0, 32, 32) {
  position.setY(y);
  position.setX(x);
  initialSetup(scene);
  this->item = item;
}

void Chest::initialSetup(Scene* scene) {
  srand(time(NULL));
  setType("Chest");
  setAnimationFrame(0);
  opened = false;
  empty = false;
  currentScene = scene;
  auto body = currentScene->getCollision()->addObject(this, ENEMY, FRIENDLY | FRIENDLYBULLET);
  this->setBody(body);
}

void Chest::randomItem() {
  int randomNumber = rand() % 8;
  switch(randomNumber) {
    case 0:
      item = (Item*)new WeaponItem(currentScene, position.getX(), position.getY(), (BaseWeapon*)new MachineGun(currentScene, false));
      break;
    case 1:
      item = (Item*)new WeaponItem(currentScene, position.getX(), position.getY(), (BaseWeapon*)new BubbleGun(currentScene, false));
      break;
    case 2:
      item = (Item*)new WeaponItem(currentScene, position.getX(), position.getY(), (BaseWeapon*)new MultiDirectionGun(currentScene, false));
      break;
    case 3:
      item = (Item*)new WeaponItem(currentScene, position.getX(), position.getY(), (BaseWeapon*)new TrippleShotGun(currentScene, false));
      break;
    case 4:
      item = (Item*)new WeaponItem(currentScene, position.getX(), position.getY(), (BaseWeapon*)new BurstGun(currentScene, false));
      break;
    case 5:
      item = (Item*)new HeartItem(currentScene, position.getX(), position.getY());
      break;
    case 6:
      item = (Item*)new HealthItem(currentScene, position.getX(), position.getY());
      break;
    case 7:
      item = (Item*)new WeaponItem(currentScene, position.getX(), position.getY(), (BaseWeapon*)new Cannon(currentScene, false));
      break;
  }
}

Chest::~Chest() {
}

void Chest::update(double delta) {
  Sprite::update(delta);
  if(opened && !empty) {
    item->spawn();
    setAnimationFrame(2);
    empty = true;
  }
}

void Chest::spawnItem() {
  opened = true;
}
