#include "RenderWindow.h"

using namespace beta;


RenderWindow::RenderWindow() 
{
    if(!glfwInit()) {
        printf("cannot initiliaze glfw\n");
    }

    this->size  = Vector2u(WIDTH_GLFW_WINDOW , HEIGHT_GLFW_WINDOW);
    this->title = TITLE_GLFW_WINDOW;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR , 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR , 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE , GLFW_OPENGL_CORE_PROFILE);

    #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT , GLFW_TRUE);
    #endif

    this->window = glfwCreateWindow(this->size.x , this->size.y , this->title.c_str() , nullptr , nullptr);

    if (this->window == nullptr) {
        return;
    }

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        return ;
    }
}

RenderWindow::RenderWindow(const Vector2u &s , const std::string &t)
{
    if(!glfwInit()) {
        printf("cannot initiliaze glfw\n");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR , 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR , 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE , GLFW_OPENGL_CORE_PROFILE);

    #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT , GLFW_TRUE);
    #endif

    this->size  = s;
    this->title = t;

    this->window = glfwCreateWindow(this->size.x , this->size.y , this->title.c_str() , nullptr , nullptr);

    if (this->window == nullptr) {
        return;
    }
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        return ;
    }
}

RenderWindow::RenderWindow(unsigned int x_ , unsigned int y_ , const char *t) 
{
    if(!glfwInit()) {
        printf("cannot initiliaze glfw\n");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR , 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR , 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE , GLFW_OPENGL_CORE_PROFILE);

    #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT , GLFW_TRUE);
    #endif

    this->size  = Vector2u(x_ , y_);
    this->title = t;

    this->window = glfwCreateWindow(this->size.x , this->size.y , this->title.c_str() , nullptr , nullptr); 

    if (this->window == nullptr) {
        return;
    }
    
    glfwMakeContextCurrent(this->window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        return ;
    }   
}

RenderWindow::~RenderWindow()
{
    glfwDestroyWindow(this->window);
}


void frameBufferCallBack(GLFWwindow *window_ , int width , int height) 
{
    glViewport(0 , 0 ,width , height);
}

void RenderWindow::processEvents()
{
    if (glfwGetKey(this->window , GLFW_KEY_ESCAPE)) {
        glfwSetWindowShouldClose(this->window , true);
    }
}

void RenderWindow::draw()
{
    glClearColor(0.1 , 0.3 , 0.4 , 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ARRAY_BUFFER , this->VBO);
    glUseProgram(this->programObject);
    glDrawArrays(GL_TRIANGLES , 0 , 3);

    glfwSwapBuffers(this->window);
    glfwPollEvents();

}

void RenderWindow::setProgram(GLuint programObj)
{
    this->programObject = programObj;
}

void RenderWindow::setVAO(GLuint vao)
{
    this->VAO = vao;
}

void RenderWindow::setVBO(GLuint vbo) 
{
    this->VBO = vbo;
}

void RenderWindow::run()
{
    if (this->window == nullptr) return;
    
    glfwSetFramebufferSizeCallback(this->window , frameBufferCallBack);
    if (this->programObject == 0) {
        printf("fuck me\n");
    }
    while (!glfwWindowShouldClose(this->window)) 
    {
        this->processEvents();
        this->draw();
    }
    glfwTerminate();
}