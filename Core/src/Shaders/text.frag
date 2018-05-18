#version 420 core

out vec4 color;

layout(origin_upper_left) in vec4 gl_FragCoord;

uniform sampler2D texSampler;

uniform vec2 mousePos;

in VS_OUT
{
	vec2 texCoord;
	vec4 vertColor;
	vec4 vertPos;
} fs_in;

void main()
{
	//vec4 texColor = vec4(1, 1, 1, texture(texSampler, fs_in.texCoord).a);
	//color = fs_in.vertColor * texColor;
	vec4 Texel = texture(texSampler, fs_in.texCoord);
	if(Texel.r <= 0.3) discard;
	
	color = vec4(1, 1, 1, Texel.r) * fs_in.vertColor;
	//color = vec4(1,1,1,1);
}