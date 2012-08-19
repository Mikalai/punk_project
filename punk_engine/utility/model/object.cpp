#include <iostream>

#include "object.h"
#include "bone.h"
#include "armature.h"
#include "skinned_mesh.h"
#include "static_mesh.h"
#include "../../system/logger.h"
#include "../../math/line3d.h"
#include "../../math/matrix.h"
#include "../../math/helper.h"
#include "../../math/triangle3d.h"

namespace Utility
{
	Object::Object()
		: m_parent(0)
	{}

	void Object::Save(std::ostream& stream)
	{		
		m_parent_name.Save(stream);
		m_name.Save(stream);
		m_bbox.Save(stream);
		m_local_matrix.Save(stream);
		m_world_matrix.Save(stream);
		m_location.Save(stream);
		m_oct_tree.Save(stream);
		m_animation_mixer.Save(stream);

		int size = (int)m_children.size();
		stream.write((char*)&size, sizeof(size));
		for each (std::shared_ptr<Object> child in m_children)
		{
			child->Save(stream);
		}

		int flag = m_mesh.get() != 0;
		stream.write((char*)&flag, sizeof(flag));
		if (flag)
			m_mesh->Save(stream);	

		flag = m_static_mesh.get() != 0;
		stream.write((char*)&flag, sizeof(flag));
		if (flag)
			m_static_mesh->Save(stream);

		flag = m_skinned_mesh.get() != 0;
		stream.write((char*)&flag, sizeof(flag));
		if (flag)
			m_skinned_mesh->Save(stream);

		m_material.Save(stream);

		flag = m_sound.get() != 0;
		stream.write((char*)&flag, sizeof(flag));
		if (flag)
			m_sound->Save(stream);
	}

	void Object::Load(std::istream& stream)
	{
		m_parent_name.Load(stream);
		m_name.Load(stream);
		m_bbox.Load(stream);
		m_local_matrix.Load(stream);
		m_world_matrix.Load(stream);
		m_location.Load(stream);
		m_oct_tree.Load(stream);
		m_animation_mixer.Load(stream);

		int size = 0;
		stream.read((char*)&size, sizeof(size));
		m_children.clear();
		m_children.resize(size);
		for (int i = 0; i < size; ++i)
		{
			std::shared_ptr<Object> object(new Object);
			object->Load(stream);
			m_children[i] = object;
		}

		int flag = 0;
		stream.read((char*)&flag, sizeof(flag));
		if (flag)
		{
			m_mesh.reset(new Mesh);
			m_mesh->Load(stream);
		}

		flag = 0;
		stream.read((char*)&flag, sizeof(flag));
		if (flag)
		{
			m_static_mesh.reset(new StaticMesh);
			m_static_mesh->Load(stream);
		}

		flag = 0;
		stream.read((char*)&flag, sizeof(flag));
		if (flag)
		{
			m_skinned_mesh.reset(new SkinnedMesh);
			m_skinned_mesh->Load(stream);
		}

		m_material.Load(stream);

		flag = 0;
		stream.read((char*)&flag, sizeof(flag));
		if (flag)
		{
			m_sound.reset(new Sound);
			m_sound->Load(stream);
		}

		UpdateCollision();
	}

	void Object::BuildOctTree()
	{
		if (m_mesh.get())
		{
			m_oct_tree.SetData(m_mesh->m_faces, m_mesh->m_vertices);
			m_bbox.Create((float*)&(m_mesh->m_vertices[0]), sizeof(m_mesh->m_vertices[0]), m_mesh->m_vertices.size());
		}
	}

	bool Object::IntersectWithRay(const Math::Vector3<float>& start, const Math::Vector3<float>& end, IntersectionCollection& res) const
	{
		Math::OctTree::FaceList fl  = m_oct_tree.CrossAll(Math::Line3D(start, end));
		if (fl.empty())
			return false;

		for (int tr = 0; tr < (int)fl.size(); tr++)
		{
			const Math::vec3& a = m_mesh->m_vertices[fl[tr].X()];
			const Math::vec3& b = m_mesh->m_vertices[fl[tr].Y()];
			const Math::vec3& c = m_mesh->m_vertices[fl[tr].Z()];

			Math::Triangle3D triangle(a, b, c);
			Math::Line3D line(start, end);
			float t;
			if (Math::LineCrossTriangle(line, triangle, t) == Math::SKEW_CROSS)
			{
				res[m_name].push_back(line.PointAt(t));				
			}
		}			

		if (res.find(m_name) == res.end())
		{
			return false;
		}
		else
		{
			res[m_name].SetName(m_name);
			return true;
		}
	}

