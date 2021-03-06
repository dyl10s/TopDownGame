#include "entities/Spawner.hpp"
#include "entities/Enemy.hpp"

Spawner::Spawner(Scene* scene) : Sprite("Wave 0", "./assets/stick.ttf", 10, 30){
    currentScene = scene;
    position.setX(450);
    position.setY(5);
}

void Spawner::update(double delta){
    if(currentWave == 0){
        currentWave++;
        setText("Wave " + std::to_string(currentWave));

        // Spawn some enemys
        for(int i = 0; i < 10; i++){
            auto enemy = new Enemy(currentScene, rand() % 1000 + 100, rand() % 600 + 100);
            currentScene->createObject(enemy);
        }        
    }
}