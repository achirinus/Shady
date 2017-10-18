#version 400 core

in vec3 pos;

uniform mat4 modelMat = mat4(1);
uniform mat4 projMat = mat4(1);
uniform mat4 viewMat = mat4(1);

out VS_OUT
{
	//vec2 texCoord;
	//vec4 vertColor;
	vec4 vertPos;
} vs_out;

void main()
{
	mat4 fullMat = projMat * viewMat * modelMat;
	gl_Position = fullMat * vec4(pos, 1.0f);
	vs_out.vertPos = gl_Position;
}