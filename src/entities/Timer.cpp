#include "entities/Timer.hpp"
#include "engine/Scene.hpp"

Timer::Timer(Scene* scene) : Sprite("Time 0:00", "./assets/stick.ttf", 10, 30){
    currentScene = scene;
    setType("Spawner");
    position.setX(850);
    position.setY(725);
}

void Timer::update(double delta){
    Sprite::update(delta);

    if(timerRunning) {
        this->ellapsedGameTime += delta;

        int mins = ellapsedGameTime / 60;
        int seconds = ellapsedGameTime - (mins * 60);

        if(seconds < 10) {
            setText("Time " + std::to_string(mins) + ":0" + std::to_string(seconds));
        }else{
            setText("Time 0" + std::to_string(mins) + ":" + std::to_string(seconds));
        }
    }
}

void Timer::stop() {
    timerRunning = false;
}

void Timer::start() {
    timerRunning = true;
}

void Timer::reset() {
    this->ellapsedGameTime = 0;
}