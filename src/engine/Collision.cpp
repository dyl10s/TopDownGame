#include "engine/Collision.hpp"
#include "engine/Interfaces.hpp"
#include "engine/Sprite.hpp"
#include <SDL2/SDL.h>
#include <box2d/box2d.h>

Collision::Collision(b2Vec2 gravity){
	SDL_Log("Creating world...");
	world = new b2World(gravity);
	SDL_Log("Created with requested gravity.");
}

Collision::~Collision(){
	delete world;
}

void Collision::update(double delta){
	world->Step(1.0 / 60.0, 1.0, 1.0);
	for(auto it = objects.begin(); it != objects.end(); ++it){
		b2Vec2 position = (*it).second->GetPosition();
		(*it).first->position.setX(position.x / METERSTOPIXELS);
		(*it).first->position.setY(position.y / METERSTOPIXELS);
	}
}

b2Body* Collision::addObject(Sprite* object, uint16 category, uint16 collideWith){
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.fixedRotation = true;
	bodyDef.angle = 0;
	bodyDef.position.Set((object->position.getX() + (object->rect->w / 2.0)) / METERSTOPIXELS, (object->position.getY() + (object->rect->h / 2.0)) / METERSTOPIXELS);
	
	b2Body* body = world->CreateBody(&bodyDef);

	b2PolygonShape box;
	box.SetAsBox((object->rect->w / 2.0) / METERSTOPIXELS, (object->rect->h / 2.0) / METERSTOPIXELS);

	b2FixtureDef fixture;
	fixture.filter.categoryBits = category;
	fixture.filter.maskBits = collideWith;
	fixture.shape = &box;
	fixture.density = 0.0001;
	fixture.friction = 0.1;
	fixture.restitution = 0;
	body->CreateFixture(&fixture);
	objects.push_back(std::make_pair(object, body));
	return body;
}