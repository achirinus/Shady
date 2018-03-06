#version 400 core

out vec4 color;


in VS_OUT
{
	//vec2 texCoord;
	vec4 vertColor;
	vec4 vertPos;
} fs_in;

void main()
{
	if(gl_FrontFacing)
	{
		color = fs_in.vertColor;	
	}
	else
	{
		color = vec4(1.0, 0.0, 0.0, 1.0);
	}
	
}