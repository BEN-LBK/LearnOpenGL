//
//  openGL_05.cpp
//  LearnOpenGL
//
//  Created by BEN-LBK on 2021/11/23.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader/Shader.hpp"

#include <iostream>
#include <cmath>

void framebuffer_size_callback(GLFWwindow * window, int width, int height);
void processInput(GLFWwindow *window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGTH = 600;

float xOffset = 0.0f;

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    
    // glfw window creation
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGTH, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    // glad load all openGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //The issue was indeed because of the apple sandboxing. This again rises the question, apple sandbox: friend or enemy?
    //After putting the file in /Users/USER/Library/Container/com.xxx.xxx/Data/ it worked.
   
#ifdef __APPLE__
    // build and compile shader program
    Shader ourShader("/Users/ben/Library/Containers/com.lbk.shader/shader_05.vs", "/Users/ben/Library/Containers/com.lbk.shader/shader_05.fs");
#else
    // build and compile shader program
    Shader ourShader("./Shader/shader_05.vs", "./Shader/shader_05.fs");
    
#endif
    
    // set vertex data
    
    float vertices[]={
        //position       // colors
        0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
       -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
        0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top
    };
    
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    // bind the vertex array object first, then bind and set vertex buffer, and then configure vertex attributes
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    
    // unbind the VAO
    glBindVertexArray(0);
    
    
    // render loop
    
    while (!glfwWindowShouldClose(window)) {
        // input
        processInput(window);
        
        // render
        glClearColor(0.2f,0.3f,0.3f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        // update key value
        int vertexPosOffset = glGetUniformLocation(ourShader.ID, "xOffset");
        glUseProgram(ourShader.ID);
        glUniform1f(vertexPosOffset, xOffset);
        
        float timeValue = glfwGetTime();
        float redValue = sin(timeValue)/2.0f + 0.5f;
        int colorOffset = glGetUniformLocation(ourShader.ID, "cOffset");
        glUseProgram(ourShader.ID);
        glUniform3f(colorOffset, redValue, redValue, redValue);
        
        // render the triangle
        ourShader.use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        //swap buffers and poll IO events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    // delete resource
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    
    // terminate clearing all previously allocate glfw reources
    glfwTerminate();
    return 0;
    
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
        xOffset += 0.001;
        std::cout << "processInput ++" << xOffset << std::endl;
    }
    else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
        xOffset -= 0.001;
        std::cout << "processInput --" << xOffset << std::endl;
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
