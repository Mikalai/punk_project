#include "base_parser.h"
#include "../../math/vec2.h"
#include "../../math/vec3.h"
#include "../../math/vec4.h"
#include "../../math/mat2.h"
#include "../../math/mat3.h"
#include "../../math/mat4.h"
#include "../../math/bounding_box.h"
#include "../../math/convex_shape_mesh.h"
#include "../../string/string.h"
#include "../../system/buffer.h"
#include "../../system/logger.h"
#include "../../system/binary_file.h"
#include "../../virtual/module.h"

#include "../../scene/scene_graph.h"

#define CHECK_START(buffer)\
	if (!CheckIntegrity(buffer))\
		{\
		out_error() << L"Integrity check failed" << std::endl;\
		return false;	\
		}

#define CHECK_END(buffer)\
	if (Parse(buffer.ReadWord()) != WORD_CLOSE_BRACKET)\
		{\
		out_error() << L"Integrity check failed" << std::endl;\
		return false;\
		}

namespace Utility
{
	extern System::Proxy<System::Object> LoadWorld(const System::string& path);
	extern System::Proxy<System::Object> ParseAnything(System::Buffer& buffer);
	extern bool ParseTextures(System::Buffer& buffer, std::map<System::string, std::vector<Math::Vector4<Math::vec2>>>& value);		
	extern bool ParseBonesWeights(System::Buffer& buffer, std::map<int, std::map<System::string, float>>& value);
	extern bool ParseWorld(System::Buffer& buffer, System::Proxy<Scene::SceneGraph> scene);
	extern bool ParseLocationIndoor(System::Buffer& buffer, System::Proxy<Scene::LocationIndoorNode> location);
	extern bool ParsePortalNode(System::Buffer& buffer, System::Proxy<Scene::PortalNode> node);
	extern bool ParseTransformNode(System::Buffer& buffer, System::Proxy<Scene::TransformNode> transform);
	extern bool ParseMaterialNode(System::Buffer& buffer, System::Proxy<Scene::MaterialNode> material);
	extern bool ParsePointLightNode(System::Buffer& buffer, System::Proxy<Scene::PointLightNode> value);
	extern bool ParseMaterials(System::Buffer& buffer, System::Proxy<Scene::SceneGraph> scene);
	extern bool ParseMaterial(System::Buffer& buffer, System::Proxy<Virtual::Material> mat);
	extern bool ParseStaticMeshes(System::Buffer& buffer);
	extern bool ParseStaticMesh(System::Buffer& buffer, System::Proxy<Virtual::StaticGeometry> geometry);
	extern bool ParseStaticMeshNode(System::Buffer& buffer, System::Proxy<Scene::StaticMeshNode> static_node);
	extern bool ParseSkinMeshes(System::Buffer& buffer);
	extern bool ParseSkinMesh(System::Buffer& buffer, System::Proxy<Virtual::SkinGeometry> geometry);
	extern bool ParseSkinMeshNode(System::Buffer& buffer, System::Proxy<Scene::SkinMeshNode> skin_node);
	extern bool ParseBone(System::Buffer& buffer, Virtual::Bone* bone);
	extern bool ParseArmature(System::Buffer& buffer, System::Proxy<Virtual::Armature> armature);
	extern bool ParseArmatures(System::Buffer& buffer);
	extern bool ParseArmatureNode(System::Buffer& buffer, System::Proxy<Scene::ArmatureNode> armature_node);
	extern bool ParseActions(System::Buffer& buffer);
	extern bool ParseAction(System::Buffer& buffer, System::Proxy<Virtual::Action> action);
	extern bool ParseAnimation(System::Buffer& buffer, System::Proxy<Virtual::Animation> animation);
	extern bool ParsePositionTrack(System::Buffer& buffer, Virtual::AnimationTrack<Math::vec3>& track);
	extern bool ParseRotationTrack(System::Buffer& buffer, Virtual::AnimationTrack<Math::quat>& track);
	extern bool ParseBoneNode(System::Buffer& buffer, System::Proxy<Scene::BoneNode> node);
	extern bool ParseMapDescription(System::Buffer& buffer, System::Proxy<Virtual::Terrain> terrain);

	/// This function convert a string representation of the file into code
	KeywordCode Parse(const System::string& word)
	{
		for (int i = 0; i < sizeof(Keyword)/sizeof(Record); i++)
		{
			if (word == Keyword[i].word)
				return Keyword[i].code;
		}	
		out_error() << System::string::Format(L"Unknown keyword %s", word.Data()) << std::endl;		
		return WORD_BAD_KEYWORD;
	}

	///	Returns false if couldn't find open bracket in the buffer
	bool CheckIntegrity(System::Buffer& buffer)
	{
		if (Parse(buffer.ReadWord()) != WORD_OPEN_BRACKET)
			return false;
		return true;
	}

	bool ParseFloat(System::Buffer& buffer, float& value)
	{
		value = buffer.ReadWord().ToFloat();
		return true;
	}

	bool ParseInteger(System::Buffer& buffer, int& value)
	{
		value = buffer.ReadWord().ToInt32();
		return true;
	}

	bool ParseVector2f(System::Buffer& buffer, Math::vec2& value)
	{
		value[0] = buffer.ReadWord().ToFloat();
		value[1] = buffer.ReadWord().ToFloat();
		return true;
	}

	bool ParseVector3f(System::Buffer& buffer, Math::vec3& value)
	{
		value[0] = buffer.ReadWord().ToFloat();
		value[1] = buffer.ReadWord().ToFloat();
		value[2] = buffer.ReadWord().ToFloat();
		return true;
	}

	bool ParseVector4f(System::Buffer& buffer, Math::vec4& value)
	{
		value[0] = buffer.ReadWord().ToFloat();
		value[1] = buffer.ReadWord().ToFloat();
		value[2] = buffer.ReadWord().ToFloat();
		value[3] = buffer.ReadWord().ToFloat();
		return true;
	}

	bool ParseVector2i(System::Buffer& buffer, Math::ivec2& value)
	{
		value[0] = buffer.ReadWord().ToInt32();
		value[1] = buffer.ReadWord().ToInt32();
		return true;
	}

	bool ParseVector3i(System::Buffer& buffer, Math::ivec3& value)
	{
		value[0] = buffer.ReadWord().ToInt32();
		value[1] = buffer.ReadWord().ToInt32();
		value[2] = buffer.ReadWord().ToInt32();
		return true;
	}

	bool ParseVector4i(System::Buffer& buffer, Math::ivec4& value)
	{
		value[0] = buffer.ReadWord().ToInt32();
		value[1] = buffer.ReadWord().ToInt32();
		value[2] = buffer.ReadWord().ToInt32();
		value[3] = buffer.ReadWord().ToInt32();
		return true;
	}

	bool ParseMatrix4x4f(System::Buffer& buffer, Math::mat4& value)
	{
		for (int i = 0; i < 16; ++i)
			value[i] = buffer.ReadWord().ToFloat();
		value = value.Transposed();
		return true;
	}

	bool ParseString(System::Buffer& buffer, System::string& value)
	{
		value = buffer.ReadWord();
		return true;
	}

	bool ParseBoundingBox(System::Buffer& buffer, Math::BoundingBox& value)
	{
		CHECK_START(buffer);
		Math::vec3 p[8];
		for (int i = 0; i < 8; ++i)
			if (!ParseVector3f(buffer, p[i]))
				return (out_error() << "Unable to parse bounding box" << std::endl, false);
		if (!value.Create(reinterpret_cast<const float*>(p), 8, sizeof(Math::vec3)))
			return (out_error() << "Unable to make bounding box from points" << std::endl, false);
		CHECK_END(buffer);
		return true;
	}

	bool ParseBlockedString(System::Buffer& buffer, System::string& value)
	{
		CHECK_START(buffer);
		if (!ParseString(buffer, value))
			return (out_error() << "Unable to parse blocked string" << std::endl, false);
		CHECK_END(buffer);
		return true;
	}

	//bool ParseSubtype(System::Buffer& buffer, ObjectTypeDesc& value)
	//{
	//	CHECK_START(buffer);
	//	System::string s;
	//	if (!ParseString(buffer, s))
	//		return (out_error() << "Unable to parse sub type" << std::endl, false);
	//	if (!value.BuildFromString(s))
	//		return (out_error() << "Unable to parse sub type" << std::endl, false);
	//	CHECK_END(buffer);
	//	return true;
	//}

	bool ParseBlockedFloat(System::Buffer& buffer, float& value)
	{
		CHECK_START(buffer);
		if (!ParseFloat(buffer, value))
			return (out_error() << "Unable to parse blocked float number" << std::endl, false);
		CHECK_END(buffer);
		return true;
	}

	bool ParseBlockedInteger(System::Buffer& buffer, int& value)
	{
		CHECK_START(buffer);
		if (!ParseInteger(buffer, value))
			return (out_error() << "Unable to parse blocked float number" << std::endl, false);
		CHECK_END(buffer);
		return true;
	}

	bool ParseBlockedVector3f(System::Buffer& buffer, Math::vec3& value)
	{
		CHECK_START(buffer);
		if (!ParseVector3f(buffer, value))
			return (out_error() << "Unable to parse blocked vec3f" << std::endl, false);
		CHECK_END(buffer);
		return true;
	}

