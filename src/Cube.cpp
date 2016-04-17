

#include <Cube.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
using namespace std;

Cube::Cube() : vbo_indices(0), vbo_pos(0), rotation(0.0f,0.0f,0.0f), position(0.0f,0.0f,0.0f), scale(1.0f,1.0f,1.0f)
{

}


void Cube::init()
{
    shaderProgram.init("../resources/shaders/cube.vs","../resources/shaders/cube.fs");
    texture.init("../resources/textures/cube.tga", GL_TEXTURE_CUBE_MAP);

    glGenBuffers(1, &vbo_pos);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_pos);
    float vertices[] = {
        0.500000,  0.500000,  0.500000,
        0.500000,  0.500000, -0.500000,
        0.500000, -0.500000,  0.500000,
        0.500000, -0.500000, -0.500000,
       -0.500000,  0.500000, -0.500000,
       -0.500000,  0.500000,  0.500000,
       -0.500000, -0.500000,  0.500000,
       -0.500000, -0.500000, -0.500000,
	};
    glBufferData(GL_ARRAY_BUFFER, sizeof vertices, vertices, GL_STATIC_DRAW);
    glGenBuffers(1, &vbo_indices);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_indices);
    unsigned short indices[] = {
        0, 1, 2,
        1, 3, 2,
        4, 1, 0,
        4, 0, 5,
        5, 0, 2,
        5, 2, 6,
        7, 3, 2,
        7, 2, 6,
        5, 4, 7,
        5, 7, 6,
        4, 1, 3,
        4, 3, 7,
	};
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof indices, indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Cube::render(const Camera &cam)
{
  shaderProgram.useProgram();
  GLint loc = shaderProgram.getUniformLocation("texture");
  glActiveTexture(GL_TEXTURE0);
  texture.bindTexture();
  glUniform1i(loc, 0);

  loc = shaderProgram.getUniformLocation("mvp");
  glm::mat4 mvp = cam.getProjectionMatrix() * cam.calcViewMatrix() * calcModelMatrix();
  glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(mvp));

  loc = shaderProgram.getAttribLocation("pos");
  glEnableVertexAttribArray(loc);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_pos);
  glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0 , 0);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_indices);
  glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

}


glm::mat4 Cube::calcModelMatrix()
{
    return glm::translate(position) *
        glm::rotate(rotation.x, glm::vec3(1.0f,0.0f,0.0f)) *
        glm::rotate(rotation.y, glm::vec3(0.0f,1.0f,0.0f)) *
        glm::rotate(rotation.z, glm::vec3(0.0f,0.0f,1.0f)) *
        glm::scale(scale);
}

Cube::~Cube()
{
    glDeleteBuffers(1, &vbo_pos);
    glDeleteBuffers(1, &vbo_indices);
}
