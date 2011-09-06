#include "../error.h"
#include "../../system/system.h"
#include "model.h"
#include "static_mesh.h"

#define CHECK_START(buffer)\
	if (!CheckIntegrity(buffer))\
		{\
		System::Logger::GetInstance()->WriteError(L"Integrity check failed", LOG_LOCATION);\
		}

#define CHECK_END(buffer)\
	if (Parse(buffer.ReadWord()) != WORD_CLOSE_BRACKET)\
		{\
		System::Logger::GetInstance()->WriteError(L"Integrity check failed", LOG_LOCATION);\
		}

namespace Utility
{

	StaticMesh* Model::CookStaticMesh()
	{
		StaticMesh* mesh = new StaticMesh;
		mesh->m_index_count = m_faces.size()*3;
		mesh->m_index = new unsigned[mesh->m_index_count];
		for (unsigned i = 0; i < m_faces.size()*3; i++)
		{
			mesh->m_index[i] = i;
		}

		mesh->m_vertex_count = m_faces.size()*3;
		VertexPositionNormalTextureTangentBitangentBone* vb;
		mesh->m_vb = vb = new VertexPositionNormalTextureTangentBitangentBone[mesh->m_vertex_count];
		memset(vb, 0, sizeof(VertexPositionNormalTextureTangentBitangentBone)*mesh->m_vertex_count);

		int index = 0;
		for (unsigned i = 0; i < m_tex_coords.size(); i++)
		{
			const Math::ivec3& f = m_faces[i];
			const Math::vec3& v1 = m_vertices[f[0]];
			const Math::vec3& v2 = m_vertices[f[1]];
			const Math::vec3& v3 = m_vertices[f[2]];
			const Math::vec2& t1 = m_tex_coords[i][0];
			const Math::vec2& t2 = m_tex_coords[i][1];
			const Math::vec2& t3 = m_tex_coords[i][2];
			const Math::vec3& n1 = m_normals[f[0]];
			const Math::vec3& n2 = m_normals[f[1]];
			const Math::vec3& n3 = m_normals[f[2]];

			Math::vec3 tgn;
			Math::vec3 nrm;
			Math::vec3 btn;
			float det;

			Math::CalculateTBN(v1, v2, v3, t1, t2, t3, tgn, btn, nrm, det);

			det = (det < 0) ? -1.0f : 1.0f;

			vb[index].x = v1[0];	vb[index].y = v1[1];	vb[index].z = v1[2];	vb[index].w = 1.0f;
			vb[index].nx = nrm[0];	vb[index].ny = nrm[1];	vb[index].nz = nrm[2];	vb[index].nw = 1.0f;
			//vb[index].nx = n1[0];	vb[index].ny = n1[1];	vb[index].nz = n1[2];	vb[index].nw = 1.0f;
			vb[index].u = t1[0];	vb[index].v = t1[1];	vb[index].s = 0;		vb[index].q = 0.0f;
			vb[index].tx = tgn[0];	vb[index].ty = tgn[1];	vb[index].tz = tgn[2];	vb[index].tw = det;
			vb[index].bx = btn[0];	vb[index].by = btn[1];	vb[index].bz = btn[2];	vb[index].bw = 0;
			index++;

			Math::CalculateTBN(v2, v3, v1, t2, t3, t1, tgn, btn, nrm, det);
			vb[index].x = v2[0];	vb[index].y = v2[1];	vb[index].z = v2[2];	vb[index].w = 1.0f;
			vb[index].nx = nrm[0];	vb[index].ny = nrm[1];	vb[index].nz = nrm[2];	vb[index].nw = 1.0f;
			//vb[index].nx = n2[0];	vb[index].ny = n2[1];	vb[index].nz = n2[2];	vb[index].nw = 1.0f;
			vb[index].u = t2[0];	vb[index].v = t2[1];	vb[index].s = 0;		vb[index].q = 0.0f;
			vb[index].tx = tgn[0];	vb[index].ty = tgn[1];	vb[index].tz = tgn[2];	vb[index].tw = det;
			vb[index].bx = btn[0];	vb[index].by = btn[1];	vb[index].bz = btn[2];	vb[index].bw = 0;
			index++;

			Math::CalculateTBN(v3, v1, v2, t3, t1, t2, tgn, btn, nrm, det);
			vb[index].x = v3[0];	vb[index].y = v3[1];	vb[index].z = v3[2];	vb[index].w = 1.0f;
			vb[index].nx = nrm[0];	vb[index].ny = nrm[1];	vb[index].nz = nrm[2];	vb[index].nw = 1.0f;
			//vb[index].nx = n3[0];	vb[index].ny = n3[1];	vb[index].nz = n3[2];	vb[index].nw = 1.0f;
			vb[index].u = t3[0];	vb[index].v = t3[1];	vb[index].s = 0;		vb[index].q = 0.0f;
			vb[index].tx = tgn[0];	vb[index].ty = tgn[1];	vb[index].tz = tgn[2];	vb[index].tw = det;
			vb[index].bx = btn[0];	vb[index].by = btn[1];	vb[index].bz = btn[2];	vb[index].bw = 0;
			index++;
		}

		mesh->m_vertex_buffer_size = sizeof(VertexPositionNormalTextureTangentBitangentBone)*mesh->m_vertex_count;
		mesh->m_vertex_component = COMPONENT_POSITION|COMPONENT_NORMAL|COMPONENT_TEXTURE|COMPONENT_BITANGENT|COMPONENT_TANGENT|COMPONENT_BONE;
		mesh->m_one_vertex_size = sizeof(VertexPositionNormalTextureTangentBitangentBone);
		return mesh;
	}

