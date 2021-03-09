#include "entities/Spawner.hpp"
#include "engine/Scene.hpp"
#include "entities/StaticEntity.hpp"
#include "entities/enemies/BaseEnemy.hpp"
#include "entities/enemies/BurstEnemy.hpp"

Spawner::Spawner(Scene* scene, StaticEntity* door) : Sprite("Welcome!", "./assets/stick.ttf", 10, 30){
    currentScene = scene;
    position.setX(850);
    position.setY(5);
    currentScene->spawner = this;
    this->door = door;
}

void Spawner::update(double delta){
    timeSinceSpawnCheck += delta;

    if(curState == SpawningEnemies){
        curState = WaitingForDeath;
        spawnEnemies();
    }else if(curState == WaitingForDeath){
        if(this->readyForNextWave()){
            curState = WaitingForDoor;
            door->setAnimationFrame(1);
        }
    }
}

void Spawner::spawnEnemies() {
    if(currentWave == 1){
        // Spawn some enemys
        for(int i = 0; i < 2; i++){
            auto enemy = new BaseEnemy(currentScene, rand() % 500 + 100, rand() % 500 + 100);
            auto burstEnemy = new BurstEnemy(currentScene, rand() % 500 + 100, rand() % 500 + 100);
            currentScene->createObject(enemy);
            currentScene->createObject(burstEnemy);
            waveSprites.push_back(enemy);
            waveSprites.push_back(burstEnemy);
        } 
    }else if(currentWave == 2){
        // Spawn some enemys
        for(int i = 0; i < 4; i++){
            auto enemy = new BaseEnemy(currentScene, rand() % 1000 + 100, rand() % 500 + 100);
            currentScene->createObject(enemy);
            waveSprites.push_back(enemy);
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

void Spawner::closeDoor() {
    if(curState == WaitingForDoor){
        curState = SpawningEnemies;
        door->setAnimationFrame(0);
        currentWave++;
        setText("Wave " + std::to_string(currentWave));
    }
}

void Spawner::resetGame() {
    currentWave = 0;
    setText("Welcome");
    for(int i = 0; i < waveSprites.size(); ++i){
        currentScene->removeObject(waveSprites[i]);
    }

    auto drawables = currentScene->getDrawables();

    for(int i = 0; i < drawables.size(); ++i){
        auto curSprite = (Sprite*)drawables[i];
        if(curSprite->getType() == "Bullet"){
            currentScene->removeObject(curSprite);
        }
    }
    waveSprites.clear();
}