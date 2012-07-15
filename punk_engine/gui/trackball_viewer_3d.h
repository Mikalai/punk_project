#ifndef _H_TRACKBALL_VIEWER_3D
#define _H_TRACKBALL_VIEWER_3D

#include "widget.h"

namespace OpenGL
{
	class VertexArrayObject;
	class RenderContext;
}

namespace Utility
{
	class Camera;
}

namespace GUI
{
	class TrackballViewer3D : public Widget
	{
		Utility::Camera* m_camera;
		std::vector<OpenGL::VertexArrayObject*> m_object_to_render;
	public:
		TrackballViewer3D(float x = 0, float y = 0, float width = 1, float height = 1, const System::string& text = L"", Widget* parent = 0);
		virtual void OnMouseMove(System::MouseMoveEvent* event);

		void SetCamera(Utility::Camera* m_camera);
	};
}

#endif	//	_H_TRACKBALL_VIEWER_3D