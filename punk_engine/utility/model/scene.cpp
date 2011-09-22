#include <assimp.hpp>      // C++ importer interface
#include <aiScene.h>       // Output data structure
#include <aiPostProcess.h> // Post processing flags

#include "../error.h"
#include "../../system/system.h"
#include "scene.h"
#include "static_mesh.h"
#include "skinned_mesh.h"
#include "skin_animation.h"
#include "bone.h"
#include <algorithm>

Assimp::Importer importer;

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

	void RawScene::OpenFile(const System::string& filename)
	{
		// And have it read the given file with some example postprocessing
		// Usually - if speed is not the most important aspect for you - you'll 
		// propably to request more postprocessing than we do in this example.
		char* buf;
		int size;
		filename.ToANSI(buf, size);
		const aiScene* scene = importer.ReadFile(buf, 
			aiProcess_CalcTangentSpace       | 
			aiProcess_Triangulate            |
			aiProcess_JoinIdenticalVertices  |
			aiProcess_SortByPType|
			aiProcess_LimitBoneWeights |
			aiProcess_ImproveCacheLocality |
			aiProcess_GenSmoothNormals
			);
		delete[] buf;

		// If the import failed, report it
		if( !scene)
		{
			return;
		}

		// Now we can access the file's contents. 		
		// We're done. Everything will be cleaned up by the importer destructor
		return;
	}

	const Material GetMaterial(const aiMaterial* raw_mat)
	{
		Material mat;
		aiString str;
		float value = 16.0f;
		aiColor4D color;
		raw_mat->GetTexture(aiTextureType_DIFFUSE, 0, &str);
		System::string s = System::string(str.data);		
		mat.SetDiffuseMap(s.Split(L"\\").back());

		raw_mat->GetTexture(aiTextureType_DIFFUSE, 1, &str);
		s = System::string(str.data);		
		mat.SetNormalMap(s.Split(L"\\").back());

		raw_mat->Get(AI_MATKEY_COLOR_DIFFUSE, color);
		mat.SetDiffuseColor(Math::vec4(color.r, color.g, color.b, color.a));

		raw_mat->Get(AI_MATKEY_COLOR_SPECULAR, color);
		mat.SetSpecularColor(Math::vec4(color.r, color.g, color.b, color.a));

		raw_mat->Get(AI_MATKEY_SHININESS_STRENGTH, value);
		mat.SetSpecularFactor(value);

		return mat;
	}

	Material RawScene::GetMaterial(const System::string& name) const
	{
		const aiScene* scene = importer.GetScene();
		if (!scene->HasMaterials())
			return Material();

		Material mat;
		for (int i = 0; i < scene->mNumMaterials; ++i)
		{			
			aiString str;
			aiColor4D color;
			float value;
			const aiMaterial* raw_mat = scene->mMaterials[i];			
			raw_mat->Get(AI_MATKEY_NAME, str);
			
			if (name != System::string(str.data))
				continue;		

			mat = ::Utility::GetMaterial(raw_mat);
			
		}

		return mat;
	}

	Material RawScene::GetMaterial(unsigned id) const
	{
		const aiScene* scene = importer.GetScene();
		if (!scene->HasMaterials())
			return Material();
		return ::Utility::GetMaterial(scene->mMaterials[id]);		
	}

	aiMesh* find_mesh(const System::string& name, aiNode* root)
	{
		if (!root)
			return 0;

		const aiScene* scene = importer.GetScene();

		if (System::string(root->mName.data) == name)
		{
			for (int i = 0; i < root->mNumMeshes; ++i)
			{	
				aiMesh* mesh = scene->mMeshes[root->mMeshes[i]];

				return mesh;
			}
		}

		for (int i = 0; i < root->mNumChildren; ++i)
		{
			aiMesh* m = find_mesh(name, root->mChildren[i]);
			if (m)
				return m;
		}	
		return 0;
	}

	StaticMesh* RawScene::CookStaticMesh(const System::string& name)
	{
		StaticMesh* res = 0;
		const aiScene* scene = importer.GetScene();
		if (!scene->HasMeshes())
			return res;

		aiMesh* mesh = find_mesh(name, scene->mRootNode);
		if (!mesh)
			return 0;

		res = new StaticMesh();
		res->m_index_count = mesh->mNumFaces*3;
		res->m_index = new unsigned[mesh->mNumFaces*3];

		res->m_vertex_count = mesh->mNumVertices;
		res->m_vb = new VertexPositionNormalTextureTangentBitangent[mesh->mNumVertices];
		res->m_one_vertex_size = sizeof(VertexPositionNormalTextureTangentBitangent);
		res->m_vertex_component = COMPONENT_POSITION|COMPONENT_NORMAL|COMPONENT_TEXTURE|COMPONENT_BITANGENT|COMPONENT_TANGENT;
		res->m_vertex_buffer_size = mesh->mNumVertices*sizeof(VertexPositionNormalTextureTangentBitangent);

		for (int face = 0; face < mesh->mNumFaces; ++face)
		{
			res->m_index[3*face + 0] = mesh->mFaces[face].mIndices[0];
			res->m_index[3*face + 1] = mesh->mFaces[face].mIndices[1];
			res->m_index[3*face + 2] = mesh->mFaces[face].mIndices[2];
		}

		for (int vertex = 0; vertex < mesh->mNumVertices; ++vertex)
		{
			VertexPositionNormalTextureTangentBitangent* v = (VertexPositionNormalTextureTangentBitangent*)res->m_vb;
			v[vertex].x = mesh->mVertices[vertex].x; 
			v[vertex].y = mesh->mVertices[vertex].y;
			v[vertex].z = mesh->mVertices[vertex].z;
			v[vertex].w = 1;

			v[vertex].nx = mesh->mNormals[vertex].x;
			v[vertex].ny = mesh->mNormals[vertex].y;
			v[vertex].nz = mesh->mNormals[vertex].z;

			v[vertex].u = mesh->mTextureCoords[0][vertex].x;
			v[vertex].v = mesh->mTextureCoords[0][vertex].y;
			v[vertex].s = mesh->mTextureCoords[0][vertex].z;
			v[vertex].q = 0;

			v[vertex].tx = mesh->mTangents[vertex].x;
			v[vertex].ty = mesh->mTangents[vertex].y;
			v[vertex].tz = mesh->mTangents[vertex].z;
			v[vertex].tx = 0;

			v[vertex].bx = mesh->mBitangents[vertex].x;
			v[vertex].by = mesh->mBitangents[vertex].y;
			v[vertex].bz = mesh->mBitangents[vertex].z;
			v[vertex].bz = 0;
		}

		res->m_material_id = mesh->mMaterialIndex;

		return res;

		return res;
	}

	unsigned GetBoneID(const System::string& mesh_name, const System::string& bone_name)
	{
		const aiScene* scene = importer.GetScene();
		aiMesh* mesh = find_mesh(mesh_name, scene->mRootNode);		

		if (!mesh->HasBones())
			return -1;

		for (int bone_id = 0; bone_id < mesh->mNumBones; bone_id++)
		{
			aiBone* bone = mesh->mBones[bone_id];
			if (System::string(bone->mName.data) == bone_name)
				return bone_id;
		}
		return -1;
	}

	SkinnedMesh* RawScene::CookSkinnedMesh(const System::string& name)
	{
		SkinnedMesh* res = 0;
		const aiScene* scene = importer.GetScene();
		if (!scene->HasMeshes())
			return res;

		aiMesh* mesh = find_mesh(name, scene->mRootNode);

		if (!mesh)
			return 0;

		if (!mesh->HasBones())
			return res;

		res = new SkinnedMesh();
		res->m_index_count = mesh->mNumFaces*3;
		res->m_index = new unsigned[mesh->mNumFaces*3];

		res->m_vertex_count = mesh->mNumVertices;
		res->m_vb = new VertexPositionNormalTextureTangentBitangentBone[mesh->mNumVertices];
		res->m_one_vertex_size = sizeof(VertexPositionNormalTextureTangentBitangentBone);
		res->m_vertex_component = COMPONENT_POSITION|COMPONENT_NORMAL|COMPONENT_TEXTURE|COMPONENT_BITANGENT|COMPONENT_TANGENT|COMPONENT_BONE_ID|COMPONENT_BONE_WEIGHT;
		res->m_vertex_buffer_size = mesh->mNumVertices*sizeof(VertexPositionNormalTextureTangentBitangentBone);

		for (int face = 0; face < mesh->mNumFaces; ++face)
		{
			res->m_index[3*face + 0] = mesh->mFaces[face].mIndices[0];
			res->m_index[3*face + 1] = mesh->mFaces[face].mIndices[1];
			res->m_index[3*face + 2] = mesh->mFaces[face].mIndices[2];
		}

		VertexPositionNormalTextureTangentBitangentBone* v = (VertexPositionNormalTextureTangentBitangentBone*)res->m_vb;

		for (int vertex = 0; vertex < mesh->mNumVertices; ++vertex)
		{				
			v[vertex].x = mesh->mVertices[vertex].x; 
			v[vertex].y = mesh->mVertices[vertex].y;
			v[vertex].z = mesh->mVertices[vertex].z;
			v[vertex].w = 1;

			v[vertex].nx = mesh->mNormals[vertex].x;
			v[vertex].ny = mesh->mNormals[vertex].y;
			v[vertex].nz = mesh->mNormals[vertex].z;
			v[vertex].nw = 0;

			v[vertex].u = mesh->mTextureCoords[0][vertex].x;
			v[vertex].v = mesh->mTextureCoords[0][vertex].y;
			v[vertex].s = mesh->mTextureCoords[0][vertex].z;
			v[vertex].q = 0;

			v[vertex].tx = mesh->mTangents[vertex].x;
			v[vertex].ty = mesh->mTangents[vertex].y;
			v[vertex].tz = mesh->mTangents[vertex].z;
			v[vertex].tw = 0;

			v[vertex].bx = mesh->mBitangents[vertex].x;
			v[vertex].by = mesh->mBitangents[vertex].y;
			v[vertex].bz = mesh->mBitangents[vertex].z;
			v[vertex].bw = 0;

			v[vertex].b1 = -1.0f; v[vertex].b2 = -1.0f; v[vertex].b3 = -1.0f; v[vertex].b4 = -1.0f;
			v[vertex].w1 = 0; v[vertex].w2 = 0; v[vertex].w3 = 0; v[vertex].w4 = 0;
		}

		res->m_material_id = mesh->mMaterialIndex;

		//
		//	set up bone weight for vertex
		//
		for (int b_id = 0; b_id < mesh->mNumBones; b_id++)
		{
			aiBone* bone = mesh->mBones[b_id];
			int bone_id = GetBoneID(name, System::string(bone->mName.data));

			for (int weight_id = 0; weight_id < bone->mNumWeights; weight_id++)
			{					
				aiVertexWeight weight = bone->mWeights[weight_id];
				if (v[weight.mVertexId].b1 < 0)
				{
					v[weight.mVertexId].b1 = bone_id;
					v[weight.mVertexId].w1 = weight.mWeight;
				} 
				else if (v[weight.mVertexId].b2 < 0)
				{
					v[weight.mVertexId].b2 = bone_id;
					v[weight.mVertexId].w2 = weight.mWeight;
				}
				else if (v[weight.mVertexId].b3 < 0)
				{
					v[weight.mVertexId].b3 = bone_id;
					v[weight.mVertexId].w3 = weight.mWeight;
				}
				else if (v[weight.mVertexId].b4 < 0)
				{
					v[weight.mVertexId].b4 = bone_id;
					v[weight.mVertexId].w4 = weight.mWeight;
				}
			}
		}			
		return res;
	}

	System::string GetParentBoneName(const System::string& mesh_name, const System::string& bone_name, aiNode* root)
	{
		const aiScene* scene = importer.GetScene();
	
		if (System::string(root->mName.data) == bone_name)
		{
			if (root->mParent)
				return System::string(root->mParent->mName.data);
			else
				return L"";
		}

		for (int i = 0; i < root->mNumChildren; ++i)
		{
			System::string res = GetParentBoneName(mesh_name, bone_name, root->mChildren[i]);
			if (res.Length() != 0)
				return res;
		}
		return L"";
	}

	SkinAnimation* RawScene::CookSkinAnimation(const System::string& mesh_name, unsigned anim_id) 
	{
		SkinAnimation* res = 0;
		const aiScene* scene = importer.GetScene();
		if (!scene->HasMeshes())
			return res;

		aiMesh* mesh = find_mesh(mesh_name, scene->mRootNode);

		if (!mesh->HasBones())
			return res;

		res = new SkinAnimation();

		//
		//	get rest pose
		//
		res->m_rest_pose.resize(mesh->mNumBones);

		for (int bone_id = 0; bone_id < mesh->mNumBones; ++bone_id)
		{
			Bone bone;
			aiBone* raw_bone = mesh->mBones[bone_id];
			bone.SetName(System::string(raw_bone->mName.data));
			Math::mat4 m;
			m[0] = raw_bone->mOffsetMatrix.a1;
			m[1] = raw_bone->mOffsetMatrix.b1;
			m[2] = raw_bone->mOffsetMatrix.c1;
			m[3] = raw_bone->mOffsetMatrix.d1;
			m[4] = raw_bone->mOffsetMatrix.a2;
			m[5] = raw_bone->mOffsetMatrix.b2;
			m[6] = raw_bone->mOffsetMatrix.c2;
			m[7] = raw_bone->mOffsetMatrix.d2;
			m[8] = raw_bone->mOffsetMatrix.a3;
			m[9] = raw_bone->mOffsetMatrix.b3;
			m[10] = raw_bone->mOffsetMatrix.c3;
			m[11] = raw_bone->mOffsetMatrix.d3;
			m[12] = raw_bone->mOffsetMatrix.a4;
			m[13] = raw_bone->mOffsetMatrix.b4;
			m[14] = raw_bone->mOffsetMatrix.c4;
			m[15] = raw_bone->mOffsetMatrix.d4;

			bone.SetMatrix(m);

			res->m_rest_pose[bone_id] = bone;
		}

		//
		//	get animation it self
		//
		if (scene->mNumAnimations == 0 || anim_id >= scene->mNumAnimations)
			return res;

		aiAnimation* anim = scene->mAnimations[anim_id];
		res->m_name = System::string(anim->mName.data);
		res->m_duration = anim->mDuration;
		res->m_tick_per_second = anim->mTicksPerSecond;
		aiNodeAnim* node_anim = anim->mChannels[0];
		res->m_animation.SetSize(mesh->mNumBones, node_anim->mNumRotationKeys);
		res->m_time.SetSize(1, node_anim->mNumRotationKeys);

		for (int channel = 0; channel < anim->mNumChannels; channel++)
		{			
			node_anim = anim->mChannels[channel];
			int bone_id = GetBoneID(mesh_name, System::string(node_anim->mNodeName.data));
			if (bone_id == -1)
				return res;
			//
			//	position
			//
			for (int pos_key_id = 0; pos_key_id < node_anim->mNumPositionKeys; ++pos_key_id)
			{
				aiVectorKey key = node_anim->mPositionKeys[pos_key_id];
				res->m_time.At(0, pos_key_id) = key.mTime;
				res->m_animation.At(bone_id, pos_key_id).m_position.Set(key.mValue.x, key.mValue.y, key.mValue.z);
				System::string parent_name = GetParentBoneName(mesh_name, System::string(node_anim->mNodeName.data), scene->mRootNode);
				unsigned parent_id = GetBoneID(mesh_name, parent_name);
				res->m_animation.At(bone_id, pos_key_id).m_parent = parent_id;
			}
			//
			//	rotation
			//
			for (int rot_key_id = 0; rot_key_id < node_anim->mNumRotationKeys; ++rot_key_id)
			{
				aiQuatKey key = node_anim->mRotationKeys[rot_key_id];
				res->m_animation.At(bone_id, rot_key_id).m_rotation.Set(key.mValue.w, key.mValue.x, key.mValue.y, key.mValue.z);
			}
		}

		return res;
	}

