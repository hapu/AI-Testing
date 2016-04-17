#ifndef TETRAHEDRON_H_
#define TETRAHEDRON_H_

#include <Drawable.hpp>
#include <Camera/Camera.hpp>
#ifdef WIN32
#include <windows.h>
#endif
#include <GL/glew.h>
#include <GL/gl.h>

class Tetrahedron : Drawable {
 public:
  Tetrahedron();
  ~Tetrahedron();
  void init();
  void render(const Camera &cam);
  glm::vec3 position;
  glm::vec3 rotation;
  glm::vec3 scale;

 private:
  GLuint vbo_positions;
  GLuint vbo_colors;
  GLuint vbo_indices;
  ShaderProgram shaderProgram;
  glm::mat4 calcModelMatrix();
};

#endif  // TETRAHEDRON_H_
