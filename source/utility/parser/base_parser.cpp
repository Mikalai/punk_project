#include "base_parser.h"
#include "../../math/vec2.h"
#include "../../math/vec3.h"
#include "../../math/vec4.h"
#include "../../math/mat2.h"
#include "../../math/mat3.h"
#include "../../math/mat4.h"
#include "../../math/bounding_box.h"
#include "../../string/string.h"
#include "../../system/buffer.h"
#include "../../system/logger.h"
#include "../../system/binary_file.h"

#include "../descriptors/object_type_desc.h"
#include "../descriptors/mesh_desc.h"
#include "../descriptors/object_desc.h"
#include "../descriptors/world_desc.h"
#include "../descriptors/action_desc.h"
#include "../descriptors/animation_desc.h"
#include "../descriptors/armature_desc.h"
#include "../descriptors/bone_desc.h"
#include "../descriptors/material_desc.h"
#include "../descriptors/camera_desc.h"
#include "../descriptors/light_desc.h"

namespace Utility
{
	/// This function convert a string representation of the file into code
	KeywordCode Parser::Parse(System::string& word)
	{
		for (int i = 0; i < sizeof(Keyword)/sizeof(void*); i++)
		{
			if (word == Keyword[i])
				return static_cast<KeywordCode>(i);
		}	
		out_error() << System::string::Format(L"Unknown keyword %s", word.Data()) << std::endl;		
		return WORD_BAD_KEYWORD;
	}

	///	Returns false if couldn't find open bracket in the buffer
	bool Parser::CheckIntegrity(System::Buffer& buffer)
	{
		if (Parse(buffer.ReadWord()) != WORD_OPEN_BRACKET)
			return false;
		return true;
	}

	bool Parser::ParseFloat(System::Buffer& buffer, float& value)
	{
		value = buffer.ReadWord().ToFloat();
		return true;
	}

	bool Parser::ParseInteger(System::Buffer& buffer, int& value)
	{
		value = buffer.ReadWord().ToInt32();
		return true;
	}

	bool Parser::ParseVector2f(System::Buffer& buffer, Math::vec2& value)
	{
		value[0] = buffer.ReadWord().ToFloat();
		value[1] = buffer.ReadWord().ToFloat();
		return true;
	}

	bool Parser::ParseVector3f(System::Buffer& buffer, Math::vec3& value)
	{
		value[0] = buffer.ReadWord().ToFloat();
		value[1] = buffer.ReadWord().ToFloat();
		value[2] = buffer.ReadWord().ToFloat();
		return true;
	}

	bool Parser::ParseVector4f(System::Buffer& buffer, Math::vec4& value)
	{
		value[0] = buffer.ReadWord().ToFloat();
		value[1] = buffer.ReadWord().ToFloat();
		value[2] = buffer.ReadWord().ToFloat();
		value[3] = buffer.ReadWord().ToFloat();
		return true;
	}

	bool Parser::ParseVector2i(System::Buffer& buffer, Math::ivec2& value)
	{
		value[0] = buffer.ReadWord().ToInt32();
		value[1] = buffer.ReadWord().ToInt32();
		return true;
	}

	bool Parser::ParseVector3i(System::Buffer& buffer, Math::ivec3& value)
	{
		value[0] = buffer.ReadWord().ToInt32();
		value[1] = buffer.ReadWord().ToInt32();
		value[2] = buffer.ReadWord().ToInt32();
		return true;
	}

	bool Parser::ParseVector4i(System::Buffer& buffer, Math::ivec4& value)
	{
		value[0] = buffer.ReadWord().ToInt32();
		value[1] = buffer.ReadWord().ToInt32();
		value[2] = buffer.ReadWord().ToInt32();
		value[3] = buffer.ReadWord().ToInt32();
		return true;
	}

	bool Parser::ParseMatrix4x4f(System::Buffer& buffer, Math::mat4& value)
	{
		for (int i = 0; i < 16; ++i)
			value[i] = buffer.ReadWord().ToFloat();
		value = value.Transposed();
		return true;
	}

