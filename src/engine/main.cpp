#include "engine/Engine.hpp"
#include "engine/Collision.hpp"
#include "entities/Player.hpp"
#include "entities/Bullet.hpp"
#include "entities/Spawner.hpp"
#include <SDL2/SDL.h>
#include <box2d/box2d.h>

int main(int argc, char** argv){
	SDL_Log("Starting up, with following arguments:");
	for(int i=0; i<argc; ++i){
		SDL_Log("%d = %s", i, argv[i]);
	}

	// Create a scene
	Scene one;
	// Create an engine.  Must happen early, creates the renderer.
	Engine engine(1024, 768);
	// Create the physics engine
	Collision collision(b2Vec2(0.0, 0.0));

	// Make a player and add to scene. Should update and draw.
	Player* mainPlayer = new Player(&one);
	b2Body* body = collision.addObject(mainPlayer);
	mainPlayer->setBody(body);
	
	one.addUpdateable(mainPlayer);
	one.addDrawable(mainPlayer);
	one.addUpdateable(&collision);

	Spawner* mainSpawner = new Spawner(&one);
	one.addUpdateable(mainSpawner);
	one.addDrawable(mainSpawner);

	// Set the scene in the engine
	engine.setScene(&one);
	
	// Get the engine running.
	engine.run();
}