	bool ParseBlockedVector2i(System::Buffer& buffer, Math::ivec2& value)
	{
		CHECK_START(buffer);
		if (!ParseVector2i(buffer, value))
			return (out_error() << "Unable to parse blocked vec3f" << std::endl, false);
		CHECK_END(buffer);
		return true;
	}

	bool ParseBlockedVector2f(System::Buffer& buffer, Math::vec2& value)
	{
		CHECK_START(buffer);
		if (!ParseVector2f(buffer, value))
			return (out_error() << "Unable to parse blocked vec3f" << std::endl, false);
		CHECK_END(buffer);
		return true;
	}

	bool ParseBlockedMatrix4x4f(System::Buffer& buffer, Math::mat4& value)
	{
		CHECK_START(buffer);
		if (!ParseMatrix4x4f(buffer, value))
			return (out_error() << "Unable to parse mat4f" << std::endl, false);
		CHECK_END(buffer);
		return true;
	}

	bool ParseVector3fv(System::Buffer& buffer, std::vector<Math::vec3>& value)
	{
		CHECK_START(buffer);
		while (1)
		{
			System::string word = buffer.ReadWord();

			if (word == Keyword[WORD_CLOSE_BRACKET].word)
				return true;

			float x = buffer.ReadWord().ToFloat();
			float y = buffer.ReadWord().ToFloat();
			float z = buffer.ReadWord().ToFloat();

			Math::vec3 v;
			v.Set(x,y,z);

			value.push_back(v);
		}
		return (out_error() << "Unable to parse array ov vec3f" << std::endl, false);
	}

	bool ParseVector3iv(System::Buffer& buffer, std::vector<Math::ivec3>& value)
	{
		CHECK_START(buffer);
		while (1)
		{
			System::string word = buffer.ReadWord();

			if (word == Keyword[WORD_CLOSE_BRACKET].word)
				return true;

			int x = buffer.ReadWord().ToInt32();
			int y = buffer.ReadWord().ToInt32();
			int z = buffer.ReadWord().ToInt32();

			Math::ivec3 v;
			v.Set(x,y,z);

			value.push_back(v);
		}
		return (out_error() << "Unable to parse vector of vec3i" << std::endl, false);
	}

	bool ParseVector4iv(System::Buffer& buffer, std::vector<Math::ivec4>& value)
	{
		CHECK_START(buffer);
		while (1)
		{
			System::string word = buffer.ReadWord();

			if (word == Keyword[WORD_CLOSE_BRACKET].word)
				return true;

			int x = word.ToInt32();
			int y = buffer.ReadWord().ToInt32();
			int z = buffer.ReadWord().ToInt32();
			int w = buffer.ReadWord().ToInt32();

			Math::ivec4 v;
			v.Set(x,y,z,w);

			value.push_back(v);
		}
		return (out_error() << "Unable to parse vector of vec4i" << std::endl, false);
	}

	bool ParseVector4Vector2iv(System::Buffer& buffer, std::vector<Math::Vector4<Math::vec2>>& value)
	{
		CHECK_START(buffer);
		while (1)
		{
			System::string word = buffer.ReadWord();

			if (word == Keyword[WORD_CLOSE_BRACKET].word)
				return true;

			float u1 = word.ToFloat();
			float v1 = buffer.ReadWord().ToFloat();
			float u2 = buffer.ReadWord().ToFloat();
			float v2 = buffer.ReadWord().ToFloat();
			float u3 = buffer.ReadWord().ToFloat();
			float v3 = buffer.ReadWord().ToFloat();
			float u4 = buffer.ReadWord().ToFloat();
			float v4 = buffer.ReadWord().ToFloat();

			Math::Vector4<Math::vec2> v;
			v[0].Set(u1, v1);
			v[1].Set(u2, v2);
			v[2].Set(u3, v3);
			v[3].Set(u4, v4);

			value.push_back(v);
		}
		return (out_error() << "Unable to parse vector of vec4<vec2f>" << std::endl, false);
	}

	bool ParseConvexMesh(System::Buffer& buffer, Math::ConvexShapeMesh& mesh)
	{
		CHECK_START(buffer);

		while (1)
		{
			if (buffer.IsEnd())
				return (out_error() << "Can't parse convex mesh" << std::endl, false);

			System::string s = buffer.ReadWord();
			KeywordCode index = Parse(s);
			switch (index)
			{
			case WORD_CLOSE_BRACKET:
				return true;
			case WORD_VERTEX_POSITION:
				{
					Math::ConvexShapeMesh::PointsCollection p;
					if (!ParseVector3fv(buffer, p))
						return (out_error() << "Can't parse vertex position" << std::endl, false);
					mesh.SetPoints(p);
				}
				break;
			case WORD_FACES:
				{
					Math::ConvexShapeMesh::FacesCollection f;
					if (!ParseVector3iv(buffer, f))
						return (out_error() << "Can't parse face indeces" << std::endl, false);
					mesh.SetFaces(f);
				}
				break;
			case WORD_FACE_NORMALS:
				{
					Math::ConvexShapeMesh::NormalsCollection n;
					if (!ParseVector3fv(buffer, n))
						return (out_error() << "Can't parse normals" << std::endl, false);
					mesh.SetNormals(n);
				}
				break;
			default:
				return (out_error() << "Unexpected word " << s << std::endl, false);
			}
		}
	}


	bool ParseBonesWeights(System::Buffer& buffer, std::map<int, std::map<System::string, float>>& value)
	{
		CHECK_START(buffer);

		while (1)
		{
			System::string word = buffer.ReadWord();
			if (word == Keyword[WORD_CLOSE_BRACKET].word)
				return true;
			int vertex_id = word.ToInt32();
			System::string bone_name = buffer.ReadWord();
			float weight = buffer.ReadWord().ToFloat();
			value[vertex_id][bone_name] = weight;
		}
		return (out_error() << "Unable to parse vertex bones weights" << std::endl, false);
	}

	//bool ParseLocationIndoor(System::Buffer& buffer, LocationIndoorDesc& o)
	//{
	//	CHECK_START(buffer);

	//	while (1)
	//	{
	//		if (buffer.IsEnd())
	//		{
	//			out_error() << L"Can't parse object" << std::endl;
	//			return false;
	//		}

	//		System::string word = buffer.ReadWord(); 

	//		KeywordCode index;
	//		switch(index = Parse(word))
	//		{
	//		case WORD_CLOSE_BRACKET:
	//			return true;
	//		case WORD_TYPE:
	//			{
	//				if (!ParseBlockedString(buffer, o.m_type))
	//				{
	//					out_error() << "Unable to parse object type" << std::endl;
	//					return false;
	//				}
	//				out_message() << L"Type " + o.m_type << std::endl;
	//			}
	//			break;
	//		case WORD_NAME:
	//			{
	//				if (!ParseBlockedString(buffer, o.m_name))
	//				{
	//					out_error() << "Unable to parse object name" << std::endl;
	//					return false;
	//				}
	//				out_message() << L"Parsing " + o.m_name << std::endl;
	//			}
	//			break;
	//		case WORD_PARENT:
	//			{
	//				if (!ParseBlockedString(buffer, o.m_parent))
	//				{
	//					out_error() << "Unable to parse object parent" << std::endl;
	//					return false;
	//				}
	//				out_message() << L"Parent " + o.m_type << std::endl;
	//			}
	//			break;
	//		case WORD_BOUNDING_BOX:
	//			{
	//				if (!ParseBoundingBox(buffer, o.m_bbox))
	//				{
	//					out_error() << "Unable to parse object bounding box" << std::endl;
	//					return false;
	//				}
	//			}				
	//			break;
	//		case WORD_LOCATION:
	//			{
	//				if (!ParseBlockedVector3f(buffer, o.m_location))
	//				{
	//					out_error() << "Unable to parse object location" << std::endl;
	//					return false;
	//				}
	//			}
	//			break;
	//		case WORD_WORLD_MATRIX:
	//			{
	//				if (!ParseBlockedMatrix4x4f(buffer, o.m_world))
	//				{
	//					out_error() << "Unable to parse object world matrix" << std::endl;
	//					return false;
	//				}
	//			}
	//			break;
	//		case WORD_PARENT_INVERSED_MATRIX:
	//			{
	//				if (!ParseBlockedMatrix4x4f(buffer, o.m_inv_parent))
	//				{
	//					out_error() << "Unable to parse object inversed parent matrix" << std::endl;
	//					return false;
	//				}
	//			}
	//			break;
	//		case WORD_LOCAL_MATRIX:
	//			{
	//				if (!ParseBlockedMatrix4x4f(buffer, o.m_local))
	//				{
	//					out_error() << "Unable to parse local matrix" << std::endl;
	//					return false;
	//				}
	//			}
	//			break;
	//		case WORD_MESH:
	//			{
	//				std::unique_ptr<MeshDesc> mesh(new MeshDesc);
	//				if (!ParseMesh(buffer, *mesh))
	//				{
	//					out_error() << "Unable to parse object mesh data" << std::endl;
	//					return false;
	//				}
	//				o.m_mesh_desc.reset(mesh.release());
	//			}
	//			break;
	//		case WORD_ARMATURE:
	//			{
	//				std::unique_ptr<ArmatureDesc> armature(new ArmatureDesc);
	//				if (!ParseArmature(buffer, *armature))
	//				{
	//					out_error() << "Unable to parse armature" << std::endl;
	//					return false;
	//				}
	//				o.m_armature_desc.reset(armature.release());
	//			}
	//			break;
	//		case WORD_CAMERA:
	//			{
	//				std::unique_ptr<CameraDesc> camera(new CameraDesc);
	//				if (!ParseCamera(buffer, *camera))
	//				{
	//					out_error() << "Unable to parse camera" << std::endl;
	//					return false;
	//				}
	//				o.m_camera_desc.reset(camera.release());
	//			}
	//			break;
	//		case WORD_POINT_LIGHT:
	//			{
	//				std::unique_ptr<LightDesc> light(new LightDesc);
	//				if (!ParseLight(buffer, *light))
	//				{
	//					out_error() << "Unable to parse light" << std::endl;
	//					return false;
	//				}
	//				o.m_light_desc.reset(light.release());
	//			}
	//			break;
	//		case WORD_MATERIAL_REF:
	//			{
	//				if (!ParseBlockedString(buffer, o.m_material))
	//				{
	//					out_error() << "Unable to parse object material" << std::endl;
	//					return false;
	//				}
	//			}
	//			break;
	//		case WORD_REFERENCE:
	//			{
	//				if (!ParseBlockedString(buffer, o.m_reference))
	//				{
	//					out_error() << "Unable to parse object reference" << std::endl;
	//					return false;
	//				}
	//			}
	//			break;
	//		case WORD_ACTIONS_REF:
	//			{
	//				if (!ParseActionsRef(buffer, o.m_supported_animations))
	//				{
	//					out_error() << "Unable to parse animation references" << std::endl;
	//					return false;
	//				}
	//			}
	//			break;
	//		case WORD_COLLISION_MESH:
	//			{
	//				std::unique_ptr<MeshDesc> mesh(new MeshDesc);
	//				if (!ParseMesh(buffer, *mesh))
	//					return (out_error() << "Unable to parse collision mesh" << std::endl, false);
	//				o.m_mesh_collision_desc.reset(mesh.release());
	//			}
	//			break;
	//		case WORD_OBJECT:
	//			{					
	//				std::auto_ptr<ObjectDesc> child(new ObjectDesc);
	//				if (!ParseObject(buffer, *child))
	//				{
	//					out_error() << "Unable to parse child object" << std::endl;
	//					return false;
	//				}
	//				o.m_children.push_back(child.release());
	//			}
	//			break;
	//		default:
	//			return (out_error() << System::string::Format(L"Unexpected keyword %s", Keyword[index]) << std::endl, false);
	//		}
	//	}
	//}

