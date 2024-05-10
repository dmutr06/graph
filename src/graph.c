#include "graph.h"
#include "shader.h"
#include "camera.h"
#include "window.h"

void init_graph(float (f)(float), Graph *graph) {
  graph->f = f;

  glGenBuffers(1, &graph->vbo);
  glBindBuffer(GL_ARRAY_BUFFER, graph->vbo);
  glBufferData(GL_ARRAY_BUFFER, 0, NULL, GL_DYNAMIC_DRAW); 

  glGenVertexArrays(1, &graph->vao);
  glBindVertexArray(graph->vao);
  glBindBuffer(GL_ARRAY_BUFFER, graph->vbo);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Point), NULL);
  glEnableVertexAttribArray(0);

  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  graph->shader_program = create_shader_program("shaders/graph.vert.glsl", "shaders/graph.frag.glsl");

  graph->uniforms.mvp = glGetUniformLocation(graph->shader_program, "mvp");
  graph->uniforms.time = glGetUniformLocation(graph->shader_program, "time");
  graph->uniforms.res = glGetUniformLocation(graph->shader_program, "res");
}

void render_graph(Graph *graph, mat4x4 vp) {
  const Point *pos = camera_pos();
  const Point *scale = camera_scale();
  float min_x = -window_ratio() / camera_zoom() * scale->x + pos->x, max_x = window_ratio() / camera_zoom() * scale->x + pos->x;

  size_t points_amount = POINTS_PER_UNIT * floor(fabs(max_x - min_x)) * camera_zoom() / scale->x;
  Point *points = malloc(points_amount * sizeof(Point));

  for (size_t i = 0; i < points_amount; i++) {
    points[i].x = min_x + (max_x - min_x) / (points_amount - 1) * i;
    points[i].y = graph->f(points[i].x);
  }

  glBindVertexArray(graph->vao);
  glBindBuffer(GL_ARRAY_BUFFER, graph->vbo);
  glBufferData(GL_ARRAY_BUFFER, points_amount * sizeof(Point), points, GL_DYNAMIC_DRAW);

  glUseProgram(graph->shader_program);
  glUniform2f(graph->uniforms.res, window_width(), window_height());
  glUniform1f(graph->uniforms.time, glfwGetTime());
  glUniformMatrix4fv(graph->uniforms.mvp, 1, GL_FALSE, (const GLfloat *) vp);
  
  glLineWidth(2.5);
  glDrawArrays(GL_LINE_STRIP, 0, points_amount);
  
  glLineWidth(1.0);
  glUseProgram(0);
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  free(points);
}
