#include "entities/Item.hpp"
#include "engine/AssetLoader.hpp"

Item::Item(Scene* scene, int x, int y) : Sprite(AssetLoader::tilesheet, AssetLoader::testItem, 3, .2, 0, 10, 11) {
  setType("Item");
  position.setX(x);
  position.setY(y);
  currentScene = scene;
}

Item::~Item() {
}

void Item::spawn() {
  auto body = currentScene->getCollision()->addObject(this, ENEMY, FRIENDLY);
  this->setBody(body);
  currentScene->createObject(this);
}
