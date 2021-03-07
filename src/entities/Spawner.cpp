#include "entities/Spawner.hpp"
#include "entities/enemies/BaseEnemy.hpp"

Spawner::Spawner(Scene* scene) : Sprite("Wave 0", "./assets/stick.ttf", 10, 30){
    currentScene = scene;
    position.setX(450);
    position.setY(5);
}

void Spawner::update(double delta){
    timeSinceSpawnCheck += delta;

    if(this->readyForNextWave()){
        if(currentWave == 0){
            currentWave++;
            setText("Wave " + std::to_string(currentWave));

            // Spawn some enemys
            for(int i = 0; i < 4; i++){
                srand(i * currentWave);
                auto enemy = new BaseEnemy(currentScene, rand() % 1000 + 100, rand() % 600 + 100);
                currentScene->createObject(enemy);
                waveSprites.push_back(enemy);
            } 
        }else if(currentWave == 1){
            currentWave++;
            setText("Wave " + std::to_string(currentWave));
            // Spawn some enemys
            for(int i = 0; i < 4; i++){
                srand(i * currentWave);
                auto enemy = new BaseEnemy(currentScene, rand() % 1000 + 100, rand() % 600 + 100);
                currentScene->createObject(enemy);
                waveSprites.push_back(enemy);
            } 
        }
    }
}

bool Spawner::readyForNextWave(){
    // Check if any enemies are alive
    // kinda an expensive operation so only check every second
    if(timeSinceSpawnCheck > 1){
        timeSinceSpawnCheck = 0;

        auto objects = currentScene->getUpdateables();
        for(int i = 0; i < objects.size(); ++i){
            for(int x = 0; x < waveSprites.size(); ++x){
                if(waveSprites[x] == objects[i]){
                    return false;
                }
            }
        }
    }else{
        return false;
    }
    
    // Clean up the wave
    waveSprites.clear();
    return true;
}