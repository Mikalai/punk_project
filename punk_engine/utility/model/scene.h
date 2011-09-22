#ifndef _H_PUNK_UTILITY_MODEL
#define _H_PUNK_UTILITY_MODEL

#include "../config.h"
#include "../../math/math.h"
#include "../../system/system.h"
#include "../../images/images.h"
#include "../../system/string.h"
#include <map>
#include <vector>
#include "material.h"

namespace Utility
{
	class StaticMesh;
	class SkinnedMesh;
	class SkinAnimation;

	struct BoneFrame
	{
		Math::quat m_rotation;
		Math::vec3 m_position;		
	};

	typedef std::map<System::string, Material> MaterialCollection;

	class LIB_UTILITY RawScene
	{	
		MaterialCollection m_materials;
	public:
		void OpenFile(const System::string& filename);
		StaticMesh* CookStaticMesh(const System::string& name);
		SkinnedMesh* CookSkinnedMesh(const System::string& name);
		SkinAnimation* CookSkinAnimation(const System::string& mesh_name, unsigned anim_id);

		Material GetMaterial(const System::string& name) const;
		Material GetMaterial(unsigned index) const;

	private:		
	};
}

/*
	class StaticMesh;
	class SkinnedMesh;
	class SkinAnimation;

	struct Bone
	{
		System::string m_parent;
		Math::mat4 m_matrix_local;
		Math::mat4 m_matrix_global;
		Math::quat m_gimbal_transform;
	};

	struct Material
	{
		System::string diffuse_map;
		System::string normal_map;
	};

	typedef int Frame;
	typedef float Weight;
	typedef int VertexIndex;
	typedef int FaceIndex;
	typedef System::string BoneName;
	typedef std::vector<Math::vec3> Vertices;
	typedef std::vector<Math::vec3> Normals;
	typedef std::vector<std::vector<Math::vec2> > TextureFaces;
	typedef std::vector<Math::ivec3> Faces;
	typedef std::map<VertexIndex, std::map<System::string, Weight> > BoneWeights;
	typedef std::map<BoneName, Bone> Skeleton;
	typedef std::map<BoneName, std::map<Frame, BoneFrame> > SkeletonAnimation;
	typedef Math::BoundingBox BoundingBox;

	typedef std::map<System::string, Material> Materials;

	typedef std::map<System::string, Math::Matrix<BoneFrame> > CookedAnimation;

	struct Action
	{
		Frame m_start_frame;
		Frame m_end_frame;
		int m_key_count;
		SkeletonAnimation m_pose;
	};

//	struct 
	typedef std::map<System::string, Action> Animation;

			static const wchar_t* Keyword[] = {
			L"{",
			L"}",
			L"*object",
			L"*bounding_box",
			L"*location",
			L"*world_matrix",
			L"*local_matrix",
			L"*mesh",
			L"*vertex_position",
			L"*normals",
			L"*faces",
			L"*vertex_positions_id",
			L"*bones_weight",
			L"*bones",
			L"*bone",
			L"*name",
			L"*skeleton_animation",
			L"*pos_x",
			L"*pos_y",
			L"*pos_z",
			L"*rot_w",
			L"*rot_x",
			L"*rot_y",
			L"*rot_z",
			L"*parent",
			L"*tex_coord",
			L"*material",
			L"*normal_map",
			L"*diffuse_map",
			L"*materials",
			L"*gimbal_transform"};

	class LIB_UTILITY Model
	{
	public:


			enum KeywordCode
			{
				WORD_OPEN_BRACKET,
				WORD_CLOSE_BRACKET,
				WORD_OBJECT,
				WORD_BOUNDING_BOX,
				WORD_LOCATION,
				WORD_WORLD_MATRIX,
				WORD_LOCAL_MATRIX,
				WORD_MESH,
				WORD_VERTEX_POSITION,
				WORD_NORMALS,
				WORD_FACES,
				WORD_VERTEX_POSITIONS_ID,
				WORD_BONES_WEIGHT,
				WORD_BONES,
				WORD_BONE,
				WORD_NAME,
				WORD_SKELETON_ANIMATION,
				WORD_POS_X,
				WORD_POS_Y,
				WORD_POS_Z,
				WORD_ROT_W,
				WORD_ROT_X,
				WORD_ROT_Y,
				WORD_ROT_Z,
				WORD_PARENT,
				WORD_TEXTURE_COORD,
				WORD_MATERIAL,
				WORD_NORMAL_MAP,
				WORD_DIFFUSE_MAP,
				WORD_MATERIALS,
				WORD_GIMBAL_TRANSFORM
			};


	public:
		System::string m_material;
		Math::BoundingBox m_bbox;
		System::string m_name;
		Vertices m_vertices;
		Normals m_normals;
		Faces m_faces;
		BoneWeights m_bone_weights;
		Skeleton m_skeleton;
		Animation m_skeleton_animation;
		TextureFaces m_tex_coords;
		Materials m_materials;
		CookedAnimation m_cooked_animation;
		std::map<System::string, Math::Matrix<float> > m_frame_value;

		std::map<BoneName, std::map<Frame, BoneFrame> >::iterator m_maximum_frames;
		std::map<BoneName, int> m_bone_index;

		Assimp::Importer importer;
	public:

		void OpenAnyFile(const System::string& filename);

		const Math::quat Model::GetBoneLocalOrientation(const System::string& bone_name, const System::string& action, Frame frame) const;
		void LoadPunkModel(System::string& filename);	
		StaticMesh* CookStaticMesh() const;
		bool CookSkinnedMesh(SkinnedMesh*& mesh, Math::mat4*& bones, int& count) const;
		bool CookAnimation(const System::string& action_name, SkinAnimation*& anim);

		void BuildBoneIndex();

		/*! Calculate maximum count of frame among bong for selected action */
