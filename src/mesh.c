#include "mesh.h"

/* Creation and destruction of Mesh */
Mesh createMesh(MeshCreateInfo createInfo) {
  /* Mesh to return */
  Mesh mesh;
  /* A total of all the attributes */
  u32 attribTotal = 0;
  /* A total of all the attributes so far */
  u32 runningTot = 0;
  /* For for loops */
  u32 i;
  /* Set num vertices */
  mesh.numVertices = createInfo.numVertices;
  /* Get attribTotal */
  for (i = 0; i < createInfo.numAttribs; i++) {
    attribTotal += createInfo.attribs[i];
  }

  /* Vertex Array Object */
  glGenVertexArrays(1, &mesh.VAO);
  glBindVertexArray(mesh.VAO);

  /* Vertex Buffer Object */
  glGenBuffers(1, &mesh.VBO);
  glBindBuffer(GL_ARRAY_BUFFER, mesh.VBO);

  /* Vertex data */
  glBufferData(
      GL_ARRAY_BUFFER,
      sizeof(f32) * attribTotal * createInfo.numVertices,
      createInfo.vertices,
      GL_DYNAMIC_DRAW
  );
  
  /* Vertex attribs */
  for (i = 0; i < createInfo.numAttribs; i++) {
    glVertexAttribPointer(
        i, createInfo.attribs[i],
        GL_FLOAT, GL_FALSE,
        attribTotal * sizeof(f32),
        (void*)(runningTot * sizeof(f32))
    );
    glEnableVertexAttribArray(i);
    runningTot += createInfo.attribs[i];
  }

  return mesh;
}
void destroyMesh(Mesh* mesh) {
  glDeleteVertexArrays(1, &mesh->VAO);
  glDeleteBuffers(1, &mesh->VBO);
}

/* Draw the mesh */
void drawMesh(Mesh* mesh) {
  glBindVertexArray(mesh->VAO);
  glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO);
  glDrawArrays(GL_TRIANGLES, 0, mesh->numVertices);
}
