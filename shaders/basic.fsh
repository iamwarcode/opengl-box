#version 330 

out vec4 outputColor;
smooth in vec3 Ocolor;

void main() 
{ 
  
   outputColor = vec4(Ocolor, 1.0); 
}