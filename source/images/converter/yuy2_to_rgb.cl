
struct Input
{
	char y0, u0, y1, v0;
};

struct Output
{
	char r0, g0, b0, r1, g1, b1;
};

__kernel void YUY2toRGB(__global const Input* src, int size_in_chunks,__global Output* dst)
{
	// Index of the elements to add \src_id"
	unsigned int src_id = get_global_id(0);
	unsigned int dst_id = 2*src_id;

	float y0 = (float)src[src_id].y0;
	float u0 = (float)src[src_id].u0;
	float y1 = (float)src[src_id].y1;
	float v0 = (float)src[src_id].v0;

	float4 f[3] = ( (1.164383f,  1.596027f,  0.000f, -222.912f),
		(1.164383f, -0.813000f, -0.391f,  135.488f),
		(1.164383f,  0.000000f,  2.018f, -276.928f));

	float4 v1 = (y0, v0, u0, 1);
	float4 v2 = (y1, v0, u0, 1);

	float4 a1 = float4(dot(f[0], v1), dot(f[1], v1), dot(f[2], v1), 1);
	float4 a2 = float4(dot(f[0], v2), dot(f[1], v2), dot(f[2], v2), 1);

	float4 pixel_1 = Clamp(a1, float4(0,0,0,0), float4(255,255,255,255));
	float4 pixel_2 = Clamp(a2, float4(0,0,0,0), float4(255,255,255,255));

	dst[dst_id].r0 = (char)pixel_1[0];
	dst[dst_id].g0 = (char)pixel_1[1];
	dst[dst_id].b0 = (char)pixel_1[2];

	dst[dst_id].r1 = (char)pixel_2[0];
	dst[dst_id].g1 = (char)pixel_2[1];
	dst[dst_id].b1 = (char)pixel_2[2];	
}