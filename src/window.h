#if !defined(WINDOW_H)
#define WINDOW_H

/* My ANSI-compatible Base library in C */
#include <ABC/base.h>

/* SDL2, the windowing library */
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

/* GLAD, the OpenGL wrapper */
#include <glad/glad.h>

/* The window structure contains the window's state */
typedef struct {
  SDL_Window* handle; /* The window handle */
  bool running;       /* Whether the program is running */

  /* Dimensions */
  u32 width;
  u32 height;

  /* The keyboard state (use SDL_SCANCODE_x for now) */
  const u8* keys;
  
  /* Does this window have an OpenGL context?
   * (alternative would be an SDL2 renderer) */
  bool is_windowgl;
  /* The rendering stuff */
  union {
    /* The OpenGL context */
    SDL_GLContext gl_context;
    /* The SDL2 renderer */
    SDL_Renderer* renderer;
  } rendering;
} Window;

/* Intialize the SDL2 library and OpenGL */
void initLibraries();
/* HAS to be called after window creation */
void initGLAD(Window* state);

/* Create a window with an OpenGL context */
Window createWindowGL(const char* title, u32 w, u32 h);
void destroyWindowGL(Window* state);
/* Create a window without an OpenGL context */
Window createWindow(const char* title, u32 w, u32 h);
void destroyWindow(Window* state);

/* Update the window events */
void updateWindows(Window** states, u32 numWindows);

/* Clear the window's framebuffer and depth buffer */
void clearWindowGL(f32 r, f32 g, f32 b);
/* Present the window's framebuffer (swap buffers) */
void presentWindowGL(Window* state);
/* Clear the window's framebuffer */
void clearWindow(Window* state, u32 r, u32 g, u32 b);
/* Present the window's framebuffer (swap buffers) */
void presentWindow(Window* state);

/* Makes the window's OpenGL context current (needed for multiple windows) */
void makeCurrent(Window* state);

#endif /* WINDOW_H */
