#ifndef _H_FIELD
#define _H_FIELD

#include "../../punk_engine.h"

class Field
{
	std::auto_ptr<Render::TerrainRender> m_terrain_render;
	std::auto_ptr<Utility::Terrain> m_terrain;
	Utility::ObjectRef m_grass;
	Utility::CameraRef m_camera;
	
	OpenGL::Texture2DRef m_diffuse_1;
	OpenGL::Texture2DRef m_diffuse_2;
	
	std::auto_ptr<OpenGL::RenderContextGrass> m_grass_rc;
	std::auto_ptr<OpenGL::TextureContext> m_grass_tc;

	float m_time;
	float m_wind_strength;
	Math::vec3 m_wind_direction;
public:
	Field();
	void Hit(const Math::vec3& point, float radius);
	void SetCameraReference(Utility::CameraRef camera);
	void Render();
	void Update(float time, float delta);

	Utility::TerrainRef GetTerrain() { return m_terrain.get(); }
};

#endif	//	_H_FIELD