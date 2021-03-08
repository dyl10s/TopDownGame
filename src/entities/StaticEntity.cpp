#include "entities/StaticEntity.hpp"
#include "engine/AssetLoader.hpp"

StaticEntity::StaticEntity(Scene* scene, SDL_Rect* sourceRect, int x, int y, int w, int h, bool collision, std::string type) 
: Sprite(AssetLoader::tilesheet, sourceRect, 0, w, h){

    setup(scene, x, y, w, h, collision, type);
    
}

StaticEntity::StaticEntity(Scene* scene, SDL_Rect** sourceRects, int frames, int x, int y, int w, int h, bool collision, std::string type) 
: Sprite(AssetLoader::tilesheet, sourceRects, frames, 0, 0, w, h){

    setup(scene, x, y, w, h, collision, type);

}

void StaticEntity::setup(Scene* scene, int x, int y, int w, int h, bool collision, std::string type){
    position.setX(x);
	position.setY(y);
	currentScene = scene;
    this->sourceRect = sourceRect;

    setType(type);

    if(collision){
        auto body = currentScene->getCollision()->addStatic(this, ALL, ALL);
        this->setBody(body);
    }
}