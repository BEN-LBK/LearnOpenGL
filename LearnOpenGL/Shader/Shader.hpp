//
//  Shader.hpp
//  LearnOpenGL
//
//  Created by BEN-LBK on 2021/11/23.
//

#ifndef Shader_hpp
#define Shader_hpp

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


class Shader{
public:
    unsigned int ID;
    // 构造Shader着色器
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
    // 使用程序
    void use();
    // 工具函数
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
private:
    void checkCompileErrors(unsigned int shader, std::string type);
};


#endif /* Shader_hpp */
