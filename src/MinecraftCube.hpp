#pragma once
#ifndef _MINECRAFT_CUBE_H_
#define _MINECRAFT_CUBE_H_

#include <Drawable.hpp>
#include <Camera/Camera.hpp>
#include <Textures/Texture.hpp>
#include <ShaderProgram/ShaderProgram.hpp>
#include <glm/glm.hpp>

class MinecraftCube : Drawable
{
    public:
        MinecraftCube();
        ~MinecraftCube();
        void init();
        void render(const Camera& cam){};
        void render(const Camera& cam, char*map, int side);
    private:
        glm::vec3 position;
        glm::vec3 rotation;
        glm::vec3 scale;

        GLuint vbo_pos;
        GLuint vbo_indices;

        ShaderProgram shaderProgram;
        Texture texture;
        glm::mat4 calcModelMatrix();

        void renderCubes(const Camera& cam, float x, float z, int count);
};

#endif // _MINECRAFT_CUBE_H_