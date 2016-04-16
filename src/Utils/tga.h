#pragma once
#ifndef _UTILS_UTILS_H
#define _UTILS_UTILS_H

#ifdef WIN32
#include <windows.h>
#endif
#include <GL/glew.h>
#include <GL/gl.h>

char * LoadTGA( const char * szFileName, int * width, int * height, int * bpp );
void LoadFace(const char* bufferTGA, int width, GLenum type, int bytePP, char* face);

#endif // _UTILS_UTILS_H
