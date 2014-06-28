#version 330 

out vec4 outputColor;
smooth in vec3 Ocolor;

void main() 
{ 
   outputColor = vec4(1-Ocolor.r, 1-Ocolor.g, 1-Ocolor.b, 1.0); 
}