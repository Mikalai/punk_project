#ifndef _H_PUNK_GPU_PAINTER_PEN
#define _H_PUNK_GPU_PAINTER_PEN

#include "../../config.h"

namespace Math { class vec4; }

namespace Gpu
{
	class PUNK_ENGINE_API Pen final
	{
	public:
		Pen();
		Pen(const Pen& pen);
		Pen& operator = (const Pen& pen);
		~Pen();

		void SetColor(const Math::vec4& color);
		void SetColor(float r, float g, float b, float a);
		void SetWidth(float value);

		const Math::vec4& GetColor() const;
		float GetWidth() const;

		struct PenImpl;
		PenImpl* impl;
	};
}

#endif	//	_H_PUNK_GPU_PAINTER_PEN
