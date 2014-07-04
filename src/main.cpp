#include <util.h>
#include <display.h>
#include <math.h>

#define PI 3.13159265
int main(int argc, char *argv[])
{
    Display d(800, 600, "boom box");
    SDL_Event windowEvent;    
    
    GLuint vs = load_shader(GL_VERTEX_SHADER, "/Users/vivek/opengl/shaders/basic.vsh");
    GLuint fs = load_shader(GL_FRAGMENT_SHADER, "/Users/vivek/opengl/shaders/basic.fsh");
    GLuint program = make_program(vs, fs);
    glUseProgram(program);
    
  float ve[1428];
  int width  = 32;
  int height = 16;
  
  float theta, phi;
  int i, j, t, ntri, nvec;
  int rad=1;
  
  for(t=0, j=1; j<height-1; j++){
    for(i=0; i<width; i++){
      theta = float(j)/(height-1) * PI;
      phi = float(i)/(width-1)*2*PI;
      ve[t++]   = sinf(theta)*cosf(phi);
      ve[t++] = cosf(theta);
      ve[t++] = -sinf(theta)*sinf(phi);    
    }
  }
    GLuint vao;
    GLuint vbo[3];
    glGenVertexArrays(1, &vao);
    glGenBuffers(3, vbo);
    
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(ve), ve, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(ve), ve, GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    
    GLint m = glGetUniformLocation(program, "m");
    GLint v = glGetUniformLocation(program, "v");
    GLint p = glGetUniformLocation(program, "p");
    
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 proj;
    
    
    model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0 , 0.0f));
    glUniformMatrix4fv(m, 1, GL_FALSE, glm::value_ptr(model));
    
    proj = glm::perspective(45.0f, 800.0f/600.0f, 1.0f, 50.0f);
    glUniformMatrix4fv(p, 1, GL_FALSE, glm::value_ptr(proj));
    
    int oldx, oldy;
    oldx = oldy = 0;
    float pitch, yaw;
    
    glm::vec3 vdir = glm::vec3(0.0f,0.0f, -5.0f);
    glm::vec3 posc = glm::vec3(0.0f,0.0f, 0.0f);
    glPointSize(1);
    while (1)
    {
       pitch=yaw=0;
       
        if (SDL_PollEvent(&windowEvent))
        {
            if (windowEvent.type == SDL_QUIT) break;
            if (windowEvent.type == SDL_MOUSEMOTION){
              pitch = oldx - windowEvent.motion.x;
              yaw = oldy - windowEvent.motion.y;
              
              oldx = windowEvent.motion.x;
              oldy = windowEvent.motion.y;
              if(pitch > 100 || pitch < -100 || yaw > 100 || yaw < -100){
                  
              }else{
                vdir = glm::mat3(glm::rotate(glm::mat4(1.0f) , (pitch*0.5f), glm::vec3(0.0f, 1.0f, 0.0f)))*vdir;
                vdir = glm::mat3(glm::rotate(glm::mat4(1.0f) ,(yaw*0.5f), glm::cross(vdir,glm::vec3(0.0f, 1.0f, 0.0f))))*vdir;
              }
            }
            
            if (windowEvent.type == SDL_KEYDOWN){
              switch(windowEvent.key.keysym.sym){
                case SDLK_w:
                  posc +=  0.5f*vdir;
                break;
                case SDLK_a:
                  posc -=  0.5f*glm::cross(vdir, glm::vec3(0.0f, 1.0f, 0.0f));
                break;
                case SDLK_s:
                  posc -=  0.5f*vdir;
                break;
                case SDLK_d:
                  posc += 0.5f*glm::cross(vdir, glm::vec3(0.0f, 1.0f, 0.0f));
                break;
              }
            }
            
            
        }
        
        d.Clear(1.0f, 1.0f, 1.0f, 1.0f);
        view = glm::lookAt(
          vdir,
          posc*vdir,
          glm::vec3(0.0f, 1.0f, 0.0f)
        );
        glUniformMatrix4fv(v, 1, GL_FALSE, glm::value_ptr(view));
        
        
        glDrawArrays(GL_POINTS, 0, 1428);
        d.SwapBuffers();
    }
    
    return 0;
}