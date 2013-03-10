#ifndef _H_PUNK_BONE
#define _H_PUNK_BONE

#include "../../config.h"
#include "../../math/mat4.h"
#include "../../string/string.h"
#include "types.h"

#include <vector>
#include <map>

namespace Virtual
{
	class AnimationMixer;
}

namespace Virtual
{
	class PUNK_ENGINE Bone
	{
	public:

		Bone();
		Bone(const Bone&);
		Bone& operator = (const Bone&);
		~Bone();

		void SetName(const System::string& name);
		void SetMatrix(const Math::mat4& matrix);
		void SetParent(Bone* parent);
		void SetLocalMatrix(const Math::mat4& matrix) { m_local_matrix = matrix; m_need_update_global_matrix = true; }
		void SetBoneMatrix(const Math::mat4& matrix) { m_bone_matrix = matrix; m_need_update_global_matrix = true;}
		const Math::mat4& GetBoneMatrix() const { return m_bone_matrix; }
		const Math::mat4& GetLocalMatrix() const { return m_local_matrix; }

		//void SetIndexInArmature(int index);		
		///void SetArmature(Armature* armature);
		///Armature* GetArmature();

		const BoneName& GetName() const;
		void SetParentName(const BoneName& name) { m_parent_name = name; }
		const BoneName& GetParentName() const { return m_parent_name; }
		const Bone* GetParent() const;
		const Math::mat4 GetWorldMatrix() const;		
		int GetIndex() const;
		void SetIndex(int index);

		void SetLength(float v) { m_length = v; }
		float GetLength() const { return m_length; }

		void AddChild(Bone* bone);

		std::vector<Bone*>& GetChildren() { return m_children; }
		const std::vector<Bone*>& GetChildren() const { return m_children; }
		Bone* Find(const System::string& name);

		const Math::mat4& GetAnimatedGlobalMatrix() const;
		const Math::mat4& GetAnimatedGlobalMatrix2() const;
		void UpdatePose(Virtual::AnimationMixer* Mixer, float frame, bool deep = false);

		/* Drops all precalculated staff */
		void ResetCache();

		bool Save(std::ostream& stream) const;
		bool Load(std::istream& stream);

	private:

		void Clear();

		int m_index;
		Bone*				m_parent;
		std::vector<Bone*>	m_children;
		BoneName			m_name;
		BoneName			m_parent_name;
		Math::mat4			m_global_matrix;				
		Math::mat4			m_bone_matrix;		
		Math::mat4			m_local_matrix;	//	matrix relative to armature
		//int					m_index_in_armature;
		Math::mat4			m_last_local_matrix_update;
		mutable Math::mat4	m_last_global_matrix_update;
		float				m_last_get_global_matrix;
		float				m_length;
		mutable bool		m_need_update_global_matrix;

		mutable Math::mat4	m_last_global_matrix_update2;
		mutable bool		m_need_update_global_matrix2;
		//Armature*			m_armature;
	};
}

#endif