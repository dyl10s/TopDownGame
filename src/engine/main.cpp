#include "engine/Engine.hpp"
#include "entities/Player.hpp"
#include "entities/Bullet.hpp"
#include "entities/Spawner.hpp"
#include <SDL2/SDL.h>

int main(int argc, char** argv){
	SDL_Log("Starting up, with following arguments:");
	for(int i=0; i<argc; ++i){
		SDL_Log("%d = %s", i, argv[i]);
	}

	// Create a scene
	Scene one;
	// Create an engine.  Must happen early, creates the renderer.
	Engine engine(1024, 768);

	// Make a banana and add to scene. Should update and draw.
	Player* mainPlayer = new Player(&one);
	one.addUpdateable(mainPlayer);
	one.addDrawable(mainPlayer);

	Spawner* mainSpawner = new Spawner(&one);
	one.addUpdateable(mainSpawner);
	one.addDrawable(mainSpawner);

	// Set the scene in the engine
	engine.setScene(&one);
	
	// Get the engine running.
	engine.run();
}
