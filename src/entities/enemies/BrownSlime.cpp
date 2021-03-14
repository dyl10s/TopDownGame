#include "engine/Engine.hpp"
#include "engine/AssetLoader.hpp"
#include "entities/enemies/BaseEnemy.hpp"
#include "entities/enemies/BrownSlime.hpp"
#include "entities/weapons/TrippleShotGun.hpp"
#include "entities/Bullet.hpp"
#include "entities/Player.hpp"
#include <SDL2/SDL.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

BrownSlime::BrownSlime(Scene* scene, int x, int y) : BaseEnemy(scene, x, y, 20, 20, AssetLoader::brownSlime, 2){
    currentWeapon = (BaseWeapon*)new TrippleShotGun(scene, true);
    currentWeapon->setFirerate(1.3);
    maxSpeed = 100;
    health = 4;
}

BrownSlime::~BrownSlime(){

}

void BrownSlime::update(double delta) {
    standardUpdate(delta); // Basic sprite animation and death when hp <= 0
   
    playerLocation = currentScene->GetPlayerLocation();

    if(currentWeapon->canShoot()){

        // Closest axis to the player
        auto leftDir = playerLocation.getX() - position.getX();
        auto rightDir = position.getX() - playerLocation.getX();
        auto upDir = playerLocation.getY() - position.getY();
        auto downDir = position.getY() - playerLocation.getY();

        if(leftDir <= rightDir && leftDir <= upDir && leftDir <= downDir) {
            currentWeapon->shoot(Left, position.getX() + (width / 2), position.getY() + (height / 2));
        }

        if(rightDir <= leftDir && rightDir <= upDir && rightDir <= downDir) {
            currentWeapon->shoot(Right, position.getX() + (width / 2), position.getY() + (height / 2));
        }

        if(upDir <= rightDir && upDir <= leftDir && upDir <= downDir) {
            currentWeapon->shoot(Up, position.getX() + (width / 2), position.getY() + (height / 2));
        }

        if(downDir <= rightDir && downDir <= upDir && downDir <= leftDir) {
            currentWeapon->shoot(Down, position.getX() + (width / 2), position.getY() + (height / 2));
        }

        
        shootFrame++;
    }

    // Slowly move at the player
    auto locationDiff = b2Vec2(playerLocation.getX() - position.getX(), playerLocation.getY() - position.getY());
    locationDiff.Normalize();
    auto moveSpeed = b2Vec2(locationDiff.x * maxSpeed * delta, locationDiff.y * maxSpeed * delta);
    body->SetLinearVelocity(moveSpeed);
}