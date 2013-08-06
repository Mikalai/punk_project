/// <summary> 
/// Fragment shader for rendering the depth values to a texture. 
/// </summary> 
#version 330

#ifdef GL_ES 
precision highp float;
#endif

/// <summary>
/// Linear depth calculation. 
/// You could optionally upload this as a shader parameter. 
/// <summary> 
uniform float uNear; 
uniform float uFar; 

/// <summary> 
/// Specifies the type of shadow map filtering to perform. 
/// 0 = None 
/// 1 = PCM 
/// 2 = VSM 
/// 3 = ESM 
/// 
/// VSM is treated differently as it must store both moments into the RGBA component. 
/// </summary> 
uniform int uFilterType; 
/// <summary> 

/// Varying variables. 
/// <summary> 
in vec4 Position; 

out vec4 Color;

/// <summary> 
/// Pack a floating point value into an RGBA (32bpp). 
/// Used by SSM, PCF, and ESM. 
/// 
/// Note that video cards apply some sort of bias (error?) to pixels, 
/// so we must correct for that by subtracting the next component's
/// value from the previous component.
/// </summary> 
vec4 pack (float depth) 
{
	const vec4 bias = vec4(1.0 / 255.0, 1.0 / 255.0, 1.0 / 255.0, 0.0);
	float r = depth; 
	float g = fract(r * 255.0); 
	float b = fract(g * 255.0); 
	float a = fract(b * 255.0); 
	vec4 colour = vec4(r, g, b, a); 
	return colour - (colour.yzww * bias); 
}

/// <summary> 
/// Pack a floating point value into a vec2 (16bpp). 
/// Used by VSM. 
/// </summary> 
vec2 packHalf (float depth) 
{ 
	const vec2 bias = vec2(1.0 / 255.0, 0.0); 
	vec2 colour = vec2(depth, fract(depth * 255.0)); 
	return colour - (colour.yy * bias); 
} 

/// <summary> 
/// Fragment shader entry. 
/// </summary> 
void main () 
{ 
	float LinearDepthConstant = 1.0 / (uFar - uNear); 
	// Linear depth 
	float linearDepth = length(Position) * LinearDepthConstant; 
	if ( uFilterType == 2 ) 
	{
		// 
		// Variance Shadow Map Code 
		// Encode moments to RG/BA 
		// 
		// float moment1 = gl_FragCoord.z; 
		float moment1 = linearDepth;
		float moment2 = moment1 * moment1; 
		Color = vec4(packHalf(moment1), packHalf(moment2)); 
	}
	else
	{
		//
		// Classic shadow mapping algorithm. 
		// Store screen-space z-coordinate or linear depth value (better precision) 
		// 
		// gl_FragColor = pack(gl_FragCoord.z); 
		Color = pack(linearDepth); 
	} 
}
