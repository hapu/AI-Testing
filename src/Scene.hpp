#pragma once
#ifndef _SCENE_H_
#define _SCENE_H_

#include <Camera/Camera.hpp>
#include <Cube.hpp>

class Scene {
 private:
  static Camera camera;
  static Cube block;
  static char map[9][9];

 public:
  static void init();
  static void update(float dt = 0.0f);
  static void render();
  static void cleanUp();
};

#endif  //_SCENE_H_
