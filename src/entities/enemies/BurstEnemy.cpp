#include "engine/Engine.hpp"
#include "engine/AssetLoader.hpp"
#include "entities/enemies/BaseEnemy.hpp"
#include "entities/enemies/BurstEnemy.hpp"
#include "entities/weapons/NoobEnemyGun.hpp"
#include "entities/weapons/BurstGun.hpp"
#include "entities/Bullet.hpp"
#include "entities/Player.hpp"
#include <SDL2/SDL.h>
#include <time.h>
#include <stdlib.h>

BurstEnemy::BurstEnemy(Scene* scene, int x, int y) : BaseEnemy(scene, x, y, 20, 20, AssetLoader::burstEnemy){
    currentWeapon = (BaseWeapon*)new BurstGun(scene, true);
    maxSpeed = 2000;
}

BurstEnemy::~BurstEnemy(){

}

void BurstEnemy::update(double delta) {
    standardUpdate(delta); // Basic sprite animation and death when hp <= 0
    timeSinceAction += delta;

    if(currentState == Wait){
        if(timeSinceAction > waitTime){
            currentState = Chase;
            
            // Find the players location
            playerLocation.setX(currentScene->GetPlayerLocation().getX());
            playerLocation.setY(currentScene->GetPlayerLocation().getY());
            timeSinceAction = 0;
        }
    }else if(currentState == Chase){
        auto locationDiff = b2Vec2(playerLocation.getX() - position.getX(), playerLocation.getY() - position.getY());
        locationDiff.Normalize();
        auto moveSpeed = b2Vec2(locationDiff.x * maxSpeed * delta, locationDiff.y * maxSpeed * delta);
        body->SetLinearVelocity(moveSpeed);

        if(timeSinceAction > chaseTime){
            currentState = Burst;
            timeSinceAction = 0;
        }
    }else if(currentState == Burst){
        // Direction does not matter because burst gun
        currentWeapon->shoot(Up, position.getX(), position.getY());
        currentState = Wait;
        timeSinceAction = 0;
    }
}