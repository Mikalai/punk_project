#include "trackball_viewer_3d.h"
#include "../utility/camera.h"

namespace GUI
{
	TrackballViewer3D::TrackballViewer3D(float x, float y, float width, float height, const System::string& text, Widget* parent)
		: Widget(x, y, width, height, text, parent)
	{
	}
}