/*
	StaticMesh* Model::CookStaticMesh() const
	{
		StaticMesh* mesh = new StaticMesh;
		mesh->m_index_count = m_faces.size()*3;
		mesh->m_index = new unsigned[mesh->m_index_count];
		for (unsigned i = 0; i < m_faces.size()*3; i++)
		{
			mesh->m_index[i] = i;
		}

		mesh->m_vertex_count = m_faces.size()*3;
		VertexPositionNormalTextureTangentBitangent* vb;
		mesh->m_vb = vb = new VertexPositionNormalTextureTangentBitangent[mesh->m_vertex_count];
		memset(vb, 0, sizeof(VertexPositionNormalTextureTangentBitangent)*mesh->m_vertex_count);

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
			index++;

			Math::CalculateTBN(v2, v3, v1, t2, t3, t1, tgn, btn, nrm, det);
			vb[index].x = v2[0];	vb[index].y = v2[1];	vb[index].z = v2[2];	vb[index].w = 1.0f;
			vb[index].nx = nrm[0];	vb[index].ny = nrm[1];	vb[index].nz = nrm[2];	vb[index].nw = 1.0f;
			//vb[index].nx = n2[0];	vb[index].ny = n2[1];	vb[index].nz = n2[2];	vb[index].nw = 1.0f;
			vb[index].u = t2[0];	vb[index].v = t2[1];	vb[index].s = 0;		vb[index].q = 0.0f;
			vb[index].tx = tgn[0];	vb[index].ty = tgn[1];	vb[index].tz = tgn[2];	vb[index].tw = det;
			index++;

			Math::CalculateTBN(v3, v1, v2, t3, t1, t2, tgn, btn, nrm, det);
			vb[index].x = v3[0];	vb[index].y = v3[1];	vb[index].z = v3[2];	vb[index].w = 1.0f;
			vb[index].nx = nrm[0];	vb[index].ny = nrm[1];	vb[index].nz = nrm[2];	vb[index].nw = 1.0f;
			//vb[index].nx = n3[0];	vb[index].ny = n3[1];	vb[index].nz = n3[2];	vb[index].nw = 1.0f;
			vb[index].u = t3[0];	vb[index].v = t3[1];	vb[index].s = 0;		vb[index].q = 0.0f;
			vb[index].tx = tgn[0];	vb[index].ty = tgn[1];	vb[index].tz = tgn[2];	vb[index].tw = det;
			index++;
		}

		mesh->m_vertex_buffer_size = sizeof(VertexPositionNormalTextureTangentBitangent)*mesh->m_vertex_count;
		mesh->m_vertex_component = COMPONENT_POSITION|COMPONENT_NORMAL|COMPONENT_TEXTURE|COMPONENT_BITANGENT|COMPONENT_TANGENT;
		mesh->m_one_vertex_size = sizeof(VertexPositionNormalTextureTangentBitangent);

		return mesh;
	}

	bool Model::CookSkinnedMesh(SkinnedMesh*& mesh, Math::mat4*& bones, int& count) const
	{
		mesh = new SkinnedMesh;
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

		std::vector<int> base_index;		/// contains vertex index in the source array

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

			CookOneVertexWithBone //{}\\==>
				(
				f[0], vb[index].b1, vb[index].b2, vb[index].b3,  vb[index].b4,
				vb[index].w1, vb[index].w2, vb[index].w3, vb[index].w4
				);

			float tmp = vb[index].w1 + vb[index].w2 + vb[index].w3 + vb[index].w4;
			if (tmp != 1.0)
				throw;

			base_index.push_back(f[0]);
			index++;

			Math::CalculateTBN(v2, v3, v1, t2, t3, t1, tgn, btn, nrm, det);
			vb[index].x = v2[0];	vb[index].y = v2[1];	vb[index].z = v2[2];	vb[index].w = 1.0f;
			vb[index].nx = nrm[0];	vb[index].ny = nrm[1];	vb[index].nz = nrm[2];	vb[index].nw = 1.0f;
			//	vb[index].nx = n2[0];	vb[index].ny = n2[1];	vb[index].nz = n2[2];	vb[index].nw = 1.0f;
			vb[index].u = t2[0];	vb[index].v = t2[1];	vb[index].s = 0;		vb[index].q = 0.0f;
			vb[index].tx = tgn[0];	vb[index].ty = tgn[1];	vb[index].tz = tgn[2];	vb[index].tw = det;
			vb[index].bx = btn[0];	vb[index].by = btn[1];	vb[index].bz = btn[2];	vb[index].bw = 0;

			CookOneVertexWithBone //{}\\==>
				(
				f[1], vb[index].b1, vb[index].b2, vb[index].b3,  vb[index].b4,
				vb[index].w1, vb[index].w2, vb[index].w3, vb[index].w4
				);

			tmp = vb[index].w1 + vb[index].w2 + vb[index].w3 + vb[index].w4;
			if (tmp != 1.0)
				throw;

			base_index.push_back(f[1]);
			index++;

			Math::CalculateTBN(v3, v1, v2, t3, t1, t2, tgn, btn, nrm, det);
			vb[index].x = v3[0];	vb[index].y = v3[1];	vb[index].z = v3[2];	vb[index].w = 1.0f;
			vb[index].nx = nrm[0];	vb[index].ny = nrm[1];	vb[index].nz = nrm[2];	vb[index].nw = 1.0f;
			//	vb[index].nx = n3[0];	vb[index].ny = n3[1];	vb[index].nz = n3[2];	vb[index].nw = 1.0f;
			vb[index].u = t3[0];	vb[index].v = t3[1];	vb[index].s = 0;		vb[index].q = 0.0f;
			vb[index].tx = tgn[0];	vb[index].ty = tgn[1];	vb[index].tz = tgn[2];	vb[index].tw = det;
			vb[index].bx = btn[0];	vb[index].by = btn[1];	vb[index].bz = btn[2];	vb[index].bw = 0;

			CookOneVertexWithBone //{}\\==>
				(
				f[2], vb[index].b1, vb[index].b2, vb[index].b3,  vb[index].b4,
				vb[index].w1, vb[index].w2, vb[index].w3, vb[index].w4
				);

			tmp = vb[index].w1 + vb[index].w2 + vb[index].w3 + vb[index].w4;
			if (tmp != 1.0)
				throw;

			base_index.push_back(f[2]);
			index++;
		}

		/// Smooth TBN
		std::vector<int> mask(mesh->m_vertex_count);
		for (int i = 0; i < m_vertices.size(); i++)
		{
			Math::vec3 norm;
			Math::vec3 tang;
			Math::vec3 btan;
			for (int j = 0; j < mesh->m_vertex_count; j++)
			{
				VertexPositionNormalTextureTangentBitangentBone* v = static_cast<VertexPositionNormalTextureTangentBitangentBone*>(mesh->m_vb) + j;
				if (base_index[j] == i)
				{					
					norm[0] += v->nx; norm[1] += v->ny; norm[2] += v->nz; 
					tang[0] += v->tx; tang[1] += v->ty; tang[2] += v->tz; 
					btan[0] += v->bx; btan[1] += v->by; btan[2] += v->bz; 
				}				
			}

			norm.Normalize();
			tang.Normalize();
			btan.Normalize();
			tang = (tang - norm.Dot(tang)*norm).Normalized();
			btan = (btan - norm.Dot(btan)*norm - tang.Dot(btan)*tang).Normalized();

			Math::Matrix<float> m(3,3);
			m.At(0,0) = tang[0]; m.At(0,1) = tang[1]; m.At(0,2) = tang[2];
			m.At(1,0) = btan[0]; m.At(1,1) = btan[1]; m.At(1,2) = btan[2];
			m.At(2,0) = norm[0]; m.At(2,1) = norm[1]; m.At(2,2) = norm[2];
			float w = m.Determinant();

			for (int j = 0; j < mesh->m_vertex_count; j++)
			{	
				VertexPositionNormalTextureTangentBitangentBone* v = static_cast<VertexPositionNormalTextureTangentBitangentBone*>(mesh->m_vb) + j;
				if (base_index[j] == i)
				{					
					v->nx = norm[0]; v->ny = norm[1]; v->nz = norm[2]; 
					v->tx = tang[0]; v->ty = tang[1]; v->tz = tang[2];  v->tw = w;
					v->bx = btan[0]; v->by = btan[1]; v->bz = btan[2]; 
				}				
			}
		}

		//CookBonesMatrix(bones, count);

		mesh->m_vertex_buffer_size = sizeof(VertexPositionNormalTextureTangentBitangentBone)*mesh->m_vertex_count;
		mesh->m_vertex_component = COMPONENT_POSITION|COMPONENT_NORMAL|COMPONENT_TEXTURE|COMPONENT_BITANGENT|COMPONENT_TANGENT|COMPONENT_BONE_ID|COMPONENT_BONE_WEIGHT;
		mesh->m_one_vertex_size = sizeof(VertexPositionNormalTextureTangentBitangentBone);
		return true;
	}


	void Model::CookAnimationFrames() 
	{
		//
		//	cook anitmation
		//
		for (Animation::iterator action = m_skeleton_animation.begin(); action != m_skeleton_animation.end(); ++action)
		{
			System::string current_action_name = (*action).first;						

			CalculateMaximumFrameCount(current_action_name);

			m_cooked_animation[current_action_name].SetSize((*action).second.m_key_count, m_skeleton.size());

			//
			//	Fill animation with the default skeletone pose
			//
			for (Skeleton::iterator bone = m_skeleton.begin(); bone != m_skeleton.end(); ++bone)
			{
				int bone_id = GetBoneID((*bone).first);
				for (int i = 0; i < (*action).second.m_key_count; ++i)
				{
					//m_cooked_animation[current_action_name].At(i, bone_id) = Math::mat4::CreateIdentity();// GetSourceGlobalMatrix((*bone).first);
				}
			}

			for (SkeletonAnimation::const_iterator animation = (*action).second.m_pose.begin(); animation != (*action).second.m_pose.end(); ++animation)
			{
				System::string current_bone_name = (*animation).first;
				int bone_id = GetBoneID(current_bone_name);				

				for (std::map<Frame, BoneFrame>::const_iterator frame = (*animation).second.begin(); frame != (*animation).second.end(); ++frame)
				{
					int current_frame = (*frame).first;
					int current_frame_id = GetFrameID(current_action_name, current_bone_name, current_frame);

					BoneFrame global = GetGlobalFrame(current_bone_name, current_action_name, current_frame);
					Bone b = m_skeleton[current_bone_name];

					while (b.m_parent.Length() != 0)
					{
						global.m_rotation = global.m_rotation*m_cooked_animation[current_action_name].At(current_frame_id, GetBoneID(b.m_parent)).m_rotation;
						b = m_skeleton[b.m_parent];
					}

					m_cooked_animation[current_action_name].At(current_frame_id, bone_id) = global;
				}
			}/**/

			/*		for(Skeleton::iterator bone = m_skeleton.begin(); bone != m_skeleton.end(); ++bone)
			{
			System::string bone_name = (*bone).first;
			for (int i = 0; i < (*action).second.m_key_count; ++i)
			{
			for (std::map<Frame, BoneFrame>::iterator frame = (*action).second.m_pose[bone_name].begin(); frame != (*action).second.m_pose[bone_name].end(); ++frame)
			{
			int current_frame = (*frame).first;
			int current_frame_id = GetFrameID(current_action_name, bone_name, current_frame);
			int bone_id = GetBoneID(bone_name);				

			Math::mat4 global = GetGlobalFrame((*bone).first, current_action_name, (*frame).first);
			m_cooked_animation[current_action_name].At(current_frame_id, bone_id) = global;
			}
			}
			}/**/
		//}
	}

	/*! Side effect of this function is filling m_frame_value that holds correspondence between
	frames index and frame values
	*/
