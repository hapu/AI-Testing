#pragma once
#ifndef _SCENE_H_
#define _SCENE_H_

#include <Camera/Camera.hpp>
#include <MinecraftCube.hpp>
#include <Tetrahedron.hpp>

class Scene {
 private:
  static Camera camera;
  static MinecraftCube cube;
  static Tetrahedron tetra;

 public:
  static void init();
  static void update(float dt = 0.0f);
  static void render();
  static void cleanUp();
  static void updateCamera(float dt);
  static char map[20 * 20];
};

#endif  //_SCENE_H_
