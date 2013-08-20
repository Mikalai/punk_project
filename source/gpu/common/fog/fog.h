#ifndef FOG_H
#define FOG_H

#include "../../../math/vec4.h"
#include "fog_mode.h"

namespace Gpu
{
	class PUNK_ENGINE_API FogDescription
	{
	public:
		FogDescription();

		void Enable(bool value);
		void SetMode(FogMode value);
		void SetColor(const Math::vec4& value);
		void SetColor(float r, float g, float b, float a);
		void SetDensity(float value);
		void SetStart(float value);
		void SetEnd(float value);
        void SetScale(float value);

		bool IsEnabled() const;
        FogMode GetMode() const;
		const Math::vec4& GetColor() const;
		float GetDensity() const;
		float GetStart() const;
		float GetEnd() const;
        float GetScale() const;

	private:
		bool m_enable;
		FogMode m_mode;
		Math::vec4 m_color;
		float m_density;
		float m_start;
		float m_end;
        float m_scale;
	};
}

#endif // FOG_H
