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
	class PUNK_ENGINE_API Bone
	{
	public:

		Bone();
		Bone(const Bone&);
		Bone& operator = (const Bone&);
		~Bone();

		void SetName(const System::string& name);
		void SetMatrix(const Math::mat4& matrix);
		void SetParent(Bone* parent);
        void SetLocalMatrix(const Math::mat4& matrix);
        void SetBoneMatrix(const Math::mat4& matrix);
        const Math::mat4& GetBoneMatrix() const;
        const Math::mat4& GetLocalMatrix() const;

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
        float				m_length;		

        friend void SaveBone(System::Buffer*, const Bone& bone);
        friend void LoadBone(System::Buffer*, Bone& bone);
	};

    PUNK_ENGINE_API void SaveBone(System::Buffer*, const Bone& bone);
    PUNK_ENGINE_API void LoadBone(System::Buffer*, Bone& bone);
}

#endif
