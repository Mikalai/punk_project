#ifndef _H_PUNK_LOGIC_TERRAIN
#define _H_PUNK_LOGIC_TERRAIN

#include "../config.h"
#include "../../images/images.h"
#include "../../math/vec3.h"
#include "../../math/mat4.h"

namespace Utility
{
	class LIB_UTILITY Terrain
	{
		ImageModule::GrayImage* m_landscape;
		Math::vec3 m_offset;
		float m_scale;
		float m_base_height;
		bool m_modified;
	public:
		float GetDistance(const Math::vec3& point);
		void SetLandscape(ImageModule::GrayImage* landscape) { m_landscape = landscape; }
		ImageModule::GrayImage* GetLandscape() { return m_landscape; }
		void SetOffset(const Math::vec3& offset) { m_offset = offset; }
		Math::vec3& GetOffset() { return m_offset; }
		void SetScale(float scale) { m_scale = scale;}
		float GetScale() const { return m_scale; }
		void SetBaseHeight(float base_height) { m_base_height = base_height; }
		float GetBaseHeight() const { return m_base_height; }
		float GetHeight(float x, float z) const;
		void SetHeight(float x, float z, float height);
 		void SetModified(bool value) { m_modified = value;}
		bool IsModified() const { return m_modified; }
		bool IntersectWithRay(const Math::vec3& start, const Math::vec3& dir, Math::vec3& out);
	};
}

#endif	//	_H_PUNK_LOGIC_TERRAIN