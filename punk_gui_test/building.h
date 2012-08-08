#ifndef _H_BUILDING
#define _H_BUILDING

#include "../punk_engine/punk_engine.h"

class Building
{
	Utility::ObjectRef m_object;	
	std::auto_ptr<OpenGL::RenderContextBumpMapping> m_rc;
	std::auto_ptr<OpenGL::TextureContext> m_tc;

	Audio::Player m_player;

public:
	Building();
	void Render(Utility::CameraRef m_camera, Utility::TerrainRef terrain);

private:
	void Render(Utility::ObjectRef object, const Math::mat4& matric);
};

#endif	 //	_H_BUILDING