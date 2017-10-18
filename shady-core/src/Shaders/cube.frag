#version 400 core

out vec4 color;


in VS_OUT
{
	//vec2 texCoord;
	//vec4 vertColor;
	vec4 vertPos;
} fs_in;

void main()
{
	color = vec4(0.2, 1.0, 1.0, 1.0);
}