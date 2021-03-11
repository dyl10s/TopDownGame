#include "engine/ContactListener.hpp"
#include "entities/enemies/BaseEnemy.hpp"
#include "entities/Bullet.hpp"
#include "entities/Player.hpp"
#include "entities/Chest.hpp"
#include "entities/items/Item.hpp"
#include <SDL2/SDL.h>

ContactListener::ContactListener(Scene* scene) {
    currentScene = scene;
}

void ContactListener::BeginContact(b2Contact* contact){
    auto item1 = (Sprite*)(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
    auto item2 = (Sprite*)(contact->GetFixtureB()->GetBody()->GetUserData().pointer);

    if(item1->getType() == "Bullet"){
        currentScene->removeObject(item1);

        if(item2->getType() == "Enemy"){
            ((BaseEnemy*)item2)->takeDamage(((Bullet*)item1)->getDamage());
        }

        if(item2->getType() == "Player"){
            ((Player*)item2)->takeDamage(((Bullet*)item1)->getDamage());
        }
    }

    if(item2->getType() == "Bullet"){
        currentScene->removeObject(item2);

        if(item1->getType() == "Enemy"){
            ((BaseEnemy*)item1)->takeDamage(((Bullet*)item2)->getDamage());
        }

        if(item1->getType() == "Player"){
            ((Player*)item1)->takeDamage(((Bullet*)item2)->getDamage());
        }
    }

    if(item2->getType() == "Door"){
        if(item1->getType() == "Player"){
            if(item2->getAnimationFrame() == 1){
                 ((Player*)item1)->playerHitDoor();
                 currentScene->spawner->closeDoor();
            }
        }
    }

    if(item2->getType() == "Player"){
        if(item1->getType() == "Door"){
            if(item1->getAnimationFrame() == 1){
                 ((Player*)item2)->playerHitDoor();
                 currentScene->spawner->closeDoor();
            }
        }
    }

    if(item1->getType() == "Chest" && item2->getType() == "Player")
            ((Chest*)item1)->spawnItem();

    if(item1->getType() == "Player" && item2->getType() == "Chest")
            ((Chest*)item2)->spawnItem();

    if(item1->getType() == "Item" && item2->getType() == "Player")
      ((Item*)item1)->activate((Player*)item2);

    if(item1->getType() == "Player" && item2->getType() == "Item")
      ((Item*)item2)->activate((Player*)item1);
}

