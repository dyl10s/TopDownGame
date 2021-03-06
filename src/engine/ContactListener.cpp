#include "engine/ContactListener.hpp"
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
            currentScene->removeObject(item2);
        }
    }

    if(item2->getType() == "Bullet"){
        currentScene->removeObject(item2);

        if(item1->getType() == "Enemy"){
            currentScene->removeObject(item1);
        }
    }

    SDL_Log("%s has collided with %s", item1->getType().c_str(), item2->getType().c_str());
}