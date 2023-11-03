#if !defined(TEXTURE_H)
#define TEXTURE_H

/* ABC, my ANSI-compatible Base library for C */
#include <ABC/base.h>

/* SDL2_Image, for image loading */
#include <SDL2/SDL_image.h>

/* GLAD, the OpenGL wrapper */
#include <glad/glad.h>

/* Shaders */
#include "shader.h"

/* Needs malloc() and free() */
#include <stdlib.h>

/* Texture structure */
typedef struct {
  u32* textures;
  u32 numTextures;
} Texture;

/* Create a texture */
Texture createTexture(
    const char** fileNames,
    const char** shaderNames,
    u32 numTextures,
    ShaderHandle shader);

/* Destroy a texture */
void destroyTexture(Texture* texture);

/* Bind texture */
void bindTexture(Texture* texture);

#endif
