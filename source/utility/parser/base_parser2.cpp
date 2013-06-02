#include "base_parser2.h"
#include "keywords.h"
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
		throw System::PunkInvalidArgumentException(L"Integrity check failed");\
		}

#define CHECK_END(buffer)\
	if (Parse(buffer.ReadWord()) != WORD_CLOSE_BRACKET)\
		{\
		throw System::PunkInvalidArgumentException(L"Integrity check failed");\
		}

namespace Utility
{
	//extern System::Object* LoadWorld(const System::string& path);
	//extern System::Object* ParseAnything(System::Buffer& buffer);
	extern bool ParseTextures(System::Buffer& buffer, std::map<System::string, std::vector<Math::Vector4<Math::vec2>>>& value);		
	extern bool ParseBonesWeights(System::Buffer& buffer, std::map<int, std::map<System::string, float>>& value);
	extern bool ParseWorld(System::Buffer& buffer, Scene::SceneGraph* scene);
	extern bool ParseLocationIndoor(System::Buffer& buffer, Scene::LocationIndoorNode* location);
	extern bool ParsePortalNode(System::Buffer& buffer, Scene::PortalNode* node);
	extern bool ParseTransformNode(System::Buffer& buffer, Scene::TransformNode* transform);
	extern bool ParseMaterialNode(System::Buffer& buffer, Scene::MaterialNode* material);
	extern bool ParsePointLightNode(System::Buffer& buffer, Scene::PointLightNode* value);
	extern bool ParseMaterials(System::Buffer& buffer, Scene::SceneGraph* scene);
	extern bool ParseMaterial(System::Buffer& buffer, Virtual::Material* mat);
	extern bool ParseStaticMeshes(System::Buffer& buffer);
	extern bool ParseStaticMesh(System::Buffer& buffer, Virtual::StaticGeometry* geometry);
	extern bool ParseStaticMeshNode(System::Buffer& buffer, Scene::StaticMeshNode* static_node);
	extern bool ParseSkinMeshes(System::Buffer& buffer);
	extern bool ParseSkinMesh(System::Buffer& buffer, Virtual::SkinGeometry* geometry);
	extern bool ParseSkinMeshNode(System::Buffer& buffer, Scene::SkinMeshNode* skin_node);
	extern bool ParseBone(System::Buffer& buffer, Virtual::Bone* bone);
	extern bool ParseArmature(System::Buffer& buffer, Virtual::Armature* armature);
	extern bool ParseArmatures(System::Buffer& buffer);
	extern bool ParseArmatureNode(System::Buffer& buffer, Scene::ArmatureNode* armature_node);
	extern bool ParseActions(System::Buffer& buffer);
	extern bool ParseAction(System::Buffer& buffer, Virtual::Action* action);
	extern bool ParseAnimation(System::Buffer& buffer, Virtual::Animation* animation);
	extern bool ParsePositionTrack(System::Buffer& buffer, Virtual::AnimationTrack<Math::vec3>& track);
	extern bool ParseRotationTrack(System::Buffer& buffer, Virtual::AnimationTrack<Math::quat>& track);
	extern bool ParseBoneNode(System::Buffer& buffer, Scene::BoneNode* node);
	extern bool ParseMapDescription(System::Buffer& buffer, Virtual::Terrain* terrain);

	/// This function convert a string representation of the file into code
	KeywordCode Parse(const System::string& word)
	{
        for (unsigned i = 0; i < sizeof(Keyword)/sizeof(Record); i++)
		{
			if (word == Keyword[i].word)
				return Keyword[i].code;
		}	
        throw System::PunkInvalidArgumentException(System::string("Unknown keyword {0}").arg(word));
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
				throw System::PunkInvalidArgumentException(L"Unable to parse bounding box");
		if (!value.Create(reinterpret_cast<const float*>(p), 8, sizeof(Math::vec3)))
			throw System::PunkInvalidArgumentException(L"Unable to make bounding box from points");
		CHECK_END(buffer);
		return true;
	}

	bool ParseBlockedString(System::Buffer& buffer, System::string& value)
	{
		CHECK_START(buffer);
		if (!ParseString(buffer, value))
			throw System::PunkInvalidArgumentException(L"Unable to parse blocked string");
		CHECK_END(buffer);
		return true;
	}

	bool ParseBlockedFloat(System::Buffer& buffer, float& value)
	{
		CHECK_START(buffer);
		if (!ParseFloat(buffer, value))
			throw System::PunkInvalidArgumentException(L"Unable to parse blocked float number");
		CHECK_END(buffer);
		return true;
	}

	bool ParseBlockedInteger(System::Buffer& buffer, int& value)
	{
		CHECK_START(buffer);
		if (!ParseInteger(buffer, value))
			throw System::PunkInvalidArgumentException(L"Unable to parse blocked float number");
		CHECK_END(buffer);
		return true;
	}

