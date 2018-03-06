#version 420 core

layout(location = 0) in vec3 pos;
layout(location = 2) in vec4 vertColor;

uniform mat4 modelMat = mat4(1);
uniform mat4 projMat = mat4(1);
uniform mat4 viewMat = mat4(1);

out VS_OUT
{
	vec4 vertColor;
	vec4 vertPos;
} vs_out;


void main()
{
	vec4 position = vec4(pos, 1.0);
	mat4 modelView =viewMat * modelMat;
	position = modelView * position;
	gl_Position = projMat * position;
	vs_out.vertPos = position;
	vs_out.vertColor = vertColor;
}