/*	void Model::CalculateMaximumFrameCount(const System::string& action_name)
	{
		int max = 0;
		Action& action = m_skeleton_animation[action_name];
		std::map<BoneName, std::map<Frame, BoneFrame> >::iterator max_iter; 
		for (std::map<BoneName, std::map<Frame, BoneFrame> >::iterator bone_anim = action.m_pose.begin(); bone_anim != action.m_pose.end(); ++bone_anim)
		{
			if (max < (*bone_anim).second.size())
			{
				max_iter = bone_anim;
				max = (*bone_anim).second.size();
			}
		}
		action.m_key_count = max;
		m_frame_value[action_name].SetSize(1, max);

		for (std::map<Frame, BoneFrame>::iterator frame = (*max_iter).second.begin(); frame != (*max_iter).second.end(); ++frame)
		{
			int frame_index = GetFrameID(action_name, (*max_iter).first, (*frame).first);
			m_frame_value[action_name].At(0, frame_index) = (*frame).first;
		}
	}

	int Model::GetBoneID(const System::string& bone_name) const
	{
		int id = 0;
		for (Skeleton::const_iterator bone = m_skeleton.begin(); bone != m_skeleton.end(); ++bone)
		{
			if ((*bone).first == bone_name)
				return id;
			id++;
		}
		return -1;
	}

	int Model::GetFrameID(const System::string& action_name, const System::string& bone_name, Frame frame) const
	{
		int id = 0;

		for (std::map<Frame, BoneFrame>::const_iterator pose = const_cast<Model*>(this)->m_skeleton_animation[action_name].m_pose[bone_name].begin(); pose != const_cast<Model*>(this)->m_skeleton_animation[action_name].m_pose[bone_name].end(); ++pose)
		{
			if ((*pose).first == frame)
				return id;
			id++;
		}
		return -1;
	}

	BoneFrame Model::GetGlobalFrame(BoneName bone_name, System::string action_name, Frame frame) const
	{
		BoneFrame res;
		if (bone_name.Length() == 0)
			return res;

		std::map<Frame, BoneFrame>& anim = const_cast<Model*>(this)->m_skeleton_animation[action_name].m_pose[bone_name];
		Skeleton& skelet = const_cast<Model*>(this)->m_skeleton;

		int frame_id = GetFrameID(action_name, bone_name, frame);
		int parent_id = GetBoneID(skelet[bone_name].m_parent);


		Math::quat p(1, 0, 0, 0);
		if (parent_id != -1)
		{
			p = GetGlobalFrame(skelet[bone_name].m_parent, action_name, frame).m_rotation;
		}


		Math::quat parent = GetBoneLocalOrientation(skelet[bone_name].m_parent, action_name, frame);


		res.m_rotation =
			(parent
			*skelet[bone_name].m_gimbal_transform
			*anim[frame].m_rotation
			*skelet[bone_name].m_gimbal_transform.Conjugated()
			*parent.Conjugated()).Normalized();
		/**/

	/*	res.m_position = Math::vec3(0,0,0);
		return res;
	}

	const Math::quat Model::GetBoneLocalOrientation(const System::string& bone_name, const System::string& action_name, Frame frame) const
	{
		Math::quat res(1, 0, 0, 0);
		if (bone_name.Length() == 0)
			return res;
		std::map<Frame, BoneFrame>& anim = const_cast<Model*>(this)->m_skeleton_animation[action_name].m_pose[bone_name];
		Skeleton& skelet = const_cast<Model*>(this)->m_skeleton;

		res = skelet[bone_name].m_gimbal_transform * anim[frame].m_rotation;;

		return (GetBoneLocalOrientation(skelet[bone_name].m_parent, action_name, frame) * res).Normalized();	
	}

	/*	const Math::quat Model::GetBoneLocalPosition(const System::string& bone_name, const System::string& action_name, Frame frame) const
	{
	Math::vec3 res(0, 0, 0);
	if (bone_name.Length() == 0)
	return res;
	std::map<Frame, BoneFrame>& anim = const_cast<Model*>(this)->m_skeleton_animation[action_name].m_pose[bone_name];
	Skeleton& skelet = const_cast<Model*>(this)->m_skeleton;

	res = anim[frame].m_rotation;;

	return (GetBoneLocalOrientation(skelet[bone_name].m_parent, action_name, frame) * res).Normalized();	
	}
	*/
