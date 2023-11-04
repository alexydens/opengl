#version 330 core
in vec2 texCoord;
in vec3 normal;
in vec3 FragPos;

uniform vec3 cameraPos;
uniform sampler2D tex;
uniform sampler2D normals;

struct Material {
  float ambient;
  float diffuse;
  float specular;
  float specularPow;
};
uniform Material material;

out vec4 FragColor;

vec2 ParallaxMapping(vec2 texCoords, vec3 viewDir);

void main() {
  vec3 tangent;
  vec3 t1 = cross(normal, vec3(0.0, 0.0, -1.0));
  vec3 t2 = cross(normal, vec3(0.0, 1.0, 0.0));
  if (length(t1) > length(t2)) {
    tangent = t1;
  } else {
    tangent = t2;
  }
  vec3 bitangent = cross(normal, tangent);
  mat3 tbn = mat3(tangent, bitangent, normal);

  vec3 viewDir = normalize(cameraPos - FragPos);

  vec3 m_normal = texture(normals, texCoord).xyz;
  m_normal = normalize(m_normal * 2.0 - 1.0);

  vec3 lightDir = vec3(1.0);
  vec3 lightCol = vec3(1.0, 1.0, 1.0);

  float ambient = material.ambient;//0.2;
  
  float lambertianDiffuse =
    dot(normalize(lightDir), normalize(tbn * m_normal)) * material.diffuse;//0.75f;

  vec3 reflectDir = reflect(-lightDir, tbn * m_normal);
  float specular =
  pow(
  max(
  dot(viewDir, reflectDir), 0.0), material.specularPow) * material.specular;//0.05f;

  float illumination = max(max(lambertianDiffuse, ambient), specular);
  FragColor = vec4(texture(tex, texCoord).xyz * illumination * lightCol, 1.0);
}
