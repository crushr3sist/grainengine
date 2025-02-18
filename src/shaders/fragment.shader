#version 460 core
in vec3 ourPos;
out vec4 FragColor;

void main()
{
    
    FragColor = vec4(ourPos * 0.5 + 0.5, 1.0);
}