	/// Perform parsing object chunk
	/*bool ParseObject(System::Buffer &buffer, ObjectDesc& o)
	{
	CHECK_START(buffer);

	while (1)
	{
	if (buffer.IsEnd())
	{
	out_error() << L"Can't parse object" << std::endl;
	return false;
	}

	System::string word = buffer.ReadWord(); 

	KeywordCode index;
	switch(index = Parse(word))
	{
	case WORD_CLOSE_BRACKET:
	return true;
	case WORD_TYPE:
	{
	if (!ParseBlockedString(buffer, o.m_type))
	{
	out_error() << "Unable to parse object type" << std::endl;
	return false;
	}
	out_message() << L"Type " + o.m_type << std::endl;
	}
	break;
	case WORD_NAME:
	{
	if (!ParseBlockedString(buffer, o.m_name))
	{
	out_error() << "Unable to parse object name" << std::endl;
	return false;
	}
	out_message() << L"Parsing " + o.m_name << std::endl;
	}
	break;
	case WORD_PARENT:
	{
	if (!ParseBlockedString(buffer, o.m_parent))
	{
	out_error() << "Unable to parse object parent" << std::endl;
	return false;
	}
	out_message() << L"Parent " + o.m_type << std::endl;
	}
	break;
	case WORD_BOUNDING_BOX:
	{
	if (!ParseBoundingBox(buffer, o.m_bbox))
	{
	out_error() << "Unable to parse object bounding box" << std::endl;
	return false;
	}
	}				
	break;
	case WORD_LOCATION:
	{
	if (!ParseBlockedVector3f(buffer, o.m_location))
	{
	out_error() << "Unable to parse object location" << std::endl;
	return false;
	}
	}
	break;
	case WORD_WORLD_MATRIX:
	{
	if (!ParseBlockedMatrix4x4f(buffer, o.m_world))
	{
	out_error() << "Unable to parse object world matrix" << std::endl;
	return false;
	}
	}
	break;
	case WORD_PARENT_INVERSED_MATRIX:
	{
	if (!ParseBlockedMatrix4x4f(buffer, o.m_inv_parent))
	{
	out_error() << "Unable to parse object inversed parent matrix" << std::endl;
	return false;
	}
	}
	break;
	case WORD_LOCAL_MATRIX:
	{
	if (!ParseBlockedMatrix4x4f(buffer, o.m_local))
	{
	out_error() << "Unable to parse local matrix" << std::endl;
	return false;
	}
	}
	break;
	case WORD_MESH:
	{
	std::unique_ptr<MeshDesc> mesh(new MeshDesc);
	if (!ParseMesh(buffer, *mesh))
	{
	out_error() << "Unable to parse object mesh data" << std::endl;
	return false;
	}
	o.m_mesh_desc.reset(mesh.release());
	}
	break;
	case WORD_ARMATURE:
	{
	std::unique_ptr<ArmatureDesc> armature(new ArmatureDesc);
	if (!ParseArmature(buffer, *armature))
	{
	out_error() << "Unable to parse armature" << std::endl;
	return false;
	}
	o.m_armature_desc.reset(armature.release());
	}
	break;
	case WORD_CAMERA:
	{
	std::unique_ptr<CameraDesc> camera(new CameraDesc);
	if (!ParseCamera(buffer, *camera))
	{
	out_error() << "Unable to parse camera" << std::endl;
	return false;
	}
	o.m_camera_desc.reset(camera.release());
	}
	break;
	case WORD_POINT_LIGHT:
	{
	std::unique_ptr<LightDesc> light(new LightDesc);
	if (!ParseLight(buffer, *light))
	{
	out_error() << "Unable to parse light" << std::endl;
	return false;
	}
	o.m_light_desc.reset(light.release());
	}
	break;
	case WORD_MATERIAL_REF:
	{
	if (!ParseBlockedString(buffer, o.m_material))
	{
	out_error() << "Unable to parse object material" << std::endl;
	return false;
	}
	}
	break;
	case WORD_REFERENCE:
	{
	if (!ParseBlockedString(buffer, o.m_reference))
	{
	out_error() << "Unable to parse object reference" << std::endl;
	return false;
	}
	}
	break;
	case WORD_ACTIONS_REF:
	{
	if (!ParseActionsRef(buffer, o.m_supported_animations))
	{
	out_error() << "Unable to parse animation references" << std::endl;
	return false;
	}
	}
	break;
	case WORD_COLLISION_MESH:
	{
	std::unique_ptr<MeshDesc> mesh(new MeshDesc);
	if (!ParseMesh(buffer, *mesh))
	return (out_error() << "Unable to parse collision mesh" << std::endl, false);
	o.m_mesh_collision_desc.reset(mesh.release());
	}
	break;
	case WORD_OBJECT:
	{					
	std::auto_ptr<ObjectDesc> child(new ObjectDesc);
	if (!ParseObject(buffer, *child))
	{
	out_error() << "Unable to parse child object" << std::endl;
	return false;
	}
	o.m_children.push_back(child.release());
	}
	break;
	default:
	return (out_error() << System::string::Format(L"Unexpected keyword %s", Keyword[index]) << std::endl, false);
	}
	}
	}*/

	bool ParsePositionTrack(System::Buffer& buffer, Virtual::AnimationTrack<Math::vec3>& value)
	{
		CHECK_START(buffer);
		while (1)
		{
			System::string word = buffer.ReadWord();

			if (word == Keyword[WORD_CLOSE_BRACKET].word)
				return true;

			int frame = word.ToInt32();
			float x = buffer.ReadWord().ToFloat();
			float y = buffer.ReadWord().ToFloat();
			float z = buffer.ReadWord().ToFloat();

			Math::vec3 v;
			v.Set(x,y,z);

			value.AddKey(frame, v);
		}
		return (out_error() << "Unable to parse position track" << std::endl, false);
	}

	bool ParseRotationTrack(System::Buffer& buffer, Virtual::AnimationTrack<Math::quat>& value)
	{
		CHECK_START(buffer);
		while (1)
		{
			System::string word = buffer.ReadWord();

			if (word == Keyword[WORD_CLOSE_BRACKET].word)
				return true;

			int frame = word.ToInt32();
			float w = buffer.ReadWord().ToFloat();
			float x = buffer.ReadWord().ToFloat();
			float y = buffer.ReadWord().ToFloat();
			float z = buffer.ReadWord().ToFloat();

			Math::Quaternion<float> v;
			v.Set(w,x,y,z);

			value.AddKey(frame, v);
		}
		return (out_error() << "Unable to parse rotation track" << std::endl, false);
	}

