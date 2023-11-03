#if !defined(WINDOW_H)
#define WINDOW_H

/* My ANSI-compatible Base library in C */
#include <ABC/base.h>

/* SDL2, the windowing library */
#include <SDL2/SDL.h>
/* GLAD, the OpenGL wrapper */
#include <glad/glad.h>

/* The window structure contains the window's state */
typedef struct {
  SDL_Window* handle; /* The window handle */
  bool running;     /* Whether the program is running */

  /* Dimensions */
  u32 width;
  u32 height;

  /* The keyboard state (use SDL_SCANCODE_x for now) */
  const u8* keys;
  
  /* The OpenGL context */
  SDL_GLContext gl_context;
} WindowGL;

/* Intialize the SDL2 library and OpenGL */
void initLibraries();
/* HAS to be called after window creation */
void initGLAD(WindowGL* state);

/* Create a window with an OpenGL context */
WindowGL createWindowGL(const char* title);
void destroyWindowGL(WindowGL* state);

/* Update the window events */
void updateWindowsGL(WindowGL** states, u32 numWindows);

/* Clear the window's framebuffer and depth buffer */
void clearWindowGL(f32 r, f32 g, f32 b);
/* Present the window's framebuffer (swap buffers) */
void presentWindowGL(WindowGL* state);

/* Makes the window's OpenGL context current (needed for multiple windows) */
void makeCurrent(WindowGL* state);

#endif /* WINDOW_H */
