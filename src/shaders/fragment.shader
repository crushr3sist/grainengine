#version 460 core
in vec3 ourPos;                          // Input from vertex shader
out vec4 FragColor;                      // Output to screen

void main()
{
    // Use the position data to create a color
    FragColor = vec4(ourPos * 0.5 + 0.5, 1.0);
}