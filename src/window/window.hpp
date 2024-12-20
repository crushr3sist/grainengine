#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <iostream>

class Window {

public:
  GLFWwindow *window;
  bool init(int width, int height, const char *title, GLFWmonitor *monitor,
            GLFWwindow *share) {
    if (!glfwInit()) {
      std::cerr << "Failed to initialize GLFW" << std::endl;
      return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // OpenGL 4.x
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6); // OpenGL 4.6
    glfwWindowHint(GLFW_OPENGL_PROFILE,
                   GLFW_OPENGL_CORE_PROFILE); // Core Profile

    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

    window = glfwCreateWindow(width, height, title, monitor, share);
    if (!window) {
      std::cerr << "failed to create GLFW window" << std::endl;
      glfwTerminate();
      return false;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
      std::cerr << "Failed to initialize GLAD\n";
      return false;
    }

    return true;
  }
};
