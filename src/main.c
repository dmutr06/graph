#include <stdio.h>

#include "window.h"
#include "camera.h"
#include "graph.h"
#include "field.h"

#define WIDTH 800
#define HEIGHT 600

#define MOVE_SPEED 2.0
#define ZOOM_SPEED 1.0
#define SCALE_SPEED 1.5

float f(float x) {
  return pow(pow(x + 2.0, 2.0), 1.0 / 3.0) - pow(pow(x - 2.0, 2.0), 1.0 / 3.0); 
}

int main() {
  create_ctx(WIDTH, HEIGHT);

  init_camera();

  Graph graph;
  init_graph(f, &graph);

  Field field;
  init_field(&field);

  float prev_time;

  GLFWwindow *window = get_glfw_window();

  glEnable(GL_LINE_SMOOTH);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glLineWidth(2.5);

  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    float cur_time = glfwGetTime();

    float dt = cur_time - prev_time;
    prev_time = cur_time;
    
    float camera_dy = 0.0, camera_dx = 0.0;
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
      camera_dy -= dt * MOVE_SPEED;
    } 
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
      camera_dy += dt * MOVE_SPEED;
    } 
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
      camera_dx -= dt * MOVE_SPEED;
    } 
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
      camera_dx += dt * MOVE_SPEED;
    }
    
    if (glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_PRESS) {
      zoom_camera(dt * ZOOM_SPEED);
    }
    if (glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS) {
      zoom_camera(-dt * ZOOM_SPEED);
    }

    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
      reset_camera();
    }

    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) {
      scale_camera(SCALE_SPEED * -dt, 0.0);
    }
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
      scale_camera(SCALE_SPEED * dt, 0.0);
    }
    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
      scale_camera(0.0, SCALE_SPEED * -dt);
    }
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {
      scale_camera(0.0, SCALE_SPEED * dt);
    }

    move_camera(camera_dx, camera_dy);

    mat4x4 vp;
    get_vp(vp);
    render_field(&field, vp);
    render_graph(&graph, vp);


    glfwPollEvents();
    glfwSwapBuffers(window);
  }
}