	bool ParseBlockedVector3f(System::Buffer& buffer, Math::vec3& value)
	{
		CHECK_START(buffer);
		if (!ParseVector3f(buffer, value))
			throw System::PunkInvalidArgumentException(L"Unable to parse blocked vec3f");
		CHECK_END(buffer);
		return true;
	}

	bool ParseBlockedVector2i(System::Buffer& buffer, Math::ivec2& value)
	{
		CHECK_START(buffer);
		if (!ParseVector2i(buffer, value))
			throw System::PunkInvalidArgumentException(L"Unable to parse blocked vec3f");
		CHECK_END(buffer);
		return true;
	}

	bool ParseBlockedVector2f(System::Buffer& buffer, Math::vec2& value)
	{
		CHECK_START(buffer);
		if (!ParseVector2f(buffer, value))
			throw System::PunkInvalidArgumentException(L"Unable to parse blocked vec3f");
		CHECK_END(buffer);
		return true;
	}

	bool ParseBlockedMatrix4x4f(System::Buffer& buffer, Math::mat4& value)
	{
		CHECK_START(buffer);
		if (!ParseMatrix4x4f(buffer, value))
			throw System::PunkInvalidArgumentException(L"Unable to parse mat4f");
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
		throw System::PunkInvalidArgumentException(L"Unable to parse array ov vec3f");
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
		throw System::PunkInvalidArgumentException(L"Unable to parse vector of vec3i");
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
		throw System::PunkInvalidArgumentException(L"Unable to parse vector of vec4i");
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
		throw System::PunkInvalidArgumentException(L"Unable to parse vector of vec4<vec2f>");
	}

	bool ParseConvexMesh(System::Buffer& buffer, Math::ConvexShapeMesh& mesh)
	{
		CHECK_START(buffer);

		while (1)
		{
			if (buffer.IsEnd())
				throw System::PunkInvalidArgumentException(L"Can't parse convex mesh");

			System::string s = buffer.ReadWord();
			KeywordCode index = Parse(s);
			switch (index)
			{
			case WORD_CLOSE_BRACKET:
				return true;
			case WORD_VERTEX_POSITION:
				{
					Math::ConvexShapeMesh::PointsCollection p;
					ParseVector3fv(buffer, p);
					mesh.SetPoints(p);
				}
				break;
			case WORD_FACES:
				{
					Math::ConvexShapeMesh::FacesCollection f;
					ParseVector3iv(buffer, f);
					mesh.SetFaces(f);
				}
				break;
			case WORD_FACE_NORMALS:
				{
					Math::ConvexShapeMesh::NormalsCollection n;
					ParseVector3fv(buffer, n);
					mesh.SetNormals(n);
				}
				break;
			default:
				throw System::PunkInvalidArgumentException(L"Unexpected word " + s);
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
		throw System::PunkInvalidArgumentException(L"Unable to parse vertex bones weights");
	}

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
		throw System::PunkInvalidArgumentException(L"Unable to parse position track");
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
		throw System::PunkInvalidArgumentException(L"Unable to parse rotation track");
	}

	bool ParseAnimation(System::Buffer& buffer, Virtual::Animation* animation)
	{
		CHECK_START(buffer);

		System::string name;

		while (1)
		{
			if (buffer.IsEnd())
			{
				throw System::PunkInvalidArgumentException(L"Can't parse object");				
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
					ParseBlockedString(buffer, name);
					animation->SetName(name);
					animation->SetStorageName(name);
				}
				break;
			case WORD_POSITION_TRACK:
				{
					Virtual::AnimationTrack<Math::vec3> track;
					ParsePositionTrack(buffer, track);
					animation->SetPositionTrack(track);
				}
				break;
			case WORD_ROTATION_TRACK:
				{
					Virtual::AnimationTrack<Math::quat> track;
					ParseRotationTrack(buffer, track);
					animation->SetRotationTrack(track);
				}
				break;
			default:
				throw System::PunkInvalidArgumentException(L"Unexpected keyword " + word);
			}
		}
		return false;
	}

	bool ParseAction(System::Buffer& buffer, Virtual::Action* action)
	{
		CHECK_START(buffer);

		System::string name;

		while (1)
		{
			if (buffer.IsEnd())
				throw System::PunkInvalidArgumentException(L"Can't parse action");

			const System::string word = buffer.ReadWord();
			KeywordCode index;				
			switch(index = Parse(word))
			{
			case WORD_CLOSE_BRACKET:
				return true;
			case WORD_NAME:
				{
					System::string value;
					ParseBlockedString(buffer, value);
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
						throw System::PunkInvalidArgumentException(L"Can't parse action timing");
				}
				break;
			case WORD_BONE_ANIMATION:
				{
					std::unique_ptr<Virtual::Animation> animation(new Virtual::Animation);
					ParseAnimation(buffer, animation.get());						
					action->Add(animation.release());
				}
				break;
			case WORD_OBJECT_ANIMATION:
				{
					std::unique_ptr<Virtual::Animation> animation(new Virtual::Animation);
					ParseAnimation(buffer, animation.get());
					action->Add(animation.release());
				}
				break;
			default:
				throw System::PunkInvalidArgumentException(L"Unexpected keyword " + word);
			}
		}
	}

