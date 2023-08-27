#include "RenderWindow.h"
#include "Triangle.h"

using namespace beta;

const std::string vertexShaderSource   = 
    "#version 410 core\n"
    "in vec4 position;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(position.x , position.y , position.z , position.w);\n"
    "}\n"
;
const std::string fragmentShaderSource = 
    "#version 410 core\n"
    "out vec4 color;\n"
    "uniform vec4 mycolor;\n"
    "void main()\n"
    "{\n"
    "   color = vec4(mycolor.x , mycolor.y , mycolor.x , mycolor.w);\n"
    "}\n"
;


int main() {
    
    RenderWindow *window = new RenderWindow(800 , 600 ,"OpenGL");
    Triangle *triangle = new Triangle();

    const std::vector<GLfloat> v = {
      -0.5f , 0.0f , 0.0f,
      0.0f  , 0.6f , 0.0f,
      0.5f  , 0.0f , 0.0f
    };


    // important note :- 
    // in oreder to work you must follow this order
    // 
    triangle->setVertexShaderSource(vertexShaderSource);
    triangle->setFragmentShaderSource(fragmentShaderSource);

    // setting shader
    triangle->initVertexArrayObject();
    triangle->initVertexBufferObject(v);
    triangle->initVertexAttribArray();

    triangle->initShaders();

    window->setProgram(triangle->getProgramObject());
    window->setVAO(triangle->getVAO());
    window->setVBO(triangle->getVBO());

    window->run();

    delete window;
    delete triangle;

    return 0;
}