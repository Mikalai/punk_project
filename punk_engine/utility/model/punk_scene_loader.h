#ifndef _H_PUNK_SCENE_LOADER
#define _H_PUNK_SCENE_LOADER

#include "../config.h"
#include "../error.h"
#include <map>
#include <vector>
#include "../../system/string.h"
#include "../../math/math.h"
#include "bone_frame.h"
#include "material.h"
#include "bone.h"
#include "skeleton.h"

namespace Utility
{
	
	class StaticMesh;
	class SkinnedMesh;
	class SkinAnimation;

	typedef int FrameID;
	typedef float Weight;
	typedef int VertexIndex;
	typedef int FaceIndex;
	typedef int BoneID;	
	typedef std::map<FrameID, BoneFrame> FramesCollection;
	typedef std::map<System::string, Weight> BoneWeights;
	typedef std::vector<Math::vec3> Vertices;
	typedef std::vector<Math::vec3> Normals;
	typedef std::vector<std::vector<Math::vec2> > TextureFaces;
	typedef std::vector<Math::ivec3> Faces;
	typedef std::map<VertexIndex, BoneWeights > VertexBoneWeights;
	typedef std::map<BoneName, FramesCollection> SkeletonAnimation;
	typedef Math::BoundingBox BoundingBox;

	typedef std::map<System::string, Material> Materials;

	typedef std::map<System::string, Math::Matrix<BoneFrame> > CookedAnimation;

	struct Action
	{
		FrameID m_start_frame;
		FrameID m_end_frame;
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
			L"*gimbal_transform",
			L"*bone_matrix"};

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
				WORD_GIMBAL_TRANSFORM,
				WORD_BONE_MATRIX
			};


	public:
		System::string m_material;
		Math::BoundingBox m_bbox;
		System::string m_name;
		Vertices m_vertices;
		Normals m_normals;
		Faces m_faces;
		VertexBoneWeights m_bone_weights;
		Skeleton m_skeleton;
		SkeletonID m_skeleton_id;
		Animation m_skeleton_animation;
		TextureFaces m_tex_coords;
		Materials m_materials;
		CookedAnimation m_cooked_animation;
		std::map<System::string, Math::Matrix<float> > m_frame_value;

		std::map<BoneName, std::map<Frame, BoneFrame> >::iterator m_maximum_frames;
		std::map<BoneName, int> m_bone_index;
	
		Math::mat4 m_local_matrix;
		Math::mat4 m_world_matrix;

	public:

		const Math::quat Model::GetBoneLocalOrientation(int bone_name, const System::string& action, FrameID frame) const;
		void LoadPunkModel(System::string& filename);	
		StaticMesh* CookStaticMesh() const;
		bool CookSkinnedMesh(SkinnedMesh*& mesh, Math::mat4*& bones, int& count) const;
		bool CookAnimation(const System::string& action_name, SkinAnimation*& anim);

		void BuildBoneIndex();

		/*! Calculate maximum count of frame among bong for selected action */
		void CalculateMaximumFrameCount(const System::string& action_name);
		/*! Returns ID of the bone */
		int GetBoneID(const System::string& bone_name) const;
		const System::string GetBoneName(int id) const;
		/// Return ID of the 
		int GetFrameID(const System::string& action_name, int bone_name, FrameID frame) const;

		void CookAnimationFrames(const System::string& action_name);
		BoneFrame GetGlobalFrame(int parent, System::string action, FrameID frame) const;
		void CookOneVertexWithBone(int index, float& b1, float& b2, float& b3, float& b4, float& w1, float& w2, float& w3, float& w4) const;
		void CookBonesMatrix(Math::mat4*& bones, int& count) const;
		
		/// Returns global transform matrix of the bone in primary skeletone state
		const Math::mat4 GetSourceGlobalMatrix(int bone_id) const;

		//
		//	PARSING STAFF
		//

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
		Math::mat4 ParseBoneMatrix(System::Buffer& buffer);

		void ParseMeshMaterial(System::Buffer&);
		void ParseMaterials(System::Buffer&);
		System::string ParseMaterialsName(System::Buffer&);
		void ParseMaterialsNormalMap(System::Buffer&, const System::string&);
		void ParseMaterialsDiffuseMap(System::Buffer&, const System::string&);
	};
};

#endif