#include <SDL2/SDL.h>
#include "engine/Interfaces.hpp"
#include "engine/Utility.hpp"
#include "engine/Scene.hpp"

Scene::Scene(){

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
	this->removedObjects.push_back(obj);
}

void Scene::createObject(DUGameObject* obj){
	this->createdObjects.push_back(obj);
}