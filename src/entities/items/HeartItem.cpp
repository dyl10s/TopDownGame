#include "entities/items/HeartItem.hpp"
#include "entities/Player.hpp"

HeartItem::HeartItem(Scene* scene, int x, int y) : Item(scene, x, y) {
  position.setX(x);
  position.setY(y);
  currentScene = scene;
}

void HeartItem::activate(Player* player) {
  player->addHeart();
  currentScene->removeObject(this);
}
