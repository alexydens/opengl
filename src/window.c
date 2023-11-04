#include "window.h"

/* Intialize the SDL2 library and OpenGL */
void initLibraries() {
#if defined(DEBUG)
  printf("INFO: Initializing SDL2...\n");
#endif
  SDL_Init(SDL_INIT_EVERYTHING);
  TTF_Init();

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
void initGLAD(Window* state) {
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
Window createWindowGL(const char* title, u32 w, u32 h) {
  Window state;
#if defined(DEBUG)
  printf("INFO: Creating window...\n");
#endif
  state.handle = SDL_CreateWindow(
      title, 0, 0, w, h, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
  state.width = w;
  state.height = h;
  if (!state.handle) {
#if defined(DEBUG)
    printf("FATAL: Window creation failed.\n");
#endif
    exit(-1);
  }

  /* Create OpenGL context */
  state.rendering.gl_context = SDL_GL_CreateContext(state.handle);
  if (!state.rendering.gl_context) {
#if defined(DEBUG)
    printf("FATAL: Failed to create OpenGL context for window\n");
#endif
    exit(-1);
  }

  /* Make keys point to sdl's keyboard state */
  state.keys = SDL_GetKeyboardState(0);

  /* Intialize running */
  state.running = true;

  /* Set is_windowgl */
  state.is_windowgl = true;

  return state;
}
void destroyWindowGL(Window* state) {
  SDL_DestroyWindow(state->handle);
}
/* Create a window without an OpenGL context */
Window createWindow(const char* title, u32 w, u32 h) {
  Window state;
#if defined(DEBUG)
  printf("INFO: Creating window...\n");
#endif
  state.handle = SDL_CreateWindow(
      title, 0, 0, w, h, SDL_WINDOW_RESIZABLE);
  state.width = w;
  state.height = h;
  if (!state.handle) {
#if defined(DEBUG)
    printf("FATAL: Window creation failed.\n");
#endif
    exit(-1);
  }

  /* Create a renderer */
  state.rendering.renderer = SDL_CreateRenderer(state.handle, 0, SDL_RENDERER_ACCELERATED);

  /* Make keys point to sdl's keyboard state */
  state.keys = SDL_GetKeyboardState(0);

  /* Intialize running */
  state.running = true;

  /* Set is_windowgl */
  state.is_windowgl = false;

  return state;
}
void destroyWindow(Window* state) {
  SDL_DestroyWindow(state->handle);
}

/* Update the window events */
void updateWindows(Window** states, u32 numWindows) {
  SDL_Event event;
  /* Check for quit or window events */
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_WINDOWEVENT:
        {
          u32 i;
          for (i = 0; i < numWindows; i++) {
            Window* state = states[i];
            if (SDL_GetWindowID(state->handle) == event.window.windowID) {
              switch (event.window.event) {
                case SDL_WINDOWEVENT_RESIZED:
                  {
                    state->width = event.window.data1;
                    state->height = event.window.data2;
                    if (state->is_windowgl) {
                      SDL_GL_MakeCurrent(state->handle, state->rendering.gl_context);
                      glViewport(0, 0, state->width, state->height);
                    }
                  }
                  break;
                case SDL_WINDOWEVENT_CLOSE:
                  {
                    state->running = false;
                    if (state->is_windowgl) destroyWindowGL(state);
                    else destroyWindow(state);
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
void presentWindowGL(Window* state) {
  SDL_GL_SwapWindow(state->handle);
}
/* Clear the window's framebuffer */
void clearWindow(Window* state, u32 r, u32 g, u32 b) {
  SDL_SetRenderDrawColor(state->rendering.renderer, r, g, b, 0xff);
  SDL_RenderClear(state->rendering.renderer);
}
/* Present the window's framebuffer (swap buffers) */
void presentWindow(Window* state) {
  SDL_RenderPresent(state->rendering.renderer);
}

/* Makes the window's OpenGL context current (needed for multiple windows) */
void makeCurrent(Window* state) {
  SDL_GL_MakeCurrent(state->handle, state->rendering.gl_context);
}