	bool ParseAnimation(System::Buffer& buffer, System::Proxy<Virtual::Animation> animation)
	{
		CHECK_START(buffer);

		System::string name;

		while (1)
		{
			if (buffer.IsEnd())
			{
				out_error() << L"Can't parse object" << std::endl;
				return false;
			}

			const System::string word = buffer.ReadWord();
			KeywordCode index = Parse(word);
			switch(index)
			{
			case WORD_CLOSE_BRACKET:
				return true;
			case WORD_NAME:
				{
					System::string name;
					if (!ParseBlockedString(buffer, name))
						return (out_error() << "Unable to parse animation name" << std::endl, false);
					animation->SetName(name);
					animation->SetStorageName(name);
				}
				break;
			case WORD_POSITION_TRACK:
				{
					Virtual::AnimationTrack<Math::vec3> track;
					if (!ParsePositionTrack(buffer, track))
						return (out_error() << "Unable to parse animation position track" << std::endl, false);
					animation->SetPositionTrack(track);
				}
				break;
			case WORD_ROTATION_TRACK:
				{
					Virtual::AnimationTrack<Math::quat> track;
					if (!ParseRotationTrack(buffer, track))
						return (out_error() << "Unable to parse animation rotation track" << std::endl, false);
					animation->SetRotationTrack(track);
				}
				break;
			default:
				return (out_error() << L"Unexpected keyword " << word << std::endl, false);
			}
		}
		return false;
	}

	bool ParseAction(System::Buffer& buffer, System::Proxy<Virtual::Action> action)
	{
		CHECK_START(buffer);

		System::string name;

		while (1)
		{
			if (buffer.IsEnd())
			{
				out_error() << L"Can't parse object" << std::endl;
				return false;
			}

			const System::string word = buffer.ReadWord();
			KeywordCode index;				
			switch(index = Parse(word))
			{
			case WORD_CLOSE_BRACKET:
				return true;
			case WORD_NAME:
				{
					System::string value;
					if (!ParseBlockedString(buffer, value))
						return (out_error() << "Unable to parse material name" << std::endl, false);
					action->SetName(value);
					action->SetStorageName(value);
				}
				break;
			case WORD_TIMING:
				{
					CHECK_START(buffer);
					action->SetStartFrame(buffer.ReadWord().ToInt32());
					action->SetEndFrame(buffer.ReadWord().ToInt32());
					if (Parse(buffer.ReadWord()) != WORD_CLOSE_BRACKET)
						return (out_error() << L"Can't parse action timing" << std::endl, false);		
				}
				break;
			case WORD_BONE_ANIMATION:
				{
					System::Proxy<Virtual::Animation> animation(new Virtual::Animation);
					animation->SetAnimationType(Virtual::ANIMATION_BONE);
					if (!ParseAnimation(buffer, animation))
						return (out_error() << "Unable to parse bone animation" << std::endl, false);
					action->Add(animation);
				}
				break;
			case WORD_OBJECT_ANIMATION:
				{
					System::Proxy<Virtual::Animation> animation(new Virtual::Animation);
					animation->SetAnimationType(Virtual::ANIMATION_OBJECT);
					if (!ParseAnimation(buffer, animation))
						return (out_error() << "Unable to parse bone animation" << std::endl, false);
					action->Add(animation);
				}
				break;
			default:
				return (out_error() << L"Unexpected keyword " << word << std::endl, false);
			}
		}
	}

	bool ParseActions(System::Buffer& buffer)
	{
		CHECK_START(buffer);

		while (1)
		{
			if (buffer.IsEnd())
			{
				out_error() << L"Can't parse object" << std::endl;
				return false;
			}

			System::string word = buffer.ReadWord();
			KeywordCode index;
			switch(index = Parse(word))
			{
			case WORD_CLOSE_BRACKET:
				return true;
			case WORD_ACTION:
				{	
					System::Proxy<Virtual::Action> action(new Virtual::Action);
					if (!ParseAction(buffer, action))
					{
						out_error() << "Unable to parse action" << std::endl;
						return false;
					}
					Virtual::ActionManager::Instance()->Manage(action->GetName(), action);
				}
				break;
			default:
				return (out_error() << L"Unexpected keyword " << word << std::endl, false);
			}
		}
		return false;
	}

	bool ParseStaticMeshes(System::Buffer& buffer)
	{
		CHECK_START(buffer);

		while (1)
		{
			if (buffer.IsEnd())
			{
				out_error() << L"Can't parse object" << std::endl;
				return false;
			}

			System::string word = buffer.ReadWord();
			KeywordCode index;
			switch(index = Parse(word))
			{
			case WORD_CLOSE_BRACKET:
				return true;
			case WORD_STATIC_MESH:
				{	
					System::Proxy<Virtual::StaticGeometry> mesh(new Virtual::StaticGeometry);
					if (!ParseStaticMesh(buffer, mesh))
					{
						out_error() << "Unable to parse static mesh" << std::endl;
						return false;
					}
					Virtual::StaticGeometry::add(mesh->GetStorageName(), mesh);
				}
				break;
			default:
				return (out_error() << L"Unexpected keyword " << word << std::endl, false);
			}
		}
		return false;
	}

	bool ParseBone(System::Buffer& buffer, Virtual::Bone* bone)
	{
		CHECK_START(buffer);
		System::string name, parent;
		while (1)
		{
			const System::string word = buffer.ReadWord();
			KeywordCode code = Parse(word);
			switch(code)
			{
			case WORD_CLOSE_BRACKET:
				return true;
			case WORD_NAME:
				{
					System::string name;
					if (!ParseBlockedString(buffer, name))
						return (out_error() << "Unable to parse bone name" << std::endl, false);
					bone->SetName(name);
				}
				break;
			case WORD_PARENT:
				{
					System::string name;
					if (!ParseBlockedString(buffer, name))
						return (out_error() << "Unable to parse bone parent name" << std::endl, false);
					bone->SetParentName(name);
				}
				break;
			case WORD_LOCAL_MATRIX:
				{
					Math::mat4 m;
					if (!ParseBlockedMatrix4x4f(buffer, m))
						return (out_error() << "Unable to parse bone local matrix" << std::endl, false);
					bone->SetLocalMatrix(m);
				}
				break;
			case WORD_BONE_MATRIX:
				{
					Math::mat4 m;
					if (!ParseBlockedMatrix4x4f(buffer, m))
						return (out_error() << "Unable to parse bone local matrix" << std::endl, false);
					//bone->SetBoneMatrix(m);
				}
				break;
			case WORD_LENGTH:
				{
					float l;
					if (!ParseBlockedFloat(buffer, l))
						return (out_error() << "Unable to parse bone length" << std::endl, false);
					bone->SetLength(l);
				}
				break;
			default:
				return (out_error() << L"Unexpected keyword " << word << std::endl, false);
			}
		}
		return false;
	}

	/// Parse single armature
	bool ParseArmature(System::Buffer& buffer, System::Proxy<Virtual::Armature> armature)
	{
		CHECK_START(buffer);
		while (1)
		{
			if (buffer.IsEnd())
			{
				out_error() << L"Can't parse object" << std::endl;
				return false;
			}
			
			System::string word = buffer.ReadWord();
			KeywordCode index;
			switch(index = Parse(word))
			{
			case WORD_CLOSE_BRACKET:
				armature->UpdateHierarchy();
				return true;
			case WORD_NAME:
				{
					System::string name;
					if (!ParseBlockedString(buffer, name))
						return (out_error() << "Unable to parse armature name" << std::endl, false);
					armature->SetName(name);
					armature->SetStorageName(name);
				}
				break;
			case WORD_BONE:
				{
					std::unique_ptr<Virtual::Bone> bone(new Virtual::Bone);
					if (!ParseBone(buffer, bone.get()))
						return (out_error() << "Unable to parse armature bone" << std::endl, false);
					Virtual::Bone* parent = armature->GetBoneByName(bone->GetParentName());
					if (parent)
						parent->AddChild(bone.release());
					else
						armature->AddRootBone(bone.release());
				}
				break;
			default:
				return (out_error() << L"Unknown keyword: " << word << std::endl, false);
			}
		}
		return false;
	}

	bool ParseArmatures(System::Buffer& buffer)
	{
		CHECK_START(buffer);
		System::string name;
		while (1)
		{
			System::string word = buffer.ReadWord();
			switch(KeywordCode code = Parse(word))
			{
			case WORD_CLOSE_BRACKET:
				return true;
			case WORD_ARMATURE:
				{
					System::Proxy<Virtual::Armature> armature(new Virtual::Armature);					
					if (!ParseArmature(buffer, armature))
						return (out_error() << "Unable to parse armature" << std::endl, false);
					Virtual::Armature::add(armature->GetStorageName(), armature);
				}
				break;
			default:
				return (out_error() << L"Unexpected keyword " << word << std::endl, false);
			}
		}
		return false;
	}

