#ifndef _H_PUNK_BONE
#define _H_PUNK_BONE

#include "../../config.h"
#include "../../math/mat4.h"
#include "../../string/string.h"
#include "types.h"

#include <vector>
#include <map>

namespace Utility
{
	class BoneDesc;
}

namespace Virtual
{
	class AnimationMixer;
}

namespace Virtual
{
	class Armature;

	class PUNK_ENGINE Bone
	{
	public:

		Bone();
		Bone(const Utility::BoneDesc& desc);
		~Bone();

		void SetName(const System::string& name);
		void SetMatrix(const Math::mat4& matrix);
		void SetParent(Bone* parent);
		void SetBoneMatrix(const Math::mat4& matrix);
		void SetIndexInArmature(int index);		
		void SetArmature(Armature* armature);
		Armature* GetArmature();

		const BoneName& GetName() const;
		const Bone* GetParent() const;
		const Math::mat4 GetWorldMatrix() const;
		const Math::mat4& GetBoneMatrix() const;
		int GetIndex() const;

		void SetLength(float v) { m_length = v; }
		float GetLength() const { return m_length; }

		void AddChild(Bone* bone);

		std::vector<Bone*>& GetChildren() { return m_children; }
		const std::vector<Bone*>& GetChildren() const { return m_children; }

		const Math::mat4& GetAnimatedGlobalMatrix(const Math::mat4& mesh_transform) const;
		void UpdatePose(Virtual::AnimationMixer* Mixer, float frame, bool deep = false);

		/* Drops all precalculated staff */
		void ResetCache();

		bool Save(std::ostream& stream) const;
		bool Load(std::istream& stream);
	private:
		Bone(const Bone&);
		Bone& operator = (const Bone&);

	private:
		Bone*				m_parent;
		std::vector<Bone*>	m_children;
		BoneName			m_name;
		Math::mat4			m_global_matrix;
		Math::mat4			m_bone_matrix;
		int					m_index_in_armature;
		Math::mat4			m_last_local_matrix_update;
		mutable Math::mat4	m_last_global_matrix_update;
		float				m_last_get_global_matrix;
		float				m_length;
		mutable bool		m_need_update_global_matrix;
		Armature*			m_armature;
	};
}

#endif