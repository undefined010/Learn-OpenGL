#include "Shaders.h"
#include <cstdio>

Shader::Shader()
{
    printf("created\n");
}

Shader::~Shader()
{
    glDeleteShader(this->vertexShader);
    glDeleteShader(this->fragmentShader);
    printf("destoried\n");
}

void Shader::setVertexShaderSource(const std::string &shaderSource)
{
    this->vertexShaderSource = shaderSource;
    printf("set vertex shader\n");
}

void Shader::setFragmentShaderSource(const std::string &shaderSource)
{
    this->fragmentShaderSource = shaderSource;
    printf("set fragment shader\n");
}

void Shader::initVertexArrayObject() 
{
    glGenVertexArrays(1 , &this->VAO);
    glBindVertexArray(this->VAO);
    printf("init vao\n");
}

void Shader::initVertexBufferObject(const std::vector<GLfloat> &vertexPos)
{
    glGenBuffers(1, &this->VBO);
    glBindBuffer(GL_ARRAY_BUFFER , this->VBO);
    glBufferData(GL_ARRAY_BUFFER , vertexPos.size() * sizeof(GLfloat) , vertexPos.data() , GL_STATIC_DRAW);
    printf("%lu\n", vertexPos.size());
}

void Shader::initVertexAttribArray()
{
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0 , 3 , GL_FLOAT , GL_FALSE , 0 ,(void*)0);
    glBindVertexArray(0);
    glDisableVertexAttribArray(0);
}

void Shader::initShaders()
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

GLuint Shader::getProgramObject()
{
    return (this->programObject);
}

GLuint Shader::getVAO() 
{
    return (this->VAO);
}

GLuint Shader::getVBO()
{
    return (this->VBO);
}

std::string Shader::getVertexShaderSource()
{
    return this->vertexShaderSource;
}