#include "Triangle.h"
#include <cstdio>

Triangle::Triangle()
{
    printf("created\n");
}

Triangle::~Triangle()
{
    glDeleteShader(this->vertexShader);
    glDeleteShader(this->fragmentShader);
    printf("destoried\n");
}

void Triangle::setVertexShaderSource(const std::string &shaderSource)
{
    this->vertexShaderSource = shaderSource;
    printf("set vertex shader\n");
}

void Triangle::setFragmentShaderSource(const std::string &shaderSource)
{
    this->fragmentShaderSource = shaderSource;
    printf("set fragment shader\n");
}

void Triangle::initVertexArrayObject() 
{
    glGenVertexArrays(1 , &this->VAO);
    glBindVertexArray(this->VAO);
    printf("init vao\n");
}

void Triangle::initVertexBufferObject(const std::vector<GLfloat> &vertexPos)
{
    glGenBuffers(1, &this->VBO);
    glBindBuffer(GL_ARRAY_BUFFER , this->VBO);
    glBufferData(GL_ARRAY_BUFFER , vertexPos.size() * sizeof(GLfloat) , vertexPos.data() , GL_STATIC_DRAW);
    printf("%lu\n", vertexPos.size());
}

void Triangle::initVertexAttribArray()
{
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0 , 3 , GL_FLOAT , GL_FALSE , 0 ,(void*)0);
    glBindVertexArray(0);
    glDisableVertexAttribArray(0);
}

void Triangle::initShaders()
{
    if (this->vertexShaderSource.length() == 0 || this->fragmentShaderSource.length() == 0) {
        fprintf(stderr,"one or all of the shaders are empty\n");
        exit(EXIT_FAILURE);
    }

    this->programObject = glCreateProgram();

    this->vertexShader  = glCreateShader(GL_VERTEX_SHADER);
    this->fragmentShader= glCreateShader(GL_FRAGMENT_SHADER);

    const char *temp_vertexShaderSource   = this->vertexShaderSource.c_str();
    const char *temp_fragmentShaderSource = this->fragmentShaderSource.c_str();

    glShaderSource(this->vertexShader , 1 , &temp_vertexShaderSource , nullptr);
    glCompileShader(this->vertexShader);

    glShaderSource(this->fragmentShader , 1 , &temp_fragmentShaderSource , nullptr);
    glCompileShader(this->fragmentShader);

    glAttachShader(this->programObject , this->vertexShader);
    glAttachShader(this->programObject , this->fragmentShader);
    glLinkProgram(this->programObject);
    glValidateProgram(this->programObject);
    printf("done setting program object\n");

}

GLuint Triangle::getProgramObject()
{
    return (this->programObject);
}

GLuint Triangle::getVAO() 
{
    return (this->VAO);
}

GLuint Triangle::getVBO()
{
    return (this->VBO);
}

std::string Triangle::getVertexShaderSource()
{
    return this->vertexShaderSource;
}