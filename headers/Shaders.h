#ifndef SHADERS_H_
#define SHADERS_H_

#include <glad/glad.h>

#include <string>
#include <vector>

class Shader
{
    private:
        // shaders source
        std::string vertexShaderSource{};
        std::string fragmentShaderSource{};

        // Vertex Array Object and Vertex Buffer Object and program object
        GLuint VAO;
        GLuint VBO;

        GLuint programObject;
        GLuint vertexShader;
        GLuint fragmentShader;      

    public:
        Shader();
        virtual ~Shader();

    public:
        void initVertexArrayObject();
        void initVertexBufferObject(const std::vector<GLfloat> &vertexPos);
        void initVertexAttribArray();
        void initShaders();
        void setVertexShaderSource(const std::string &shaderSource);
        void setFragmentShaderSource(const std::string &shaderSource);

        GLuint getVBO();
        GLuint getVAO();
        GLuint getProgramObject();

        std::string getVertexShaderSource();
        

};

#endif