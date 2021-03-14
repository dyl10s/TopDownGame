#include "entities/Spawner.hpp"
#include "engine/Scene.hpp"
#include "entities/StaticEntity.hpp"
#include "entities/enemies/BaseEnemy.hpp"
#include "entities/enemies/BurstEnemy.hpp"
#include "entities/enemies/SpiralEnemy.hpp"
#include "entities/enemies/GreenSlime.hpp"
#include "entities/enemies/BrownSlime.hpp"
#include "entities/Chest.hpp"
#include "entities/items/Item.hpp"

Spawner::Spawner(Scene* scene, StaticEntity* door) : Sprite("Test", "./assets/stick.ttf", 10, 30){
    currentScene = scene;
    currentScene->spawner = this;
    this->door = door;
    setType("Spawner");
}

void Spawner::update(double delta){

    if(isFirstUpdate) {
        isFirstUpdate = false;
        setTextAsMessage("Welcome to DinoDungeon!");
    }

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

    // Clean up anything we dont need
    auto drawables = currentScene->getDrawables();
    // All the things we need to keep alive to start the next room
    for(int i = 0; i < drawables.size(); ++i){
        auto curSprite = (Sprite*)drawables[i];

        // All the things we need to keep alive to start the next game
        if(
            curSprite->getType() != "Static" && 
            curSprite->getType() != "Player" && 
            curSprite->getType() != "Spawner" &&
            curSprite->getType() != "Door"){
            currentScene->removeObject(curSprite);
        }
    }

    if(currentWave % 5 == 0) // On each 5th room we can generate a chest
    {
        auto chest = new Chest(currentScene);
        currentScene->createObject(chest);
    }
    else if(currentWave <= 2) // First 2 rooms
    {
        currentScene->timer->reset();
        currentScene->timer->start();

        for(int i = 0; i < getRandomNumber(2, 5); i++){
            auto enemy = new BaseEnemy(currentScene, getRandomNumber(100, 900), getRandomNumber(50, 400));
            currentScene->createObject(enemy);
            waveSprites.push_back(enemy);
        }
    }
    else if(currentWave <= 5) // rooms before first item
    { 
        for(int i = 0; i < getRandomNumber(0, 3); i++){
            auto enemy = new BaseEnemy(currentScene, getRandomNumber(100, 900), getRandomNumber(50, 400));
            currentScene->createObject(enemy);
            waveSprites.push_back(enemy);
        }

        for(int i = 0; i < getRandomNumber(1, 2); i++){
            auto enemy = new GreenSlime(currentScene, getRandomNumber(100, 900), getRandomNumber(50, 400));
            currentScene->createObject(enemy);
            waveSprites.push_back(enemy);
        }
    }
    else if(currentWave <= 7)
    { 
        for(int i = 0; i < getRandomNumber(0, 1); i++){
            auto enemy = new BaseEnemy(currentScene, getRandomNumber(100, 900), getRandomNumber(50, 400));
            currentScene->createObject(enemy);
            waveSprites.push_back(enemy);
        }

        for(int i = 0; i < getRandomNumber(3, 5); i++){
            auto enemy = new BurstEnemy(currentScene, getRandomNumber(100, 900), getRandomNumber(50, 400));
            currentScene->createObject(enemy);
            waveSprites.push_back(enemy);
        }
    }
    else if(currentWave <= 8) // Intro to spiral 
    { 
        auto enemy = new SpiralEnemy(currentScene, getRandomNumber(100, 900), getRandomNumber(50, 400));
        currentScene->createObject(enemy);
        waveSprites.push_back(enemy);
    }
    else if(currentWave <= 10) // Mix of everyone so far
    { 
        for(int i = 0; i < getRandomNumber(1, 2); i++){
            auto enemy = new BaseEnemy(currentScene, getRandomNumber(100, 900), getRandomNumber(50, 400));
            currentScene->createObject(enemy);
            waveSprites.push_back(enemy);
        }

        for(int i = 0; i < getRandomNumber(1, 1); i++){
            auto enemy = new BurstEnemy(currentScene, getRandomNumber(100, 900), getRandomNumber(50, 400));
            currentScene->createObject(enemy);
            waveSprites.push_back(enemy);
        }

        for(int i = 0; i < getRandomNumber(1, 1); i++){
            auto enemy = new SpiralEnemy(currentScene, getRandomNumber(100, 900), getRandomNumber(50, 400));
            currentScene->createObject(enemy);
            waveSprites.push_back(enemy);
        }
    }
    else if(currentWave <= 15) {
        for(int i = 0; i < getRandomNumber(1, 3); i++){
            auto enemy = new GreenSlime(currentScene, getRandomNumber(100, 900), getRandomNumber(50, 400));
            currentScene->createObject(enemy);
            waveSprites.push_back(enemy);
        }

        for(int i = 0; i < getRandomNumber(1, 3); i++){
            auto enemy = new BrownSlime(currentScene, getRandomNumber(100, 900), getRandomNumber(50, 400));
            currentScene->createObject(enemy);
            waveSprites.push_back(enemy);
        }
    }
    else if(currentWave <= 20) { // Really hard waves
        for(int i = 0; i < getRandomNumber(0, 2); i++){
            auto enemy = new GreenSlime(currentScene, getRandomNumber(100, 900), getRandomNumber(50, 400));
            currentScene->createObject(enemy);
            waveSprites.push_back(enemy);
        }

        for(int i = 0; i < getRandomNumber(0, 2); i++){
            auto enemy = new BrownSlime(currentScene, getRandomNumber(100, 900), getRandomNumber(50, 400));
            currentScene->createObject(enemy);
            waveSprites.push_back(enemy);
        }

        for(int i = 0; i < getRandomNumber(1, 2); i++){
            auto enemy = new BaseEnemy(currentScene, getRandomNumber(100, 900), getRandomNumber(50, 400));
            currentScene->createObject(enemy);
            waveSprites.push_back(enemy);
        }

        for(int i = 0; i < getRandomNumber(0, 1); i++){
            auto enemy = new SpiralEnemy(currentScene, getRandomNumber(100, 900), getRandomNumber(50, 400));
            currentScene->createObject(enemy);
            waveSprites.push_back(enemy);
        }

        for(int i = 0; i < getRandomNumber(3, 4); i++){
            auto enemy = new BurstEnemy(currentScene, getRandomNumber(100, 900), getRandomNumber(50, 400));
            currentScene->createObject(enemy);
            waveSprites.push_back(enemy);
        }
    }
    else 
    {
        currentScene->timer->stop();
        // Win game
        setTextAsMessage("You have concurred DinoDungeon!");
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
        setTextAsUI("Room " + std::to_string(currentWave));
    }
}

void Spawner::resetGame() {
    currentWave = 0;
    setTextAsMessage("Welcome to DinoDungeon!");

    auto drawables = currentScene->getDrawables();

    for(int i = 0; i < drawables.size(); ++i){
        auto curSprite = (Sprite*)drawables[i];

        // All the things we need to keep alive to start the next game
        if(
            curSprite->getType() != "Static" && 
            curSprite->getType() != "Player" && 
            curSprite->getType() != "Spawner" &&
            curSprite->getType() != "Door"){
            currentScene->removeObject(curSprite);
        }

    }
    waveSprites.clear();
}

void Spawner::setTextAsMessage(std::string text) {
    //1024, 768
    setText(text);

    position.setX(1024 / 2 - width / 2);
    position.setY(500);
}

void Spawner::setTextAsUI(std::string text) {
    position.setX(850);
    position.setY(5);
    setText(text);
}

int Spawner::getRandomNumber(int min, int max) {
    int range = max - min + 1;
    return (rand() % range) + min;
}