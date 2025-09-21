#version 330 core
out vec4 FragColor;

in vec3 ourColor;

uniform vec3 newColour;

void main()
{
    FragColor = vec4(ourColor + newColour, 1.0f);
}