	Object* Object::GetChild(const System::string& name, bool deep_search)
	{
		return const_cast<Object*>(static_cast<const Object*>(this)->GetChild(name, deep_search));
	}

	const Object* Object::GetChild(const System::string& name, bool deep_search) const
	{
		for each (std::shared_ptr<Object> obj in m_children)
		{
			if (obj->GetName() == name)
				return obj.get();

			if (deep_search)
			{
				const Object* res = obj->GetChild(name, deep_search);
				if (res)
				{
					return res;
				}
			}
		}
		return 0;
	}

	int Object::GetChildIndex(const System::string& name)
	{
		int index = 0;
		for each(auto child in m_children)
		{
			if (child->GetName() == name)
				return index;
			index++;
		}
		return -1;
	}

	bool Object::CookAsStaticMesh()
	{
		bool has_geom = true;
		struct Vertex
		{
			float x, y, z, w;
			float nx, ny, nz, nw;
			float tx, ty, tz, tw;
			float bx, by, bz, bw;				
			float u, v, s, q;
		};

		if (!GetMesh())
			has_geom = false;
		else if (GetMesh()->m_normals.empty()
			|| GetMesh()->m_tex_coords[0].size() == 0)
			has_geom = false;

		if (has_geom)
		{
			m_static_mesh.reset(new StaticMesh);
			m_static_mesh->SetIndexCount(GetMesh()->m_faces.size()*3);
			m_static_mesh->SetIndexBuffer(0, sizeof(unsigned)*m_static_mesh->GetIndexCount());
			for (unsigned i = 0; i < GetMesh()->m_faces.size()*3; i++)
			{
				((unsigned*)m_static_mesh->GetIndexBuffer())[i] = i;
			}
			m_static_mesh->SetVertexCount(GetMesh()->m_faces.size()*3);			
			m_static_mesh->SetVertexBuffer(0, sizeof(Vertex)*m_static_mesh->GetVertexCount());
			Vertex* vb = (Vertex*)m_static_mesh->GetVertexBuffer();

			std::vector<int> base_index;		/// contains vertex index in the source array
			int index = 0;
			for (unsigned i = 0; i < GetMesh()->m_tex_coords[0].size(); i++)
			{
				const Math::ivec3& f = GetMesh()->m_faces[i];
				const Math::vec3& v1 = GetMesh()->m_vertices[f[0]];
				const Math::vec3& v2 = GetMesh()->m_vertices[f[1]];
				const Math::vec3& v3 = GetMesh()->m_vertices[f[2]];
				const Math::vec2& t1 = GetMesh()->m_tex_coords[0][i][0];
				const Math::vec2& t2 = GetMesh()->m_tex_coords[0][i][1];
				const Math::vec2& t3 = GetMesh()->m_tex_coords[0][i][2];
				const Math::vec3& n1 = GetMesh()->m_normals[f[0]];
				const Math::vec3& n2 = GetMesh()->m_normals[f[1]];
				const Math::vec3& n3 = GetMesh()->m_normals[f[2]];

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
				base_index.push_back(f[0]);
				index++;

				Math::CalculateTBN(v2, v3, v1, t2, t3, t1, tgn, btn, nrm, det);
				vb[index].x = v2[0];	vb[index].y = v2[1];	vb[index].z = v2[2];	vb[index].w = 1.0f;
				vb[index].nx = nrm[0];	vb[index].ny = nrm[1];	vb[index].nz = nrm[2];	vb[index].nw = 1.0f;
				//vb[index].nx = n2[0];	vb[index].ny = n2[1];	vb[index].nz = n2[2];	vb[index].nw = 1.0f;
				vb[index].u = t2[0];	vb[index].v = t2[1];	vb[index].s = 0;		vb[index].q = 0.0f;
				vb[index].tx = tgn[0];	vb[index].ty = tgn[1];	vb[index].tz = tgn[2];	vb[index].tw = det;
				vb[index].bx = btn[0];	vb[index].by = btn[1];	vb[index].bz = btn[2];	vb[index].bw = 0;
				base_index.push_back(f[1]);
				index++;

				Math::CalculateTBN(v3, v1, v2, t3, t1, t2, tgn, btn, nrm, det);
				vb[index].x = v3[0];	vb[index].y = v3[1];	vb[index].z = v3[2];	vb[index].w = 1.0f;
				vb[index].nx = nrm[0];	vb[index].ny = nrm[1];	vb[index].nz = nrm[2];	vb[index].nw = 1.0f;
				//vb[index].nx = n3[0];	vb[index].ny = n3[1];	vb[index].nz = n3[2];	vb[index].nw = 1.0f;
				vb[index].u = t3[0];	vb[index].v = t3[1];	vb[index].s = 0;		vb[index].q = 0.0f;
				vb[index].tx = tgn[0];	vb[index].ty = tgn[1];	vb[index].tz = tgn[2];	vb[index].tw = det;
				vb[index].bx = btn[0];	vb[index].by = btn[1];	vb[index].bz = btn[2];	vb[index].bw = 0;
				base_index.push_back(f[2]);
				index++;
			}

			/// Smooth TBN
			std::vector<int> mask(m_static_mesh->GetVertexCount());
			for (int i = 0; i < (int)GetMesh()->m_vertices.size(); i++)
			{
				Math::vec3 norm;
				Math::vec3 tang;
				Math::vec3 btan;
				for (int j = 0; j < (int)m_static_mesh->GetVertexCount(); j++)
				{
					Vertex* v = static_cast<Vertex*>(m_static_mesh->GetVertexBuffer()) + j;
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

				for (int j = 0; j < (int)m_static_mesh->GetVertexCount(); j++)
				{	
					Vertex* v = static_cast<Vertex*>(m_static_mesh->GetVertexBuffer()) + j;
					if (base_index[j] == i)
					{					
						v->nx = norm[0]; v->ny = norm[1]; v->nz = norm[2]; 
						v->tx = tang[0]; v->ty = tang[1]; v->tz = tang[2];  v->tw = w;
						v->bx = btan[0]; v->by = btan[1]; v->bz = btan[2]; 
					}				
				}
			}

			m_static_mesh->SetMeshOffset(GetLocalMatrix());
			m_static_mesh->SetVertexComponent(COMPONENT_POSITION|COMPONENT_NORMAL|COMPONENT_TEXTURE|COMPONENT_BITANGENT|COMPONENT_TANGENT);
			m_static_mesh->SetOneVertexSize(sizeof(Vertex));
		}

		for each (auto child in m_children)
		{
			bool res = child->CookAsStaticMesh();
			has_geom = !has_geom ? true : res;
		}

		return has_geom;
	}

	struct Vertex
	{
		float x, y, z, w;
		float nx, ny, nz, nw;				
		float bx, by, bz, bw;
		float tx, ty, tz, tw;
		float u, v, s, q;
		float b1, b2, b3, b4;
		float w1, w2, w3, w4;
	};

	bool Object::CookAsSkinnedMesh(Armature& armature)
	{
		bool has_geom = true;
		if (!m_mesh.get())
		{
			System::Logger::Instance()->WriteError(L"Can't cook skinned mesh, because no mesh");
			has_geom = false;		
		}
		else if (m_mesh->m_bone_weights.empty()
			|| m_mesh->m_normals.empty()
			|| m_mesh->m_tex_coords[0].size() == 0)
		{
			System::Logger::Instance()->WriteError(L"Can't cook skinned mesh, because no bone weights");
			has_geom = false;
		}

		if (has_geom)
		{
			m_skinned_mesh.reset(new SkinnedMesh);

			m_skinned_mesh->SetIndexCount(GetMesh()->m_faces.size()*3);
			m_skinned_mesh->SetIndexBuffer(0, sizeof(unsigned)*m_skinned_mesh->GetIndexCount());

			for (unsigned i = 0; i < GetMesh()->m_faces.size()*3; i++)
			{
				((unsigned*)m_skinned_mesh->GetIndexBuffer())[i] = i;
			}

			m_skinned_mesh->SetVertexCount(GetMesh()->m_faces.size()*3);			
			m_skinned_mesh->SetVertexBuffer(0, sizeof(Vertex)*m_skinned_mesh->GetVertexCount());
			Vertex* vb = (Vertex*)m_skinned_mesh->GetVertexBuffer();

			std::vector<int> base_index;		/// contains vertex index in the source array

			int index = 0;
			for (unsigned i = 0, max_i = GetMesh()->m_tex_coords[0].size(); i < max_i; i++)
			{
				if (index == 18)
					i = i;
				if (index == 180)
					i = i;
				if (index == 280)
					i = i;
				if (index == 380)
					i = i;
				if (index == 480)
					i = i;
				if (index == 1480)
					i = i;
				const Math::ivec3& f = GetMesh()->m_faces[i];
				const Math::vec3& v1 = GetMesh()->m_vertices[f[0]];
				const Math::vec3& v2 = GetMesh()->m_vertices[f[1]];
				const Math::vec3& v3 = GetMesh()->m_vertices[f[2]];
				const Math::vec2& t1 = GetMesh()->m_tex_coords[0][i][0];
				const Math::vec2& t2 = GetMesh()->m_tex_coords[0][i][1];
				const Math::vec2& t3 = GetMesh()->m_tex_coords[0][i][2];
				const Math::vec3& n1 = GetMesh()->m_normals[f[0]];
				const Math::vec3& n2 = GetMesh()->m_normals[f[1]];
				const Math::vec3& n3 = GetMesh()->m_normals[f[2]];			

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
					armature, f[0], vb[index].b1, vb[index].b2, vb[index].b3,  vb[index].b4,
					vb[index].w1, vb[index].w2, vb[index].w3, vb[index].w4
					);

				float tmp = vb[index].w1 + vb[index].w2 + vb[index].w3 + vb[index].w4;
				if (tmp != 1.0)
					throw;

				base_index.push_back(f[0]);
				index++;
				if (index == 18)
					i = i;

				Math::CalculateTBN(v2, v3, v1, t2, t3, t1, tgn, btn, nrm, det);
				vb[index].x = v2[0];	vb[index].y = v2[1];	vb[index].z = v2[2];	vb[index].w = 1.0f;
				vb[index].nx = nrm[0];	vb[index].ny = nrm[1];	vb[index].nz = nrm[2];	vb[index].nw = 1.0f;
				//	vb[index].nx = n2[0];	vb[index].ny = n2[1];	vb[index].nz = n2[2];	vb[index].nw = 1.0f;
				vb[index].u = t2[0];	vb[index].v = t2[1];	vb[index].s = 0;		vb[index].q = 0.0f;
				vb[index].tx = tgn[0];	vb[index].ty = tgn[1];	vb[index].tz = tgn[2];	vb[index].tw = det;
				vb[index].bx = btn[0];	vb[index].by = btn[1];	vb[index].bz = btn[2];	vb[index].bw = 0;

				CookOneVertexWithBone //{}\\==>
					(
					armature, f[1], vb[index].b1, vb[index].b2, vb[index].b3,  vb[index].b4,
					vb[index].w1, vb[index].w2, vb[index].w3, vb[index].w4
					);

				tmp = vb[index].w1 + vb[index].w2 + vb[index].w3 + vb[index].w4;
				if (tmp != 1.0)
					throw;

				base_index.push_back(f[1]);
				index++;
				if (index == 18)
					i = i;

				Math::CalculateTBN(v3, v1, v2, t3, t1, t2, tgn, btn, nrm, det);
				vb[index].x = v3[0];	vb[index].y = v3[1];	vb[index].z = v3[2];	vb[index].w = 1.0f;
				vb[index].nx = nrm[0];	vb[index].ny = nrm[1];	vb[index].nz = nrm[2];	vb[index].nw = 1.0f;
				//	vb[index].nx = n3[0];	vb[index].ny = n3[1];	vb[index].nz = n3[2];	vb[index].nw = 1.0f;
				vb[index].u = t3[0];	vb[index].v = t3[1];	vb[index].s = 0;		vb[index].q = 0.0f;
				vb[index].tx = tgn[0];	vb[index].ty = tgn[1];	vb[index].tz = tgn[2];	vb[index].tw = det;
				vb[index].bx = btn[0];	vb[index].by = btn[1];	vb[index].bz = btn[2];	vb[index].bw = 0;

				CookOneVertexWithBone //{}\\==>
					(
					armature, f[2], vb[index].b1, vb[index].b2, vb[index].b3,  vb[index].b4,
					vb[index].w1, vb[index].w2, vb[index].w3, vb[index].w4
					);

				tmp = vb[index].w1 + vb[index].w2 + vb[index].w3 + vb[index].w4;
				if (tmp != 1.0)
					throw;

				base_index.push_back(f[2]);
				index++;

				std::cout << i << " ";
			}

			/// Smooth TBN
			std::vector<int> mask(m_skinned_mesh->GetVertexCount());
			for (int i = 0; i < (int)GetMesh()->m_vertices.size(); i++)
			{
				Math::vec3 norm;
				Math::vec3 tang;
				Math::vec3 btan;
				for (int j = 0; j < (int)m_skinned_mesh->GetVertexCount(); j++)
				{
					Vertex* v = static_cast<Vertex*>(m_skinned_mesh->GetVertexBuffer()) + j;
					if (base_index[j] == i)
					{					
						norm[0] += v->nx; norm[1] += v->ny; norm[2] += v->nz; 
						tang[0] += v->tx; tang[1] += v->ty; tang[2] += v->tz; 
						btan[0] += v->bx; btan[1] += v->by; btan[2] += v->bz; 
					}				
				}

				if (norm.Length() == 0)
					norm = norm;
				norm.Normalize();

				if (tang.Length() == 0)
					tang = tang;
				tang.Normalize();

				if (btan.Length() == 0)
					btan = btan;
				btan.Normalize();
				tang = (tang - norm.Dot(tang)*norm).Normalized();
				btan = (btan - norm.Dot(btan)*norm - tang.Dot(btan)*tang).Normalized();

				Math::Matrix<float> m(3,3);
				m.At(0,0) = tang[0]; m.At(0,1) = tang[1]; m.At(0,2) = tang[2];
				m.At(1,0) = btan[0]; m.At(1,1) = btan[1]; m.At(1,2) = btan[2];
				m.At(2,0) = norm[0]; m.At(2,1) = norm[1]; m.At(2,2) = norm[2];
				float w = m.Determinant();

				for (int j = 0; j < (int)m_skinned_mesh->GetVertexCount(); j++)
				{	
					Vertex* v = static_cast<Vertex*>(m_skinned_mesh->GetVertexBuffer()) + j;
					if (base_index[j] == i)
					{					
						v->nx = norm[0]; v->ny = norm[1]; v->nz = norm[2]; 
						v->tx = tang[0]; v->ty = tang[1]; v->tz = tang[2];  v->tw = w;
						v->bx = btan[0]; v->by = btan[1]; v->bz = btan[2]; 
					}				
				}
			}

			//CookBonesMatrix(bones, count);

			m_skinned_mesh->SetMeshOffset(GetLocalMatrix());
			m_skinned_mesh->SetVertexComponent(COMPONENT_POSITION|COMPONENT_NORMAL|COMPONENT_TEXTURE|COMPONENT_BITANGENT|COMPONENT_TANGENT|COMPONENT_BONE_ID|COMPONENT_BONE_WEIGHT);
			m_skinned_mesh->SetOneVertexSize(sizeof(Vertex));	

		}
		for each (auto child in m_children)
		{
			bool res = child->CookAsSkinnedMesh(armature);
			has_geom = !has_geom ? true : res;
		}

		return has_geom;
	}

