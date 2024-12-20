#include <direct.h>
#include <fstream>
#include <glad/glad.h>
#include <iostream>
#include <sstream>
#include <string>

class Shaders {
public:
  int success;
  char infoLog[512];

  std::string readShader(const char *path) {
    std::ifstream file(path);
    if (!file.is_open()) {
      std::cerr << "Could not open file: " << path << std::endl;

      // Print current working directory
      char cwd[1024];
      if (_getcwd(cwd, sizeof(cwd)) != NULL) {
        std::cerr << "Current working directory: " << cwd << std::endl;
      } else {
        std::cerr << "Unable to retrieve current working directory."
                  << std::endl;
      }
      return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
  }

  unsigned int compileShader(const std::string &shaderCode, GLenum shaderType) {
    unsigned int shader = glCreateShader(shaderType);
    const char *shaderSource = shaderCode.c_str();
    glShaderSource(shader, 1, &shaderSource, NULL);
    glCompileShader(shader);

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(shader, sizeof(infoLog), nullptr, infoLog);
      std::cerr << "ERROR:SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    return shader;
  }

  unsigned int compileVertShader(const std::string &vertexShaderCode) {
    return compileShader(vertexShaderCode, GL_VERTEX_SHADER);
  }

  unsigned int compileFragShader(const std::string &fragmentShaderCode) {
    return compileShader(fragmentShaderCode, GL_FRAGMENT_SHADER);
  }

  unsigned int linkShaders(unsigned int vertexShader,
                           unsigned int fragmentShader) {
    unsigned int shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
      glGetProgramInfoLog(shaderProgram, sizeof(infoLog), NULL, infoLog);
      std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
                << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
  }
};
