

#include <Scene.hpp>
#include <InputManager/InputManager.hpp>
#ifdef WIN32
#include <windows.h>
#endif
#include <GL/glew.h>
#include <GL/gl.h>

void Scene::init()
{
    glewInit();
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void Scene::update(float dt)
{
   // update your scene here
}

void Scene::render()
{
    // It clears the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}

void Scene::cleanUp()
{

}
