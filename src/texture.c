#include "texture.h"

/* Create a texture */
Texture createTexture(
    const char** fileNames,
    const char** shaderNames,
    u32 numTextures,
    ShaderHandle shader) {
  Texture texture;
  SDL_Surface* img_surface;
  i32 mode;
  u32 i;
  texture.textures = malloc(sizeof(u32) * numTextures);

  /* set numTextures */
  texture.numTextures = numTextures;

  /* Generate handles */
  glGenTextures(numTextures, texture.textures);
  /* Generate rest, bind */
  for (i = 0; i < numTextures; i++) {
    glActiveTexture(GL_TEXTURE0 + i);
    glBindTexture(GL_TEXTURE_2D, texture.textures[i]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    /* Set uniform */
    bindShader(shader);
    glUniform1i(glGetUniformLocation(shader, shaderNames[i]), i);

    /* Load image */
    img_surface = IMG_Load(fileNames[i]);
    mode = GL_RGB;
    if (img_surface->format->BytesPerPixel == 4)
      mode = GL_RGBA;
    glTexImage2D(
        GL_TEXTURE_2D, 0, mode,
        img_surface->w, img_surface->h,
        0, mode, GL_UNSIGNED_BYTE,
        img_surface->pixels
    );
    SDL_FreeSurface(img_surface);
  }

  return texture;
}
/* Destroy a texture */
void destroyTexture(Texture* texture) {
  glDeleteTextures(texture->numTextures, texture->textures);
  free(texture->textures);
}

/* Bind texture */
void bindTexture(Texture* texture) {
  u32 i;
  for (i = 0; i < texture->numTextures; i++) {
    glActiveTexture(GL_TEXTURE0 + i);
    glBindTexture(GL_TEXTURE_2D, texture->textures[i]);
  }
}
