#ifndef _H_PUNK_TERRAIN
#define _H_PUNK_TERRAIN

#include "terrain_render.h"
#include "../system/driver/video/opengl/texture2d.h"
#include "../system/driver/video/opengl/grid_object.h"
#include "../system/driver/video/opengl/render_context/rc_terrain.h"
#include "../system/driver/video/opengl/texture_context.h"
#include "../system/driver/video/opengl/extensions.h"
#include "../utility/elements/terrain.h"
#include "../utility/camera.h"

namespace Render
{
	struct TerrainRender::TerrainRenderImpl
	{
		OpenGL::Texture2D m_height_map;
		OpenGL::Texture2DRef m_normal_map;
		OpenGL::Texture2DRef m_diffuse_map_1;
		OpenGL::Texture2DRef m_diffuse_map_2;

		OpenGL::GridObject m_grid;
		Utility::Terrain* m_terrain;

		OpenGL::RenderContextTerrain m_terrain_rc;
		OpenGL::TextureContext m_texture_context;

		TerrainRenderImpl()
			: m_height_map()
			, m_normal_map(0)
			, m_diffuse_map_1(0)
			, m_diffuse_map_2(0)
			, m_grid()
			, m_terrain(0)
			, m_terrain_rc()
			, m_texture_context()
		{}

		TerrainRenderImpl(const TerrainRenderImpl& impl)
			: m_height_map(impl.m_height_map)
			, m_normal_map(impl.m_normal_map)
			, m_diffuse_map_1(impl.m_diffuse_map_1)
			, m_diffuse_map_2(impl.m_diffuse_map_2)
			, m_grid(impl.m_grid)
			, m_terrain(impl.m_terrain)
			, m_terrain_rc(impl.m_terrain_rc)
			, m_texture_context(impl.m_texture_context)
		{}

		void Init()
		{
			m_grid.SetWidth(1);
			m_grid.SetHeight(1);
			m_grid.SetWidthSlice(16);
			m_grid.SetHeightSlice(16);			
			m_grid.Init();
		}

		void SetTerrain(Utility::Terrain* terrain)
		{
			m_terrain = terrain;
			m_height_map.Create(*m_terrain->GetLandscape());
		}

		//void SetDiffuseMap1(const ImageModule::Image& image)
		//{
		//	m_diffuse_map_1.Create(image);
		//}
		//
		//void SetDiffuseMap2(const ImageModule::Image& image)
		//{
		//	m_diffuse_map_2.Create(image);
		//}

		void SetDiffuseMap1(const OpenGL::Texture2DRef t)
		{
			m_diffuse_map_1 = t;
		}

		void SetDiffuseMap2(const OpenGL::Texture2DRef t)
		{
			m_diffuse_map_2 = t;
		}

		void Render(Utility::Camera* camera)
		{
			static Math::vec3 sun(100, 100, 100);
			static float angle = 0;

			if (m_terrain->IsModified())
			{
				m_height_map.Create(*m_terrain->GetLandscape());
				m_terrain->SetModified(false);
			}
			Math::mat4 local_matrix = Math::mat4::CreateTranslate(m_terrain->GetOffset());
			Math::vec3 camera_position = camera->GetPosition();
			Math::mat4 projViewWorld = camera->GetViewProjectionMatrix();
			Math::mat3 normalTransform = (local_matrix*camera->GetViewMatrix()).RotationPart().Inversed().Transposed();

			m_grid.Bind(m_terrain_rc.GetSupportedVertexAttributes());
	
			int start = -4;
			int end = 4;
		
			m_texture_context.SetTexture0(m_diffuse_map_1);
			m_texture_context.SetTexture1(m_diffuse_map_2);
			m_texture_context.SetTexture2(&m_height_map);						
			m_texture_context.Bind();					

			for (int level = 1; level < 10; level++)
			{
				for (int i = start; i < end; i++)
				{
					for (int j = start; j < end; j++)
					{
						Math::vec2 position((int)camera_position[0], (int)camera_position[2]);

						Math::mat4 world_transform = Math::mat4::CreateTranslate(position[0], 0, position[1]);
						//if (j == -1)
							//continue;
						if (level != 1)
							if (!(j < start+2 || j >= end - 2 || i < start+2 || i >= end - 2))
								continue;

						//if (!Common::Camera::GetActiveCamera()->BoxInFrustum(m_vao->GetBoundingBox().Transform(world_transform)))
							//continue;
						
						m_terrain_rc.SetWorldMatrix(world_transform);
						m_terrain_rc.SetViewMatrix(camera->GetViewMatrix());
						m_terrain_rc.SetProjectionMatrix(camera->GetProjectionMatrix());
						m_terrain_rc.SetNormalTransform(normalTransform);
						m_terrain_rc.SetLightDirection(sun.Normalized());
						m_terrain_rc.SetDiffuseColor(Math::vec4(1,1,1,1));
						m_terrain_rc.SetPosition(position);
						m_terrain_rc.SetLevel(float(level));
						m_terrain_rc.SetI(i);
						m_terrain_rc.SetJ(j);
						m_terrain_rc.SetVerticalScale(m_terrain->GetScale());

						m_terrain_rc.Begin();
						m_grid.Render();

					}
				}
			}
			m_terrain_rc.End();
			m_grid.Unbind();
			m_texture_context.Unbind();
		}		
	};
}

#endif