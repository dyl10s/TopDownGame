#include "entities/Bullet.hpp"
#include "engine/Collision.hpp"

Bullet::Bullet(Scene* scene, int x, int y, int xVel, int yVel) : Sprite("./assets/coin.png", 0, 12, 14){
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
        body->GetPosition().x * METERSTOPIXELS < 0 || body->GetPosition().y * METERSTOPIXELS < 0 || 
        body->GetPosition().x * METERSTOPIXELS > 1024 || body->GetPosition().y * METERSTOPIXELS > 768) {
        currentScene->removeObject(this);
    }
}
