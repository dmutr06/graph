#include <stdio.h>
#include <stdlib.h>

#include "shader.h"

GLuint create_shader_program(const char *vert_path, const char *frag_path) {
  FILE *vert_file = fopen(vert_path, "rb");
  FILE *frag_file = fopen(frag_path, "rb");

  if (!vert_file) {
    fprintf(stderr, "Could not open vertex shader file :(\n");
    exit(1);
  }

  if (!frag_file) {
    fprintf(stderr, "Could not open fragment shader file :(\n");
    exit(1);
  }

  fseek(vert_file, 0, SEEK_END);
  size_t vert_len = ftell(vert_file);
  fseek(vert_file, 0, SEEK_SET);
  fseek(frag_file, 0, SEEK_END);
  size_t frag_len = ftell(frag_file);
  fseek(frag_file, 0, SEEK_SET);

  char *vert_src = (char *) malloc(vert_len + 1);
  char *frag_src = (char *) malloc(frag_len + 1);

  fread(vert_src, vert_len, 1, vert_file);
  fread(frag_src, frag_len, 1, frag_file);

  fclose(vert_file);
  fclose(frag_file);

  vert_src[vert_len] = '\0';
  frag_src[frag_len] = '\0';

  GLint vert_shader = glCreateShader(GL_VERTEX_SHADER); 
  GLint frag_shader = glCreateShader(GL_FRAGMENT_SHADER); 

  glShaderSource(vert_shader, 1, (const char **) &vert_src, NULL);
  glShaderSource(frag_shader, 1, (const char **) &frag_src, NULL);
  glCompileShader(vert_shader);
  glCompileShader(frag_shader);

  free(vert_src);
  free(frag_src);

  GLuint program = glCreateProgram();

  glAttachShader(program, vert_shader);
  glAttachShader(program, frag_shader);

  glLinkProgram(program);

  glDeleteShader(vert_shader);
  glDeleteShader(frag_shader);

  return program;
}
