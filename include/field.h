#ifndef FIELD_H_
#define FIELD_H_

#include "shared.h"
#include "linmath.h"

typedef struct {
  GLuint vao;
  GLuint vbo;
  GLuint shader_program;
  struct {
    GLint mvp; 
  } uniforms;
} Field;

void init_field(Field *field);
void render_field(Field *field, mat4x4 vp);


#endif
