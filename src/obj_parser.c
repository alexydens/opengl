#include "obj_parser.h"

VertexBuffer createVertexBuffer(const char* obj_path) {
  VertexBuffer buffer;
  f32* normals = NULL;
  f32* positions = NULL;
  f32* texCoords = NULL;
  u32 numNormals = 0;
  u32 numPositions = 0;
  u32 numTexCoords = 0;
  FILE* file;
  char chIn;
  buffer.data = NULL;
  buffer.vertexCount = 0;

  /* Open file */
  file = fopen(obj_path, "r");

  /* Loop through characters of file */
  while (!feof(file)) {
    /* Get next character */
    chIn = fgetc(file);
    switch (chIn) {
      case 'v':
        {
          /* Not enough to tell what to do - get next char */
          chIn = fgetc(file);
          switch (chIn) {
            case ' ': /* Position: v x y z */
              {
                /* Parse position */
                i32 i;
                if (positions == NULL) {
                  positions = (f32*)malloc(sizeof(f32) * 3);
                  numPositions++;
                } else
                  positions =
                    (f32*)realloc(positions, sizeof(f32) * 3 * ++numPositions);
                for (i = 0; i < 3; i++) {
                  f32 res;
                  ASSERT(fscanf(file, " %f", &res) != EOF);
                  positions[((numPositions-1)*3)+i] = res;
                }
              } break;
            case 'n': /* Normal: vn x y z */
              {
                /* Parse normal */
                i32 i;
                if (normals == NULL) {
                  normals = (f32*)malloc(sizeof(f32) * 3);
                  numNormals++;
                } else
                  normals =
                    (f32*)realloc(normals, sizeof(f32) * 3 * ++numNormals);
                for (i = 0; i < 3; i++) {
                  f32 res;
                  ASSERT(fscanf(file, " %f", &res) != EOF);
                  normals[((numNormals-1)*3)+i] = res;
                }
              } break;
            case 't': /* Texture coordinate: vt u v */
              {
                /* Parse texCoord */
                i32 i;
                if (texCoords == NULL) {
                  texCoords = (f32*)malloc(sizeof(f32) * 2);
                  numTexCoords++;
                } else
                  texCoords =
                    (f32*)realloc(texCoords, sizeof(f32) * 2 * ++numTexCoords);
                for (i = 0; i < 2; i++) {
                  f32 res;
                  ASSERT(fscanf(file, " %f", &res) != EOF);
                  texCoords[((numTexCoords-1)*2)+i] = res;
                }
              } break;
            default: break;
          }
        } break;
      case 'f': /* Face: f p/t/n p/t/n p/t/n */
        {
          /* Parse face */
          u32 face[3][3];
          u32 i;
          for (i = 0; i < 3; i++) {
            ASSERT(fscanf(file, " %u/%u/%u", &face[i][0], &face[i][1], &face[i][2]) != EOF);
          }
          for (i = 0; i < 3; i++) {
            if (buffer.data == NULL) {
              buffer.data = (f32*)malloc(sizeof(f32) * 8);
              buffer.vertexCount = 1;
            } else {
              buffer.data =
                (f32*)realloc(buffer.data, sizeof(f32) * 8 * ++buffer.vertexCount);
            }
            buffer.data[((buffer.vertexCount-1)*8)] =   positions[(face[i][0]-1)*3];
            buffer.data[((buffer.vertexCount-1)*8)+1] = positions[(face[i][0]-1)*3+1];
            buffer.data[((buffer.vertexCount-1)*8)+2] = positions[(face[i][0]-1)*3+2];
            buffer.data[((buffer.vertexCount-1)*8)+3] = texCoords[(face[i][1]-1)*2];
            buffer.data[((buffer.vertexCount-1)*8)+4] = texCoords[(face[i][1]-1)*2+1];
            buffer.data[((buffer.vertexCount-1)*8)+5] =   normals[(face[i][2]-1)*3];
            buffer.data[((buffer.vertexCount-1)*8)+6] =   normals[(face[i][2]-1)*3+1];
            buffer.data[((buffer.vertexCount-1)*8)+7] =   normals[(face[i][2]-1)*3+2];
          }
        } break;
      default: break;
    }
  }

  /* Free arrays */
  free(positions);
  free(normals);
  free(texCoords);

  /* Close file */
  fclose(file);

  return buffer;
}

void destroyVertexBuffer(VertexBuffer* buffer) {
  free(buffer->data);
}
