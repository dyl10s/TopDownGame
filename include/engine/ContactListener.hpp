#ifndef			__HPP__CONTACTLISTENER__
#define			__HPP__CONTACTLISTENER__

#include <box2d/box2d.h>
#include "engine/Scene.hpp"

class ContactListener : public b2ContactListener {
    public:
        ContactListener(Scene* scene);
        void BeginContact(b2Contact* contact);
    private:
        Scene* currentScene;
};

#endif