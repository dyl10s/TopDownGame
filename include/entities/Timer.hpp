#ifndef			__HPP__TIMER__
#define			__HPP__TIMER__

#include "engine/Sprite.hpp"
#include "engine/Scene.hpp"

class Timer : public Sprite {
	public:
		Timer(Scene* scene);
		void update(double delta);
		void stop();
		void start();
		void reset();
	private:
		bool timerRunning = false;
		long double ellapsedGameTime;
		Scene* currentScene;
};

#endif
