#ifndef _H_PUNK_GPU_BRUSH
#define _H_PUNK_GPU_BRUSH

#include "../../config.h"

namespace Math
{
	class vec4;
	class mat3;
	class mat2;
}

namespace GPU
{
	class Texture2D;

	class PUNK_ENGINE_PUBLIC Brush final
	{
	public:
		Brush();
		Brush(const Brush& value);
		Brush& operator = (const Brush& value);
		~Brush();

		void SetColor(const Math::vec4& value);
		const Math::vec4& GetColor() const;
		void SetMatrix(const Math::mat3& value);
		const Math::mat3& GetMatrix() const;
		void SetStyle(int value);
		int GetStyle() const;
		void SetTexture(const Texture2D* texture);
		const Texture2D* GetTexture() const;

		struct BrushImpl;
		BrushImpl* impl;
	};
}

#endif	//	_H_PUNK_GPU_BRUSH