	Model::KeywordCode Model::Parse(System::string& word)
	{
		for (int i = 0; i < sizeof(Keyword)/sizeof(void*); i++)
		{
			if (word == Keyword[i])
				return static_cast<KeywordCode>(i);
		}	
		System::Logger::GetInstance()->WriteError(System::string::Format(L"Unknown keyword %s", word.Data()), LOG_LOCATION);		
		throw UtilityError(L"Unable to parse model file");
	}

	bool Model::CheckIntegrity(System::Buffer& buffer)
	{
		if (Parse(buffer.ReadWord()) != WORD_OPEN_BRACKET)
			return false;
		return true;
	}

	void Model::LoadPunkModel(System::string &filename)
	{
		System::Buffer buffer;
		if (!System::BinaryFile::Load(filename, buffer))
			throw UtilityError((L"Unable to load file " + filename).Data());

		while (!buffer.IsEnd())
		{
			switch(Parse(buffer.ReadWord()))
			{
			case WORD_OBJECT:
				ParseObject(buffer);
				break;
			}
		}
	}

	void Model::ParseObject(System::Buffer &buffer)
	{
		CHECK_START(buffer);

		while (1)
		{
			if (buffer.IsEnd())
			{
				System::Logger::GetInstance()->WriteError(L"Can't parse object", LOG_LOCATION);
				return;
			}

			int index;
			switch(index = Parse(buffer.ReadWord()))
			{
			case WORD_CLOSE_BRACKET:
				return;
			case WORD_NAME:
				ParseObjectName(buffer);
				break;
			case WORD_BOUNDING_BOX:
				ParseObjectBoundingBox(buffer);
				break;
			case WORD_LOCATION:
				ParseObjectLocation(buffer);
				break;
			case WORD_WORLD_MATRIX:
				ParseObjectWorldMatrix(buffer);
				break;
			case WORD_LOCAL_MATRIX:
				ParseObjectLocalMatrix(buffer);
				break;
			case WORD_MESH:
				ParseObjectMesh(buffer);
				break;
			case WORD_BONES_WEIGHT:
				ParseBonesWeights(buffer);
				break;
			case WORD_BONES:
				ParseBones(buffer);
				break;
			case WORD_SKELETON_ANIMATION:
				ParseSkeletoneAnimation(buffer);
				break;
			case WORD_MATERIALS:
				ParseMaterials(buffer);
				break;
			default:
				System::Logger::GetInstance()->WriteError(System::string::Format(L"Unexpected keyword %s", Keyword[index]), LOG_LOCATION);
			}
		}
	}