	bool Parser::ParseString(System::Buffer& buffer, System::string& value)
	{
		value = buffer.ReadWord();
		return true;
	}

	bool Parser::ParseBoundingBox(System::Buffer& buffer, Math::BoundingBox& value)
	{
		CHECK_START(buffer);
		for (int i = 0; i < 8; ++i)
			if (!ParseVector3f(buffer, value[i]))
				return (out_error() << "Unable to parse bounding box" << std::endl, false);
		CHECK_END(buffer);
		return true;
	}

	bool Parser::ParseBlockedString(System::Buffer& buffer, System::string& value)
	{
		CHECK_START(buffer);
		if (!ParseString(buffer, value))
			return (out_error() << "Unable to parse blocked string" << std::endl, false);
		CHECK_END(buffer);
		return true;
	}

	bool Parser::ParseSubtype(System::Buffer& buffer, ObjectTypeDesc& value)
	{
		CHECK_START(buffer);
		System::string s;
		if (!ParseString(buffer, s))
			return (out_error() << "Unable to parse sub type" << std::endl, false);
		if (!value.BuildFromString(s))
			return (out_error() << "Unable to parse sub type" << std::endl, false);
		CHECK_END(buffer);
		return true;
	}

	bool Parser::ParseBlockedFloat(System::Buffer& buffer, float& value)
	{
		CHECK_START(buffer);
		if (!ParseFloat(buffer, value))
			return (out_error() << "Unable to parse blocked float number" << std::endl, false);
		CHECK_END(buffer);
		return true;
	}

	bool Parser::ParseBlockedVector3f(System::Buffer& buffer, Math::vec3& value)
	{
		CHECK_START(buffer);
		if (!ParseVector3f(buffer, value))
			return (out_error() << "Unable to parse blocked vec3f" << std::endl, false);
		CHECK_END(buffer);
		return true;
	}

	bool Parser::ParseBlockedMatrix4x4f(System::Buffer& buffer, Math::mat4& value)
	{
		CHECK_START(buffer);
		if (!ParseMatrix4x4f(buffer, value))
			return (out_error() << "Unable to parse mat4f" << std::endl, false);
		CHECK_END(buffer);
		return true;
	}

