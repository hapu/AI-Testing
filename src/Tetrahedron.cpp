#include <Tetrahedron.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Tetrahedron::Tetrahedron()
    : position(0.0f, 0.0f, 0.0f),
      rotation(0.0f, 0.0f, 0.0f),
      scale(1.0f, 1.0f, 1.0f) {}

void Tetrahedron::init() {
  glEnable(GL_BLEND);
  shaderProgram.init("../resources/shaders/basic.vs",
                     "../resources/shaders/basic.fs");

  glGenBuffers(1, &vbo_positions);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_positions);
  float vertices[] = {
      -0.5f, 0.5f, -0.5f,  // Vertex 1
      0.5f,  0.5f, -0.5f,  // Vertex 2
      0.0f,  0.5f,  0.5f,  // Vertex 3
      0.0f,  -0.5f,  0.0f,  // Vertex 4
  };
  glBufferData(GL_ARRAY_BUFFER, sizeof vertices, vertices, GL_STATIC_DRAW);

  glGenBuffers(1, &vbo_colors);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_colors);
  float colors[] = {
      1.0f, 0.0f, 1.0f,  // color 1
      0.0f, 1.0f, 1.0f,  // color 2
      0.0f, 0.0f, 1.0f,  // color 3
      1.0f, 1.0f, 1.0f,  // color 4
  };
  glBufferData(GL_ARRAY_BUFFER, sizeof colors, colors, GL_STATIC_DRAW);

  glGenBuffers(1, &vbo_indices);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_indices);
  unsigned short indices[] = {
      0, 2, 3,  // Face 1
      0, 1, 2,  // Face 2
      0, 1, 3,  // Face 3
      2, 1, 3,  // Face 4
  };
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof indices, indices, GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Tetrahedron::render(const Camera &camera) {
  shaderProgram.makeCurrent();

  glm::mat4 mvp =
      camera.getProjectionMatrix() * camera.calcViewMatrix() * calcModelMatrix();
  int address = shaderProgram.getUniformLocation("mvp");
  glUniformMatrix4fv(address, 1, GL_FALSE, glm::value_ptr(mvp));

  address = shaderProgram.getAttribLocation("position");
  glEnableVertexAttribArray(address);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_positions);
  glVertexAttribPointer(address, 3, GL_FLOAT, GL_FALSE, 0, 0);

  address = shaderProgram.getAttribLocation("color");
  glEnableVertexAttribArray(address);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_colors);
  glVertexAttribPointer(address, 3, GL_FLOAT, GL_FALSE, 0, 0);

  // Index buffer
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_indices);
  // Draw the triangles !
  glDrawElements(GL_TRIANGLES,       // mode
                 12,                 // count
                 GL_UNSIGNED_SHORT,  // type
                 0                   // element array buffer offset
                 );

  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

glm::mat4 Tetrahedron::calcModelMatrix() {
  glm::mat4 translate = glm::translate(position);
  glm::mat4 rotX = glm::rotate(rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
  glm::mat4 rotY = glm::rotate(rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
  glm::mat4 rotZ = glm::rotate(rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
  glm::mat4 scaleMatrix = glm::scale(scale);

  return translate * scaleMatrix * rotX * rotY * rotZ;
}

Tetrahedron::~Tetrahedron() {
  glDeleteBuffers(1, &vbo_positions);
  glDeleteBuffers(1, &vbo_colors);
  glDeleteBuffers(1, &vbo_indices);
}
