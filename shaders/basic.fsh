#version 330 

out vec4 outputColor;
in vec3 Color;

void main() 
{ 
   outputColor = vec4(Color,1); 
}