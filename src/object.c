#include "object.h"

Object createObject(ObjectCreateInfo createInfo) {
  Object object;
  /* Create mesh */
  MeshCreateInfo meshCreateInfo;
  u32 attribs[] = { 3, 2, 3 };
  object.vBuffer = createVertexBuffer(createInfo.obj_path);
  meshCreateInfo.numAttribs = 3;
  meshCreateInfo.attribs = attribs;
  meshCreateInfo.numVertices = object.vBuffer.vertexCount;
  meshCreateInfo.vertices = object.vBuffer.data;
  object.mesh = createMesh(meshCreateInfo);

  /* Create shader */
  object.shader = createShader(createInfo.vert_path, createInfo.frag_path);

  /* Create texture */
  object.texture = createTexture(
      (const char**)createInfo.texture_paths,
      (const char**)createInfo.texture_names,
      createInfo.numTextures,
      object.shader);

  /* Create model matrix */
  kmMat4Identity(&object.model);

  /* Create material */
  object.material.ambient = 0.3f;
  object.material.diffuse = 0.7f;
  object.material.specular = 0.2f;
  object.material.specularPow = 4;

  return object;
}
void destroyObject(Object* object) {
  destroyVertexBuffer(&object->vBuffer);
  destroyMesh(&object->mesh);
  destroyShader(object->shader);
  destroyTexture(&object->texture);
}

void drawObject(Object* object, kmMat4 view, kmMat4 projection, kmVec3 camPos) {
  bindShader(object->shader);
  bindTexture(&object->texture);
  glUniformMatrix4fv(
      glGetUniformLocation(
        object->shader, "model"
      ), 1, GL_FALSE, object->model.mat);
  glUniformMatrix4fv(
      glGetUniformLocation(
        object->shader, "view"
      ), 1, GL_FALSE, view.mat);
  glUniformMatrix4fv(
      glGetUniformLocation(
        object->shader, "projection"
      ), 1, GL_FALSE, projection.mat);
  glUniform1f(
      glGetUniformLocation(
        object->shader, "material.ambient"),
      object->material.ambient);
  glUniform1f(
      glGetUniformLocation(
        object->shader, "material.diffuse"),
      object->material.diffuse);
  glUniform1f(
      glGetUniformLocation(
        object->shader, "material.specular"),
      object->material.specular);
  glUniform1f(
      glGetUniformLocation(
        object->shader, "material.specularPow"),
      object->material.specularPow);
  glUniform3fv(glGetUniformLocation(object->shader, "cameraPos"), 1, (f32*)&camPos);
  drawMesh(&object->mesh);
}
