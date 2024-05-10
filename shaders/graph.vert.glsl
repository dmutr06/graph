#version 330 core

uniform mat4 mvp;
layout (location = 0) in vec2 pos;

void main() {
  gl_Position = mvp * vec4(pos, 0.0, 1.0);
}
