#ifndef GRAPH_H_
#define GRAPH_H_

#include "linmath.h"
#include "shared.h"

#define POINTS_PER_UNIT 600 

typedef struct {
  GLint time;
  GLint res;
  GLint mvp;
} GraphUniforms;

typedef struct {
  float (*f)(float);
  GLuint vbo;
  GLuint vao;
  GLuint shader_program;
  GraphUniforms uniforms;
} Graph;

void init_graph(float (func)(float), Graph *graph);
void render_graph(Graph *graph, mat4x4 vp);

#endif
