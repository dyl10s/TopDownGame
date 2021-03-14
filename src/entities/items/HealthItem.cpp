#include "entities/items/HealthItem.hpp"
#include "engine/AssetLoader.hpp"
#include "entities/Player.hpp"

HealthItem::HealthItem(Scene* scene, int x, int y) : Item(scene, x, y, &AssetLoader::hpPot) {
  position.setX(x);
  position.setY(y);
  currentScene = scene;
}

void HealthItem::activate(Player* player) {
  player->giveHealth(2);
  currentScene->removeObject(this);
}
