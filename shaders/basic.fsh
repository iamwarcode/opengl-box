#version 330 

out vec4 outputColor;
smooth in vec3 Ocolor;
uniform sampler2D tex;
in vec2 Tex;

void main() 
{ 
  
   outputColor = texture(tex, Tex)*vec4(1,1,1, 1.0); 
}