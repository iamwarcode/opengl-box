#version 330 

uniform mat4 p;
uniform mat4 v;
uniform mat4 m;

layout (location = 0) in vec3 position; 
layout (location = 1) in vec3 color;

smooth out vec3 Ocolor;
void main() 
{ 
   Ocolor = color;
   gl_Position = vec4(position, 1.0); 
}