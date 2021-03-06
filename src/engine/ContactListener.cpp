#include "engine/ContactListener.hpp"
#include "entities/Enemy.hpp"
#include "entities/Bullet.hpp"
#include "entities/Player.hpp"
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
            ((Enemy*)item2)->takeDamage(((Bullet*)item1)->getDamage());
        }

        if(item2->getType() == "Player"){
            ((Player*)item2)->takeDamage(((Bullet*)item1)->getDamage());
        }
    }

    if(item2->getType() == "Bullet"){
        currentScene->removeObject(item2);

        if(item1->getType() == "Enemy"){
            ((Enemy*)item1)->takeDamage(((Bullet*)item2)->getDamage());
        }

        if(item1->getType() == "Player"){
            ((Player*)item1)->takeDamage(((Bullet*)item2)->getDamage());
        }
    }
}