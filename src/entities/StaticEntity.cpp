#include "entities/StaticEntity.hpp"
#include "engine/AssetLoader.hpp"

StaticEntity::StaticEntity(Scene* scene, SDL_Rect* sourceRect, int x, int y, int w, int h, bool collision) : Sprite(AssetLoader::tilesheet, sourceRect, 0, w, h){
    position.setX(x);
	position.setY(y);
	currentScene = scene;
    this->sourceRect = sourceRect;

    if(collision){
        auto body = currentScene->getCollision()->addStatic(this, ALL, ALL);
        this->setBody(body);
    }else{
        auto body = currentScene->getCollision()->addStatic(this, FLOOR);
        this->setBody(body);
    }
}