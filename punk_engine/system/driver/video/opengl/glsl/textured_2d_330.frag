#version 330

uniform vec4 uDiffuseColor;
uniform sampler2D uDiffuseMap;

in vec2 pos;
in vec2 texCoord;

out vec4 color;

void main(void)
{
	//color = vec4(texCoord.y, 0, 0, 1);

	vec4 diff = texture(uDiffuseMap, texCoord).rrrr;
	if (diff.r == 0)
		color = vec4(0,0,0,0);
	else
	{
		//if (diff.r < 0.5)
			color = vec4( (diff * uDiffuseColor).rgb, diff.r);
	//	else
		//	color = uDiffuseColor;
	}/**/
}