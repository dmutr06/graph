#ifndef WINDOW_H_
#define WINDOW_H_

#include "shared.h"

void create_ctx(size_t width, size_t height);

GLFWwindow *get_glfw_window();
int window_height();
int window_width();
float window_ratio();

#endif
