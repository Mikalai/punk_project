#ifndef _H_PUNK_BONE
#define _H_PUNK_BONE

#include "../config.h"
#include "../../math/mat4.h"
#include "../../system/string.h"
#include "../animation/animation_mixer.h"

#include <vector>
#include <map>

namespace Utility
{
	class Armature;

	typedef System::string BoneName;
	typedef int BoneID;		
	typedef float Weight;
	typedef std::map<BoneName, Weight> BoneWeights;

	/*class LIB_UTILITY Bone2
	{
		int m_id;
		Bone* m_parent;

	};*/

	class LIB_UTILITY Bone
	{
		Bone*				m_parent;
		std::vector<Bone*>	m_children;
		BoneName			m_name;
		Math::mat4			m_global_matrix;
		Math::mat4			m_bone_matrix;
		int					m_index_in_armature;
		AnimationMixer		m_animation;
		Math::mat4			m_last_local_matrix_update;
		Math::mat4			m_last_global_matrix_update;
		float				m_last_get_global_matrix;
		bool				m_need_update_global_matrix;
		Armature*			m_armature;
	public:
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

		void AddChild(Bone* bone);

		Math::mat4& GetAnimatedGlobalMatrix();
		void UpdatePose(float frame);
		AnimationMixer& GetAnimationMixer();
		const AnimationMixer& GetAnimationMixer() const;

		/* Drops all precalculated staff */
		void ResetCache();

		void Save(std::ostream& stream);
		void Load(std::istream& stream);
	};
}

#endif