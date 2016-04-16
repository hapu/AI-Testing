#pragma once
#ifndef _SCENE_H_
#define _SCENE_H_


class Scene
{
    private:

    public:
        static void init();
        static void update(float dt = 0.0f);
        static void render();
        static void cleanUp();
};

#endif //_SCENE_H_
