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
        auto enemy1 = new Enemy(currentScene, 500, 300);
        auto enemy2 = new Enemy(currentScene, 500, 600);
        auto enemy3 = new Enemy(currentScene, 1000, 400);
        auto enemy4 = new Enemy(currentScene, 100, 600);

        currentScene->createObject(enemy1);
        currentScene->createObject(enemy2);
        currentScene->createObject(enemy3);
        currentScene->createObject(enemy4);
    }
}