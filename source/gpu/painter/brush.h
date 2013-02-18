#ifndef _H_PUNK_GPU_BRUSH
#define _H_PUNK_GPU_BRUSH

namespace Math 
{
	class vec4;
	class mat3;
	class mat2;
}

namespace GPU
{
	namespace OpenGL { class Texture2D; }

	class Brush
	{
	public:
		Brush();		
		void SetColor(const Math::vec4& value);
		const Math::vec4& GetColor() const;
		void SetMatrix(const Math::mat3& value);
		const Math::mat3& GetMatrix() const;
		void SetStyle(int value);
		int GetStyle() const;
		void SetTexture(const OpenGL::Texture2D* texture);
		const OpenGL::Texture2D* GetTexture() const;
	};
}

#endif	//	_H_PUNK_GPU_BRUSH