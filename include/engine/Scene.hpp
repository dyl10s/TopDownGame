#ifndef			__HPP__SCENE__
#define			__HPP__SCENE__

#include <SDL2/SDL.h>
#include <vector>
#include <utility>
#include <functional>
#include "Interfaces.hpp"
#include "Collision.hpp"
#include "Utility.hpp"

// http://www.cplusplus.com/forum/general/56475/
class Collision;

class Scene {
	public:
		Scene();
		Scene(Collision* collision);
		~Scene();
		void addUpdateable(Updateable* obj);
		void addDrawable(Drawable* obj);
		void addKeyEvent(SDL_Keycode key, Callback fn);
		Collision* getCollision();
		void createUpdateable(Updateable* obj);
		void createDrawable(Drawable* obj);

		void removeObject(DUGameObject* obj);
		void createObject(DUGameObject* obj);

		void SetPlayerLocation(double x, double y);
		Vector2 GetPlayerLocation();

		std::vector<Updateable*> getUpdateables();
		std::vector<Drawable*> getDrawables();
	private:
		std::vector<Updateable*> updateables;
		std::vector<Drawable*> drawables;

		std::vector<Drawable*> createDrawables;
		std::vector<Updateable*> createUpdatables;

		std::vector<DUGameObject*> removedObjects;
		std::vector<DUGameObject*> createdObjects;

		std::vector<std::pair<SDL_Keycode, Callback > > keyEvents;
		Collision* collision;

		Vector2 playerLocation;
	friend class Engine;
};

#endif
