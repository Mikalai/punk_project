#include "terrain_render.h"
#include "terrain_render_impl.h"

namespace Render
{
	TerrainRender::TerrainRender()
		: impl_terrain_render(new TerrainRender::TerrainRenderImpl)
	{}

	TerrainRender::TerrainRender(const TerrainRender& render)
		: impl_terrain_render(new TerrainRender::TerrainRenderImpl(*render.impl_terrain_render))
	{}

	TerrainRender& TerrainRender::operator= (const TerrainRender& render)
	{
		TerrainRender temp(render);
		std::swap(impl_terrain_render, temp.impl_terrain_render);
		return *this;
	}

	TerrainRender::~TerrainRender()
	{
		impl_terrain_render.reset(0);
	}

	OpenGL::Texture2D* TerrainRender::GetHeightMap()
	{
		return &impl_terrain_render->m_height_map;
	}

	void TerrainRender::SetTerrain(Utility::Terrain* terrain)
	{
		impl_terrain_render->SetTerrain(terrain);
	}

	void TerrainRender::Render(Utility::Camera* camera)
	{
		impl_terrain_render->Render(camera);
	}

	void TerrainRender::Init()
	{
		impl_terrain_render->Init();
	}

	void TerrainRender::SetDiffuseMap1(OpenGL::Texture2D* image)
	{
		impl_terrain_render->SetDiffuseMap1(image);
	}

	void TerrainRender::SetDiffuseMap2(OpenGL::Texture2D* image)
	{
		impl_terrain_render->SetDiffuseMap2(image);
	}

	/*void TerrainRender::SetDiffuseMap2(const ImageModule::Image& image)
	{
		impl_terrain_render->SetDiffuseMap2(image);
	}

	void TerrainRender::SetDiffuseMap1(const ImageModule::Image& image)
	{
		impl_terrain_render->SetDiffuseMap1(image);
	}*/

}

