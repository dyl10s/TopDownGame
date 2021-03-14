#include "entities/items/Item.hpp"
#include "engine/AssetLoader.hpp"

Item::Item(Scene* scene, int x, int y, SDL_Rect* itemImage) : Sprite(AssetLoader::tilesheet, itemImage, 0, 10, 11) {
  setType("Item");
  position.setX(x);
  position.setY(y);
  currentScene = scene;
}

Item::~Item() {
}

void Item::update(double delta) {

  if(shouldSpawn) {
    auto body = currentScene->getCollision()->addObject(this, ENEMY, FRIENDLY | ENEMY);
    this->setBody(body);

    // Get random direction
    double xDir = (rand() % 11 + (-5)) / 10.0;
    double yDir = (rand() % 11 + (-5)) / 10.0;

    auto minValue = .12;

    if(xDir < 0) {
      xDir = -minValue;
    }

    if(yDir < 0) {
      yDir = -minValue;
    }

    if(xDir > 0) {
      xDir = minValue;
    }

    if(yDir > 0) {
      yDir = minValue;
    }

    body->ApplyLinearImpulseToCenter(b2Vec2(xDir, yDir), true);
    timeAlive = 0;
    shouldSpawn = false;
  }

  if(body != nullptr) {
    timeAlive += delta;

    body->SetLinearDamping(5);
  }
}

void Item::spawn() {
  shouldSpawn = true;
  currentScene->createObject(this);
}
