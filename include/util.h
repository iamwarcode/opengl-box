#ifndef UTIL_H
#define UTIL_H
#define GLEW_STATIC
#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>

#include <glm/glm.hpp>

#include <stdio.h>
#include <stdlib.h>

GLuint make_buffer(GLenum target, GLsizei size, const void *data);
GLuint make_shader(GLenum type, const char *source);
GLuint load_shader(GLenum type, const char *path);
GLuint make_program(GLuint shader1, GLuint shader2);
GLuint load_program(GLenum type1, GLenum type2, const char *path1, const char *path2);

#endif