	bool ParseActions(System::Buffer& buffer)
	{
		CHECK_START(buffer);

		while (1)
		{
			if (buffer.IsEnd())
				throw System::PunkInvalidArgumentException(L"Can't parse object");

			System::string word = buffer.ReadWord();
			KeywordCode index;
			switch(index = Parse(word))
			{
			case WORD_CLOSE_BRACKET:
				return true;
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
				throw System::PunkInvalidArgumentException(L"Can't parse object");

			System::string word = buffer.ReadWord();
			KeywordCode index;
			switch(index = Parse(word))
			{
			case WORD_CLOSE_BRACKET:
				return true;
			case WORD_STATIC_MESH:
				{	
					std::unique_ptr<Virtual::StaticGeometry> mesh(new Virtual::StaticGeometry);
					ParseStaticMesh(buffer, mesh.get());
					Virtual::StaticGeometry::add(mesh->GetStorageName(), mesh.get());
					mesh.release();
				}
				break;
			default:
				throw System::PunkInvalidArgumentException(L"Unexpected keyword " + word);
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
	bool ParseArmature(System::Buffer& buffer, Virtual::Armature* armature)
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
		while (1)
		{
			System::string word = buffer.ReadWord();
            KeywordCode code = Parse(word);
            switch(code)
			{
			case WORD_CLOSE_BRACKET:
				return true;
			case WORD_ARMATURE:
				{
					std::unique_ptr<Virtual::Armature> armature(new Virtual::Armature);					
					ParseArmature(buffer, armature.get());
					Virtual::Armature::add(armature->GetStorageName(), armature.get());
					armature.release();
				}
				break;
			default:
				throw System::PunkInvalidArgumentException(L"Unexpected keyword " + word);
			}
		}
		return false;
	}

	bool ParseTextures(System::Buffer& buffer, std::map<System::string, std::vector<Math::Vector4<Math::vec2>>>& value)
	{
		CHECK_START(buffer);

		System::string name;

		while (1)
		{
			if (buffer.IsEnd())
				throw System::PunkInvalidArgumentException(L"Can't parse object");

			System::string s = buffer.ReadWord();			

			switch(KeywordCode index = Parse(s))
			{
			case WORD_CLOSE_BRACKET:
				return true;
			case WORD_NAME:
				{		
					ParseBlockedString(buffer, name);
				}
				break;
			case WORD_TEXTURE_COORD:
				{
					ParseVector4Vector2iv(buffer, value[name]);
				}
				break;
			default:
                throw System::PunkInvalidArgumentException(System::string("Unexpected keyword {0}").arg(Keyword[index].word));
			}
		}
		return true;
	}

	bool ParseStaticMesh(System::Buffer& buffer, Virtual::StaticGeometry* geometry)
	{
		CHECK_START(buffer);
		while (1)
		{
			if (buffer.IsEnd())
				throw System::PunkInvalidArgumentException(L"Can't parse object");

			System::string word = buffer.ReadWord();

            KeywordCode code = Parse(word);
            switch(code)
			{
			case WORD_CLOSE_BRACKET:				
				return true;
			case WORD_NAME:
				{
					System::string name;
					ParseBlockedString(buffer, name);
					geometry->SetName(name);
					geometry->SetStorageName(name);
				}
				break;
			case WORD_VERTEX_POSITION:
				{
					Virtual::StaticGeometry::Vertices v;
					ParseVector3fv(buffer, v);
					geometry->SetVertices(v);
				}
				break;					
			case WORD_NORMALS:
				{
					Virtual::StaticGeometry::Normals n;
					ParseVector3fv(buffer, n);
					geometry->SetNormals(n);
				}
				break;
			case WORD_FACES:
				{
					Virtual::StaticGeometry::Faces f;
					ParseVector3iv(buffer, f);
					geometry->SetFaces(f);
				}
				break;
			case WORD_TEXTURE:
				{										
					Virtual::StaticGeometry::TextureMeshes t;
					ParseTextures(buffer, t);
					geometry->SetTextureMeshes(t);
				}
				break;
			case WORD_WORLD_MATRIX:
				{
					Math::mat4 m;
					ParseBlockedMatrix4x4f(buffer, m);
					geometry->SetWorldOffset(m);
				}
				break;
			default:
				throw System::PunkInvalidArgumentException(L"Unexpected keyword " + word);
			}
		}
	}

	bool ParseSkinMesh(System::Buffer& buffer, Virtual::SkinGeometry* geometry)
	{
		CHECK_START(buffer);
		while (1)
		{
			if (buffer.IsEnd())
				throw System::PunkInvalidArgumentException(L"Can't parse object");

			System::string word = buffer.ReadWord();

            KeywordCode code = Parse(word);
            switch(code)
			{
			case WORD_CLOSE_BRACKET:				
				return true;
			case WORD_NAME:
				{
					System::string name;
					ParseBlockedString(buffer, name);
					geometry->SetName(name);
					geometry->SetStorageName(name);
				}
				break;
			case WORD_VERTEX_POSITION:
				{
					Virtual::SkinGeometry::Vertices v;
					ParseVector3fv(buffer, v);
					geometry->SetVertices(v);
				}
				break;					
			case WORD_NORMALS:
				{
					Virtual::SkinGeometry::Normals n;
					ParseVector3fv(buffer, n);
					geometry->SetNormals(n);
				}
				break;
			case WORD_FACES:
				{
					Virtual::SkinGeometry::Faces f;
					ParseVector3iv(buffer, f);
					geometry->SetFaces(f);
				}
				break;
			case WORD_TEXTURE:
				{										
					Virtual::SkinGeometry::TextureMeshes t;
					ParseTextures(buffer, t);
					geometry->SetTextureMeshes(t);
				}
				break;
			case WORD_BONES_WEIGHT:
				{
					Virtual::SkinGeometry::BoneWeights b;
					ParseBonesWeights(buffer, b);
					geometry->SetBoneWeights(b);
				}
				break;
			case WORD_WORLD_MATRIX:
				{
					Math::mat4 m;
					ParseBlockedMatrix4x4f(buffer, m);
					geometry->SetWorldOffset(m);
				}
				break;
			default:
				throw System::PunkInvalidArgumentException(L"Unexpected keyword " + word);
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
            KeywordCode code = Parse(word);
            switch(code)
			{
			case WORD_CLOSE_BRACKET:
				return true;
			case WORD_SKIN_MESH:
				{
					std::unique_ptr<Virtual::SkinGeometry> mesh(new Virtual::SkinGeometry);
					ParseSkinMesh(buffer, mesh.get());
					Virtual::SkinGeometry::add(mesh->GetStorageName(), mesh.get());
					mesh.release();
				}
				break;
			default:
				throw System::PunkInvalidArgumentException(L"Unexpected keyword " + word);
			}
		}
		return false;
	}

	bool ParseMaterial(System::Buffer& buffer, Virtual::Material* mat)
	{
		CHECK_START(buffer);
		System::string name;
		while (1)
		{
			System::string word = buffer.ReadWord();
            KeywordCode code = Parse(word);
            switch(code)
			{
			case WORD_CLOSE_BRACKET:
				return true;
			case WORD_NAME:
				{
					System::string value;
					ParseBlockedString(buffer, value);
					mat->SetName(value);
					mat->SetStorageName(value);
				}
				break;
			case WORD_ALPHA:
				{
					float value;
					ParseBlockedFloat(buffer, value);
					mat->SetAlpha(value);
				}
				break;
			case WORD_AMBIENT:
				{
					float value;
					ParseBlockedFloat(buffer, value);
					mat->SetAmbient(value);
				}
				break;
			case WORD_DARKNESS:
				{
					float value;
					ParseBlockedFloat(buffer, value);
					mat->SetDarkness(value);
				}
				break;
			case WORD_DIFFUSE_COLOR:
				{
					Math::vec3 value;
					ParseBlockedVector3f(buffer, value);
					mat->SetDiffuseColor(Math::vec4(value, mat->GetAlpha()));
				}
				break;
			case WORD_DIFFUSE_FRESNEL:
				{
					float value;
					ParseBlockedFloat(buffer, value);
					mat->SetDiffuseFresnel(value);
				}
				break;
			case WORD_DIFFUSE_FRESNEL_FACTOR:				
				{
					float value;
					ParseBlockedFloat(buffer, value);
					mat->SetDiffuseFresnelFactor(value);
				}
				break;
			case WORD_DIFFUSE_INTENSITY:
				{
					float value;
					ParseBlockedFloat(buffer, value);
					mat->SetDiffuseIntensity(value);
				}
				break;
			case WORD_EMIT:
				{
					float value;
					ParseBlockedFloat(buffer, value);
					mat->SetEmit(value);
				}
				break;
			case WORD_MIRROR_COLOR:
				{
					Math::vec3 value;
					ParseBlockedVector3f(buffer, value);
					mat->SetMirrorColor(value);
				}
				break;
			case WORD_ROUGHNESS:
				{
					float value;
					ParseBlockedFloat(buffer, value);
					mat->SetRoughness(value);
				}
				break;
			case WORD_SPECULAR_ALPHA:
				{
					float value;
					ParseBlockedFloat(buffer, value);
					mat->SetSpecularAlpha(value);
				}
				break;
			case WORD_SPECULAR_COLOR:
				{
					Math::vec3 value;
					ParseBlockedVector3f(buffer, value);
					mat->SetSpecularColor(Math::vec4(value, mat->GetSpecularAlpha()));
				}
				break;
			case WORD_SPECULAR_HARDNESS:
				{
					float value;
					ParseBlockedFloat(buffer, value);
					mat->SetSpecularFactor(value);
				}
				break;
			case WORD_SPECULAR_INTENSITY:
				{
					float value;
					ParseBlockedFloat(buffer, value);
					mat->SetSpecularIntensity(value);
				}
				break;
			case WORD_SPECULAR_IOR:
				{
					float value;
					ParseBlockedFloat(buffer, value);
					mat->SetSpecularIndexOfRefraction(value);
				}
				break;
			case WORD_SPECULAR_SLOPE:
				{
					float value;
					ParseBlockedFloat(buffer, value);
					mat->SetSpecularSlope(value);
				}
				break;
			case WORD_TRANSLUCENCY:
				{
					float value;
					ParseBlockedFloat(buffer, value);
					mat->SetTranslucency(value);
				}
				break;
			case WORD_NORMAL_MAP:
				{
					System::string value;
					ParseBlockedString(buffer, value);
					mat->SetTexture1(value);
				}
				break;
			case WORD_DIFFUSE_MAP:
				{
					System::string value;
					ParseBlockedString(buffer, value);
					mat->SetTexture0(value);
				}
				break;
			default:
				throw System::PunkInvalidArgumentException(L"Unexpected keyword " + word);
			}
		}
		return false;
	}

    bool ParseMaterials(System::Buffer& buffer, Scene::SceneGraph*)
	{
		CHECK_START(buffer);
		System::string name;
		while (1)
		{
			System::string word = buffer.ReadWord();
            KeywordCode code = Parse(word);
            switch(code)
			{
			case WORD_CLOSE_BRACKET:
				return true;
			case WORD_MATERIAL:
				{
					std::unique_ptr<Virtual::Material> m(new Virtual::Material);					
					ParseMaterial(buffer, m.get());
					Virtual::Material::add(m->GetStorageName(), m.get());
					m.release();
				}
				break;
			default:
				throw System::PunkInvalidArgumentException(L"Unexpected keyword " + word);
			}
		}
		return false;
	}

	bool ParsePointLightNode(System::Buffer& buffer, Scene::PointLightNode* value)
	{
		CHECK_START(buffer);
		std::unique_ptr<Virtual::PointLight> light(new Virtual::PointLight);
		while (!buffer.IsEnd())
		{
			System::string word = buffer.ReadWord();
			switch(Parse(word))
			{
			case WORD_CLOSE_BRACKET:
				value->SetPointLight(light.release());
				return true;
			case WORD_NAME:
				{
					System::string name;
					ParseBlockedString(buffer, name);
					value->SetName(name);
					value->SetStorageName(name);
				}
				break;
			case WORD_COLOR:
				{
					Math::vec3 color;
					ParseBlockedVector3f(buffer, color);
					light->SetColor(color);
				}
				break;
			case WORD_DISTANCE:
				{
					float dst;
					ParseBlockedFloat(buffer, dst);
					light->SetDistance(dst);
				}
				break;
			case WORD_ENERGY:
				{
					float energy;
					ParseBlockedFloat(buffer, energy);
					light->SetEnergy(energy);
				}
				break;
			case WORD_LINEAR_ATTENUATION:
				{
					float v;
					ParseBlockedFloat(buffer, v);
					light->SetLinearAttenuation(v);
				}
				break;
			case WORD_QUADRATIC_ATTENUATION:
				{
					float v;
					ParseBlockedFloat(buffer, v);
					light->SetQuadraticAttenuation(v);
				}
				break;
			default:
				throw System::PunkInvalidArgumentException(L"Unexpected keyword " + word);
			}
		}
		return true;
	}

	bool ParseStaticMeshNode(System::Buffer& buffer, Scene::StaticMeshNode* mesh)
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
					ParseBlockedString(buffer, value);
					mesh->SetName(value);
					mesh->SetStorageName(value);
				}
				break;
			default:
				throw System::PunkInvalidArgumentException(L"Unexpected keyword " + word);
			}
		}
		return false;
	}

