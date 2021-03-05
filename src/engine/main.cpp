#include "engine/Engine.hpp"
#include "engine/Collision.hpp"
#include "entities/Player.hpp"
#include "entities/Bullet.hpp"
#include "entities/Spawner.hpp"
#include "engine/Sound.hpp"
#include <SDL2/SDL.h>
#include <box2d/box2d.h>
#include <SDL2/SDL_mixer.h>

int main(int argc, char** argv){
	SDL_Log("Starting up, with following arguments:");
	for(int i=0; i<argc; ++i){
		SDL_Log("%d = %s", i, argv[i]);
	}

	// Create an engine.  Must happen early, creates the renderer.
	Engine engine(1024, 768);
	// Create the physics engine
	Collision collision(b2Vec2(0.0, 0.0));
	// Create a scene
	Scene one(&collision);

	// Make a player and add to scene. Should update and draw.
	Player* mainPlayer = new Player(&one);

	// Initialize Sound
	Sound* sound = new Sound();

	sound->setVolume(MIX_MAX_VOLUME/2);

    // Play the music
	sound->playBGMusic("/assets/8bitBackground.wav");

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
