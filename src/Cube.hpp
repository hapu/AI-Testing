#pragma once
#ifndef CUBE_H_
#define CUBE_H_

#include <Drawable.hpp>
#include <Camera/Camera.hpp>
#include <Textures/Texture.hpp>
#include <ShaderProgram/ShaderProgram.hpp>
#include <glm/glm.hpp>

class Cube : Drawable
{
public:
  Cube();
  ~Cube();
  void init();
  void render(const Camera& cam);
  glm::vec3 position;
  glm::vec3 rotation;
  glm::vec3 scale;
private:
  GLuint vbo_pos;
  GLuint vbo_indices;

  ShaderProgram shaderProgram;
  Texture texture;
  glm::mat4 calcModelMatrix();
};

#endif // CUBE_H_
