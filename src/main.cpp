#include "window/window.hpp"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <iostream>

// Vertex shader source code
// const char *vertexShaderSource = R"(
// #version 330 core
// layout (location = 0) in vec3 aPos;
// layout (location = 1) in vec3 aColor;
// out vec3 ourColor;

// void main()
// {
//     gl_Position = vec4(aPos, 1.0);
//     ourColor = aColor;
// }
// )";

// // Fragment shader source code
// const char *fragmentShaderSource = R"(
// #version 330 core
// in vec3 ourColor;
// out vec4 FragColor;

// void main()
// {
//     FragColor = vec4(ourColor, 1.0);
// }
// )";

int main() {
  // Initialize GLFW
  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW\n";
    return -1;
  }

  test();
  test2();

  // // Create a windowed mode window and its OpenGL context
  // GLFWwindow *window =
  //     glfwCreateWindow(800, 600, "Rainbow Triangle", NULL, NULL);
  // if (!window) {
  //   std::cerr << "Failed to create GLFW window\n";
  //   glfwTerminate();
  //   return -1;
  // }

  // // Make the window's context current
  // glfwMakeContextCurrent(window);

  // // Load GLAD to configure OpenGL
  // if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
  //   std::cerr << "Failed to initialize GLAD\n";
  //   return -1;
  // }

  // // Build and compile the vertex shader
  // unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  // glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  // glCompileShader(vertexShader);

  // // Check for shader compile errors
  // int success;
  // char infoLog[512];
  // glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  // if (!success) {
  //   glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
  //   std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
  //             << infoLog << std::endl;
  // }

  // // Build and compile the fragment shader
  // unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  // glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  // glCompileShader(fragmentShader);

  // // Check for shader compile errors
  // glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  // if (!success) {
  //   glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
  //   std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
  //             << infoLog << std::endl;
  // }

  // // Link shaders
  // unsigned int shaderProgram = glCreateProgram();
  // glAttachShader(shaderProgram, vertexShader);
  // glAttachShader(shaderProgram, fragmentShader);
  // glLinkProgram(shaderProgram);

  // // Check for linking errors
  // glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
  // if (!success) {
  //   glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
  //   std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
  //             << infoLog << std::endl;
  // }

  // // Delete the shaders as they're linked into our program now and no longer
  // // necessary
  // glDeleteShader(vertexShader);
  // glDeleteShader(fragmentShader);

  // // Set up vertex data and buffers and configure vertex attributes
  // float vertices[] = {
  //     // Positions         // Colors
  //     0.0f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, // Top vertex (Red)
  //     -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // Bottom left vertex (Green)
  //     0.5f,  -0.5f, 0.0f, 0.0f, 0.0f, 1.0f  // Bottom right vertex (Blue)
  // };

  // unsigned int VBO, VAO;
  // glGenVertexArrays(1, &VAO);
  // glGenBuffers(1, &VBO);

  // glBindVertexArray(VAO);

  // glBindBuffer(GL_ARRAY_BUFFER, VBO);
  // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // // Position attribute
  // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void
  // *)0); glEnableVertexAttribArray(0);

  // // Color attribute
  // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
  //                       (void *)(3 * sizeof(float)));
  // glEnableVertexAttribArray(1);

  // // Unbind the VBO and VAO
  // glBindBuffer(GL_ARRAY_BUFFER, 0);
  // glBindVertexArray(0);

  // // Render loop
  // while (!glfwWindowShouldClose(window)) {
  //   // Clear the color buffer
  //   glClear(GL_COLOR_BUFFER_BIT);

  //   // Use our shader program
  //   glUseProgram(shaderProgram);
  //   glBindVertexArray(VAO);

  //   // Draw the triangle
  //   glDrawArrays(GL_TRIANGLES, 0, 3);

  //   // Swap the buffers and poll for events
  //   glfwSwapBuffers(window);
  //   glfwPollEvents();
  // }

  // // Deallocate resources
  // glDeleteVertexArrays(1, &VAO);
  // glDeleteBuffers(1, &VBO);
  // glDeleteProgram(shaderProgram);

  // // Terminate GLFW
  // glfwTerminate();
  return 0;
}
