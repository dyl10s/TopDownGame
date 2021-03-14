#include "engine/Engine.hpp"
#include "engine/AssetLoader.hpp"
#include "entities/enemies/BaseEnemy.hpp"
#include "entities/enemies/SpiralEnemy.hpp"
#include "entities/weapons/MachineGun.hpp"
#include "entities/Bullet.hpp"
#include "entities/Player.hpp"
#include <SDL2/SDL.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

SpiralEnemy::SpiralEnemy(Scene* scene, int x, int y) : BaseEnemy(scene, x, y, 40, 50, AssetLoader::spiralEnemy){
    currentWeapon = (BaseWeapon*)new MachineGun(scene, true);
    maxSpeed = 100;
    health = 10;
}

SpiralEnemy::~SpiralEnemy(){

}

void SpiralEnemy::update(double delta) {
    standardUpdate(delta); // Basic sprite animation and death when hp <= 0
   
    playerLocation = currentScene->GetPlayerLocation();

    if(currentWeapon->canShoot()){
        auto x = 1 * cos(2 * M_PI * shootFrame / 75);
        auto y = 1 * sin(2 * M_PI * shootFrame / 75);

        currentWeapon->shoot(x, y, position.getX() + (width / 2), position.getY() + (height / 2));
        shootFrame++;
    }

    // Slowly move at the player
    auto locationDiff = b2Vec2(playerLocation.getX() - position.getX(), playerLocation.getY() - position.getY());
    locationDiff.Normalize();
    auto moveSpeed = b2Vec2(locationDiff.x * maxSpeed * delta, locationDiff.y * maxSpeed * delta);
    body->SetLinearVelocity(moveSpeed);
}