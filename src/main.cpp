#include "shaders/shader.hpp"
#include "window/window.hpp"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

// The global projection matrix is a core part of rendering. It defines how 3D
// points are projected onto the 2D screen space. Here, it starts as an
// orthographic projection but will dynamically update when the window is
// resized.
glm::mat4 projection;

/*
 * Callback function that gets triggered whenever the GLFW window is resized.
 * This function ensures the rendered scene adjusts to fit the new dimensions,
 * maintaining a proper aspect ratio in the projection matrix.
 *
 * Data Flow:
 * - Takes the new `width` and `height` of the window.
 * - Updates the OpenGL viewport to match these dimensions.
 * - Recomputes the global `projection` matrix for rendering consistency.
 *
 * Overall, this function ensures that resizing the window does not distort the
 * rendered objects.
 */
void framebuffer_size_callback(GLFWwindow *, int width, int height) {
  glViewport(0, 0, width, height);

  // Maintain aspect ratio in the orthographic projection matrix
  float aspect = (float)width / (float)height;
  projection = glm::ortho(-aspect, aspect, -1.0f, 1.0f, -1.0f, 1.0f);
}

int main() {
  // Window and Shader objects are custom classes managing the window and shader
  // utilities.
  Window Window;
  Shaders Shaders;

  // Initialize the rendering window with a title and predefined dimensions.
  // This is the entry point for creating the OpenGL context and managing GLFW
  // events.
  Window.init(800, 600, "grainengine", NULL, NULL);

  // Print OpenGL version info for debugging or compatibility checks.
  std::cout << GLVersion.major << GLVersion.minor << std::endl;

  // Load shader source code from files. The shaders define how vertex and
  // fragment data are processed on the GPU. These files contain the core logic
  // for rendering.
  std::string frag_file = Shaders.readShader("fragment.shader");
  std::string vert_file = Shaders.readShader("vertex.shader");

  // Compile the vertex and fragment shaders, then link them into a single
  // program. This shader program is used for rendering and acts as a pipeline
  // on the GPU.
  unsigned int shaderProgram =
      Shaders.linkShaders(Shaders.compileVertShader(vert_file),
                          Shaders.compileFragShader(frag_file));

  // Register the framebuffer callback for dynamic resizing support.
  glfwSetFramebufferSizeCallback(Window.window, framebuffer_size_callback);

  // Initialize the orthographic projection matrix for a default aspect ratio.
  // This matrix transforms 3D coordinates into normalized screen coordinates.
  projection = glm::ortho(-1.33333f, 1.33333f, -1.0f, 1.0f, -1.0f, 1.0f);

  // The model matrix starts as an identity matrix, representing no
  // transformations.
  glm::mat4 model = glm::mat4(1.0f);

  // Obtain the locations of uniform variables in the shader program.
  // These variables are used to pass the projection and model matrices to the
  // GPU.
  unsigned int projLoc = glGetUniformLocation(shaderProgram, "projection");
  unsigned int modelLoc = glGetUniformLocation(shaderProgram, "model");

  // Define vertex positions for a quad (two triangles forming a rectangle).
  // These vertices are in object space and will be transformed by the matrices.
  float vertices[] = {
      -0.5f, -0.5f, 0.0f, // Bottom left
      0.5f,  -0.5f, 0.0f, // Bottom right
      0.5f,  0.5f,  0.0f, // Top right
      -0.5f, 0.5f,  0.0f, // Top left
      -0.5f, -0.5f, 0.0f, // Bottom left (triangle duplication)
      0.5f,  0.5f,  0.0f  // Top right (triangle duplication)
  };

  // Vertex Array Object (VAO) and Vertex Buffer Object (VBO) are OpenGL
  // constructs that store vertex data and state. They optimize data management
  // on the GPU.
  unsigned int VBO, VAO;

  // Create a VAO to manage the state of vertex attributes.
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  // Create a VBO to store the vertex data on the GPU.
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // Define the structure of the vertex data for the shader (position only).
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  // Unbind the VAO and VBO to prevent accidental modifications.
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  // Main rendering loop: Executes continuously until the window is closed.
  while (!glfwWindowShouldClose(Window.window)) {
    int width, height;
    glfwGetWindowSize(Window.window, &width, &height);

    // Clear the screen for the next frame.
    glClear(GL_COLOR_BUFFER_BIT);

    // Activate the shader program and update uniforms.
    glUseProgram(shaderProgram);
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    // Bind the VAO and render the vertex data as triangles.
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    // Swap the buffers to display the rendered frame and process input events.
    glfwSwapBuffers(Window.window);
    glfwPollEvents();
  }

  // Clean up GPU resources to prevent memory leaks.
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteProgram(shaderProgram);

  // Terminate GLFW to release system resources.
  glfwTerminate();

  return 0;
}
