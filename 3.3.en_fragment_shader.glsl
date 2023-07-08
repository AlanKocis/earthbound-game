#version 330 core
in vec2 TexCoord;
out vec4 FragColor;

uniform float targeted;  //will have to be some sin function between 0 and 1.
uniform sampler2D ourTexture;

void main()
{
	FragColor = mix(texture(ourTexture, TexCoord), vec4(1.0, 0.0, 0.0, 1.0), targeted);
}