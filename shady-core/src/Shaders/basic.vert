#version 420 core

in vec3 pos;
in vec2 texCoord;
in vec4 vertColor;

uniform mat4 modelMat = mat4(1);
uniform mat4 projMat = mat4(1);
uniform mat4 viewMat = mat4(1);
uniform mat4 totalMovedMat = mat4(1);

out VS_OUT
{
	vec2 texCoord;
	vec4 vertColor;
	vec4 vertPos;
} vs_out;


void main()
{
	vec4 position = vec4(pos, 1.0);
	mat4 moveBack = inverse(totalMovedMat);
	mat4 modelView = viewMat * modelMat;
	
	vec4 modelPos = moveBack * position;
	modelPos =  modelView * modelPos;
	modelPos = totalMovedMat * modelPos;

	gl_Position = projMat * modelPos;

	vs_out.vertPos = gl_Position;
	vs_out.vertColor = vertColor;
	vs_out.texCoord = texCoord;
	
}