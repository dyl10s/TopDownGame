#ifndef			__HPP__SCENE__
#define			__HPP__SCENE__

#include <SDL2/SDL.h>
#include <vector>
#include <utility>
#include <functional>
#include "Interfaces.hpp"
#include "Utility.hpp"

class Scene {
	public:
		Scene();
		~Scene();
		void addUpdateable(Updateable* obj);
		void addDrawable(Drawable* obj);
		void addKeyEvent(SDL_Keycode key, Callback fn);

		void createUpdateable(Updateable* obj);
		void createDrawable(Drawable* obj);

		void removeObject(DUGameObject* obj);
		void createObject(DUGameObject* obj);
	private:
		std::vector<Updateable*> updateables;
		std::vector<Drawable*> drawables;

		std::vector<Drawable*> createDrawables;
		std::vector<Updateable*> createUpdatables;

		std::vector<DUGameObject*> removedObjects;
		std::vector<DUGameObject*> createdObjects;

		std::vector<std::pair<SDL_Keycode, Callback > > keyEvents;

	friend class Engine;
};

#endif
