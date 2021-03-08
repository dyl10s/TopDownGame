#include <SDL2/SDL.h>
#include "engine/Interfaces.hpp"
#include "engine/Utility.hpp"
#include "engine/Scene.hpp"
#include "engine/Collision.hpp"

Scene::Scene(){

}

Scene::Scene(Collision* collision){
	this->collision = collision;
}

Scene::~Scene(){
}

void Scene::addUpdateable(Updateable* obj){
	this->updateables.push_back(obj);
}

void Scene::addDrawable(Drawable* obj){
	this->drawables.push_back(obj);
}

void Scene::addKeyEvent(SDL_Keycode key, Callback fn){
	keyEvents.push_back(std::make_pair(key, fn));	
}

void Scene::createUpdateable(Updateable* obj){
	this->createUpdatables.push_back(obj);
}

void Scene::createDrawable(Drawable* obj){
	this->createDrawables.push_back(obj);
}

void Scene::removeObject(DUGameObject* obj){
	// Make sure the object is not already marked to delete
	for(int i = 0; i < (int)this->removedObjects.size(); ++i){
		if(this->removedObjects[i] == obj){
			return;
		}
	}

	this->removedObjects.push_back(obj);
}

void Scene::createObject(DUGameObject* obj){
	this->createdObjects.push_back(obj);
}

Collision* Scene::getCollision() {
	return collision;
}

std::vector<Updateable*> Scene::getUpdateables() {
	return updateables;
}

void Scene::SetPlayerLocation(double x, double y){
	playerLocation.setX(x);
	playerLocation.setY(y);
}

Vector2 Scene::GetPlayerLocation(){
	return playerLocation;
}