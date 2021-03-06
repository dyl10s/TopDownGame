#include "engine/Engine.hpp"
#include "engine/Collision.hpp"
#include "entities/Player.hpp"
#include "entities/Bullet.hpp"
#include "entities/Spawner.hpp"
#include "entities/StaticEntity.hpp"
#include "engine/Sound.hpp"
#include <SDL2/SDL.h>
#include <box2d/box2d.h>
#include <SDL2/SDL_mixer.h>
#include "engine/AssetLoader.hpp"

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
	// Load assets
	auto loader = new AssetLoader("./assets/tilemap.png");

	// Create the floor

	for(int x = 0; x < 32; x++){
		for(int y = 0; y < 24; y++){
			auto floor = new StaticEntity(&one, &AssetLoader::floorTile, x * 32 + 16, y * 32 + 16, 33, 33, false);
			one.addDrawable(floor);
		}
	}

	// Create the walls
	for(int i = 1; i < 31; i++){
		auto wallTop = new StaticEntity(&one, &AssetLoader::topWall, 32 * i + (32 / 2), 54 / 2, 33, 54);
		auto wallBottom = new StaticEntity(&one, &AssetLoader::bottomWall, 32 * i + (32 / 2), 768 - 54 / 2, 33, 54);

		one.addDrawable(wallBottom);
		one.addDrawable(wallTop);
	}

	for(int i = 1; i < 23; i++){
		auto wallLeft = new StaticEntity(&one, &AssetLoader::leftWall, 8, 32 * i + (32 / 2), 16, 33);
		auto wallRight = new StaticEntity(&one, &AssetLoader::rightWall, 1024 - 8, 32 * i + (32 / 2), 16, 33);

		one.addDrawable(wallLeft);
		one.addDrawable(wallRight);
	}

	auto topLeftWall = new StaticEntity(&one, &AssetLoader::topLeftWall, 16, 27, 33, 54);
	auto topRightWall = new StaticEntity(&one, &AssetLoader::topRightWall, 1024 - 16, 27, 33, 54);
	auto bottomLeftWall = new StaticEntity(&one, &AssetLoader::bottomLeftWall, 16, 768 - 27, 33, 54);
	auto bottomRightWall = new StaticEntity(&one, &AssetLoader::bottomRightWall, 1024 - 16, 768 - 27, 33, 54);

	one.addDrawable(topLeftWall);
	one.addDrawable(topRightWall);
	one.addDrawable(bottomLeftWall);
	one.addDrawable(bottomRightWall);

	// Make a player and add to scene. Should update and draw.
	Player* mainPlayer = new Player(&one);

	// Initialize Sound
	Sound* sound = new Sound();

	sound->setVolume(MIX_MAX_VOLUME/2);

    // Play the music
	sound->playBGMusic("./assets/8bitBackground.wav");

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

	delete loader;
}
