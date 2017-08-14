#version 400 core

out vec4 color;

layout(origin_upper_left) in vec4 gl_FragCoord;

uniform sampler2D texSampler;

uniform vec2 mousePos;
uniform bool hasTexture;

in VS_OUT
{
	vec2 texCoord;
	vec4 vertColor;
	vec4 vertPos;
} fs_in;

void main()
{
	vec4 texColor = texture(texSampler, fs_in.texCoord);
	
	//float intensity = 1.0f/ length(fs_in.vertPos.xy - mousePos);
	if(hasTexture)
	{
		color = fs_in.vertColor * texColor;
	}
	else
	{
		color = fs_in.vertColor;
	}
}