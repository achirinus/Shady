#version 420 core

out vec4 color;

in VS_OUT
{
	vec4 vertColor;
	vec4 vertPos;
} fs_in;

void main()
{
	color = fs_in.vertColor;
	color = vec4(1.0, 1.0, 0.0, 1.0);
}