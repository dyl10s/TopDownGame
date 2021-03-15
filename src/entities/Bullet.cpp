#include "entities/Bullet.hpp"
#include "engine/Collision.hpp"
#include "engine/AssetLoader.hpp"

Bullet::Bullet(Scene* scene, int x, int y, double xVel, double yVel, int damage, bool enemy, double scale) : 
    Sprite({
        enemy ?
        Sprite{AssetLoader::tilesheet, AssetLoader::enemyBullet, 4, .2, 0, static_cast<int>(10 * scale), static_cast<int>(10 * scale)} :
        Sprite{AssetLoader::tilesheet, AssetLoader::friendlyBullet, 4, .2, 0, static_cast<int>(10 * scale), static_cast<int>(10 * scale)}
    }) {
    currentScene = scene;
    position.setX(x);
    position.setY(y);
    velocity.setX(xVel);
    velocity.setY(yVel);

    this->damage = damage;
    
    setType("Bullet");

    if(enemy){
        auto body = currentScene->getCollision()->addObject(this, ENEMYBULLET, FRIENDLY);
        this->setBody(body);
    }else{
        auto body = currentScene->getCollision()->addObject(this, FRIENDLYBULLET, ENEMY);
        this->setBody(body);
    }
}

Bullet::~Bullet(){
    // Clean up the collision body somehow (this is done by the Collision class)
}

void Bullet::update(double delta){
    Sprite::update(delta);
    auto moveSpeed = b2Vec2(velocity.getX() * delta, velocity.getY() * delta);
	body->SetLinearVelocity(moveSpeed);
    if(
        position.getX() < 0 || position.getY() < 0 || 
        position.getX() > 1024 || position.getY() > 768) {
        currentScene->removeObject(this);
    }
}

int Bullet::getDamage(){
    return damage;
}
