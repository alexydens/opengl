#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 texCoord;
out vec3 normal;
out vec3 FragPos;

void main() {
  gl_Position = projection * view * model * vec4(aPos, 1.0f);
  FragPos = transpose(inverse(mat3(model))) * aPos;
  texCoord = aTexCoord;
  normal = normalize(transpose(inverse(mat3(model))) * aNormal);
}
