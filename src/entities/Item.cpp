#include "entities/Item.hpp"
#include "engine/AssetLoader.hpp"

Item::Item(Scene* scene, int x, int y) : Sprite(AssetLoader::tilesheet, AssetLoader::testItem, 3, .2, 0, 20, 22) {
  setType("Item");
  position.setX(x);
  position.setY(y);
  currentScene = scene;
}

Item::~Item() {
}

void Item::activate() {

}

void Item::spawn() {
  auto body = currentScene->getCollision()->addObject(this, ENEMY, FRIENDLY);
  this->setBody(body);
  currentScene->createObject(this);
}
