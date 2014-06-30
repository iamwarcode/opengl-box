#version 330 

uniform mat4 p;
uniform mat4 v;
uniform mat4 m;

layout (location = 0) in vec3 position; 
layout (location = 1) in vec3 color;

out vec3 Color;
void main() 
{ 
   Color = color;
   gl_Position = p*v*m*vec4(position, 0.6); 
}