	/*bool ParseCamera(System::Buffer& buffer, CameraDesc& value)
	{
		CHECK_START(buffer);
		while (!buffer.IsEnd())
		{
			System::string word = buffer.ReadWord();
			switch(Parse(word))
			{
			case WORD_CLOSE_BRACKET:
				return true;
			case WORD_NAME:
				if (!ParseBlockedString(buffer, value.m_name))
					return (out_error() << "Unable to parse camera name" << std::endl, false);
				break;
			case WORD_TYPE:
				if (!ParseBlockedString(buffer, value.m_type))
					return (out_error() << "Unable to parse camera type" << std::endl, false);
				break;
			case WORD_FOV:
				if (!ParseBlockedFloat(buffer, value.m_fov))
					return (out_error() << "Unable to parse camera field of view" << std::endl, false);					
				break;
			case WORD_NEAR_PLANE:
				if (!ParseBlockedFloat(buffer, value.m_near))
					return (out_error() << "Unable to parse camera near plane" << std::endl, false);
				break;
			case WORD_FAR_PLANE:
				if (!ParseBlockedFloat(buffer, value.m_far))
					return (out_error() << "Unable to parse camera far plane" << std::endl, false);
				break;
			case WORD_FOCUS:
				if (!ParseBlockedFloat(buffer, value.m_focus))
					return (out_error() << "Unable to parse camera focus" << std::endl, false);
				break;
			case WORD_ORTHO_SCALE:
				if (!ParseBlockedFloat(buffer, value.m_scale))
					return (out_error() << "Unable to parse camera ortho scale" << std::endl, false);
				break;
			default:
				return (out_error() << System::string::Format(L"Unexpected keyword: %s",  word.Data()) << std::endl, false);
			}
		}
		return true;
	}*/

	bool ParseTextures(System::Buffer& buffer, std::map<System::string, std::vector<Math::Vector4<Math::vec2>>>& value)
	{
		CHECK_START(buffer);

		System::string name;

		while (1)
		{
			if (buffer.IsEnd())
				return (out_error() << L"Can't parse object" << std::endl, false);

			System::string s = buffer.ReadWord();			

			switch(KeywordCode index = Parse(s))
			{
			case WORD_CLOSE_BRACKET:
				return true;
			case WORD_NAME:
				{		
					if (!ParseBlockedString(buffer, name))
						return (out_error() << "Unable to parse textures name" << std::endl, false);					
				}
				break;
			case WORD_TEXTURE_COORD:
				{
					if (!ParseVector4Vector2iv(buffer, value[name]))
						return (out_error() << "Unable to parse textures coords" << std::endl, false);
				}
				break;
			default:
				return (out_error() << System::string::Format(L"Unexpected keyword %s", Keyword[index]) << std::endl, false);
			}
		}
		return true;
	}

	/*bool ParseStaticMeshes(System::Buffer& buffer)
	{
		CHECK_START(buffer);
		System::string name;
		while (1)
		{
			System::string word = buffer.ReadWord();
			switch(KeywordCode code = Parse(word))
			{
			case WORD_CLOSE_BRACKET:
				return true;
			case WORD_STATIC_MESH:
				{
					System::Proxy<Virtual::StaticGeometry> mesh(new Virtual::StaticGeometry);
					if (!ParseStaticMesh(buffer, mesh))
						return (out_error() << "Unable to parse static mesh" << std::endl, false);
					Virtual::StaticGeometryManager::Instance()->Manage(mesh->GetStorageName(), mesh);
				}
				break;
			default:
				return (out_error() << L"Unexpected keyword " << word << std::endl, false);
			}
		}
		return false;
	}*/

	bool ParseStaticMesh(System::Buffer& buffer, System::Proxy<Virtual::StaticGeometry> geometry)
	{
		CHECK_START(buffer);
		while (1)
		{
			if (buffer.IsEnd())
				return (out_error() << L"Can't parse object" << std::endl, false);
			System::string word = buffer.ReadWord();

			switch(int index = Parse(word))
			{
			case WORD_CLOSE_BRACKET:				
				return true;
			case WORD_NAME:
				{
					System::string name;
					if (!ParseBlockedString(buffer, name))
						return (out_error() << "Can't parse mesh name" << std::endl, false);
					geometry->SetName(name);
					geometry->SetStorageName(name);
				}
				break;
			case WORD_VERTEX_POSITION:
				{
					Virtual::StaticGeometry::Vertices v;
					if (!ParseVector3fv(buffer, v))
						return (out_error() << "Unable to parse vertex positions" << std::endl, false);
					geometry->SetVertices(v);
				}
				break;					
			case WORD_NORMALS:
				{
					Virtual::StaticGeometry::Normals n;
					if (!ParseVector3fv(buffer, n))
						return (out_error() << "Unable to parse vertex normals" << std::endl, false);
					geometry->SetNormals(n);
				}
				break;
			case WORD_FACES:
				{
					Virtual::StaticGeometry::Faces f;
					if (!ParseVector3iv(buffer, f))
						return (out_error() << "Unable to parse mesh faces" << std::endl, false);
					geometry->SetFaces(f);
				}
				break;
			case WORD_TEXTURE:
				{										
					Virtual::StaticGeometry::TextureMeshes t;
					if (!ParseTextures(buffer, t))
						return (out_error() << "Unable to parse mesh texture coords" << std::endl, false);
					geometry->SetTextureMeshes(t);
				}
				break;
			default:
				return (out_error() << L"Unexpected keyword " << word << std::endl, false);
			}
		}
	}

	bool ParseSkinMesh(System::Buffer& buffer, System::Proxy<Virtual::SkinGeometry> geometry)
	{
		CHECK_START(buffer);
		while (1)
		{
			if (buffer.IsEnd())
				return (out_error() << L"Can't parse object" << std::endl, false);
			System::string word = buffer.ReadWord();

			switch(int index = Parse(word))
			{
			case WORD_CLOSE_BRACKET:				
				return true;
			case WORD_NAME:
				{
					System::string name;
					if (!ParseBlockedString(buffer, name))
						return (out_error() << "Can't parse mesh name" << std::endl, false);
					geometry->SetName(name);
					geometry->SetStorageName(name);
				}
				break;
			case WORD_VERTEX_POSITION:
				{
					Virtual::SkinGeometry::Vertices v;
					if (!ParseVector3fv(buffer, v))
						return (out_error() << "Unable to parse vertex positions" << std::endl, false);
					geometry->SetVertices(v);
				}
				break;					
			case WORD_NORMALS:
				{
					Virtual::SkinGeometry::Normals n;
					if (!ParseVector3fv(buffer, n))
						return (out_error() << "Unable to parse vertex normals" << std::endl, false);
					geometry->SetNormals(n);
				}
				break;
			case WORD_FACES:
				{
					Virtual::SkinGeometry::Faces f;
					if (!ParseVector3iv(buffer, f))
						return (out_error() << "Unable to parse mesh faces" << std::endl, false);
					geometry->SetFaces(f);
				}
				break;
			case WORD_TEXTURE:
				{										
					Virtual::SkinGeometry::TextureMeshes t;
					if (!ParseTextures(buffer, t))
						return (out_error() << "Unable to parse mesh texture coords" << std::endl, false);
					geometry->SetTextureMeshes(t);
				}
				break;
			case WORD_BONES_WEIGHT:
				{
					Virtual::SkinGeometry::BoneWeights b;
					if (!ParseBonesWeights(buffer, b))
						return (out_error() << "Unable to parse mesh bone weights" << std::endl, false);
					geometry->SetBoneWeights(b);
				}
				break;
			default:
				return (out_error() << L"Unexpected keyword " << word << std::endl, false);
			}
		}
	}

	bool ParseSkinMeshes(System::Buffer& buffer)
	{
		CHECK_START(buffer);
		System::string name;
		while (1)
		{
			System::string word = buffer.ReadWord();
			switch(KeywordCode code = Parse(word))
			{
			case WORD_CLOSE_BRACKET:
				return true;
			case WORD_SKIN_MESH:
				{
					System::Proxy<Virtual::SkinGeometry> mesh(new Virtual::SkinGeometry);
					if (!ParseSkinMesh(buffer, mesh))
						return (out_error() << "Unable to parse static mesh" << std::endl, false);
					Virtual::SkinGeometry::add(mesh->GetStorageName(), mesh);
				}
				break;
			default:
				return (out_error() << L"Unexpected keyword " << word << std::endl, false);
			}
		}
		return false;
	}

