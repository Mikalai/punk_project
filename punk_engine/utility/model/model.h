#ifndef _H_PUNK_UTILITY_MODEL
#define _H_PUNK_UTILITY_MODEL

#include "../config.h"
#include "../../math/math.h"
#include "../../system/system.h"
#include "../../images/images.h"
#include "../../system/string.h"
#include "static_mesh.h"
#include <map>
#include <vector>

namespace Utility
{

	struct Bone
	{
		System::string m_parent;
		Math::mat4 m_matrix;
	};

	struct BoneFrame
	{
		Math::vec3 m_position;
		Math::quat m_rotation;
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
	typedef std::vector<Math::vec3> Vertices;
	typedef std::vector<Math::vec3> Normals;
	typedef std::vector<std::vector<Math::vec2> > TextureFaces;
	typedef std::vector<Math::ivec3> Faces;
	typedef std::map<VertexIndex, std::map<System::string, Weight> > BoneWeights;
	typedef std::map<System::string, Bone> Skeleton;
	typedef std::map<System::string, std::map<Frame, BoneFrame> > SkeletonAnimation;
	typedef Math::BoundingBox BoundingBox;
	typedef std::map<System::string, Material> Materials;

	struct Action
	{
		Frame m_start_frame;
		Frame m_end_frame;
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
			L"*materials"};

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
				WORD_MATERIALS
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
	public:
		void LoadPunkModel(System::string& filename);	
		StaticMesh* CookStaticMesh();

	private:
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

		void ParseMeshMaterial(System::Buffer&);
		void ParseMaterials(System::Buffer&);
		System::string ParseMaterialsName(System::Buffer&);
		void ParseMaterialsNormalMap(System::Buffer&, const System::string&);
		void ParseMaterialsDiffuseMap(System::Buffer&, const System::string&);
	};
}

#endif