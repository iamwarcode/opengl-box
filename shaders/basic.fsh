#version 330

out vec4 color;

void main(){
  vec2 resolution = vec2(800, 600);
  vec2 position = (gl_FragCoord.xy / resolution.xy) - vec2(0.5);
color=vec4(1);
  float len = length(position);
  vec3 c = vec3(len);
  color = vec4(mix(vec3(1),c, 1), 1.0);
}