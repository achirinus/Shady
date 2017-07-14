#version 420 core

in vec3 pos;
in vec2 texCoord;
in vec4 vertColor;

uniform mat4 modelMat = mat4(1);
uniform mat4 projMat = mat4(1);
uniform mat4 viewMat = mat4(1);

out VS_OUT
{
	vec2 texCoord;
	vec4 vertColor;
	vec4 vertPos;
} vs_out;


void main()
{
	gl_Position = viewMat * projMat * modelMat * vec4(pos, 1.0);
	vs_out.vertPos = gl_Position;
	vs_out.vertColor = vertColor;
	vs_out.texCoord = texCoord;
	
}