	void Model::ParseObjectMesh(System::Buffer& buffer)
	{
		CHECK_START(buffer);

		while (1)
		{
			if (buffer.IsEnd())
			{
				System::Logger::GetInstance()->WriteError(L"Can't parse object", LOG_LOCATION);
				return;
			}

			switch(int index = Parse(buffer.ReadWord()))
			{
			case WORD_CLOSE_BRACKET:
				return;
			case WORD_VERTEX_POSITION:
				ParseVertexPosition(buffer);					
				break;					
			case WORD_NORMALS:
				ParseNormals(buffer);
				break;
			case WORD_FACES:
				ParseFaces(buffer);
				break;
			case WORD_TEXTURE_COORD:
				ParseTextureCoords(buffer);
				break;
			case WORD_MATERIAL:
				ParseMeshMaterial(buffer);
				break;
			default:
				System::Logger::GetInstance()->WriteError(System::string::Format(L"Unexpected keyword %s", Keyword[index]), LOG_LOCATION);
			}
		}
	}

	void Model::ParseTextureCoords(System::Buffer& buffer)
	{
		CHECK_START(buffer);
		while (1)
		{
			System::string word = buffer.ReadWord();

			if (word == Keyword[WORD_CLOSE_BRACKET])
				return;
			float u1 = word.ToFloat();
			float v1 = buffer.ReadWord().ToFloat();
			float u2 = buffer.ReadWord().ToFloat();
			float v2 = buffer.ReadWord().ToFloat();
			float u3 = buffer.ReadWord().ToFloat();
			float v3 = buffer.ReadWord().ToFloat();
			float u4 = buffer.ReadWord().ToFloat();
			float v4 = buffer.ReadWord().ToFloat();

			std::vector<Math::vec2> coords;
			coords.push_back(Math::vec2(u1, v1));
			coords.push_back(Math::vec2(u2, v2));
			coords.push_back(Math::vec2(u3, v3));
			coords.push_back(Math::vec2(u4, v4));

			m_tex_coords.push_back(coords);
		}
	}

	void Model::ParseObjectName(System::Buffer &buffer)
	{
		CHECK_START(buffer);

		m_name = buffer.ReadWord();

		CHECK_END(buffer);
	}

	void Model::ParseObjectBoundingBox(System::Buffer &buffer)
	{
		CHECK_START(buffer);

		for (int i = 0; i < 8; i++)
		{
			m_bbox[i].X() = buffer.ReadWord().ToFloat();
			m_bbox[i].Y() = buffer.ReadWord().ToFloat();
			m_bbox[i].Z() = buffer.ReadWord().ToFloat();
		}

		CHECK_END(buffer);
	}

	void Model::ParseObjectLocation(System::Buffer &buffer)
	{
		CHECK_START(buffer);

		for (int i = 0; i < 3; i++)
			buffer.ReadWord();

		CHECK_END(buffer);
	}

	void Model::ParseObjectWorldMatrix(System::Buffer &buffer)
	{
		CHECK_START(buffer);
		for (int i = 0; i < 16; i++)
			buffer.ReadWord();
		CHECK_END(buffer);
	}

	void Model::ParseObjectLocalMatrix(System::Buffer &buffer)
	{
		CHECK_START(buffer);
		for (int i = 0; i < 16; i++)
			buffer.ReadWord();
		CHECK_END(buffer);
	}

	void Model::ParseVertexPosition(System::Buffer &buffer)
	{
		CHECK_START(buffer);
		int count = buffer.ReadWord().ToInt32();
		for (int i = 0; i < count; i++)
		{
			buffer.ReadWord();
			float x = buffer.ReadWord().ToFloat();
			float y = buffer.ReadWord().ToFloat();
			float z = buffer.ReadWord().ToFloat();
			m_vertices.push_back(Math::vec3(x,y,z));
		}
		CHECK_END(buffer);
	}

	void Model::ParseNormals(System::Buffer &buffer)
	{
		CHECK_START(buffer);
		int count = buffer.ReadWord().ToInt32();
		for (int i = 0; i < count; i++)
		{
			buffer.ReadWord();
			float x = buffer.ReadWord().ToFloat();
			float y = buffer.ReadWord().ToFloat();
			float z = buffer.ReadWord().ToFloat();
			m_normals.push_back(Math::vec3(x,y,z));
		}
		CHECK_END(buffer);
	}

