#include "engine/Engine.hpp"
#include "engine/AssetLoader.hpp"
#include "entities/enemies/BaseEnemy.hpp"
#include "entities/enemies/BossEnemy.hpp"
#include "entities/weapons/BurstGun.hpp"
#include "entities/weapons/BubbleGun.hpp"
#include "entities/weapons/MachineGun.hpp"
#include "entities/Bullet.hpp"
#include "entities/Player.hpp"
#include <SDL2/SDL.h>
#include <time.h>
#include <stdlib.h>

BossEnemy::BossEnemy(Scene* scene, int x, int y) : BaseEnemy(scene, x, y, 50, 70, AssetLoader::bossEnemy, 4){
    currentWeapon = (BaseWeapon*)new BubbleGun(scene, true);
    currentWeapon->setFirerate(2);
    maxSpeed = 200;
    health = 100;
}

BossEnemy::~BossEnemy(){

}

void BossEnemy::update(double delta) {
    standardUpdate(delta); // Basic sprite animation and death when hp <= 0

    timer += delta;

    timeSinceAction += delta;

    if(currentState == Bubble){
        currentWeapon->shoot(Up, position.getX() + width / 2, position.getY() + height / 2);

        if(currentSubState == Left) {
            body->ApplyLinearImpulseToCenter(b2Vec2(-1, 0), true);

            if(timer > 2) {
                timer = 0;
                currentSubState = Right;
            }
        }

        if(currentSubState == Right) {
            body->ApplyLinearImpulseToCenter(b2Vec2(1, 0), true);

            if(timer > 2) {
                timer = 0;
                currentSubState = Left;
            }
        }

        if(position.getY() < 100) {
            body->ApplyLinearImpulseToCenter(b2Vec2(0, .1), true);
        }

        if(position.getY() > 200) {
            body->ApplyLinearImpulseToCenter(b2Vec2(0, -.1), true);
        }
        


        // Trigger for next state
        if(health <= 75) {
            currentState = Rage;
            currentWeapon = (BaseWeapon*)new BurstGun(currentScene, true);
        }
    }

    if(currentState == Rage) {
        playerLocation.setX(currentScene->GetPlayerLocation().getX());
        playerLocation.setY(currentScene->GetPlayerLocation().getY());


        auto locationDiff = b2Vec2(playerLocation.getX() - position.getX(), playerLocation.getY() - position.getY());
        locationDiff.Normalize();
        auto moveSpeed = b2Vec2(locationDiff.x * maxSpeed * delta, locationDiff.y * maxSpeed * delta);
        body->SetLinearVelocity(moveSpeed);
        currentWeapon->shoot(Up, position.getX() + width / 2, position.getY() + height / 2);

        if(health <= 25) {
            currentState = Charge;
            currentSubState = Shoot;
            currentWeapon = (BaseWeapon*)new MachineGun(currentScene, true);
            currentWeapon->setFirerate(.1);
            timer = 0;
        }
    }

    if(currentState == Charge) {
        maxSpeed = 750;
        playerLocation = currentScene->GetPlayerLocation();

        playerLocation.setX(currentScene->GetPlayerLocation().getX());
        playerLocation.setY(currentScene->GetPlayerLocation().getY());

        if(currentSubState == Dart) {
            auto locationDiff = b2Vec2(targetX - position.getX(), targetY - position.getY());
            locationDiff.Normalize();
            auto moveSpeed = b2Vec2(locationDiff.x * maxSpeed * delta, locationDiff.y * maxSpeed * delta);
            body->SetLinearVelocity(moveSpeed);

            if(timer >= .25) {
                currentSubState = Shoot;
            }
        }

        if(currentSubState == Shoot) {
            if(currentWeapon->canShoot()){
                auto x = 1 * cos(2 * M_PI * shootFrame / 25);
                auto y = 1 * sin(2 * M_PI * shootFrame / 25);

                currentWeapon->shoot(x, y, position.getX() + (width / 2), position.getY() + (height / 2));
                shootFrame++;

                if(shootFrame == 25) {
                    currentSubState = Dart;
                    timer = 0;
                    targetX = rand() % 600 + 100;
                    targetY = rand() % 600 + 100;
                }
            }
        }
    }

    body->SetLinearDamping(5);
}