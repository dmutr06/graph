#version 330 core

uniform vec2 res;
uniform float time;

out vec4 FragColor;

const float PI = 3.14159265359;

void main() {
  vec2 uv = gl_FragCoord.xy / res; 
  FragColor = vec4(sin(uv.x * PI - time), cos(uv.y * PI - time), 1.0, 1.0); 
}
