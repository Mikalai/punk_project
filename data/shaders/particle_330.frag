#version 330

#define BLEND_TIME 1

uniform vec4 uDiffuseColor;
uniform sampler2D uDiffuseMap;

in vec2 texCoord;
in float life_time;
in float cur_time;
in float start_time;

out vec4 color;

void main(void)
{	
	if (cur_time < start_time)
		discard;
	else
	{
		if (cur_time > life_time)
			color = vec4(0,0,0,0);
		else 
		{
			vec4 c = texture(uDiffuseMap, gl_PointCoord);
			if (c.w <= 0.9)
				discard;
			if (life_time - cur_time > BLEND_TIME)
				color = vec4(c.xyz, 1.0);
			else
				color = vec4(c.xyz, (life_time - cur_time) / BLEND_TIME);
		}
	}
}