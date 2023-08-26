#ifndef RENDER_WINDOW_H_
#define RENDER_WINDOW_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

//#define DEBUG_


// init default values
//-----------------------------
#define WIDTH_GLFW_WINDOW  800
#define HEIGHT_GLFW_WINDOW 600
#define TITLE_GLFW_WINDOW  "GLFW Window"

namespace beta
{
    struct Vector2u
    {
        unsigned int x;
        unsigned int y;

        Vector2u(unsigned int x_ , unsigned y_) : x(x_) , y(y_) {}
        Vector2u() {}
    };
    
    class RenderWindow
    {
        private:
            Vector2u size;
            std::string title;

            GLFWwindow *window;
            GLuint programObject , VAO , VBO;

        public:
            RenderWindow();
            RenderWindow(const Vector2u &s , const std::string &t);
            RenderWindow(unsigned int x_ , unsigned int y_ , const char *t);
            virtual ~RenderWindow();

        private:
            friend void frameBufferCallBack(GLFWwindow *window_ , int width , int height);
            void processEvents();
            void draw();

        public:
            void setVBO(GLuint vbo);
            void setVAO(GLuint vao);
            void setProgram(GLuint programObj);
            void run();
    };

}

#endif