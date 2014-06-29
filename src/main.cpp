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
    
    float fPyramidColor[36];
    float fPyramid[36];
    fPyramid[0] = 0.0f; fPyramid[1] = 5.0f; fPyramid[2] = 0.0f;
	  fPyramid[3] = -3.0f; fPyramid[4] = 0.0f; fPyramid[5] = 3.0f;
	  fPyramid[6] = 3.0f; fPyramid[7] = 0.0f; fPyramid[8] = 3.0f;

	// Back face
	fPyramid[9] = 0.0f; fPyramid[10] = 5.0f; fPyramid[11] = 0.0f;
	fPyramid[12] = 3.0f; fPyramid[13] = 0.0f; fPyramid[14] = -3.0f;
	fPyramid[15] = -3.0f; fPyramid[16] = 0.0f; fPyramid[17] = -3.0f;

	// Left face
	fPyramid[18] = 0.0f; fPyramid[19] = 5.0f; fPyramid[20] = 0.0f;
	fPyramid[21] = -3.0f; fPyramid[22] = 0.0f; fPyramid[23] = -3.0f;
	fPyramid[24] = -3.0f; fPyramid[25] = 0.0f; fPyramid[26] = 3.0f;

	// Right face
	fPyramid[27] = 0.0f; fPyramid[28] = 5.0f; fPyramid[29] = 0.0f;
	fPyramid[30] = 3.0f; fPyramid[31] = 0.0f; fPyramid[32] = 3.0f;
	fPyramid[33] = 3.0f; fPyramid[34] = 0.0f; fPyramid[35] = -3.0f;

  for(int i=0; i<4; i++)
	{
		fPyramidColor[i*9] = 1.0f; fPyramidColor[i*9+1] = 0.0f; fPyramidColor[i*9+2] = 0.0f;
		if(i < 2)
		{
			fPyramidColor[i*9+1] = 0.0f; fPyramidColor[i*9+4] = 1.0f; fPyramidColor[i*9+5] = 0.0f;
			fPyramidColor[i*9+2] = 0.0f; fPyramidColor[i*9+7] = 0.0f; fPyramidColor[i*9+8] = 1.0f;
		}
		else
		{
			fPyramidColor[i*9+2] = 0.0f; fPyramidColor[i*9+7] = 1.0f; fPyramidColor[i*9+8] = 0.0f;
			fPyramidColor[i*9+1] = 0.0f; fPyramidColor[i*9+4] = 0.0f; fPyramidColor[i*9+5] = 1.0f;
		}
	}
    
    float qua[] = {
      -0.2, -0.1, +0.0,
      -0.2, -0.6, +0.0,
      +0.2, -0.1, +0.0,
      +0.2, -0.6, +0.0
    };
    
    int mloc = glGetUniformLocation(program, "m");
    int ploc = glGetUniformLocation(program, "p");
    int vloc = glGetUniformLocation(program, "v");
    
    glm::mat4 trans;
    glm::mat4 proje;
    
    proje = glm::perspective(45.0f, 800.0f/600.0f, 1.0f, 200.0f);
    glUniformMatrix4fv(ploc, 1, GL_FALSE, glm::value_ptr(proje));
    
    
    
    GLuint vao[2];
    glGenVertexArrays(2, vao);
    GLuint vbo[4];
    glGenBuffers(4, vbo);
    
    glBindVertexArray(vao[0]);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(qua), qua, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(fPyramid), fPyramidColor, GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
      
    float a;
    a=0.0;
    glm::mat4 view;
    glEnable(GL_DEPTH_TEST);
  //  glClearDepth(1.0);
    while (1)
    {
        a += 0.01;
        if(a > 360) a=0;
        if (SDL_PollEvent(&windowEvent))
        {
            if (windowEvent.type == SDL_QUIT) break;
        }
        
        glClearColor(0.6, 0.4 ,0.7,1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        view = glm::lookAt(
          glm::vec3(0.0f, 0.0f, 0.0f),
          glm::vec3(0.0f, 0.0f, 0.0f),
          glm::vec3(0.0f, 0.0f, 1.0f)
        );
        
        glUniformMatrix4fv(vloc, a, GL_FALSE, glm::value_ptr(view));
        
        trans  = glm::rotate(trans, a, glm::vec3(0.0,1.0,1.0));
        glUniformMatrix4fv(mloc, 1, GL_FALSE, glm::value_ptr(trans));
        
        glBindVertexArray(vao[0]);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
                
        SDL_GL_SwapWindow(window);
    
    }
    SDL_GL_DeleteContext(context);    
    SDL_Quit();
    return 0;
}