/*	const Math::mat4 Model::GetSourceGlobalMatrix(const System::string& bone_name) const
	{
		const Bone& bone = const_cast<Model*>(this)->m_skeleton[bone_name];
		if (bone.m_parent.Length() == 0)
			return bone.m_matrix_local;

		Math::mat4 res = GetSourceGlobalMatrix(bone.m_parent)*bone.m_matrix_local;
		return res;
	}

	const Math::mat4 Model::GetSourceGlobalMatrix(int bone_id) const
	{
		int id = 0;
		for (Skeleton::const_iterator bone = m_skeleton.begin(); bone != m_skeleton.end(); ++bone)
		{
			if (id == bone_id)
				return (*bone).second.m_matrix_local;
			id++;
		}
		return Math::mat4();
	}


	void Model::CookBonesMatrix(Math::mat4*& bones, int& count) const
	{
		throw(System::SystemError(L"Not implemented"));
		count = m_skeleton.size();
		Math::mat4* cur_bone = bones = new Math::mat4[count];
		for (std::map<System::string, Bone>::const_iterator i = m_skeleton.begin(); i != m_skeleton.end(); ++i)
		{
			//		Math::mat4 m = CookGlobalMatrix((*i).first);
			/*	m[12] = 0;
			m[13] = 0;
			m[14] = 0;/**/
			//		*cur_bone++ = m;
		//}
