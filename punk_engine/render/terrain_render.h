#ifndef _H_PUNK_TERRAIN_RENDER
#define _H_PUNK_TERRAIN_RENDER

#include "abstract_render.h"
#include "per_vertex_render.h"
#include "../driver/video/driver.h"

#include "../math/math.h"

namespace Render
{
	class TerrainRender : public AbstractRender
	{
		VertexArrayObject* m_vao;
	public:
		struct Parameters
		{
		private:
			static std::queue<Parameters*> parametersPool;
			
			Parameters() {}
			Parameters(const Parameters&);
			Parameters& operator = (const Parameters&);

		public:
			Math::mat4 m_world_transform;
			Math::mat4 m_view_transform;
			Math::mat4 m_projection_transform;
			Math::vec3 m_light_direction;
			const Driver::Texture2D* m_height_map;
			const Driver::Texture2D* m_normal_map;
			const Driver::Texture2D* m_diffuse_map;

			void Set(const Math::mat4& world_transform, 
				const Math::mat4& view_transformconst,
				const Math::mat4& projection_transform,
				const Math::vec3& light_direction,
				const Driver::Texture2D* m_height_map,
				const Driver::Texture2D* m_normal_map,
				const Driver::Texture2D* diffuse_map);

			static Parameters* Create();
			void Release();
		};

	private:
		
		ShaderProgram* m_shader_program;

		GLint m_vertex_attribute;
		GLint m_vertexFlagsAttrib;
		GLint m_normalsAttrib;
		GLint m_texcoord0Attrib;
		GLint m_normalTransformUniform;
		GLint m_proj_view_world_uniform;
		GLint m_diffuse_color_uniform;
		GLint m_viewUniform;
		GLint m_worldUniform;
		GLint m_ProjectionUniform;
		GLint m_lightDirectionUniform;
		GLint m_lightPositionUniform;
		GLint m_heightMapUniform;
		GLint m_normalMapUniform;
		GLint m_diffuseMapUniform;
		GLint m_position;
		GLint m_level;
		GLint m_i;
		GLint m_j;

	protected:

		TerrainRender();
		TerrainRender(const TerrainRender&);
		TerrainRender& operator = (const TerrainRender&);

	public:

		static TerrainRender* GetRender();
		virtual ~TerrainRender();
		virtual void Render(void* parameters);
		virtual void BindShaderData();
	};
}

#endif
