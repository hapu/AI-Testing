

#include <Scene.hpp>
#include <InputManager/InputManager.hpp>
#ifdef WIN32
#include <windows.h>
#endif
#include <GL/glew.h>
#include <GL/gl.h>
#include <iostream>

using namespace std;

Camera Scene::camera;
MinecraftCube Scene::cube;
Tetrahedron Scene::tetra;

char Scene::map[20*20] = {
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
};

void Scene::init()
{
    glewInit();
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.9f, 0.9f, 1.0f, 1.0f);
    camera.init(24.0, 15.0, 24.0, -0.785398, 0.785398, 0.00);
    cube.init();
    tetra.init();
    tetra.position.y++;
}

void Scene::update(float dt)
{
    updateCamera(dt);
}

void Scene::render()
{
    // It clears the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    cube.render(camera, map, 20);
    tetra.render(camera);
}

void Scene::cleanUp() {}

void Scene::updateCamera(float dt)
{
   float rot_speed = InputManager::keyboard.lctrl? 6.0f : 3.0f;
   if (InputManager::keyboard.right) camera.rotation.y -= rot_speed * dt;
   if (InputManager::keyboard.left) camera.rotation.y += rot_speed * dt;
   if (InputManager::keyboard.up) camera.rotation.x += rot_speed * dt;
   if (InputManager::keyboard.down) camera.rotation.x -= rot_speed * dt;
   if (InputManager::keyboard.rshift) camera.scale.z += rot_speed * dt;
   if (InputManager::keyboard.rctrl) camera.scale.z -= rot_speed * dt;
   glm::vec4 tmp_movement(0.0f, 0.0f, 0.0f, 0.0f);
   if (InputManager::keyboard.w) tmp_movement.z -= rot_speed * dt;
   if (InputManager::keyboard.s) tmp_movement.z += rot_speed * dt;
   if (InputManager::keyboard.a) tmp_movement.x -= rot_speed * dt;
   if (InputManager::keyboard.d) tmp_movement.x += rot_speed * dt;
   if (InputManager::keyboard.lshift) tmp_movement.y -= rot_speed * dt;
   if (InputManager::keyboard.space) tmp_movement.y += rot_speed * dt;
   tmp_movement = glm::rotate(camera.rotation.y, glm::vec3(0.0f, 1.0f, 0.0)) * tmp_movement;
   camera.position += glm::vec3(tmp_movement.x, tmp_movement.y, tmp_movement.z);
   //printf("camera.init(%.2f, %.2f, %.2f, %.2f, %.2f, %.2f)\r\n", camera.position.x, camera.position.y, camera.position.z, camera.rotation.x, camera.rotation.y, camera.rotation.z);
}
