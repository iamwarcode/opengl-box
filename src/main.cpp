#include <util.h>

SDL_Window *window;
SDL_GLContext context;

void init(){
  SDL_Init(SDL_INIT_EVERYTHING);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
  
  window = SDL_CreateWindow("OpenGL", 100, 100, 800, 600, SDL_WINDOW_OPENGL);
  context = SDL_GL_CreateContext(window);
  glewExperimental = GL_TRUE;
  glewInit();

}

int main(int argc, char *argv[])
{
    init();
    SDL_Event windowEvent;    
    
    GLuint vs = load_shader(GL_VERTEX_SHADER, "/Users/vivek/opengl/shaders/basic.vsh");
    GLuint fs = load_shader(GL_FRAGMENT_SHADER, "/Users/vivek/opengl/shaders/basic.fsh");
    GLuint program = make_program(vs, fs);
    glUseProgram(program);
    
    
    int elements[] = {
        0,  1,  2,      0,  2,  3,    // front
        4,  5,  6,      4,  6,  7,    // back
        8,  9,  10,     8,  10, 11,   // top
        12, 13, 14,     12, 14, 15,   // bottom
        16, 17, 18,     16, 18, 19,   // right
        20, 21, 22,     20, 22, 23    // left
    };
    
    float vertices[] = {
      // Front face
      -1.0, -1.0,  1.0,
       1.0, -1.0,  1.0,
       1.0,  1.0,  1.0,
      -1.0,  1.0,  1.0,
      
      // Back face
      -1.0, -1.0, -1.0,
      -1.0,  1.0, -1.0,
       1.0,  1.0, -1.0,
       1.0, -1.0, -1.0,
      
      // Top face
      -1.0,  1.0, -1.0,
      -1.0,  1.0,  1.0,
       1.0,  1.0,  1.0,
       1.0,  1.0, -1.0,
      
      // Bottom face
      -1.0, -1.0, -1.0,
       1.0, -1.0, -1.0,
       1.0, -1.0,  1.0,
      -1.0, -1.0,  1.0,
      
      // Right face
       1.0, -1.0, -1.0,
       1.0,  1.0, -1.0,
       1.0,  1.0,  1.0,
       1.0, -1.0,  1.0,
      
      // Left face
      -1.0, -1.0, -1.0,
      -1.0, -1.0,  1.0,
      -1.0,  1.0,  1.0,
      -1.0,  1.0, -1.0
    };
    
    float color[] = {
      1.0,0.0,0.0,
      1.0,0.0,0.0,
      1.0,0.0,0.0,
      1.0,0.0,0.0,
      
      0.0,1.0,0.0,
      0.0,1.0,0.0,
      0.0,1.0,0.0,
      0.0,1.0,0.0,
      
      0.0,0.0,1.0,
      0.0,0.0,1.0,
      0.0,0.0,1.0,
      0.0,0.0,1.0,
      
      1.0,1.0,0.0,
      1.0,1.0,0.0,
      1.0,1.0,0.0,
      1.0,1.0,0.0,
      
      1.0,0.0,1.0,
      1.0,0.0,1.0,
      1.0,0.0,1.0,
      1.0,0.0,1.0,
      
      0.0,1.0,1.0,
      0.0,1.0,1.0,
      0.0,1.0,1.0,
      0.0,1.0,1.0
    };
    
    GLuint vao;
    GLuint vbo[3];
    glGenVertexArrays(1, &vao);
    glGenBuffers(3, vbo);
    
    glBindVertexArray(vao);
  
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    
    GLint m = glGetUniformLocation(program, "m");
    GLint v = glGetUniformLocation(program, "v");
    GLint p = glGetUniformLocation(program, "p");
    
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 proj;
    
    
    model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0 , -10.0f));
    glUniformMatrix4fv(m, 1, GL_FALSE, glm::value_ptr(model));
    
    proj = glm::perspective(45.0f, 800.0f/600.0f, 1.0f, 50.0f);
    glUniformMatrix4fv(p, 1, GL_FALSE, glm::value_ptr(proj));
    
    int oldx, oldy;
    oldx = oldy = 0;
    float pitch, yaw;
    
    glEnable(GL_DEPTH_TEST);
    
    glm::vec3 vdir = glm::vec3(0.0f,0.0f,-1.0f);
    glm::vec3 posc = glm::vec3(0.0f,0.0f, 0.0f);
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
                vdir = glm::mat3(glm::rotate(glm::mat4(1.0f) ,-(pitch*0.5f), glm::vec3(0.0f, 1.0f, 0.0f)))*vdir;
                vdir = glm::mat3(glm::rotate(glm::mat4(1.0f) ,-(yaw*0.5f), glm::cross(vdir, glm::vec3(0.0f, 1.0f, 0.0f))))*vdir;
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
        glClearColor(0.6, 0.4 ,0.7,1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        view = glm::lookAt(
          posc,
          posc + vdir,
          glm::vec3(0.0f, 1.0f, 0.0f)
        );
        glUniformMatrix4fv(v, 1, GL_FALSE, glm::value_ptr(view));
        
        
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        
        
        SDL_GL_SwapWindow(window);
    
    }
    SDL_GL_DeleteContext(context);    
    SDL_Quit();
    return 0;
}