//#include "terrain_render.h"
//#include "../shaders/shader_manager.h"
//#include "../generator/generator.h"
//#include "../common/camera.h"
//
//namespace Render
//{
//	void TerrainRender::Parameters::Set(const Math::mat4& world_transform, 
//				const Math::mat4& view_transform,
//				const Math::mat4& projection_transform,
//				const Math::vec3& light_direction,
//				const Driver::Texture2D* height_map,
//				const Driver::Texture2D* normal_map,
//				const Driver::Texture2D* diffuse_map)
//	{
//		m_world_transform = world_transform;
//		m_view_transform = view_transform;
//		m_projection_transform = projection_transform;
//		m_light_direction = light_direction;
//		m_height_map = height_map;
//		m_normal_map = normal_map;
//		m_diffuse_map = diffuse_map;
//	}
//
//	TerrainRender::TerrainRender()
//	{
//		::Driver::CheckError();
//		if(!(m_shader_program = Shaders::g_ShaderManager.GetProgram(L"terrain")))
//			throw System::Exception(L"terrain program not found" + LOG_LOCATION_STRING);
//
//		m_vao = new VertexArrayObject();
//		
//		Common::StaticGeometry* geom = Generator::Creator::GeneratPlane(1,1,16,16);
//		
//		m_vao->Create(*geom, 0);
//		
//		delete geom;
//
//		BindShaderData();
//
//	}
//
//	void TerrainRender::BindShaderData()
//	{
//		m_vertex_attribute = m_shader_program->GetAttribLocation("rm_Vertex");
//		m_vertexFlagsAttrib = m_shader_program->GetAttribLocation("rm_Flags");
//		m_normalsAttrib = m_shader_program->GetAttribLocation("rm_Normal");
//		m_texcoord0Attrib = m_shader_program->GetAttribLocation("rm_Texcoord0");
//		m_proj_view_world_uniform = m_shader_program->GetUniformLocation("uProjViewWorld");
//		m_normalTransformUniform = m_shader_program->GetUniformLocation("uNormalTransform");
//		m_lightDirectionUniform = m_shader_program->GetUniformLocation("uLightDirection");
//		m_diffuse_color_uniform = m_shader_program->GetUniformLocation("uDiffuseColor");
//		m_viewUniform = m_shader_program->GetUniformLocation("uView");
//		m_worldUniform = m_shader_program->GetUniformLocation("uWorld");
//		m_ProjectionUniform = m_shader_program->GetUniformLocation("uProjection");
//		m_heightMapUniform = m_shader_program->GetUniformLocation("uHeightMapUniform");
//		m_normalMapUniform = m_shader_program->GetUniformLocation("uNormalMapUniform");
//		m_diffuseMapUniform = m_shader_program->GetUniformLocation("uDiffuseMapUniform");
//		m_position = m_shader_program->GetUniformLocation("uPosition");
//		m_level = m_shader_program->GetUniformLocation("uLevel");
//		m_i = m_shader_program->GetUniformLocation("ui");
//		m_j = m_shader_program->GetUniformLocation("uj");
//	}
//
//	void TerrainRender::Render(void* parameters)
//	{		
//		static Math::vec3 sun(100, 100, 100);
//		static float angle = 0;
//
//		Parameters* p = static_cast<Parameters*>(parameters);
//		
//		Math::vec3 camera_position = p->m_world_transform.TranslationPart();
//		Math::mat4 projViewWorld = p->m_world_transform*p->m_view_transform*p->m_projection_transform;
//		Math::mat3 normalTransform = (p->m_world_transform*p->m_view_transform).RotationPart();
//
//		m_vao->Bind();
//
//		Common::StaticGeometry::Vertex* v = (Common::StaticGeometry::Vertex*)glMapBuffer(GL_ARRAY_BUFFER, GL_READ_ONLY);
//
//		
//		glUnmapBuffer(GL_ARRAY_BUFFER);
//
//		int passCount = m_shader_program->GetPassCount();
//		
//		int start = -4;
//		int end = 4;
//		for (int i = 0; i < passCount; i++)
//		{
//			m_shader_program->Bind(i);			
//			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//
//			for (int level = 1; level < 6; level++)
//			{
//				for (int i = start; i < end; i++)
//				{
//					for (int j = start; j < end; j++)
//					{
//						Math::vec2 position((int)camera_position[0], (int)camera_position[2]);
//
//						Math::mat4 world_transform = Math::mat4::CreateTranslate(position[0], 0, position[1]);
//						//if (j == -1)
//							//continue;
//						if (level != 1)
//							if (!(j < start+2 || j >= end - 2 || i < start+2 || i >= end - 2))
//								continue;
//
//						//if (!Common::Camera::GetActiveCamera()->BoxInFrustum(m_vao->GetBoundingBox().Transform(world_transform)))
//							//continue;
//						
//						m_shader_program->SetUniformMatrix4f(m_proj_view_world_uniform, projViewWorld);
//						m_shader_program->SetUniformMatrix4f(m_worldUniform, world_transform);
//						m_shader_program->SetUniformMatrix4f(m_viewUniform, p->m_view_transform);
//						m_shader_program->SetUniformMatrix4f(m_ProjectionUniform, p->m_projection_transform);
//						m_shader_program->SetUniformMatrix3f(m_normalTransformUniform, normalTransform);
//						m_shader_program->SetUniformVector3f(m_lightDirectionUniform, p->m_light_direction);
//						m_shader_program->SetUniformVector4f(m_diffuse_color_uniform, Math::vec4(1,1,1,1));
//						m_shader_program->SetUniformVector2f(m_position, position);
//						m_shader_program->SetUniformInt(m_heightMapUniform, 0);
//						m_shader_program->SetUniformInt(m_diffuseMapUniform, 1);
//						m_shader_program->SetUniformFloat(m_level, float(level));
//						m_shader_program->SetUniformInt(m_i, i);
//						m_shader_program->SetUniformInt(m_j, j);
//						m_shader_program->SetUniformVector3f(m_lightDirectionUniform, Math::mat4::CreateRotation(1,0,0, angle) * sun.ToHomogeneous());
//
//					//	angle += 0.000001;
//
//						glActiveTexture(GL_TEXTURE0);										
//						p->m_height_map->Bind();
//						glActiveTexture(GL_TEXTURE0+1);					
//						p->m_diffuse_map->Bind();					
//
//						//glDrawRangeElements(GL_TRIANGLES, 0,  p->m_vertex_array_object.GetIndexCount() / 3, GL_UNSIGNED_SHORT, 0);
//						glDrawElements(GL_TRIANGLES, m_vao->GetIndexCount(), GL_UNSIGNED_SHORT, 0);			
//					}
//				}
//			}
//		}		
//		
//		
//		m_shader_program->Unbind();
//	
//		m_vao->Unbind();
//
//		p->Release();
//	}
//
//	TerrainRender::~TerrainRender()
//	{
//	}
//}