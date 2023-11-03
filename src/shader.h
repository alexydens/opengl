#if !defined(SHADER_H)
#define SHADER_H

/* My ANSI-compatible Base library for C */
#include <ABC/base.h>     /* Core */
#include <ABC/file_io.h>  /* File I/O */

/* GLAD, the OpenGL wrapper */
#include <glad/glad.h>

/* ShaderHandle type is just a GLuint */
typedef u32 ShaderHandle;

/* Create and destroy shader */
ShaderHandle createShader(const char* vertPath, const char* fragPath);
void destroyShader(ShaderHandle handle);

/* Bind shader */
void bindShader(ShaderHandle handle);

#endif /* SHADER_H */
