#ifndef _H_BUILDING
#define _H_BUILDING

#include "../../punk_engine.h"

class Building
{
	Utility::ObjectRef m_object;	
	std::auto_ptr<OpenGL::RenderContextBumpMapping> m_rc;
	std::auto_ptr<OpenGL::TextureContext> m_tc;

	std::auto_ptr<Utility::RigidBody> m_rb;
	Audio::Player m_player;
	
	Render::BBoxRender render;

public:
	Building();
	void Render(Utility::CameraRef m_camera, Utility::TerrainRef terrain);

private:
	void Render(Utility::ObjectRef object, const Math::mat4& matric, const Math::mat4& view, const Math::mat4& proj);
};

#endif	 //	_H_BUILDING