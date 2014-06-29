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
    
    int mloc = glGetUniformLocation(program, "m");
    int ploc = glGetUniformLocation(program, "p");
    int vloc = glGetUniformLocation(program, "v");
    
    
    GLuint vao[2];
    GLuint vbo[4];
    GLuint ebo[2];
    glGenVertexArrays(2, vao);
    glGenBuffers(4, vbo);
    glGenBuffers(2, ebo);
    float face[] = {
       -0.5f, +0.5f, 0.0f,
       -0.5f, -0.5f, 0.0f,
       +0.5f, +0.5f, 0.0f,
       +0.5f, -0.5f, 0.0f
    };
    
    float color[] = {
       1,1,1,
       1,0,0,
       0,1,0,
       0,0,1
    };
    
    float text[] = {
      0,0,
      0,1,
      1,0,
      1,1
    };
    
    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    
    int width, height;
    unsigned char* image = SOIL_load_image("../textures/congruent_pentagon.png", &width, &height, 0, SOIL_LOAD_RGB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE,image);
    
    SOIL_free_image_data(image);
    
        
    glBindVertexArray(vao[0]);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(face), face, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(text), text, GL_STATIC_DRAW);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glEnable(GL_DEPTH_TEST);
    while (1)
    {
        if (SDL_PollEvent(&windowEvent))
        {
            if (windowEvent.type == SDL_QUIT) break;
        }
        
        glClearColor(0.6, 0.4 ,0.7,1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glBindVertexArray(vao[0]);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
        SDL_GL_SwapWindow(window);
    
    }
    SDL_GL_DeleteContext(context);    
    SDL_Quit();
    return 0;
}