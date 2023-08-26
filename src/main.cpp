#include "RenderWindow.h"
#include "Shaders.h"

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
    "void main()\n"
    "{\n"
    "   color = vec4(0.2f , 0.1f , 0.5f , 1.0f);\n"
    "}\n"
;


int main() {
    
    RenderWindow *window = new RenderWindow(800 , 600 ,"OpenGL");
    Shader *shader = new Shader();

    const std::vector<GLfloat> v = {
      -0.5f , 0.0f , 0.0f,
      0.0f  , 0.6f , 0.0f,
      0.5f  , 0.0f , 0.0f
    };


    // important note :- 
    // in oreder to work you must follow this order
    // 
    shader->setVertexShaderSource(vertexShaderSource);
    shader->setFragmentShaderSource(fragmentShaderSource);

    // setting shader
    shader->initVertexArrayObject();
    shader->initVertexBufferObject(v);
    shader->initVertexAttribArray();

    shader->initShaders();

    window->setProgram(shader->getProgramObject());
    window->setVAO(shader->getVAO());
    window->setVBO(shader->getVBO());


    window->run();

    delete window;
    delete shader;

    return 0;
}