	bool Parser::ParseVector3fv(System::Buffer& buffer, std::vector<Math::vec3>& value)
	{
		CHECK_START(buffer);
		while (1)
		{
			System::string word = buffer.ReadWord();

			if (word == Keyword[WORD_CLOSE_BRACKET])
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

	bool Parser::ParseVector3iv(System::Buffer& buffer, std::vector<Math::ivec3>& value)
	{
		CHECK_START(buffer);
		while (1)
		{
			System::string word = buffer.ReadWord();

			if (word == Keyword[WORD_CLOSE_BRACKET])
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

	bool Parser::ParseVector4iv(System::Buffer& buffer, std::vector<Math::ivec4>& value)
	{
		CHECK_START(buffer);
		while (1)
		{
			System::string word = buffer.ReadWord();

			if (word == Keyword[WORD_CLOSE_BRACKET])
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

	bool Parser::ParseVector4Vector2iv(System::Buffer& buffer, std::vector<Math::Vector4<Math::vec2>>& value)
	{
		CHECK_START(buffer);
		while (1)
		{
			System::string word = buffer.ReadWord();

			if (word == Keyword[WORD_CLOSE_BRACKET])
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

	bool Parser::ParseTextures(System::Buffer& buffer, std::map<System::string, std::vector<Math::Vector4<Math::vec2>>>& value)
	{
		CHECK_START(buffer);

		while (1)
		{
			if (buffer.IsEnd())
			{
				out_error() << L"Can't parse object" << std::endl;
				return false;
			}

			System::string s;

			switch(KeywordCode index = Parse(buffer.ReadWord()))
			{
			case WORD_CLOSE_BRACKET:
				return true;
			case WORD_NAME:
				{					
					if (!ParseBlockedString(buffer, s))
					{
						out_error() << "Unable to parse textures name" << std::endl;
						return false;
					}
				}
				break;
			case WORD_TEXTURE_COORD:
				{
					if (!ParseVector4Vector2iv(buffer, value[s]))
					{
						out_error() << "Unable to parse textures coords" << std::endl;
						return false;
					}
				}
				break;
			default:
				return (out_error() << System::string::Format(L"Unexpected keyword %s", Keyword[index]) << std::endl, false);
			}
		}
		return true;
	}

	bool Parser::ParseBonesWeights(System::Buffer& buffer, Virtual::VertexBoneWeights& value)
	{
		CHECK_START(buffer);

		while (1)
		{
			System::string word = buffer.ReadWord();
			if (word == Keyword[WORD_CLOSE_BRACKET])
				return true;
			int vertex_id = word.ToInt32();
			System::string bone_name = buffer.ReadWord();
			float weight = buffer.ReadWord().ToFloat();
			value[vertex_id][bone_name] = weight;
		}
		return (out_error() << "Unable to parse vertex bones weights" << std::endl, false);
	}

	bool Parser::ParseMesh(System::Buffer& buffer, MeshDesc& value)
	{
		CHECK_START(buffer);

		while (1)
		{
			if (buffer.IsEnd())
			{
				out_error() << L"Can't parse object" << std::endl;
				return false;
			}

			switch(int index = Parse(buffer.ReadWord()))
			{
			case WORD_CLOSE_BRACKET:
				return true;
			case WORD_VERTEX_POSITION:
				std::cout << "Loading vertex position..." << std::endl;
				if (!ParseVector3fv(buffer, value.m_vertices))
				{
					out_error() << "Unable to parse vertex positions" << std::endl;
					return false;
				}
				break;					
			case WORD_NORMALS:
				std::cout << "Loading normals..." << std::endl;
				if (!ParseVector3fv(buffer, value.m_normals))
				{
					out_error() << "Unable to parse vertex normals" << std::endl;
					return false;
				}
				break;
			case WORD_FACES:
				std::cout << "Loading faces..." << std::endl;
				if (!ParseVector3iv(buffer, value.m_faces))
				{
					out_error() << "Unable to parse mesh faces" << std::endl;
					return false;
				}
				break;
			case WORD_BONES_WEIGHT:
				{
					if (!ParseBonesWeights(buffer, value.m_bone_weights))
					{
						out_error() << "Unable to parse textures bones weights" << std::endl;
						return false;
					}
				}
				break;
			case WORD_TEXTURE:
				{										
					if (!ParseTextures(buffer, value.m_tex_coords))
					{
						out_error() << "Unable to parse mesh texture coords" << std::endl;
						return false;
					}
				}
				break;
			case WORD_MATERIAL_REF:
				{
					System::string name;
					if (!ParseBlockedString(buffer, name))
					{
						out_error() << "Unable to parse material reference" << std::endl;
						return false;
					}
					value.m_material_ref.push_back(name);
				}
				break;
			default:
				return (out_error() << System::string::Format(L"Unexpected keyword %s", Keyword[index]) << std::endl, false);
			}
		}
	}

	/// Perform parsing object chunk
	bool Parser::ParseObject(System::Buffer &buffer, ObjectDesc& o)
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
	}

	bool Parser::ParsePositionTrack(System::Buffer& buffer, Virtual::AnimationTrack<Math::vec3>& value)
	{
		CHECK_START(buffer);
		while (1)
		{
			System::string word = buffer.ReadWord();

			if (word == Keyword[WORD_CLOSE_BRACKET])
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

	bool Parser::ParseRotationTrack(System::Buffer& buffer, Virtual::AnimationTrack<Math::quat>& value)
	{
		CHECK_START(buffer);
		while (1)
		{
			System::string word = buffer.ReadWord();

			if (word == Keyword[WORD_CLOSE_BRACKET])
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

	bool Parser::ParseAnimation(System::Buffer& buffer, AnimationDesc& value)
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

			KeywordCode index;				
			switch(index = Parse(buffer.ReadWord()))
			{
			case WORD_CLOSE_BRACKET:
				return true;
			case WORD_NAME:
				{
					if (!ParseBlockedString(buffer, value.m_bone_name))
					{
						out_error() << "Unable to parse animation name" << std::endl;
						return false;
					}
				}
				break;
			case WORD_POSITION_TRACK:
				{
					if (!ParsePositionTrack(buffer, value.m_pos_track))
					{
						out_error() << "Unable to parse animation position track" << std::endl;
						return false;
					}
				}
				break;
			case WORD_ROTATION_TRACK:
				{
					if (!ParseRotationTrack(buffer, value.m_rot_track))
					{
						out_error() << "Unable to parse animation rotation track" << std::endl;
						return false;
					}
				}
				break;
			default:
				return (out_error() << System::string::Format(L"Unexpected keyword %s", Keyword[index]) << std::endl, false);
			}
		}
		return false;
	}

	bool Parser::ParseAction(System::Buffer& buffer, ActionDesc& value)
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

			KeywordCode index;				
			switch(index = Parse(buffer.ReadWord()))
			{
			case WORD_CLOSE_BRACKET:
				return true;
			case WORD_NAME:
				{
					if (!ParseBlockedString(buffer, value.m_name))
					{
						out_error() << "Unable to parse action name" << std::endl;
						return false;
					}
				}
				break;
			case WORD_TIMING:
				{
					CHECK_START(buffer);
					value.m_start = buffer.ReadWord().ToInt32();
					value.m_end = buffer.ReadWord().ToInt32();
					if (Parse(buffer.ReadWord()) != WORD_CLOSE_BRACKET)
					{
						out_error() << L"Can't parse action timing" << std::endl;		
						return false;
					}					
				}
				break;
			case WORD_BONE_ANIMATION:
				{
					std::unique_ptr<AnimationDesc> anim(new AnimationDesc);
					anim->m_is_bone_anim = true;
					if (!ParseAnimation(buffer, *anim))
					{
						out_error() << "Unable to parse bone animation" << std::endl;
						return false;
					}
					value.m_animation.push_back(anim.release());
				}
				break;
			case WORD_OBJECT_ANIMATION:
				{
					std::unique_ptr<AnimationDesc> anim(new AnimationDesc);
					anim->m_is_bone_anim = false;
					if (!ParseAnimation(buffer, *anim))
					{
						out_error() << "Unable to parse action animation" << std::endl;
						return false;
					}
					value.m_animation.push_back(anim.release());
				}
				break;
			default:
				return (out_error() << System::string::Format(L"Unexpected keyword %s", Keyword[index]) << std::endl, false);
			}
		}
	}

	bool Parser::ParseActions(System::Buffer& buffer, std::map<System::string, ActionDesc*>& value)
	{
		CHECK_START(buffer);

		while (1)
		{
			if (buffer.IsEnd())
			{
				out_error() << L"Can't parse object" << std::endl;
				return false;
			}

			KeywordCode index;
			switch(index = Parse(buffer.ReadWord()))
			{
			case WORD_CLOSE_BRACKET:
				return true;
			case WORD_ACTION:
				{	
					std::unique_ptr<ActionDesc> action(new ActionDesc);
					if (!ParseAction(buffer, *action))
					{
						out_error() << "Unable to parse action" << std::endl;
						return false;
					}
					value[action->m_name] = action.get();
					action.release();
				}
				break;
			}
		}
		return false;
	}

	bool Parser::ParseBone(System::Buffer& buffer, BoneDesc& value)
	{
		CHECK_START(buffer);
		System::string name, parent;
		while (1)
		{
			switch(int code = Parse(buffer.ReadWord()))
			{
			case WORD_CLOSE_BRACKET:
				return true;
			case WORD_NAME:
				{
					if (!ParseBlockedString(buffer, value.m_name))
					{
						out_error() << "Unable to parse bone name" << std::endl;
						return false;
					}
				}
				break;
			case WORD_PARENT:
				{
					if (!ParseBlockedString(buffer, value.m_parent))
					{
						out_error() << "Unable to parse bone parent name" << std::endl;
						return false;
					}
				}
				break;
			case WORD_LOCAL_MATRIX:
				{
					if (!ParseBlockedMatrix4x4f(buffer, value.m_local))
					{
						out_error() << "Unable to parse bone local matrix" << std::endl;
						return false;
					}
				}
				break;
			case WORD_LENGTH:
				{
					if (!ParseBlockedFloat(buffer, value.m_length))
					{
						out_error() << "Unable to parse bone length" << std::endl;
						return false;
					}
				}
				break;
			default:
				return (out_error() << System::string::Format(L"Unexpected keyword %s", Keyword[code]) << std::endl, false);
			}
		}
		return false;
	}

	/// Parse single armature
	bool Parser::ParseArmature(System::Buffer& buffer, ArmatureDesc& value)
	{
		CHECK_START(buffer);
		while (1)
		{
			if (buffer.IsEnd())
			{
				out_error() << L"Can't parse object" << std::endl;
				return false;
			}

			int index;
			System::string name;
			switch(index = Parse(name = buffer.ReadWord()))
			{
			case WORD_CLOSE_BRACKET:
				return true;
			case WORD_NAME:
				{
					if (!ParseBlockedString(buffer, value.m_name))
					{
						out_error() << "Unable to parse armature name" << std::endl;
						return false;
					}
				}
				break;
			case WORD_BONE:
				{
					std::unique_ptr<BoneDesc> bone(new BoneDesc);
					if (!ParseBone(buffer, *bone))
					{
						out_error() << "Unable to parse armature bone" << std::endl;
						return false;
					}
					value.m_bones.push_back(bone.release());
				}
				break;
			default:
				return (out_error() << L"Unknown keyword: " + name << std::endl, false);
			}
		}
		return false;
	}

	bool Parser::ParseActionsRef(System::Buffer& buffer, std::vector<System::string>& value)
	{
		CHECK_START(buffer);
		System::string name;
		while (1)
		{
			switch(KeywordCode code = Parse(buffer.ReadWord()))
			{
			case WORD_CLOSE_BRACKET:
				return true;
			case WORD_ACTION_REF:
				{
					System::string s;
					if (!ParseBlockedString(buffer, s))
					{
						out_error() << "Unable to parse action reference" << std::endl;
						return false;
					}
					value.push_back(s);
				}
				break;
			default:
				return (out_error() << System::string::Format(L"Unexpected keyword %s", Keyword[code]) << std::endl, false);
			}
		}
		return false;
	}


	bool Parser::ParseMaterials(System::Buffer& buffer, std::map<System::string, MaterialDesc*>& value)
	{
		CHECK_START(buffer);
		System::string name;
		while (1)
		{
			switch(KeywordCode code = Parse(buffer.ReadWord()))
			{
			case WORD_CLOSE_BRACKET:
				return true;
			case WORD_MATERIAL:
				{
					std::unique_ptr<MaterialDesc> m(new MaterialDesc);
					if (!ParseMaterial(buffer, *m))
					{
						out_error() << "Unable to parse material" << std::endl;
						return false;
					}
					value[m->m_name] = m.get();
					m.release();
				}
				break;
			default:
				return (out_error() << System::string::Format(L"Unexpected keyword %s", Keyword[code]) << std::endl, false);
			}
		}
		return false;
	}

	bool Parser::ParseMaterial(System::Buffer& buffer, MaterialDesc& value)
	{
		CHECK_START(buffer);
		System::string name;
		while (1)
		{
			switch(KeywordCode code = Parse(buffer.ReadWord()))
			{
			case WORD_CLOSE_BRACKET:
				return true;
			case WORD_NAME:
				if (!ParseBlockedString(buffer, value.m_name))
				{
					out_error() << "Unable to parse material name" << std::endl;
					return false;
				}
				break;
			case WORD_ALPHA:
				if (!ParseBlockedFloat(buffer, value.m_alpha))
				{
					out_error() << "Unable to parse material alpha" << std::endl;
					return false;
				}
				break;
			case WORD_AMBIENT:
				if (!ParseBlockedFloat(buffer, value.m_ambient))
				{
					out_error() << "Unable to parse material ambient" << std::endl;
					return false;
				}
				break;
			case WORD_DARKNESS:
				if (!ParseBlockedFloat(buffer, value.m_darkness))
				{
					out_error() << "Unable to parse material darkness" << std::endl;
					return false;
				}
				break;
			case WORD_DIFFUSE_COLOR:
				if (!ParseBlockedVector3f(buffer, value.m_diffuse_color))
				{
					out_error() << "Unable to parse material diffuse color" << std::endl;
					return false;
				}
				break;
			case WORD_DIFFUSE_FRESNEL:
				if (!ParseBlockedFloat(buffer, value.m_diffuse_fresnel))
				{
					out_error() << "Unable to parse material diffuse fresnel" << std::endl;
					return false;
				}
				break;
			case WORD_DIFFUSE_FRESNEL_FACTOR:				
				if (!ParseBlockedFloat(buffer, value.m_diffuse_fresnel_factor))
				{
					out_error() << "Unable to parse material diffuse fresnel factor" << std::endl;
					return false;
				}
				break;
			case WORD_DIFFUSE_INTENSITY:
				if (!ParseBlockedFloat(buffer, value.m_diffuse_intensity))
				{
					out_error() << "Unable to parse material diffuse intensity" << std::endl;
					return false;
				}
				break;
			case WORD_EMIT:
				if (!ParseBlockedFloat(buffer, value.m_emit))
				{
					out_error() << "Unable to parse material emition" << std::endl;
					return false;
				}
				break;
			case WORD_MIRROR_COLOR:
				if (!ParseBlockedVector3f(buffer, value.m_mirror_color))
				{
					out_error() << "Unable to parse material mirror color" << std::endl;
					return false;
				}
				break;
			case WORD_ROUGHNESS:
				if (!ParseBlockedFloat(buffer, value.m_roughness))
				{
					out_error() << "Unable to parse material roughness" << std::endl;
					return false;
				}
				break;
			case WORD_SPECULAR_ALPHA:
				if (!ParseBlockedFloat(buffer, value.m_specular_alpha))
				{
					out_error() << "Unable to parse material specular alpha" << std::endl;
					return false;
				}
				break;
			case WORD_SPECULAR_COLOR:
				if (!ParseBlockedVector3f(buffer, value.m_specular_color))
				{
					out_error() << "Unable to parse material specular color" << std::endl;
					return false;
				}
				break;
			case WORD_SPECULAR_HARDNESS:
				if (!ParseBlockedFloat(buffer, value.m_specular_factor))
				{
					out_error() << "Unable to parse material specular hardness" << std::endl;
					return false;
				}
				break;
			case WORD_SPECULAR_INTENSITY:
				if (!ParseBlockedFloat(buffer, value.m_specular_intensity))
				{
					out_error() << "Unable to parse material specular intensity" << std::endl;
					return false;
				}
				break;
			case WORD_SPECULAR_IOR:
				if (!ParseBlockedFloat(buffer, value.m_specular_index_of_refraction))
				{
					out_error() << "Unable to parse material specular index of refraction" << std::endl;
					return false;
				}
				break;
			case WORD_SPECULAR_SLOPE:
				if (!ParseBlockedFloat(buffer, value.m_specular_slope))
				{
					out_error() << "Unable to parse material specular slope" << std::endl;
					return false;
				}
				break;
			case WORD_TRANSLUCENCY:
				if (!ParseBlockedFloat(buffer, value.m_translucency))
				{
					out_error() << "Unable to parse material translucency" << std::endl;
					return false;
				}
				break;
			case WORD_NORMAL_MAP:
				if (!ParseBlockedString(buffer, value.m_normal_map))
				{
					out_error() << "Unable to parse material normal map" << std::endl;
					return false;
				}
				break;
			case WORD_DIFFUSE_MAP:
				if (!ParseBlockedString(buffer, value.m_diffuse_map))
				{
					out_error() << "Unable to parse material diffuse map" << std::endl;
					return false;
				}
				break;
			default:
				return (out_error() << System::string::Format(L"Unexpected keyword %s", Keyword[code]) << std::endl, false);
			}
		}
		return false;
	}

	bool Parser::ParseWorld(System::Buffer& buffer, WorldDesc& value)
	{
		while (!buffer.IsEnd())
		{
			System::string word = buffer.ReadWord();
			switch(Parse(word))
			{
			case WORD_OBJECT:
				{
					out_message() << "Parsing object..." << std::endl;
					std::auto_ptr<ObjectDesc> object(new ObjectDesc);
					if (!ParseObject(buffer, *object))
					{
						out_error() << "Unable to parse object" << std::endl;
						return false;
					}
					value.m_objects.push_back(object.release());
				}
				break;
			case WORD_MATERIALS:
				out_message() << "Parsing material..." << std::endl;
				if (!ParseMaterials(buffer, value.m_materials))
				{
					out_error() << "Unable to parse materials" << std::endl;
					return false;
				}
				break;
			case WORD_ACTIONS:
				out_message() << "Parsing actions..." << std::endl;
				if (!ParseActions(buffer, value.m_actions))
				{
					out_error() << "Unable to parse actions" << std::endl;
					return false;
				}
				break;
			default:
				return (out_error() << System::string::Format(L"Unexpected keyword: %s",  word.Data()) << std::endl, false);
			}
		}
		return true;
	}

	bool Parser::ParseLight(System::Buffer& buffer, LightDesc& value)
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
					return (out_error() << "Unable to parse light name" << std::endl, false);
				break;
			case WORD_LIGHT_TYPE:
				if (!ParseBlockedString(buffer, value.m_type))
					return (out_error() << "Unable to parse light type" << std::endl, false);
				break;
			case WORD_COLOR:
				if (!ParseBlockedVector3f(buffer, value.m_color))
					return (out_error() << "Unable to parse light color" << std::endl, false);
				break;
			case WORD_DISTANCE:
				if (!ParseBlockedFloat(buffer, value.m_distance))
					return (out_error() << "Unable to parse light distance" << std::endl, false);					
				break;
			case WORD_ENERGY:
				if (!ParseBlockedFloat(buffer, value.m_energy))
					return (out_error() << "Unable to parse light energy" << std::endl, false);
				break;
			case WORD_FALLOFF_TYPE:
				if (!ParseBlockedString(buffer, value.m_fall_off_type))
					return (out_error() << "Unable to parse light fall off type" << std::endl, false);
				break;
			case WORD_LINEAR_ATTENUATION:
				if (!ParseBlockedFloat(buffer, value.m_linear_attenuation))
					return (out_error() << "Unable to parse light linear attenuation" << std::endl, false);
				break;
			case WORD_QUADRATIC_ATTENUATION:
				if (!ParseBlockedFloat(buffer, value.m_quadratic_attenuation))
					return (out_error() << "Unable to parse light quadratic attenuation" << std::endl, false);
				break;
			default:
				return (out_error() << System::string::Format(L"Unexpected keyword: %s",  word.Data()) << std::endl, false);
			}
		}
		return true;
	}

	bool Parser::ParseCamera(System::Buffer& buffer, CameraDesc& value)
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
	}

	bool Parser::LoadWorld(const System::string& path, WorldDesc& world)
	{
		System::Buffer buffer;
		if (!System::BinaryFile::Load(path, buffer))
		{
			out_error() << (L"Unable to load file " + path).Data() << std::endl;
			return false;
		}

		return ParseWorld(buffer, world);				
	}
}