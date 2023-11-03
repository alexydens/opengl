#if !defined(OBJ_PARSER)
#define OBJ_PARSER

/* ABC, My ANSI-compatible Base library for C */
#include <ABC/base.h>

/* For file handling */
#include <stdio.h>

typedef struct {
  f32* data;
  u32 vertexCount;
} VertexBuffer;

/* Create vertex buffer */
VertexBuffer createVertexBuffer(const char* obj_path);

/* Destroy vertex buffer */
void destroyVertexBuffer(VertexBuffer* buffer);

#endif /* OBJ_PARSER */
