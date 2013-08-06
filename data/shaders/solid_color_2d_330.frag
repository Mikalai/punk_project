#version 330

uniform vec4 uDiffuseColor;
uniform float uRadius;
//uniform vec2 uTopLeft;
//uniform vec2 uBottomRight;

in vec2 pos;
out vec4 color;
in vec2 topLeft;
in vec2 bottomRight;

void main(void)
{
	vec2 xc1 = vec2(topLeft.x + uRadius, topLeft.y - uRadius);
	vec2 xc2 = vec2(bottomRight.x - uRadius, topLeft.y - uRadius);
	vec2 xc3 = vec2(bottomRight.x - uRadius, bottomRight.y + uRadius);
	vec2 xc4 = vec2(topLeft.x + uRadius, bottomRight.y + uRadius);
	if (pos.x <= xc1.x && pos.y >= xc1.y)
	{
		vec2 d = vec2(xc1.x - pos.x, xc1.y - pos.y);

		if ( d.x*d.x + d.y*d.y < uRadius*uRadius)
			color = vec4( uDiffuseColor.rgb, uDiffuseColor.a-(d.x*d.x + d.y*d.y)/(uRadius*uRadius));
		else
			color = vec4( 0, 0, 1, 0);
	}
	else if (pos.x >= xc2.x && pos.y >= xc2.y)
	{
		vec2 d = vec2(xc2.x - pos.x, xc2.y - pos.y);

		if ( d.x*d.x + d.y*d.y < uRadius*uRadius)
			color = vec4( uDiffuseColor.rgb, uDiffuseColor.a-(d.x*d.x + d.y*d.y)/(uRadius*uRadius));
		else
			color = vec4( 0, 0, 1, 0);

	}
	else if (pos.x >= xc3.x && pos.y <= xc3.y)
	{
		vec2 d = vec2(xc3.x - pos.x, xc3.y - pos.y);

		if ( d.x*d.x + d.y*d.y < uRadius*uRadius)
			color = vec4( uDiffuseColor.rgb, uDiffuseColor.a-(d.x*d.x + d.y*d.y)/(uRadius*uRadius));
		else
			color = vec4( 0, 0, 1, 0);
	}
	else if (pos.x <= xc4.x && pos.y <= xc4.y)
	{
		vec2 d = vec2(xc4.x - pos.x, xc4.y - pos.y);

		if ( d.x*d.x + d.y*d.y < uRadius*uRadius)
			color = vec4( uDiffuseColor.rgb, uDiffuseColor.a-(d.x*d.x + d.y*d.y)/(uRadius*uRadius));
		else
			color = vec4( 0, 0, 1, 0);
	}
	else if (pos.x >= xc1.x && pos.x <= xc2.x && pos.y >= xc1.y)
	{
		vec2 d = vec2(0, xc1.y - pos.y);
		color = vec4( uDiffuseColor.rgb, uDiffuseColor.a - (d.y*d.y)/(uRadius*uRadius));
	}
	else if (pos.x >= xc2.x && pos.y >= xc3.y && pos.y <= xc2.y)
	{
		vec2 d = vec2(xc2.x - pos.x, 0);
		color = vec4( uDiffuseColor.rgb, uDiffuseColor.a - (d.x*d.x)/(uRadius*uRadius));
	}
	else if (pos.x >= xc1.x && pos.x <= xc2.x && pos.y <= xc3.y)
	{
		vec2 d = vec2(0, xc3.y - pos.y);
		color = vec4( uDiffuseColor.rgb, uDiffuseColor.a - (d.y*d.y)/(uRadius*uRadius));
	}
	else if (pos.x <= xc1.x && pos.y >= xc3.y && pos.y <= xc2.y)
	{
		vec2 d = vec2(xc1.x - pos.x, 0);
		color = vec4( uDiffuseColor.rgb, uDiffuseColor.a - (d.x*d.x)/(uRadius*uRadius));
	} else
		color = uDiffuseColor;		
}