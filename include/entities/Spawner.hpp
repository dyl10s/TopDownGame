#ifndef			__HPP__Spawner__
#define			__HPP__Spawner__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include "engine/Interfaces.hpp"
#include "engine/Utility.hpp"
#include "engine/Sprite.hpp"
#include "entities/StaticEntity.hpp"
#include "engine/Scene.hpp"

class StaticEntity;

class Spawner : public Sprite {
	public:
		Spawner(Scene* scene, StaticEntity* door);
		void update(double delta);
		void closeDoor();
		void resetGame();
	private:
        Scene* currentScene;
		int currentWave = 0;
		StaticEntity* door = nullptr;
		float timeSinceSpawnCheck = 0;
		std::vector<Sprite*> waveSprites;
		bool readyForNextWave();
		void spawnEnemies();
		void setTextAsMessage(std::string text);
		void setTextAsUI(std::string text);
		bool isFirstUpdate = true;
		int difficultyLevel = 0;

		int getRandomNumber(int min, int max);

		enum State {
			WaitingForDeath,
			WaitingForDoor,
			SpawningEnemies
		};

		State curState = WaitingForDoor;
};

#endif