	bool ParseMaterial(System::Buffer& buffer, System::Proxy<Virtual::Material> mat)
	{
		CHECK_START(buffer);
		System::string name;
		while (1)
		{
			System::string word = buffer.ReadWord();
			switch(KeywordCode code = Parse(word))
			{
			case WORD_CLOSE_BRACKET:
				return true;
			case WORD_NAME:
				{
					System::string value;
					if (!ParseBlockedString(buffer, value))
						return (out_error() << "Unable to parse material name" << std::endl, false);
					mat->SetName(value);
					mat->SetStorageName(value);
				}
				break;
			case WORD_ALPHA:
				{
					float value;
					if (!ParseBlockedFloat(buffer, value))
						return (out_error() << "Unable to parse material alpha" << std::endl, false);
					mat->SetAlpha(value);
				}
				break;
			case WORD_AMBIENT:
				{
					float value;
					if (!ParseBlockedFloat(buffer, value))
						return (out_error() << "Unable to parse material ambient" << std::endl, false);
					mat->SetAmbient(value);
				}
				break;
			case WORD_DARKNESS:
				{
					float value;
					if (!ParseBlockedFloat(buffer, value))
						return (out_error() << "Unable to parse material darkness" << std::endl, false);
					mat->SetDarkness(value);
				}
				break;
			case WORD_DIFFUSE_COLOR:
				{
					Math::vec3 value;
					if (!ParseBlockedVector3f(buffer, value))
						return (out_error() << "Unable to parse material diffuse color" << std::endl, false);
					mat->SetDiffuseColor(Math::vec4(value, mat->GetAlpha()));
				}
				break;
			case WORD_DIFFUSE_FRESNEL:
				{
					float value;
					if (!ParseBlockedFloat(buffer, value))
						return (out_error() << "Unable to parse material diffuse fresnel" << std::endl, false);
					mat->SetDiffuseFresnel(value);
				}
				break;
			case WORD_DIFFUSE_FRESNEL_FACTOR:				
				{
					float value;
					if (!ParseBlockedFloat(buffer, value))
						return (out_error() << "Unable to parse material diffuse fresnel factor" << std::endl, false);
					mat->SetDiffuseFresnelFactor(value);
				}
				break;
			case WORD_DIFFUSE_INTENSITY:
				{
					float value;
					if (!ParseBlockedFloat(buffer, value))
						return (out_error() << "Unable to parse material diffuse intensity" << std::endl, false);
					mat->SetDiffuseIntensity(value);
				}
				break;
			case WORD_EMIT:
				{
					float value;
					if (!ParseBlockedFloat(buffer, value))
						return (out_error() << "Unable to parse material emition" << std::endl, false);
					mat->SetEmit(value);
				}
				break;
			case WORD_MIRROR_COLOR:
				{
					Math::vec3 value;
					if (!ParseBlockedVector3f(buffer, value))
						return (out_error() << "Unable to parse material mirror color" << std::endl, false);
					mat->SetMirrorColor(value);
				}
				break;
			case WORD_ROUGHNESS:
				{
					float value;
					if (!ParseBlockedFloat(buffer, value))
						return (out_error() << "Unable to parse material roughness" << std::endl, false);
					mat->SetRoughness(value);
				}
				break;
			case WORD_SPECULAR_ALPHA:
				{
					float value;
					if (!ParseBlockedFloat(buffer, value))
						return (out_error() << "Unable to parse material specular alpha" << std::endl, false);
					mat->SetSpecularAlpha(value);
				}
				break;
			case WORD_SPECULAR_COLOR:
				{
					Math::vec3 value;
					if (!ParseBlockedVector3f(buffer, value))
						return (out_error() << "Unable to parse material specular color" << std::endl, false);
					mat->SetSpecularColor(Math::vec4(value, mat->GetSpecularAlpha()));
				}
				break;
			case WORD_SPECULAR_HARDNESS:
				{
					float value;
					if (!ParseBlockedFloat(buffer, value))
						return (out_error() << "Unable to parse material specular hardness" << std::endl, false);
					mat->SetSpecularFactor(value);
				}
				break;
			case WORD_SPECULAR_INTENSITY:
				{
					float value;
					if (!ParseBlockedFloat(buffer, value))
						return (out_error() << "Unable to parse material specular intensity" << std::endl, false);
					mat->SetSpecularIntensity(value);
				}
				break;
			case WORD_SPECULAR_IOR:
				{
					float value;
					if (!ParseBlockedFloat(buffer, value))
						return (out_error() << "Unable to parse material specular index of refraction" << std::endl, false);
					mat->SetSpecularIndexOfRefraction(value);
				}
				break;
			case WORD_SPECULAR_SLOPE:
				{
					float value;
					if (!ParseBlockedFloat(buffer, value))
						return (out_error() << "Unable to parse material specular slope" << std::endl, false);
					mat->SetSpecularSlope(value);
				}
				break;
			case WORD_TRANSLUCENCY:
				{
					float value;
					if (!ParseBlockedFloat(buffer, value))
						return (out_error() << "Unable to parse material translucency" << std::endl, false);
					mat->SetTranslucency(value);
				}
				break;
			case WORD_NORMAL_MAP:
				{
					System::string value;
					if (!ParseBlockedString(buffer, value))
						return (out_error() << "Unable to parse material normal map" << std::endl, false);
					mat->SetTexture1(value);
				}
				break;
			case WORD_DIFFUSE_MAP:
				{
					System::string value;
					if (!ParseBlockedString(buffer, value))
						return (out_error() << "Unable to parse material diffuse map" << std::endl, false);
					mat->SetTexture0(value);
				}
				break;
			default:
				return (out_error() << L"Unexpected keyword " << word << std::endl, false);
			}
		}
		return false;
	}

	bool ParseMaterials(System::Buffer& buffer, System::Proxy<Scene::SceneGraph> scene)
	{
		CHECK_START(buffer);
		System::string name;
		while (1)
		{
			System::string word = buffer.ReadWord();
			switch(KeywordCode code = Parse(word))
			{
			case WORD_CLOSE_BRACKET:
				return true;
			case WORD_MATERIAL:
				{
					System::Proxy<Virtual::Material> m(new Virtual::Material);					
					if (!ParseMaterial(buffer, m))
						return (out_error() << "Unable to parse material" << std::endl, false);
					Virtual::Material::add(m->GetStorageName(), m);
					scene->AddMaterial(m);
				}
				break;
			default:
				return (out_error() << L"Unexpected keyword " << word << std::endl, false);
			}
		}
		return false;
	}

	bool ParsePointLightNode(System::Buffer& buffer, System::Proxy<Scene::PointLightNode> value)
	{
		CHECK_START(buffer);
		System::Proxy<Virtual::PointLight> light(new Virtual::PointLight);
		while (!buffer.IsEnd())
		{
			System::string word = buffer.ReadWord();
			switch(Parse(word))
			{
			case WORD_CLOSE_BRACKET:
				value->SetPointLight(light.As<Virtual::Light>());
				return true;
			case WORD_NAME:
				{
					System::string name;
					if (!ParseBlockedString(buffer, name))
						return (out_error() << "Unable to parse light name" << std::endl, false);
					value->SetName(name);
					value->SetStorageName(name);
				}
				break;
			case WORD_COLOR:
				{
					Math::vec3 color;
					if (!ParseBlockedVector3f(buffer, color))
						return (out_error() << "Unable to parse light color" << std::endl, false);
					light->SetColor(color);
				}
				break;
			case WORD_DISTANCE:
				{
					float dst;
					if (!ParseBlockedFloat(buffer, dst))
						return (out_error() << "Unable to parse light distance" << std::endl, false);					
					light->SetDistance(dst);
				}
				break;
			case WORD_ENERGY:
				{
					float energy;
					if (!ParseBlockedFloat(buffer, energy))
						return (out_error() << "Unable to parse light energy" << std::endl, false);
					light->SetEnergy(energy);
				}
				break;
			case WORD_LINEAR_ATTENUATION:
				{
					float v;
					if (!ParseBlockedFloat(buffer, v))
						return (out_error() << "Unable to parse light linear attenuation" << std::endl, false);
					light->SetLinearAttenuation(v);
				}
				break;
			case WORD_QUADRATIC_ATTENUATION:
				{
					float v;
					if (!ParseBlockedFloat(buffer, v))
						return (out_error() << "Unable to parse light quadratic attenuation" << std::endl, false);
					light->SetQuadraticAttenuation(v);
				}
				break;
			default:
				return (out_error() << L"Unexpected keyword " << word << std::endl, false);
			}
		}
		return true;
	}

	bool ParseStaticMeshNode(System::Buffer& buffer, System::Proxy<Scene::StaticMeshNode> mesh)
	{
			CHECK_START(buffer);
		while (!buffer.IsEnd())
		{
			System::string word = buffer.ReadWord();
			switch (Parse(word))
			{
			case WORD_CLOSE_BRACKET:
				return true;
			case WORD_NAME:
				{
					System::string value;
					if (!ParseBlockedString(buffer, value))
						return (out_error() << "Can't parse material node name" << std::endl, false);
					mesh->SetName(value);
					mesh->SetStorageName(value);
				}
				break;
			default:
				return (out_error() << L"Unexpected keyword " << word << std::endl, false);
			}
		}
		return false;
	}

	bool ParseBoneNode(System::Buffer& buffer, System::Proxy<Scene::BoneNode> bone)
	{
		CHECK_START(buffer);
		while (!buffer.IsEnd())
		{
			System::string word = buffer.ReadWord();
			switch (Parse(word))
			{
			case WORD_CLOSE_BRACKET:
				return true;
			case WORD_NAME:
				{
					System::string value;
					if (!ParseBlockedString(buffer, value))
						return (out_error() << "Can't parse material node name" << std::endl, false);
					bone->SetName(value);
					bone->SetStorageName(value);
				}
				break;
			case WORD_TRANSFORM_NODE:
				{
					System::Proxy<Scene::TransformNode> node(new Scene::TransformNode);
					if (!ParseTransformNode(buffer, node))
						return (out_error() << "Can't parse transform node" << std::endl, false);
					bone->Add(node);
				}
				break;
			default:
				return (out_error() << L"Unexpected keyword " << word << std::endl, false);
			}
		}
		return false;
	}

