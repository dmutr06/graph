#include "window.h"

static struct {
  GLFWwindow *window;
  int width;
  int height;
} window;

static void on_window_resize(GLFWwindow *glfw_window, int new_width, int new_height) {
  (void) glfw_window;
  window.width = new_width;
  window.height = new_height;
  glViewport(0, 0, new_width, new_height);
}

void create_ctx(size_t width, size_t height) {
  if (!glfwInit()) {
    fprintf(stderr, "Could not init glfw :(\n");
    exit(1);
  }
  
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window.window = glfwCreateWindow(width, height, "Graph", NULL, NULL);
  window.width = width;
  window.height = height;

  if (!window.window) {
    fprintf(stderr, "Could not create a window :(\n");
    glfwTerminate();
    exit(1);
  }

  glfwMakeContextCurrent(window.window);

  if (glewInit() != GLEW_OK) {
    fprintf(stderr, "Could not init glew :(\n");
    glfwDestroyWindow(window.window);
    glfwTerminate();
    exit(1);
  }

  glfwSetWindowSizeCallback(window.window, on_window_resize);
  // glfwSetMouseButtonCallback(window, on_click);
  // glfwSetKeyCallback(window, on_key_press);
  // glfwSetScrollCallback(window, on_scroll);
}

GLFWwindow *get_glfw_window() {
  return window.window;
}

int window_height() {
  return window.height;
}

int window_width() {
  return window.width;
}

float window_ratio() {
  return (float) window.width / window.height;
}
