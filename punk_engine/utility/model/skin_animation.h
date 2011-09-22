#ifndef _H_PUNK_SKIN
#define _H_PUNK_SKIN

#include "../config.h"
#include <vector>
#include <map>
#include "../../math/smart_matrix.h"
#include "../../math/mat4.h"
#include "../../math/quat.h"
#include "scene.h"
#include "bone.h"

namespace System
{
	class Buffer;
}

namespace Utility
{
	class Model;

	struct Frame
	{
		int m_parent;
		Math::quat m_rotation;
		Math::vec3 m_position;
	};

	typedef std::vector<Bone> BonesCollection;

	class LIB_UTILITY SkinAnimation
	{	
		System::string m_name;
		BonesCollection m_rest_pose;
		
		float m_duration;
		float m_tick_per_second;

		Math::Matrix<float> m_time;
		Math::Matrix<Frame> m_animation;

	public:
		void Save(System::Buffer& buffer);
		void Load(System::Buffer& buffer);

		int GetBonesCount() const;

		const Math::quat GetRotation(unsigned bone_id, unsigned frame) const;
		const Math::vec3 GetPosition(unsigned bone_id, unsigned frame) const;
		const Math::mat4 GetTransform(unsigned bone_id, unsigned frame) const;
		unsigned GetFramesCount() const;

		const Bone& GetBone(unsigned id) const;

		friend class RawScene;
	};
}

#endif