	bool ParseSkinMeshNode(System::Buffer& buffer, System::Proxy<Scene::SkinMeshNode> mesh)
	{
			CHECK_START(buffer);
		while (!buffer.IsEnd())
		{
			System::string word = buffer.ReadWord();
			switch (Parse(word))
			{
			case WORD_CLOSE_BRACKET:
				return true;
			case WORD_NAME:
				{
					System::string value;
					if (!ParseBlockedString(buffer, value))
						return (out_error() << "Can't parse material node name" << std::endl, false);
					mesh->SetName(value);
					mesh->SetStorageName(value);
				}
				break;
			default:
				return (out_error() << L"Unexpected keyword " << word << std::endl, false);
			}
		}
		return false;
	}

	bool ParseMaterialNode(System::Buffer& buffer, System::Proxy<Scene::MaterialNode> material)
	{
		CHECK_START(buffer);
		while (!buffer.IsEnd())
		{
			System::string word = buffer.ReadWord();
			switch (Parse(word))
			{
			case WORD_CLOSE_BRACKET:
				return true;
			case WORD_NAME:
				{
					System::string value;
					if (!ParseBlockedString(buffer, value))
						return (out_error() << "Can't parse material node name" << std::endl, false);
					material->SetName(value);
					material->SetStorageName(value);
				}
				break;
			case WORD_STATIC_MESH_NODE:
				{
					System::Proxy<Scene::StaticMeshNode> node(new Scene::StaticMeshNode);
					if (!ParseStaticMeshNode(buffer, node))
						return (out_error() << "Can't parse static mesh node" << std::endl, false);
					material->Add(node);
				}
				break;
			case WORD_SKIN_MESH_NODE:
				{
					System::Proxy<Scene::SkinMeshNode> node(new Scene::SkinMeshNode);
					if (!ParseSkinMeshNode(buffer, node))
						return (out_error() << "Can't parse skin mesh node" << std::endl, false);
					material->Add(node);
				}
				break;
			case WORD_TRANSFORM_NODE:
				{
					System::Proxy<Scene::TransformNode> node(new Scene::TransformNode);
					if (!ParseTransformNode(buffer, node))
						return (out_error() << "Can't parse transform node" << std::endl, false);
					material->Add(node);
				}
				break;
			case WORD_MATERIAL_NODE:
				{
					System::Proxy<Scene::MaterialNode> node(new Scene::MaterialNode);
					if (!ParseMaterialNode(buffer, node))
						return (out_error() << "Can't parse material node" << std::endl, false);
					material->Add(node);
				}
				break;
			default:
				return (out_error() << L"Unexpected keyword " << word << std::endl, false);
			}
		}
		return false;
	}

	bool ParseArmatureNode(System::Buffer& buffer, System::Proxy<Scene::ArmatureNode> armature_node)
	{
		CHECK_START(buffer);
		while (!buffer.IsEnd())
		{
			System::string word = buffer.ReadWord();
			switch (Parse(word))
			{
			case WORD_CLOSE_BRACKET:
				return true;
			case WORD_NAME:
				{
					System::string value;
					if (!ParseBlockedString(buffer, value))
						return (out_error() << "Can't parse transform name" << std::endl, false);
					armature_node->SetName(value);
					armature_node->SetStorageName(value);
				}
				break;
			case WORD_MATERIAL_NODE:
				{
					System::Proxy<Scene::MaterialNode> node(new Scene::MaterialNode);
					if (!ParseMaterialNode(buffer, node))
						return (out_error() << "Can't parse material node" << std::endl, false);
					armature_node->Add(node);
				}
				break;				
			case WORD_BONE_NODE:
				{
					System::Proxy<Scene::BoneNode> node(new Scene::BoneNode);
					if (!ParseBoneNode(buffer, node))
						return (out_error() << "Can't parse bone node" << std::endl, false);
					armature_node->Add(node);
				}
				break;
			default:
				return (out_error() << L"Unexpected keyword " << word << std::endl, false);
			}
		}
		return false;
	}

	bool ParseTransformNode(System::Buffer& buffer, System::Proxy<Scene::TransformNode> transform)
	{
		CHECK_START(buffer);
		while (!buffer.IsEnd())
		{
			System::string word = buffer.ReadWord();
			switch (Parse(word))
			{
			case WORD_CLOSE_BRACKET:
				return true;
			case WORD_NAME:
				{
					System::string value;
					if (!ParseBlockedString(buffer, value))
						return (out_error() << "Can't parse transform name" << std::endl, false);
					transform->SetName(value);
					transform->SetStorageName(value);
				}
				break;
			case WORD_LOCAL_MATRIX:
				{
					Math::mat4 m;
					if (!ParseBlockedMatrix4x4f(buffer, m))
						return (out_error() << "Can't parse local matrix" << std::endl, false);
					transform->SetLocalMatrix(m);
				}
				break;
			case WORD_POINT_LIGHT:
				{
					System::Proxy<Scene::PointLightNode> node(new Scene::PointLightNode);
					if (!ParsePointLightNode(buffer, node))
						return (out_error() << "Can't parse point light node" << std::endl, false);
					transform->Add(node);
				}
				break;
			case WORD_STATIC_MESH_NODE:
				{
					System::Proxy<Scene::StaticMeshNode> node(new Scene::StaticMeshNode);
					if (!ParseStaticMeshNode(buffer, node))
						return (out_error() << "Can't parse static mesh node" << std::endl, false);
					transform->Add(node);
				}
				break;
			case WORD_SKIN_MESH_NODE:
				{
					System::Proxy<Scene::SkinMeshNode> node(new Scene::SkinMeshNode);
					if (!ParseSkinMeshNode(buffer, node))
						return (out_error() << "Can't parse skin mesh node" << std::endl, false);
					transform->Add(node);
				}
				break;
			case WORD_ARMATURE_NODE:
				{
					System::Proxy<Scene::ArmatureNode> node(new Scene::ArmatureNode);
					if (!ParseArmatureNode(buffer, node))
						return (out_error() << "Can't parse armature node" << std::endl, false);
					transform->Add(node);
				}
				break;
			case WORD_MATERIAL_NODE:
				{
					System::Proxy<Scene::MaterialNode> node(new Scene::MaterialNode);
					if (!ParseMaterialNode(buffer, node))
						return (out_error() << "Can't parse material node" << std::endl, false);
					transform->Add(node);
				}
				break;
			case WORD_TRANSFORM_NODE:
				{
					System::Proxy<Scene::TransformNode> node(new Scene::TransformNode);
					if (!ParseTransformNode(buffer, node))
						return (out_error() << "Can't parse transform node" << std::endl, false);
					transform->Add(node);
				}
				break;
			case WORD_LOCATION_INDOOR:
				{
					System::Proxy<Scene::LocationIndoorNode> node(new Scene::LocationIndoorNode);
					if (!ParseLocationIndoor(buffer, node))
						return (out_error() << "Can't parse location indoor node" << std::endl, false);
					transform->Add(node);
				}
				break;
			case WORD_BOUNDING_BOX:
				{
					Math::BoundingBox bbox;
					if (!ParseBoundingBox(buffer, bbox))
						return (out_error() << "Can't parse bounding box" << std::endl, false);
					transform->SetBoundingBox(bbox);
				}
				break;
			default:
				return (out_error() << L"Unexpected keyword " << word << std::endl, false);
			}
		}
		return false;
	}

	bool ParsePortalNode(System::Buffer& buffer, System::Proxy<Scene::PortalNode> node)
	{
		CHECK_START(buffer);

		while (!buffer.IsEnd())
		{
			System::string word = buffer.ReadWord();
			switch (Parse(word))
			{
			case WORD_CLOSE_BRACKET:
				return true;
			case WORD_NAME:
				{
					System::string name;
					if (!ParseBlockedString(buffer, name))
						return (out_error() << "Can't parse portal node name" << std::endl, false);
					node->SetName(name);
					node->SetStorageName(name);
				}
				break;
			case WORD_LOCAL_MATRIX:
				{
					Math::mat4 m;
					if (!ParseBlockedMatrix4x4f(buffer, m))
						return (out_error() << "Can't parse portal local matrix" << std::endl, false);
					node->SetLocalMatrix(m);
				}
				break;
			case WORD_VERTEX_POSITION:
				{
					Math::Portal::PointsCollection p;
					if (!ParseVector3fv(buffer, p))
						return (out_error() << "Can't parse portal vertex positions" << std::endl, false);
					Math::Portal portal;
					portal.SetPoints(p);
					node->SetPortal(portal);
				}
				break;
			default:
				return (out_error() << L"Unexpected keyword " << word << std::endl, false);
			}
		}
		return false;
	}