	bool ParseBoneNode(System::Buffer& buffer, Scene::BoneNode* bone)
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
					ParseBlockedString(buffer, value);
					bone->SetName(value);
					bone->SetStorageName(value);
				}
				break;
			case WORD_TRANSFORM_NODE:
				{
					std::unique_ptr<Scene::TransformNode> node(new Scene::TransformNode);
					ParseTransformNode(buffer, node.get());
					bone->Add(node.release());
				}
				break;
			default:
				throw System::PunkInvalidArgumentException(L"Unexpected keyword " + word);
			}
		}
		return false;
	}

	bool ParseSkinMeshNode(System::Buffer& buffer, Scene::SkinMeshNode* mesh)
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
					ParseBlockedString(buffer, value);
					mesh->SetName(value);
					mesh->SetStorageName(value);
				}
				break;
			default:
				throw System::PunkInvalidArgumentException(L"Unexpected keyword " + word);
			}
		}
		return false;
	}

	bool ParseMaterialNode(System::Buffer& buffer, Scene::MaterialNode* material)
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
					ParseBlockedString(buffer, value);
					material->SetName(value);
					material->SetStorageName(value);
				}
				break;
			case WORD_STATIC_MESH_NODE:
				{
					std::unique_ptr<Scene::StaticMeshNode> node(new Scene::StaticMeshNode);
					ParseStaticMeshNode(buffer, node.get());
					material->Add(node.release());
				}
				break;
			case WORD_SKIN_MESH_NODE:
				{
					std::unique_ptr<Scene::SkinMeshNode> node(new Scene::SkinMeshNode);
					ParseSkinMeshNode(buffer, node.get());
					material->Add(node.release());
				}
				break;
			case WORD_TRANSFORM_NODE:
				{
					std::unique_ptr<Scene::TransformNode> node(new Scene::TransformNode);
					ParseTransformNode(buffer, node.get());
					material->Add(node.release());
				}
				break;
			case WORD_MATERIAL_NODE:
				{
					std::unique_ptr<Scene::MaterialNode> node(new Scene::MaterialNode);
					ParseMaterialNode(buffer, node.get());
					material->Add(node.release());
				}
				break;
			default:
				throw System::PunkInvalidArgumentException(L"Unexpected keyword " + word);
			}
		}
		return false;
	}

	bool ParseArmatureNode(System::Buffer& buffer, Scene::ArmatureNode* armature_node)
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
					ParseBlockedString(buffer, value);
					armature_node->SetName(value);
					armature_node->SetStorageName(value);
				}
				break;
			case WORD_MATERIAL_NODE:
				{
					std::unique_ptr<Scene::MaterialNode> node(new Scene::MaterialNode);
					ParseMaterialNode(buffer, node.get());
					armature_node->Add(node.release());
				}
				break;				
			case WORD_BONE_NODE:
				{
					std::unique_ptr<Scene::BoneNode> node(new Scene::BoneNode);
					ParseBoneNode(buffer, node.get());
					armature_node->Add(node.release());
				}
				break;
			default:
				throw System::PunkInvalidArgumentException(L"Unexpected keyword " + word);
			}
		}
		return false;
	}

	bool ParseTransformNode(System::Buffer& buffer, Scene::TransformNode* transform)
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
					ParseBlockedString(buffer, value);
					transform->SetName(value);
					transform->SetStorageName(value);
				}
				break;
			case WORD_LOCAL_MATRIX:
				{
					Math::mat4 m;
					ParseBlockedMatrix4x4f(buffer, m);
					transform->SetLocalMatrix(m);
				}
				break;
			case WORD_POINT_LIGHT:
				{
					std::unique_ptr<Scene::PointLightNode> node(new Scene::PointLightNode);
					ParsePointLightNode(buffer, node.get());
					transform->Add(node.release());
				}
				break;
			case WORD_STATIC_MESH_NODE:
				{
					std::unique_ptr<Scene::StaticMeshNode> node(new Scene::StaticMeshNode);
					ParseStaticMeshNode(buffer, node.get());
					transform->Add(node.release());
				}
				break;
			case WORD_SKIN_MESH_NODE:
				{
					std::unique_ptr<Scene::SkinMeshNode> node(new Scene::SkinMeshNode);
					ParseSkinMeshNode(buffer, node.get());
					transform->Add(node.release());
				}
				break;
			case WORD_ARMATURE_NODE:
				{
					std::unique_ptr<Scene::ArmatureNode> node(new Scene::ArmatureNode);
					ParseArmatureNode(buffer, node.get());
					transform->Add(node.release());
				}
				break;
			case WORD_MATERIAL_NODE:
				{
					std::unique_ptr<Scene::MaterialNode> node(new Scene::MaterialNode);
					ParseMaterialNode(buffer, node.get());
					transform->Add(node.release());
				}
				break;
			case WORD_TRANSFORM_NODE:
				{
					std::unique_ptr<Scene::TransformNode> node(new Scene::TransformNode);
					ParseTransformNode(buffer, node.get());
					transform->Add(node.release());
				}
				break;
			case WORD_LOCATION_INDOOR:
				{
					std::unique_ptr<Scene::LocationIndoorNode> node(new Scene::LocationIndoorNode);
					ParseLocationIndoor(buffer, node.get());
					transform->Add(node.release());
				}
				break;
			case WORD_BOUNDING_BOX:
				{
					Math::BoundingBox bbox;
					ParseBoundingBox(buffer, bbox);
					transform->SetBoundingBox(bbox);
				}
				break;
			default:
				throw System::PunkInvalidArgumentException(L"Unexpected keyword " + word);
			}
		}
		return false;
	}

	bool ParsePortalNode(System::Buffer& buffer, Scene::PortalNode* node)
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
					ParseBlockedString(buffer, name);
					node->SetName(name);
					node->SetStorageName(name);
				}
				break;
			case WORD_LOCAL_MATRIX:
				{
					Math::mat4 m;
					ParseBlockedMatrix4x4f(buffer, m);
					node->SetLocalMatrix(m);
				}
				break;
			case WORD_VERTEX_POSITION:
				{
					Math::Portal::PointsCollection p;
					ParseVector3fv(buffer, p);
					Math::Portal portal;
					portal.SetPoints(p);
					node->SetPortal(portal);
				}
				break;
			default:
				throw System::PunkInvalidArgumentException(L"Unexpected keyword " + word);
			}
		}
		return false;
	}

	bool ParseLocationIndoor(System::Buffer& buffer, Scene::LocationIndoorNode* location)
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
					ParseBlockedString(buffer, name);
					location->SetName(name);
					location->SetStorageName(name);
				}
			case WORD_LOCAL_MATRIX:
				{
					Math::mat4 m;
					ParseBlockedMatrix4x4f(buffer, m);
					location->SetLocalMatrix(m);
				}
				break;
			case WORD_CONVEX_MESH:
				{
					Math::ConvexShapeMesh mesh;
					ParseConvexMesh(buffer, mesh);
					location->SetConvexMesh(mesh);
				}
				break;
			case WORD_MATERIAL_NODE:
				{
					std::unique_ptr<Scene::MaterialNode> node(new Scene::MaterialNode);
					ParseMaterialNode(buffer, node.get());
					location->Add(node.release());
				}
				break;
			case WORD_TRANSFORM_NODE:
				{
					std::unique_ptr<Scene::TransformNode> node(new Scene::TransformNode);
					ParseTransformNode(buffer, node.get());
					location->Add(node.release());
				}
				break;
			case WORD_PORTAL_NODE:
				{
					std::unique_ptr<Scene::PortalNode> node(new Scene::PortalNode);
					ParsePortalNode(buffer, node.get());
					location->Add(node.release());
				}
				break;
			default:
				throw System::PunkInvalidArgumentException(L"Unexpected keyword " + word);
			}
		}
		return false;
	}

	bool ParseWorld(System::Buffer& buffer, Scene::SceneGraph* scene)
	{		
		std::unique_ptr<Scene::Node> root(new Scene::Node);		
		while (!buffer.IsEnd())
		{
			System::string word = buffer.ReadWord();
			switch(Parse(word))
			{
			case WORD_CLOSE_BRACKET:						
				scene->SetRootNode(root.release());	
				return true;
			case WORD_LOCATION_INDOOR:
				{
					std::unique_ptr<Scene::LocationIndoorNode> node(new Scene::LocationIndoorNode);
					ParseLocationIndoor(buffer, node.get());
					root->Add(node.release());
				}
				break;	
			case WORD_TRANSFORM_NODE:
				{
					std::unique_ptr<Scene::TransformNode> node(new Scene::TransformNode);
					ParseTransformNode(buffer, node.get());
					root->Add(node.release());
				}
				break;
			case WORD_MATERIAL_NODE:
				{
					std::unique_ptr<Scene::MaterialNode> node(new Scene::MaterialNode);
					ParseMaterialNode(buffer, node.get());
					root->Add(node.release());
				}
				break;
			case WORD_MATERIALS:
				{									
					ParseMaterials(buffer, scene);
				}
				break;
			case WORD_STATIC_MESHES:
				{
					ParseStaticMeshes(buffer);
				}
				break;
			case WORD_SKIN_MESHES:
				{
					ParseSkinMeshes(buffer);
				}
				break;
			case WORD_ACTIONS:
				{
					ParseActions(buffer);
				}
				break;
			case WORD_ARMATURES:
				{
					ParseArmatures(buffer);
				}
				break;
			default:
				throw System::PunkInvalidArgumentException(L"Unexpected keyword " + word);
			}
		}
		scene->SetRootNode(root.release());	
		return true;
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
					ParseBlockedString(buffer, value);
					source.SetRawFile(value);
				}
				break;
			default:
				throw System::PunkInvalidArgumentException(L"Unexpected keyword " + word);
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
					ParseBlockedString(buffer, value);
					cell.SetName(value);
				}
				break;
			case WORD_LOCATION:
				{
					Math::ivec2 value;
					ParseBlockedVector2i(buffer, value);
					cell.SetLocation(value);
				}
				break;
			case WORD_RAW_DATA_SOURCE:
				{
					Virtual::TerrainRawDataSource value;
					ParseTerrainRawDataSource(buffer, value);
					cell.SetRawDataSource(value);
				}
				break;
			default:
				throw System::PunkInvalidArgumentException(L"Unexpected keyword " + word);
			}
		}
		return false;
	}

	bool ParseMapDescription(System::Buffer& buffer, Virtual::Terrain* terrain)
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
					ParseBlockedInteger(buffer, value);
					terrain->SetNumBlocks(value);
				}
				break;
			case WORD_BLOCK_SCALE:
				{
					float value;
					ParseBlockedFloat(buffer, value);
					terrain->SetBlockScale(value);
				}
				break;
			case WORD_BLOCK_SIZE:
				{
					int value;
					ParseBlockedInteger(buffer, value);
					terrain->SetBlocksSize(value);
				}
				break;
			case WORD_HEIGHT_SCALE:
				{
					float value;
					ParseBlockedFloat(buffer, value);
					terrain->SetHeightScale(value);
				}
				break;
			case WORD_WORLD_ORIGIN:
				{
					Math::vec2 value;
					ParseBlockedVector2f(buffer, value);
					terrain->SetOrigin(value);
				}
				break;
			case WORD_CELL:
				{
					Virtual::TerrainCell value;
					ParseTerrainCell(buffer, value);
					value.Validate();
					terrain->AddOrUpdateCell(value);
				}
				break;
			default:
				throw System::PunkInvalidArgumentException(L"Unexpected keyword " + word);
			}
		}
		return true;
	}

	System::Object* ParseAnything(System::Buffer& buffer)
	{
		while (!buffer.IsEnd())
		{
			System::string word = buffer.ReadWord();
			KeywordCode code = Parse(word);
			switch(code)
			{
			case WORD_MAPDESCTEXT:
				{
					std::unique_ptr<Virtual::Terrain> terrain(new Virtual::Terrain);
					ParseMapDescription(buffer, terrain.get());
					return terrain.release();
				}
			case WORD_ARMATURETEXT:
				{
					System::string word = buffer.ReadWord();
					std::unique_ptr<Virtual::Armature> armature;
					if (word == L"male_armature")
					{
						armature.reset(new Virtual::HumanMaleArmature);
					}
					else
					{
						armature.reset(new Virtual::Armature);
					}
						
					ParseArmature(buffer, armature.get());
					Virtual::Armature::add(word, armature.get());
					return armature.release();
				}
			case WORD_ACTIONTEXT:
				{
					System::string word = buffer.ReadWord();
					std::unique_ptr<Virtual::Action> action;
					if (word == L"male_walk")					
						action.reset(new Virtual::ActionMaleWalk);
					else
						throw System::PunkInvalidArgumentException(L"Punk engine doesn't support " + word + L" action"); 
					ParseAction(buffer, action.get());
					Virtual::Action::add(word, action.get());
					return action.release();
				}
			case WORD_STATICMESHTEXT:
				{
					System::string word = buffer.ReadWord();
					std::unique_ptr<Virtual::StaticGeometry> mesh(new Virtual::StaticGeometry);
					ParseStaticMesh(buffer, mesh.get());
					Virtual::StaticGeometry::add(word, mesh.get());					
					mesh->SetName(word);
					mesh->SetStorageName(word);
					return mesh.release();
				}
				break;
			case WORD_MATERIALTEXT:
				{
					System::string word = buffer.ReadWord();
					std::unique_ptr<Virtual::Material> material(new Virtual::Material);
					ParseMaterial(buffer, material.get());
					Virtual::Material::add(word, material.get());
					return material.release();
				}
			default:
				throw System::PunkInvalidArgumentException(L"Unexpected keyword " + word);
			}
		}		
		throw System::PunkInvalidArgumentException(L"Can't parse something");
	}

	System::Object* ParsePunkFile(const System::string& path)
	{
		System::Buffer buffer;
		System::BinaryFile::Load(path, buffer);				
		return ParseAnything(buffer);
	}

	System::Object* LoadWorld(const System::string& path)
	{
		System::Buffer buffer;
		System::BinaryFile::Load(path, buffer);
		std::unique_ptr<Scene::SceneGraph> scene(new Scene::SceneGraph);
		ParseWorld(buffer, scene.get());
		scene->SetActiveCamera(new Virtual::Camera());
		return scene.release();
	}

}
