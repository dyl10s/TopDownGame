#include "entities/Bullet.hpp"

Bullet::Bullet(Scene* scene, int x, int y, int xVel, int yVel) : Sprite("./assets/coin.png"){
    currentScene = scene;
    position.setX(x);
    position.setY(y);
    velocity.setX(xVel);
    velocity.setY(yVel);
}

void Bullet::update(double delta){
    position.setX(position.getX() + (velocity.getX() * delta));
    position.setY(position.getY() + (velocity.getY() * delta));
}
