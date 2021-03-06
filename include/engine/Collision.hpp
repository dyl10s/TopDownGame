#ifndef			__HPP_COLLISION__
#define			__HPP_COLLISION__

/**
 * This is NOT a decent attempt at a collision detection engine.
 * It is NOT optimized in any way.  It is merely a demonstration
 * of how we could plug a collision engine into our engine.
 **/

#include "Engine.hpp"
#include "Scene.hpp"
#include "Interfaces.hpp"
#include "Sprite.hpp"
#include <SDL2/SDL.h>
#include <box2d/box2d.h>
#include <vector>

const float METERSTOPIXELS = 50.0;

enum CollisionLayers {
	NONE = 0x0000,
	FRIENDLY = 0x0001,
	ENEMY = 0x0002,
	WALL = 0x0003,
	NOTSET = 0x0004,
	ALL = 0x0FFF,
	FLOOR = 0x1000,
};

class Collision: public UGameObject {

	public:
		Collision(b2Vec2 gravity);
		~Collision();
		void update(double delta);
		b2World* getWorld();
		b2Body* addObject(Sprite* object, uint16 category = NOTSET, uint16 collideWith = ALL);
		b2Body* addStatic(Sprite* object, uint16 category = NOTSET, uint16 collideWith = ALL);
		void removeObject(Sprite* object);

	private:
		b2World* world;		
		std::vector<std::pair<Sprite*, b2Body*> > objects;
};

#endif