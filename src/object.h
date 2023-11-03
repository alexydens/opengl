#if !defined(OBJECT_H)
#define OBJECT_H

/* ABC, my ANSI-compatible Base library for C */
#include <ABC/base.h>

/* kazmath, like GLM but for C */
#include <kazmath/kazmath.h>

/* project headers */
#include "shader.h"
#include "mesh.h"
#include "texture.h"
#include "obj_parser.h"

typedef struct {
  /* Vertex data - OBJ model */
  char* obj_path;
  /* Texture data - Images */
  char** texture_paths;
  char** texture_names;
  u32 numTextures;

  /* Shaders - paths */
  char* frag_path;
  char* vert_path;
} ObjectCreateInfo;

typedef struct {
  /* Mesh and VertexBuffer */
  Mesh mesh;
  VertexBuffer vBuffer;
  /* Shader */
  ShaderHandle shader;
  /* Texture */
  Texture texture;
  /* Model matrix */
  kmMat4 model;
} Object;

/* Create and destroy object */
Object createObject(ObjectCreateInfo createInfo);
void destroyObject(Object* object);

/* Draw object */
void drawObject(Object* object, kmMat4 view, kmMat4 projection, kmVec3 camPos);

#endif /* OBJECT_H */
