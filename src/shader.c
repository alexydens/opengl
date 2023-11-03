#include "shader.h"

/* Create and destroy shader */
ShaderHandle createShader(const char* vertPath, const char* fragPath) {
  u32 shaderProgram;
  u32 vertexShader, fragmentShader;
  i32 success;
  char infoLog[512];
  const char* vertexShaderSource = readFromFile(vertPath);
  const char* fragmentShaderSource = readFromFile(fragPath);
  /* Vertex shader */
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    printf("ERROR: VERTEX SHADER COMPILATION: \n%s\n", infoLog);
  }
  /* Fragment shader */
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    printf("ERROR: FRAGMENT SHADER COMPILATION: \n%s\n", infoLog);
  }
  /* Shader program */
  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);
  glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    printf("ERROR: SHADER PROGRAM LINKING: \n%s\n", infoLog);
  }
  /* Delete shaders */
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
  return shaderProgram;
}
void destroyShader(ShaderHandle handle) {
  glDeleteProgram(handle);
}

/* Bind shader */
void bindShader(ShaderHandle handle) {
  glUseProgram(handle);
}
