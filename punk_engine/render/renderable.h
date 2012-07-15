#ifndef _H_ADVANCED_STATIC_MESH
#define _H_ADVANCED_STATIC_MESH

#include "../math/mat4.h"

namespace OpenGL
{
	class VertexArrayObject;
	class Texture2D;
}

namespace Render
{
	class StaticRenderable
	{
		Math::mat4					m_local_transform;
		///	should be destroyed by some manager
		OpenGL::VertexArrayObject*	m_vao;	
		///	should be destroyed by some manager 
		OpenGL::Texture2D*			m_diffuse_map;
		///	should be destroyed by some manager
		OpenGL::Texture2D*			m_normal_map;		

	public:

		inline void SetVAO(OpenGL::VertexArrayObject* vao)
		{
			m_vao = vao;
		}

		inline OpenGL::VertexArrayObject* GetVAO()
		{
			return m_vao;
		}

		inline const OpenGL::VertexArrayObject* GetVAO() const
		{
			return m_vao;
		}

		void SetLocalTransform(const Math::mat4& m)
		{
			m_local_transform = m;
		}

		Math::mat4& GetLocalTransform()
		{
			return m_local_transform;
		}

		const Math::mat4& GetLocalTransform() const 
		{
			return m_local_transform;
		}

		void SetDiffuseMap(OpenGL::Texture2D* t)
		{
			m_diffuse_map = t;
		}

		OpenGL::Texture2D* GetDiffuseMap()
		{
			return m_diffuse_map;
		}

		const OpenGL::Texture2D* GetDiffuseMap() const
		{
			return m_diffuse_map;
		}

		void SetNormalMap(OpenGL::Texture2D* t)
		{
			m_normal_map = t;
		}

		OpenGL::Texture2D* GetNormalMap() 
		{
			return m_normal_map;
		}

		const OpenGL::Texture2D* GetNormalMap() const
		{
			return m_normal_map;
		}

		static const StaticRenderable Build(OpenGL::VertexArrayObject* vao, OpenGL::Texture2D* diffuse, OpenGL::Texture2D* normal, const Math::mat4& local)
		{
			StaticRenderable res;
			res.SetVAO(vao);
			res.SetDiffuseMap(diffuse);
			res.SetNormalMap(normal);
			res.SetLocalTransform(local);
			return res;
		}

		static StaticRenderable* Build(StaticRenderable* res, OpenGL::VertexArrayObject* vao, OpenGL::Texture2D* diffuse, OpenGL::Texture2D* normal, const Math::mat4& local)
		{
			res->SetVAO(vao);
			res->SetDiffuseMap(diffuse);
			res->SetNormalMap(normal);
			res->SetLocalTransform(local);
			return res;
		}
	};
}

#endif //	_H_STATIC_MESH_WITH_VBO