//		void CalculateMaximumFrameCount(const System::string& action_name);
		/*! Returns ID of the bone */
//		int GetBoneID(const System::string& bone_name) const;
		/// Return ID of the 
//		int GetFrameID(const System::string& action_name, const System::string& bone_name, Frame frame) const;
/*
		void CookAnimationFrames();
		BoneFrame GetGlobalFrame(System::string parent, System::string action, Frame frame) const;
		void CookOneVertexWithBone(int index, float& b1, float& b2, float& b3, float& b4, float& w1, float& w2, float& w3, float& w4) const;
		void CookBonesMatrix(Math::mat4*& bones, int& count) const;
		
		/// Returns global transform matrix of the bone in primary skeletone state
		const Math::mat4 GetSourceGlobalMatrix(const System::string& bone) const;
		const Math::mat4 GetSourceGlobalMatrix(int bone_id) const;


		KeywordCode Parse(System::string& word);
		bool CheckIntegrity(System::Buffer& buffer);
		void ParseObject(System::Buffer& buffer);
		void ParseMesh(System::Buffer& buffer);
		void ParseObjectName(System::Buffer& buffer);
		void ParseObjectBoundingBox(System::Buffer& buffer);
		void ParseObjectLocation(System::Buffer& buffer);
		void ParseObjectWorldMatrix(System::Buffer& buffer);
		void ParseObjectLocalMatrix(System::Buffer& buffer);
		void ParseObjectMesh(System::Buffer& buffer);
		void ParseBonesWeights(System::Buffer& buffer);
		void ParseBones(System::Buffer& buffer);
		void ParseBone(System::Buffer& buffer);
		void ParseVertexPosition(System::Buffer& buffer);
		void ParseNormals(System::Buffer& buffer);
		void ParseFaces(System::Buffer& buffer);
		void ParseFaceVertexID(System::Buffer& buffer);
		System::string ParseBoneName(System::Buffer& buffer);
		Math::mat4 ParseBoneLocalMatrix(System::Buffer& buffer);
		void ParseSkeletoneAnimation(System::Buffer& buffer);
		void ParseBoneAnimation(System::Buffer& buffer, Action& action);
		void ParseBoneAnimationValues(System::Buffer&, Action& action, System::string& name, KeywordCode code);
		void ParseTextureCoords(System::Buffer& buffer);
		Math::quat ParseGimbalTransform(System::Buffer& buffer);

		void ParseMeshMaterial(System::Buffer&);
		void ParseMaterials(System::Buffer&);
		System::string ParseMaterialsName(System::Buffer&);
		void ParseMaterialsNormalMap(System::Buffer&, const System::string&);
		void ParseMaterialsDiffuseMap(System::Buffer&, const System::string&);
	};
}*/

#endif