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
		res->SetIndexCount(mesh->mNumFaces*3);
		res->SetIndexBuffer(new unsigned[mesh->mNumFaces*3]);

		res->SetVertexCount(mesh->mNumVertices);
		res->SetVertexBuffer(new VertexPositionNormalTextureTangentBitangent[mesh->mNumVertices]);
		res->SetOneVertexSize(sizeof(VertexPositionNormalTextureTangentBitangent));
		res->SetVertexComponent(COMPONENT_POSITION|COMPONENT_NORMAL|COMPONENT_TEXTURE|COMPONENT_BITANGENT|COMPONENT_TANGENT);
		res->SetVertexBufferSize(mesh->mNumVertices*sizeof(VertexPositionNormalTextureTangentBitangent));

		for (int face = 0; face < mesh->mNumFaces; ++face)
		{
			res->GetIndexBuffer()[3*face + 0] = mesh->mFaces[face].mIndices[0];
			res->GetIndexBuffer()[3*face + 1] = mesh->mFaces[face].mIndices[1];
			res->GetIndexBuffer()[3*face + 2] = mesh->mFaces[face].mIndices[2];
		}

		for (int vertex = 0; vertex < mesh->mNumVertices; ++vertex)
		{
			VertexPositionNormalTextureTangentBitangent* v = (VertexPositionNormalTextureTangentBitangent*)res->GetVertexBuffer();
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

		res->SetMaterialID(mesh->mMaterialIndex);

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
		res->SetIndexCount(mesh->mNumFaces*3);
		res->SetIndexBuffer(new unsigned[mesh->mNumFaces*3]);

		res->SetVertexCount(mesh->mNumVertices);
		res->SetVertexBuffer(new VertexPositionNormalTextureTangentBitangentBone[mesh->mNumVertices]);
		res->SetOneVertexSize(sizeof(VertexPositionNormalTextureTangentBitangentBone));
		res->SetVertexComponent(COMPONENT_POSITION|COMPONENT_NORMAL|COMPONENT_TEXTURE|COMPONENT_BITANGENT|COMPONENT_TANGENT|COMPONENT_BONE_ID|COMPONENT_BONE_WEIGHT);
		res->SetVertexBufferSize(mesh->mNumVertices*sizeof(VertexPositionNormalTextureTangentBitangentBone));

		for (int face = 0; face < mesh->mNumFaces; ++face)
		{
			res->GetIndexBuffer()[3*face + 0] = mesh->mFaces[face].mIndices[0];
			res->GetIndexBuffer()[3*face + 1] = mesh->mFaces[face].mIndices[1];
			res->GetIndexBuffer()[3*face + 2] = mesh->mFaces[face].mIndices[2];
		}

		VertexPositionNormalTextureTangentBitangentBone* v = (VertexPositionNormalTextureTangentBitangentBone*)res->GetVertexBuffer();

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

		res->SetMaterialID(mesh->mMaterialIndex);

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
		//res->m_rest_pose.resize(mesh->mNumBones);

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
				res->m_rest_pose.at(bone_id).SetParent( parent_id);
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


}