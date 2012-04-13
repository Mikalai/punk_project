#ifndef _H_PUNK_OPENGL_MODULE_VERTEX_ATTRIBUTES
#define _H_PUNK_OPENGL_MODULE_VERTEX_ATTRIBUTES

namespace OpenGL
{
		enum VertexComponents {
		VERTEX_POSITION = 1, 
		VERTEX_NORMAL = 2, 
		VERTEX_TANGENT = 4, 
		VERTEX_BITANGENT = 8, 
		VERTEX_TEXTURE_0 = 16, 
		VERTEX_BONE = 32,
		VERTEX_FLAGS = 64// If bones present that it is supposed to be bone id and weight
	};

	typedef int VertexAttributes;
}

#endif