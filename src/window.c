#include "window.h"

/* Intialize the SDL2 library and OpenGL */
void initLibraries() {
#if defined(DEBUG)
  printf("INFO: Initializing SDL2...\n");
#endif
  SDL_Init(SDL_INIT_EVERYTHING);

  /* Load OpenGL */
#if defined(DEBUG)
  printf("INFO: Loading OpenGL...\n");
#endif
  SDL_GL_LoadLibrary(NULL); /* Loading SDL's OpenGL stuff */

  /* Set GL attributes - I can get up to OpenGL 3.3 Core profile, so I will */
  SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  /* Get 24-bit depth buffer */
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
}
/* HAS to be called after window creation */
void initGLAD(WindowGL* state) {
#if defined(DEBUG)
  printf("INFO: Loading GLAD...\n");
#endif
  if (!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
#if defined(DEBUG)
    printf("FATAL: Failed to load GLAD.\n");
#endif
    exit(-1);
  }

  /* Use depth buffer */
  glEnable(GL_DEPTH_TEST);

  /* Create viewport */
  glViewport(0, 0, state->width, state->height);
}

/* Create a window with an OpenGL context */
WindowGL createWindowGL(const char* title) {
  WindowGL state;
#if defined(DEBUG)
  printf("INFO: Creating window...\n");
#endif
  state.handle = SDL_CreateWindow(
      title, 0, 0, 1280, 720, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
  state.width = 1280;
  state.height = 720;
  if (!state.handle) {
#if defined(DEBUG)
    printf("FATAL: Window creation failed.\n");
#endif
    exit(-1);
  }

  /* Create OpenGL context */
  state.gl_context = SDL_GL_CreateContext(state.handle);
  if (!state.gl_context) {
#if defined(DEBUG)
    printf("FATAL: Failed to create OpenGL context for window\n");
#endif
    exit(-1);
  }

  /* Not exactly sure what this does... */
  SDL_GL_SetSwapInterval(1);

  /* Make keys point to sdl's keyboard state */
  state.keys = SDL_GetKeyboardState(0);

  /* Intialize running */
  state.running = true;

  return state;
}
void destroyWindowGL(WindowGL* state) {
  SDL_DestroyWindow(state->handle);
}

/* Update the window events */
void updateWindowsGL(WindowGL** states, u32 numWindows) {
  SDL_Event event;
  /* Check for quit or window events */
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_WINDOWEVENT:
        {
          u32 i;
          for (i = 0; i < numWindows; i++) {
            WindowGL* state = states[i];
            if (SDL_GetWindowID(state->handle) == event.window.windowID) {
              switch (event.window.event) {
                case SDL_WINDOWEVENT_RESIZED:
                  {
                    state->width = event.window.data1;
                    state->height = event.window.data2;
                    glViewport(0, 0, state->width, state->height);
                  }
                  break;
                case SDL_WINDOWEVENT_CLOSE:
                  {
                    state->running = false;
                    destroyWindowGL(state);
                  }
                  break;
              }
            }
          }
        }
        break;
      default: break;
    }
  }
}

/* Clear the window's framebuffer and depth buffer */
void clearWindowGL(f32 r, f32 g, f32 b) {
  glClearColor(r, g, b, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
/* Present the window's framebuffer (swap buffers) */
void presentWindowGL(WindowGL* state) {
  SDL_GL_SwapWindow(state->handle);
}

/* Makes the window's OpenGL context current (needed for multiple windows) */
void makeCurrent(WindowGL* state) {
  SDL_GL_MakeCurrent(state->handle, state->gl_context);
}
