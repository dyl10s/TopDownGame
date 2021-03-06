#include "entities/Bullet.hpp"
#include "engine/Collision.hpp"

Bullet::Bullet(Scene* scene, int x, int y, int xVel, int yVel) : Sprite("./assets/coin.png", 0, 6, 7){
    currentScene = scene;
    position.setX(x);
    position.setY(y);
    velocity.setX(xVel);
    velocity.setY(yVel);
    
    auto body = currentScene->getCollision()->addObject(this, FRIENDLY, ENEMY);
    this->setBody(body);
}

Bullet::~Bullet(){
    // Clean up the collision body somehow
    // delete body breaks for some weird reason
}

void Bullet::update(double delta){
    auto moveSpeed = b2Vec2(velocity.getX() * delta, velocity.getY() * delta);
	body->SetLinearVelocity(moveSpeed);
    if(
        position.getX() < 0 || position.getY() < 0 || 
        position.getX() > 1024 || position.getY() > 768) {
        currentScene->removeObject(this);
    }
}