//	}

/*	void Model::CookOneVertexWithBone(int index, float& b1, float& b2, float& b3, float& b4, float& w1, float& w2, float& w3, float& w4) const
	{
		const std::map<System::string, Weight>& weight = const_cast<Model*>(this)->m_bone_weights[index];

		int b_id[4];
		memset(b_id, 0, sizeof(b_id));
		float w[4];
		memset(w, 0, sizeof(w));
		int used = 0;
		for (std::map<System::string, Bone>::const_iterator bone = m_skeleton.begin(); bone != m_skeleton.end() && used < 4; ++bone)
		{
			if (weight.find((*bone).first) != weight.end())
			{	
				//
				// зам€н€ем найменьш уплывовую в€ршыну
				//
				int min = 0;
				for (int i = 0; i < 4; i++)
				{
					if (w[i] < w[min])
						min = i;
				}
				b_id[min] = GetBoneID((*bone).first);
				w[min] = const_cast<std::map<System::string, Weight>& >(weight)[(*bone).first];
				used++;
			}
		}

		//
		//	normalize
		//
		float l = w[0] + w[1] + w[2] + w[3];
		//		if (l == 0)
		//			throw System::SystemError(System::string::Format(L"Unable to calculate bone weight for %d vertex", index));

		if (w[0] < 0 || w[1] < 0 || w[2] < 0 || w[3] < 0)
			throw;

		w[0] /= l; w[1] /= l; w[2] /= l; w[3] /= l;
		w1 = w[0]; w2 = w[1]; w3 = w[2]; w4 = 1.0 - w1 - w2 - w3 ;
		b1 = b_id[0]; b2 = b_id[1]; b3 = b_id[2]; b4 = b_id[3];
	}
	/*
	bool Model::CookSkinAnimation(SkinAnimation*& anim)
	{
	anim = new SkinAnimation;
	anim->m_bones.resize(m_skeleton_animation.size());

	int index = 0;
	for (Animation::iterator i = m_skeleton_animation.begin(); i != m_skeleton_animtion.end(); ++i)
	{
	(*i).second.
	anim->m_bones[
	}
	}
	/**/