	bool ParseLocationIndoor(System::Buffer& buffer, System::Proxy<Scene::LocationIndoorNode> location)
	{
		CHECK_START(buffer);
		while (!buffer.IsEnd())
		{
			System::string word = buffer.ReadWord();
			switch (Parse(word))
			{
			case WORD_CLOSE_BRACKET:
				return true;
			case WORD_NAME:
				{
					System::string name;
					if (!ParseBlockedString(buffer, name))
						return (out_error() << "Can't parse location name" << std::endl, false);
					location->SetName(name);
					location->SetStorageName(name);
				}
			case WORD_LOCAL_MATRIX:
				{
					Math::mat4 m;
					if (!ParseBlockedMatrix4x4f(buffer, m))
						return (out_error() << "Can't parse indoor location" << std::endl, false);
					location->SetLocalMatrix(m);
				}
				break;
			case WORD_CONVEX_MESH:
				{
					Math::ConvexShapeMesh mesh;
					if (!ParseConvexMesh(buffer, mesh))
						return (out_error() << "Can't parse convex mesh" << std::endl, false);
					location->SetConvexMesh(mesh);
				}
				break;
			case WORD_MATERIAL_NODE:
				{
					System::Proxy<Scene::MaterialNode> node(new Scene::MaterialNode);
					if (!ParseMaterialNode(buffer, node))
						return (out_error() << "Can't parse material node" << std::endl, false);
					location->Add(node);
				}
				break;
			case WORD_TRANSFORM_NODE:
				{
					System::Proxy<Scene::TransformNode> node(new Scene::TransformNode);
					if (!ParseTransformNode(buffer, node))
						return (out_error() << "Can't parse transform node" << std::endl, false);
					location->Add(node);
				}
				break;
			case WORD_PORTAL_NODE:
				{
					System::Proxy<Scene::PortalNode> node(new Scene::PortalNode);
					if (!ParsePortalNode(buffer, node))
						return (out_error() << "Can't parse portal node" << std::endl, false);
					location->Add(node);
				}
				break;
			default:
				return (out_error() << L"Unexpected keyword " << word << std::endl, false);
			}
		}
		return false;
	}

	bool ParseWorld(System::Buffer& buffer, System::Proxy<Scene::SceneGraph> scene)
	{		
		System::Proxy<Scene::Node> root(new Scene::Node);
		scene->SetRootNode(root);	
		while (!buffer.IsEnd())
		{
			System::string word = buffer.ReadWord();
			switch(Parse(word))
			{
			case WORD_CLOSE_BRACKET:							
				return true;
			case WORD_LOCATION_INDOOR:
				{
					System::Proxy<Scene::LocationIndoorNode> node(new Scene::LocationIndoorNode);
					if (!ParseLocationIndoor(buffer, node))				
						return (out_error() << "Can't parse location indoor" << std::endl, false);
					root->Add(node);
				}
				break;	
			case WORD_TRANSFORM_NODE:
				{
					System::Proxy<Scene::TransformNode> node(new Scene::TransformNode);
					if (!ParseTransformNode(buffer, node))
						return (out_error() << "Can't parse transform node" << std::endl, false);
					root->Add(node);
				}
				break;
			case WORD_MATERIAL_NODE:
				{
					System::Proxy<Scene::MaterialNode> node(new Scene::MaterialNode);
					if (!ParseMaterialNode(buffer, node))
						return (out_error() << "Can't parse material node" << std::endl, false);
					root->Add(node);
				}
				break;
			case WORD_MATERIALS:
				{									
					if (!ParseMaterials(buffer, scene))
						return (out_error() << "Unable to parse materials" << std::endl, false);
				}
				break;
			case WORD_STATIC_MESHES:
				{
					if (!ParseStaticMeshes(buffer))
						return (out_error() << "Unable to parse static meshes" << std::endl, false);
				}
				break;
			case WORD_SKIN_MESHES:
				{
					if (!ParseSkinMeshes(buffer))
						return (out_error() << "Unable to parse skin meshes" << std::endl, false);
				}
				break;
			case WORD_ACTIONS:
				{
					if (!ParseActions(buffer))
						return (out_error() << "Unable to parse actions" << std::endl, false);
				}
				break;
			case WORD_ARMATURES:
				{
					if (!ParseArmatures(buffer))
						return (out_error() << "Unable to parse armatures" << std::endl, false);
				}
				break;
			default:
				return (out_error() << L"Unexpected keyword " << word << std::endl, false);
			}
		}
		return true;
	}

	System::Proxy<System::Object> LoadWorld(const System::string& path)
	{
		System::Buffer buffer;
		if (!System::BinaryFile::Load(path, buffer))
			return (out_error() << (L"Unable to load file " + path).Data() << std::endl, System::Proxy<Scene::SceneGraph>(nullptr));

		System::Proxy<Scene::SceneGraph> scene(new Scene::SceneGraph);
		if (!ParseWorld(buffer, scene))
			return (out_error() << "Can't load world from " << path << std::endl, System::Proxy<Scene::SceneGraph>(nullptr));

		scene->SetActiveCamera(System::Proxy<Virtual::Camera>(new Virtual::FirstPersonCamera()));

		return scene;
	}

	bool ParseTerrainRawDataSource(System::Buffer& buffer, Virtual::TerrainRawDataSource& source)
	{
		CHECK_START(buffer);
		while (!buffer.IsEnd())
		{
			System::string word = buffer.ReadWord();
			switch(Parse(word))
			{
			case WORD_CLOSE_BRACKET:							
				return true;
			case WORD_REF:
				{
					System::string value;
					if (!ParseBlockedString(buffer, value))
						return (out_error() << "Can't parse terrain cell name" << std::endl, false);
					source.SetRawFile(value);
				}
				break;
			default:
				return (out_error() << L"Unexpected keyword " << word << std::endl, false);
			}
		}
		return false;
	}

	bool ParseTerrainCell(System::Buffer& buffer, Virtual::TerrainCell& cell)
	{
		CHECK_START(buffer);
		while (!buffer.IsEnd())
		{
			System::string word = buffer.ReadWord();
			switch(Parse(word))
			{
			case WORD_CLOSE_BRACKET:							
				return true;
			case WORD_NAME:
				{
					System::string value;
					if (!ParseBlockedString(buffer, value))
						return (out_error() << "Can't parse terrain cell name" << std::endl, false);
					cell.SetName(value);
				}
				break;
			case WORD_LOCATION:
				{
					Math::ivec2 value;
					if (!ParseBlockedVector2i(buffer, value))
						return (out_error() << "Can't parse terrain cell location" << std::endl, false);
					cell.SetLocation(value);
				}
				break;
			case WORD_RAW_DATA_SOURCE:
				{
					Virtual::TerrainRawDataSource value;
					if (!ParseTerrainRawDataSource(buffer, value))
						return (out_error() << "Can't parse terrain raw data source" << std::endl, false);
					cell.SetRawDataSource(value);
				}
				break;
			default:
				return (out_error() << L"Unexpected keyword " << word << std::endl, false);
			}
		}
		return false;
	}

	bool ParseMapDescription(System::Buffer& buffer, System::Proxy<Virtual::Terrain> terrain)
	{
		while (!buffer.IsEnd())
		{
			System::string word = buffer.ReadWord();
			switch(Parse(word))
			{
			case WORD_CLOSE_BRACKET:							
				return true;
			case WORD_NUM_BLOCKS:
				{
					int value;
					if (!ParseBlockedInteger(buffer, value))
						return (out_error() << "Can't parse terrain num blocks" << std::endl, false);
					terrain->SetNumBlocks(value);
				}
				break;
			case WORD_BLOCK_SCALE:
				{
					float value;
					if (!ParseBlockedFloat(buffer, value))
						return (out_error() << "Can't parse terrain block scale" << std::endl, false);
					terrain->SetBlockScale(value);
				}
				break;
			case WORD_BLOCK_SIZE:
				{
					int value;
					if (!ParseBlockedInteger(buffer, value))
						return (out_error() << "Can't parse terrain block size" << std::endl, false);
					terrain->SetBlocksSize(value);
				}
				break;
			case WORD_HEIGHT_SCALE:
				{
					float value;
					if (!ParseBlockedFloat(buffer, value))
						return (out_error() << "Can't parse terrain height scale" << std::endl, false);
					terrain->SetHeightScale(value);
				}
				break;
			case WORD_WORLD_ORIGIN:
				{
					Math::vec2 value;
					if (!ParseBlockedVector2f(buffer, value))
						return (out_error() << "Can't parse terrain origin position" << std::endl, false);
					terrain->SetOrigin(value);
				}
				break;
			case WORD_CELL:
				{
					Virtual::TerrainCell value;
					if (!ParseTerrainCell(buffer, value))
						return (out_error() << "Can't parse terrain cell" << std::endl, false);
					value.Validate();
					terrain->AddOrUpdateCell(value);
				}
				break;
			default:
				return (out_error() << L"Unexpected keyword " << word << std::endl, false);
			}
		}
		return true;
	}

	System::Proxy<System::Object> ParseAnything(System::Buffer& buffer)
	{
		while (!buffer.IsEnd())
		{
			System::string word = buffer.ReadWord();
			KeywordCode code = Parse(word);
			switch(code)
			{
			case WORD_MAPDESCTEXT:
				{
					System::Proxy<Virtual::Terrain> terrain(new Virtual::Terrain);
					if (!ParseMapDescription(buffer, terrain))
						return (out_error() << "Can't parse terrain" << std::endl, System::Proxy<System::Object>(nullptr));
					return terrain;
				}
			default:
				return (out_error() << L"Unexpected keyword " << word << std::endl, System::Proxy<System::Object>(nullptr));
			}
		}
		return System::Proxy<System::Object>(nullptr);
	}

	System::Proxy<System::Object> ParsePunkFile(const System::string& path)
	{
		System::Buffer buffer;
		if (!System::BinaryFile::Load(path, buffer))
			return (out_error() << (L"Unable to load file " + path).Data() << std::endl, System::Proxy<Scene::SceneGraph>(nullptr));
		
		return ParseAnything(buffer);
	}
}