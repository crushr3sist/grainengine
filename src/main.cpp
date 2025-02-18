#include "shaders/shader.hpp"
#include "window/window.hpp"
#include "camera/camera.hpp"
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

double lastX = 400.0;
double lastY = 300.0;
bool firstMouse = true;
float deltaTime = 0.0f;
float lastFrame = 0.0f;

void mouse_callback(GLFWwindow *window [[maybe_unused]], double xpos,
                    double ypos) {
  if (firstMouse) {
    lastX = xpos;
    lastY = ypos;
    firstMouse = false;
  }

  double xoffset = xpos - lastX;
  double yoffset = lastY - ypos;
  lastX = xpos;
  lastY = ypos;

  camera.processMouseMovement(static_cast<float>(xoffset),
                              static_cast<float>(yoffset));
}

void processInput(GLFWwindow *window){
  if (glfwGetKey(window, GLFW_KEY_ESCAPE)==GLFW_PRESS){
    glfwSetWindowShouldClose(window, true);
  }
  float currentFrame = static_cast<float>(glfwGetTime());
  deltaTime = currentFrame - lastFrame;
  lastFrame = currentFrame;

  if (glfwGetKey(window, GLFW_KEY_W)==GLFW_PRESS){
    camera.processKeyboard(FORWARD, deltaTime);
  }
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
    camera.processKeyboard(BACKWARD, deltaTime);
  }
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
    camera.processKeyboard(LEFT, deltaTime);
  }
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
    camera.processKeyboard(RIGHT, deltaTime);
  }
}

int main() {

  Window Window;
  Shaders Shaders;


  Window.init(800, 600, "grainengine", NULL, NULL);

  std::cout << GLVersion.major << GLVersion.minor << std::endl;
  glfwSetInputMode(Window.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glfwSetCursorPosCallback(Window.window, mouse_callback);

  std::string frag_file = Shaders.readShader("fragment.shader");
  std::string vert_file = Shaders.readShader("vertex.shader");

  
  unsigned int shaderProgram = Shaders.linkShaders(Shaders.compileVertShader(vert_file), Shaders.compileFragShader(frag_file));
  
  unsigned int fragcolor = glad_glGetUniformLocation(shaderProgram, "FragColor");
  
  std::cout << fragcolor << std::endl;

  float vertices[] = {-0.5f, -0.5f, 0.0f, 0.5f,  -0.5f, 0.0f, 0.5f, 0.5f, 0.0f,
    -0.5f, 0.5f,  0.0f, -0.5f, -0.5f, 0.0f, 0.5f, 0.5f, 0.0f};
    
  unsigned int VBO, VAO;
  
  

  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  // Move uniform locations outside the loop
  unsigned int modelLoc = glad_glGetUniformLocation(shaderProgram, "model");
  unsigned int viewLoc = glad_glGetUniformLocation(shaderProgram, "view");
  unsigned int projLoc = glad_glGetUniformLocation(shaderProgram, "projection");

  // Use shader program once before loop
  glUseProgram(shaderProgram);

  while (!glfwWindowShouldClose(Window.window)) {
    processInput(Window.window);
    
    int width, height;

    glfwGetWindowSize(Window.window, &width, &height);
    glViewport(0,0,width, height);
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = camera.getViewMatrix();

    float aspect = static_cast<float>(width) / static_cast<float>(height);
    glm::mat4 projection =
        glm::perspective(glm::radians(camera.getZoom()), aspect, 0.1f, 100.0f);

    // No need to call glUseProgram here since we did it before the loop
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glfwSwapBuffers(Window.window);
    glfwPollEvents();
  }

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteProgram(shaderProgram);

  glfwTerminate();

  return 0;
}