	void Model::ParseFaces(System::Buffer& buffer)
	{
		CHECK_START(buffer);
		int count = buffer.ReadWord().ToInt32();
		m_faces.resize(count);

		while(1)
		{
			int index;
			switch(index = Parse(buffer.ReadWord()))
			{
			case WORD_CLOSE_BRACKET:
				return;
			case WORD_VERTEX_POSITIONS_ID:
				ParseFaceVertexID(buffer);
				break;
			}
		}
	}

	void Model::ParseFaceVertexID(System::Buffer &buffer)
	{
		CHECK_START(buffer);
		for (int i = 0; i < (int)m_faces.size(); i++)
		{
			buffer.ReadWord();	//skip index
			m_faces[i].X() = buffer.ReadWord().ToInt32();
			m_faces[i].Y() = buffer.ReadWord().ToInt32();
			m_faces[i].Z() = buffer.ReadWord().ToInt32();
		}
		CHECK_END(buffer);
	}

	void Model::ParseBonesWeights(System::Buffer& buffer)
	{
		CHECK_START(buffer);

		while (1)
		{
			System::string word = buffer.ReadWord();
			if (word == Keyword[WORD_CLOSE_BRACKET])
				return;
			int vertex_id = word.ToInt32();
			System::string bone_name = buffer.ReadWord();
			float weight = buffer.ReadWord().ToFloat();
			m_bone_weights[vertex_id][bone_name] = weight;
		}
	}

	void Model::ParseBones(System::Buffer &buffer)
	{
		CHECK_START(buffer);

		int count = buffer.ReadWord().ToInt32();
		for (int i = 0; i < count; i++)
		{
			if (Parse(buffer.ReadWord()) != WORD_BONE)
				return;
			ParseBone(buffer);
		}
		CHECK_END(buffer);
	}

	System::string Model::ParseBoneName(System::Buffer& buffer)
	{
		CHECK_START(buffer);
		System::string res = buffer.ReadWord();
		CHECK_END(buffer);
		return res;
	}

	Math::mat4 Model::ParseBoneLocalMatrix(System::Buffer &buffer)
	{
		CHECK_START(buffer);
		Math::mat4 res;
		for (int i = 0; i < 16; i++)
		{
			res[i] = buffer.ReadWord().ToFloat();
		}
		CHECK_END(buffer);
		return res;
	}

	void Model::ParseBone(System::Buffer& buffer)
	{
		CHECK_START(buffer);

		System::string name, parent;

		while (1)
		{
			switch(int code = Parse(buffer.ReadWord()))
			{
			case WORD_CLOSE_BRACKET:
				return;
			case WORD_NAME:
				name = ParseBoneName(buffer);				
				break;
			case WORD_PARENT:
				m_skeleton[name].m_parent = ParseBoneName(buffer);
				break;
			case WORD_LOCAL_MATRIX:
				m_skeleton[name].m_matrix = ParseBoneLocalMatrix(buffer);
				break;
			default:
				System::Logger::GetInstance()->WriteError(System::string::Format(L"Unexpected keyword %s", Keyword[code]), LOG_LOCATION);
			}
		}
	}

	void Model::ParseSkeletoneAnimation(System::Buffer& buffer)
	{
		System::string animation_name;
		while (1)
		{
			switch(int code = Parse(buffer.ReadWord()))
			{
			case WORD_OPEN_BRACKET:
				animation_name = buffer.ReadWord();
				m_skeleton_animation[animation_name].m_start_frame = buffer.ReadWord().ToInt32();
				m_skeleton_animation[animation_name].m_end_frame = buffer.ReadWord().ToInt32();
				break;
			case WORD_CLOSE_BRACKET:
				return;
			case WORD_BONE:
				ParseBoneAnimation(buffer, m_skeleton_animation[animation_name]);
				break;
			default:
				System::Logger::GetInstance()->WriteError(System::string::Format(L"Unexpected keyword %s", Keyword[code]), LOG_LOCATION);
			}
		}
	}

