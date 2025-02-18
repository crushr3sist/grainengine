// camera.hpp
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum Camera_Movement { FORWARD, BACKWARD, LEFT, RIGHT };

class Camera {
private:
  glm::vec3 position;
  glm::vec3 front;
  glm::vec3 up;
  glm::vec3 right;
  glm::vec3 worldUp;

  // Euler angles
  float yaw;
  float pitch;

  // Camera options
  float movementSpeed;
  float mouseSensitivity;
  float zoom;

public:
  Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f))
      : position(position), front(glm::vec3(0.0f, 0.0f, -1.0f)),
        worldUp(glm::vec3(0.0f, 1.0f, 0.0f)), yaw(-90.0f), pitch(0.0f),
        movementSpeed(2.5f), mouseSensitivity(0.1f), zoom(45.0f) {
    updateCameraVectors();
  }

  glm::mat4 getViewMatrix() {
    return glm::lookAt(position, position + front, up);
  }

  void processKeyboard(Camera_Movement direction, float deltaTime) {
    float velocity = movementSpeed * deltaTime;
    if (direction == FORWARD)
      position += front * velocity;
    if (direction == BACKWARD)
      position -= front * velocity;
    if (direction == LEFT)
      position -= right * velocity;
    if (direction == RIGHT)
      position += right * velocity;
  }

  void processMouseMovement(float xoffset, float yoffset,
                            bool constrainPitch = true) {
    xoffset *= mouseSensitivity;
    yoffset *= mouseSensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (constrainPitch) {
      if (pitch > 89.0f)
        pitch = 89.0f;
      if (pitch < -89.0f)
        pitch = -89.0f;
    }

    updateCameraVectors();
  }

  float getZoom() const { return zoom; }
  glm::vec3 getPosition() const { return position; }
  glm::vec3 getFront() const { return front; }

private:
  void updateCameraVectors() {
    glm::vec3 newFront;
    newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    newFront.y = sin(glm::radians(pitch));
    newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    this->front = glm::normalize(newFront);

    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
  }
};

