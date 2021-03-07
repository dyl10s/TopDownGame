#include "engine/Collision.hpp"
#include "engine/Interfaces.hpp"
#include "engine/ContactListener.hpp"
#include "engine/Scene.hpp"
#include "engine/Sprite.hpp"
#include <SDL2/SDL.h>
#include <box2d/box2d.h>
#include <algorithm>

Collision::Collision(b2Vec2 gravity){
	SDL_Log("Creating world...");
	world = new b2World(gravity);
	SDL_Log("Created with requested gravity.");
}

Collision::~Collision(){
	delete world;
}

void Collision::update(double delta){
	world->Step(1.0 / 59.0, 1.0, 1.0);
	for(auto it = objects.begin(); it != objects.end(); ++it){
		b2Vec2 position = (*it).second->GetPosition();
		(*it).first->position.setX((position.x * METERSTOPIXELS) - ((*it).first->rect->w / 2.0));
		(*it).first->position.setY((position.y * METERSTOPIXELS) - ((*it).first->rect->h / 2.0));
	}
}

b2World* Collision::getWorld() {
	return world;
}

void Collision::removeObject(Sprite* object){
	// I am just gonna not care about performance right here
	// because I don't know how to do this in c++
	std::vector<std::pair<Sprite*, b2Body*>> livingObjects;
	for(auto it = 0; it < objects.size(); ++it){
		auto cur = objects[it];
		if(cur.first != object){
			livingObjects.push_back(std::make_pair(cur.first, cur.second));
		}else{
			// The sprite is already going to be destroyed elsewhere
			// just get rid of the box2d body
			world->DestroyBody(cur.second);
		}
	}
	objects = livingObjects;
}

b2Body* Collision::addStatic(Sprite* object, uint16 category, uint16 collideWith){
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.fixedRotation = true;
	bodyDef.angle = 0;
	bodyDef.bullet = true;
	bodyDef.position.Set(object->position.getX() / METERSTOPIXELS, object->position.getY() / METERSTOPIXELS);
	
	b2Body* body = world->CreateBody(&bodyDef);
	body->GetUserData().pointer = (uintptr_t)object;

	b2PolygonShape box;
	box.SetAsBox((object->rect->w / 2.0) / METERSTOPIXELS, (object->rect->h / 2.0) / METERSTOPIXELS);

	b2FixtureDef fixture;
	fixture.filter.categoryBits = category;
	fixture.filter.maskBits = collideWith;
	fixture.shape = &box;
	fixture.density = 0.3;
	fixture.friction = 0;
	fixture.restitution = 0;
	body->CreateFixture(&fixture);
	objects.push_back(std::make_pair(object, body));
	return body;
}

b2Body* Collision::addObject(Sprite* object, uint16 category, uint16 collideWith){
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.fixedRotation = true;
	bodyDef.angle = 0;
	bodyDef.position.Set(object->position.getX() / METERSTOPIXELS, object->position.getY() / METERSTOPIXELS);

	b2Body* body = world->CreateBody(&bodyDef);
	body->GetUserData().pointer = (uintptr_t)object;
	
	b2PolygonShape box;
	box.SetAsBox((object->rect->w / 2.0) / METERSTOPIXELS, (object->rect->h / 2.0) / METERSTOPIXELS);

	b2FixtureDef fixture;
	fixture.filter.categoryBits = category;
	fixture.filter.maskBits = collideWith;
	fixture.shape = &box;
	fixture.density = 0.3;
	fixture.friction = 0;
	fixture.restitution = 0;
	body->CreateFixture(&fixture);
	objects.push_back(std::make_pair(object, body));
	return body;
}