	void Object::CookOneVertexWithBone(Armature& armature, int index, float& b1, float& b2, float& b3, float& b4, float& w1, float& w2, float& w3, float& w4)
	{
		const BoneWeights& weights = m_mesh->m_bone_weights.at(index);

		int b_id[4];
		memset(b_id, 0, sizeof(b_id));
		float w[4];
		memset(w, 0, sizeof(w));
		int used = 0;
		for (int i = 0; i < armature.GetBonesCount() /*&& used < 4*/; ++i)
		{
			const Bone* cur_bone = armature.GetBoneByIndex(i);
			if (weights.find(cur_bone->GetName()) != weights.end())
			{	
				//
				// зам€н€ем найменьш уплывовую в€ршыну
				//
				int min = 0;
				for (int j = 0; j < 4; j++)
				{
					if (w[j] < w[min])
						min = j;
				}
				b_id[min] = i;
				w[min] = weights.at(cur_bone->GetName());
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
		w1 = w[0]; w2 = w[1]; w3 = w[2]; w4 = 1.0f - w1 - w2 - w3 ;
		b1 = (float)b_id[0]; b2 = (float)b_id[1]; b3 = (float)b_id[2]; b4 = (float)b_id[3];
	}

	void Object::UpdateCollision()
	{
		for each (auto object in m_children)
		{
			if (std::wstring(object->GetName().Data()).find(L"collision") != std::wstring::npos)
			{
				m_collision.push_back(object.get());
			}
		}
	}

	bool Object::IsCollisionVolume() const
	{
		const wchar_t name[] = L"collision";
		bool result = wmemcmp(m_name.Data(), name, sizeof(name)/sizeof(name[0])-1) == 0; 
		return result;
	}

	bool Object::TestCollision(const Math::BoundingBox& bbox) const
	{
		return TestCollision(bbox, m_local_matrix, *this);
	}

	bool Object::TestCollision(const Math::BoundingBox& bbox, const Math::mat4& parent, const Object& obj) const
	{
		return false;
	}
}

