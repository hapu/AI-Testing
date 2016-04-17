

#include <Scene.hpp>
#include <InputManager/InputManager.hpp>
#ifdef WIN32
#include <windows.h>
#endif
#include <GL/glew.h>
#include <GL/gl.h>
#include <iostream>

Camera Scene::camera;
Cube Scene::block;
char Scene::map[9][9] = {{2, 1, 1, 1, 1, 1, 1, 1, 2},
                         {1, 0, 0, 0, 0, 0, 0, 0, 1},
                         {1, 0, 1, 1, 1, 1, 1, 0, 1},
                         {1, 0, 1, 2, 2, 2, 1, 0, 1},
                         {1, 0, 1, 2, 0, 2, 1, 0, 1},
                         {1, 0, 1, 2, 2, 2, 1, 0, 1},
                         {1, 0, 1, 1, 1, 1, 1, 0, 1},
                         {1, 0, 0, 0, 1, 0, 0, 0, 1},
                         {2, 1, 1, 1, 1, 1, 1, 1, 2}};

void Scene::init() {
  glewInit();
  glEnable(GL_DEPTH_TEST);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  camera.init(-2.5f, 7.5f, 10.0f, -0.785398f, -0.785398f, 0.0f);
  block.init();
}

void Scene::update(float dt) {
  float rot_speed = InputManager::keyboard.lctrl ? 6.0f : 3.0f;

  if (InputManager::keyboard.right) camera.rotation.y -= rot_speed * dt;
  if (InputManager::keyboard.left) camera.rotation.y += rot_speed * dt;
  if (InputManager::keyboard.up) camera.rotation.x += rot_speed * dt;
  if (InputManager::keyboard.down) camera.rotation.x -= rot_speed * dt;

  if (InputManager::keyboard.rshift) camera.scale.z += rot_speed * dt;
  if (InputManager::keyboard.rctrl) camera.scale.z -= rot_speed * dt;

  // TRASLADAR LA CAMARA
  // movimiento del jugador
  glm::vec4 tmp_movement(0.0f, 0.0f, 0.0f, 0.0f);
  if (InputManager::keyboard.w) tmp_movement.z -= rot_speed * dt;
  if (InputManager::keyboard.s) tmp_movement.z += rot_speed * dt;
  if (InputManager::keyboard.a) tmp_movement.x -= rot_speed * dt;
  if (InputManager::keyboard.d) tmp_movement.x += rot_speed * dt;
  if (InputManager::keyboard.lshift) tmp_movement.y -= rot_speed * dt;
  if (InputManager::keyboard.space) tmp_movement.y += rot_speed * dt;

  tmp_movement =
      glm::rotate(camera.rotation.y, glm::vec3(0.0f, 1.0f, 0.0)) * tmp_movement;
  camera.position += glm::vec3(tmp_movement.x, tmp_movement.y, tmp_movement.z);
  // if (InputManager::keyboard.lctrl)
  //   printf("camera.init(%.2f, %.2f, %.2f, %.2f, %.2f, %.2f)", camera.position.x,
  //          camera.position.y, camera.position.z, camera.rotation.x,
  //          camera.rotation.y, camera.rotation.z);
}

void Scene::render() {
  // It clears the screen
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  unsigned char height = 9;
  unsigned char width = 9;
  for (unsigned char x = 0; x < width; x++) {
    for (unsigned char y = 0; y < height; y++) {
      for (unsigned char h = 0; h < map[y][x]; h++) {
        block.position.x = x * 1.0;
        block.position.z = y * 1.0;
        block.position.y = h * 1.0;
        block.render(camera);
      }
    }
  }
}

void Scene::cleanUp() {}
