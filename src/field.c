
#include "field.h"
#include "camera.h"
#include "window.h"
#include "shared.h"
#include "shader.h"

void init_field(Field *field) {
  Point vertices[] = {
    { -1, 0 }, { 1, 0 },
    { 0, -1 }, { 0, 1 },

    {-0.28, -0.6},
    {0.0, 0.0},
    {0.28, -0.6},
    {0.0, 0.0}, // Arrow
  };

  glGenBuffers(1, &field->vbo);
  glBindBuffer(GL_ARRAY_BUFFER, field->vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glGenVertexArrays(1, &field->vao);
  glBindVertexArray(field->vao);
  glBindBuffer(GL_ARRAY_BUFFER, field->vbo);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Point), NULL);
  glEnableVertexAttribArray(0);

  field->shader_program = create_shader_program("shaders/axes.vert.glsl", "shaders/axes.frag.glsl");

  field->uniforms.mvp = glGetUniformLocation(field->shader_program, "mvp");

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void render_field(Field *field, mat4x4 vp) {
  const Point *pos = camera_pos();
  const Point *scale = camera_scale();

  glBindVertexArray(field->vao);
  glUseProgram(field->shader_program);

  mat4x4 mvp;

  size_t units_y = ceil(scale->y / camera_zoom()) * 2;
  
  for (size_t i = 0; i < units_y * 2; i++) {
    mat4x4_identity(mvp);
    mat4x4_translate(mvp, pos->x, floor(pos->y) + i - units_y, 0.0);
    mat4x4_scale_aniso(mvp, mvp, scale->x / camera_zoom() * window_ratio(), 1.0, 0.0);
    mat4x4_mul(mvp, vp, mvp);

    glUniformMatrix4fv(field->uniforms.mvp, 1, GL_FALSE, (const GLfloat *) mvp);

    glDrawArrays(GL_LINES, 0, 2);
  }

  size_t units_x = ceil(scale->x / camera_zoom()) * 2;
  for (size_t i = 0; i < units_x * 2; i++) {
    mat4x4_identity(mvp);
    mat4x4_translate(mvp, floor(pos->x) + i - units_x, pos->y, 0.0);
    mat4x4_scale_aniso(mvp, mvp, 1.0, scale->y / camera_zoom(), 0.0);
    mat4x4_mul(mvp, vp, mvp);

    glUniformMatrix4fv(field->uniforms.mvp, 1, GL_FALSE, (const GLfloat *) mvp);

    glDrawArrays(GL_LINES, 2, 2);
  }
  
  glLineWidth(3.5);
  mat4x4_identity(mvp);
  mat4x4_translate(mvp, pos->x, 0.0, 0.0);
  mat4x4_scale_aniso(mvp, mvp, scale->x / camera_zoom() * window_ratio(), 1.0, 0.0);
  mat4x4_mul(mvp, vp, mvp);

  glUniformMatrix4fv(field->uniforms.mvp, 1, GL_FALSE, (const GLfloat *) mvp);

  glDrawArrays(GL_LINES, 0, 2);
  
  mat4x4_identity(mvp);
  mat4x4_translate(mvp, 0.0, pos->y, 0.0);
  mat4x4_scale_aniso(mvp, mvp, 1.0, scale->y / camera_zoom(), 0.0);
  mat4x4_mul(mvp, vp, mvp);

  glUniformMatrix4fv(field->uniforms.mvp, 1, GL_FALSE, (const GLfloat *) mvp);
  glDrawArrays(GL_LINES, 2, 2);

  mat4x4_identity(mvp);
  mat4x4_translate(mvp, 0.0, pos->y + scale->y / camera_zoom(), 0.0);
  mat4x4_scale_aniso(mvp, mvp, 0.1 * scale->x / camera_zoom(), 0.1 * scale->y / camera_zoom(), 0.0);
  mat4x4_mul(mvp, vp, mvp);
  glUniformMatrix4fv(field->uniforms.mvp, 1, GL_FALSE, (const GLfloat *) mvp);

  glDrawArrays(GL_LINES, 4, 4);

  mat4x4_identity(mvp);
  mat4x4_translate(mvp, pos->x + scale->x / camera_zoom() * window_ratio(), 0.0, 0.0);
  mat4x4_scale_aniso(mvp, mvp, 0.1 * scale->x / camera_zoom(), 0.1 * scale->y / camera_zoom(), 0.0);
  mat4x4_rotate_Z(mvp, mvp, -M_PI / 2);
  mat4x4_mul(mvp, vp, mvp);
  glUniformMatrix4fv(field->uniforms.mvp, 1, GL_FALSE, (const GLfloat *) mvp);

  glDrawArrays(GL_LINES, 4, 4);

  glLineWidth(1.0);
  glUseProgram(0);
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}