	void Model::ParseBoneAnimation(System::Buffer& buffer, Action& action)
	{
		CHECK_START(buffer);

		System::string bone_name;
		while (1)
		{
			switch(KeywordCode code = Parse(buffer.ReadWord()))
			{
			case WORD_CLOSE_BRACKET:
				return;
			case WORD_NAME:
				bone_name = ParseBoneName(buffer);
				break;
			case WORD_POS_X:
			case WORD_POS_Y:
			case WORD_POS_Z:
			case WORD_ROT_W:
			case WORD_ROT_X:
			case WORD_ROT_Y:
			case WORD_ROT_Z:
				ParseBoneAnimationValues(buffer, action, bone_name, code);
				break;
			}
		}
	}

	void Model::ParseBoneAnimationValues(System::Buffer& buffer, Action& action, System::string& name, KeywordCode code)
	{
		CHECK_START(buffer);

		while (1)
		{
			System::string s = buffer.ReadWord();
			if (s == L"}")
				return;

			switch(code)
			{
			case WORD_CLOSE_BRACKET:
				return;
			case WORD_POS_X:
				{
					int frame = s.ToInt32();
					float x = buffer.ReadWord().ToFloat();
					action.m_pose[name][frame].m_position[0] = x;
				}
				break;
			case WORD_POS_Y:
				{
					int frame = s.ToInt32();
					float x = buffer.ReadWord().ToFloat();
					action.m_pose[name][frame].m_position[1] = x;
				}
				break;
			case WORD_POS_Z:
				{
					int frame = s.ToInt32();
					float x = buffer.ReadWord().ToFloat();
					action.m_pose[name][frame].m_position[2] = x;
				}
				break;
			case WORD_ROT_W:
				{
					int frame = s.ToInt32();
					float x = buffer.ReadWord().ToFloat();
					action.m_pose[name][frame].m_rotation.W() = x;
				}
				break;
			case WORD_ROT_X:
				{
					int frame = s.ToInt32();
					float x = buffer.ReadWord().ToFloat();
					action.m_pose[name][frame].m_rotation.X() = x;
				}
				break;
			case WORD_ROT_Y:
				{
					int frame = s.ToInt32();
					float x = buffer.ReadWord().ToFloat();
					action.m_pose[name][frame].m_rotation.Y() = x;
				}
				break;
			case WORD_ROT_Z:
				{
					int frame = s.ToInt32();
					float x = buffer.ReadWord().ToFloat();
					action.m_pose[name][frame].m_rotation.Z() = x;
				}
				break;
			}
		}
	}

	void Model::ParseMeshMaterial(System::Buffer& buffer)
	{
		CHECK_START(buffer);
		m_material = buffer.ReadWord();
		CHECK_END(buffer);
	}

	System::string Model::ParseMaterialsName(System::Buffer &buffer)
	{		
		CHECK_START(buffer);
		System::string name = buffer.ReadWord();	
		CHECK_END(buffer);
		return name;
	}

	void Model::ParseMaterialsDiffuseMap(System::Buffer& buffer, const System::string& name)
	{
		CHECK_START(buffer);
		m_materials[name].diffuse_map = buffer.ReadWord();
		CHECK_END(buffer);
	}

	void Model::ParseMaterialsNormalMap(System::Buffer& buffer, const System::string& name)
	{
		CHECK_START(buffer);
		m_materials[name].normal_map = buffer.ReadWord();
		CHECK_END(buffer);
	}

	void Model::ParseMaterials(System::Buffer &buffer)
	{
		CHECK_START(buffer);
		System::string name;
		while (1)
		{
			switch(KeywordCode code = Parse(buffer.ReadWord()))
			{
			case WORD_CLOSE_BRACKET:
				return;
			case WORD_NAME:
				name = ParseMaterialsName(buffer);
				break;
			case WORD_NORMAL_MAP:
				ParseMaterialsNormalMap(buffer, name);
				break;
			case WORD_DIFFUSE_MAP:
				ParseMaterialsDiffuseMap(buffer, name);
				break;
			default:
				System::Logger::GetInstance()->WriteError(System::string::Format(L"Unexpected keyword %s", Keyword[code]), LOG_LOCATION);
			}
		}
	}
}