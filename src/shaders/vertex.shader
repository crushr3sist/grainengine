#version 460 core
layout (location = 0) in vec3 aPos;      // Input from C++ vertex data

uniform mat4 projection;                  // Input from C++ uniforms
uniform mat4 model;                      // Input from C++ uniforms

out vec3 ourPos;                         // Output to fragment shader

void main()
{
    gl_Position = projection * model * vec4(aPos, 1.0);  // Required output
    ourPos = aPos;                       // Pass data to fragment shader
}