/*	Model::KeywordCode Model::Parse(System::string& word)
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

		BuildBoneIndex();
		CookAnimationFrames();
	}

	bool Model::CookAnimation(const System::string& action_name, SkinAnimation*& anim)
	{
		anim = new SkinAnimation;

		anim->m_animation = m_cooked_animation[action_name];
		anim->m_frame_values = m_frame_value[action_name];

		return true;
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
		return res.Transposed();
	}

	Math::quat Model::ParseGimbalTransform(System::Buffer& buffer)
	{
		CHECK_START(buffer);

		Math::quat q;
		q.W() = buffer.ReadWord().ToFloat();
		q.X() = buffer.ReadWord().ToFloat();
		q.Y() = buffer.ReadWord().ToFloat();
		q.Z() = buffer.ReadWord().ToFloat();
		CHECK_END(buffer);

		return q;
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
				m_skeleton[name].m_matrix_local = ParseBoneLocalMatrix(buffer);
				break;
			case WORD_GIMBAL_TRANSFORM:
				m_skeleton[name].m_gimbal_transform = ParseGimbalTransform(buffer);
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

	void Model::BuildBoneIndex()
	{
		int i = 0;
		for (Skeleton::iterator bone = m_skeleton.begin(); bone != m_skeleton.end(); ++bone)
		{
			m_bone_index[(*bone).first] = i;
			++i;
		}
	}
}*/