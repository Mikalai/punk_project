#ifndef _H_PUNK_AI_NAVI_MESH
#define _H_PUNK_AI_NAVI_MESH

#include "../config.h"
#include "../math/mat4.h"
#include "../math/vec3.h"

namespace System { class string; }
namespace Utility { class MeshDesc; }

namespace AI
{
	class PUNK_ENGINE_PUBLIC NaviMesh
	{
	public:

		void SetTransform(const Math::mat4& value) { m_transfrom = value; }
		const Math::mat4 GetTranform() { return m_transfrom; }

		NaviMesh(const Utility::MeshDesc& desc);
		static NaviMesh* CreateFromFile(const System::string& path);

		const Math::vec3 GetPoint(int index);

	private:
		Math::mat4 m_transfrom;
		std::vector<Math::vec3> m_points;
	};
}

#endif	//	_H_PUNK_AI_NAVI_MESH