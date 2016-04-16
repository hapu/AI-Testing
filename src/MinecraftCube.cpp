

#include <MinecraftCube.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
using namespace std;

MinecraftCube::MinecraftCube() : vbo_indices(0), vbo_pos(0), rotation(0.0f,0.0f,0.0f), position(0.0f,0.0f,0.0f), scale(1.0f,1.0f,1.0f)
{

}


void MinecraftCube::init()
{
    shaderProgram.init("../../resources/shaders/minecraft.vs","../../resources/shaders/minecraft.fs");
    texture.init("../../resources/textures/minecraft.tga", GL_TEXTURE_CUBE_MAP);

    glGenBuffers(1, &vbo_pos);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_pos);
    float vertices[] = {
        1.000000,  1.000000,  1.000000,
        1.000000,  1.000000, -1.000000,
        1.000000, -1.000000,  1.000000,
        1.000000, -1.000000, -1.000000,
       -1.000000,  1.000000, -1.000000,
       -1.000000,  1.000000,  1.000000,
       -1.000000, -1.000000,  1.000000,
       -1.000000, -1.000000, -1.000000,
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

void MinecraftCube::render(const Camera &cam, char*map, int side)
{
    shaderProgram.useProgram();
    GLint loc = shaderProgram.getUniformLocation("texture");
    glActiveTexture(GL_TEXTURE0);
    texture.bindTexture();
    glUniform1i(loc, 0);

    for(int x = 0; x < side; x++)
    {
        for(int y = 0; y < side; y++)
        {
            int index = (y * side) + x;
            renderCubes(cam, x * 2.0f, y * 2.0f, map[index] );
        }
    }

    renderCubes(cam, 0.0f, 0.0f, 1);

}

void MinecraftCube::renderCubes(const Camera& cam, float x, float y, int count)
{
    for(int i = 0; i < count; i++)
    {
        position.x = x;
        position.z = y;
        position.y = (i-1)*2.0f;
        GLint loc = shaderProgram.getUniformLocation("mvp");
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
}


glm::mat4 MinecraftCube::calcModelMatrix()
{
    return glm::translate(position) * 
        glm::rotate(rotation.x, glm::vec3(1.0f,0.0f,0.0f)) *
        glm::rotate(rotation.y, glm::vec3(0.0f,1.0f,0.0f)) *
        glm::rotate(rotation.z, glm::vec3(0.0f,0.0f,1.0f)) *
        glm::scale(scale);
}

MinecraftCube::~MinecraftCube()
{
    glDeleteBuffers(1, &vbo_pos);
    glDeleteBuffers(1, &vbo_indices);
}