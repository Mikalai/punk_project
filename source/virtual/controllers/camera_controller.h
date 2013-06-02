#ifndef _H_PUNK_VIRTUAL_CAMERA_CONTROLLER
#define _H_PUNK_VIRTUAL_CAMERA_CONTROLLER

#include "../../config.h"

namespace Virtual
{
	class Camera;
	class PUNK_ENGINE_API CameraController
	{
	public:
		CameraController(Camera* camera);

		void MoveRight(float offset);
		void MoveLeft(float offset);
		void MoveForward(float offset);
		void MoveBackward(float offset);

		void MoveAlongWorldAxisX(float offset);
		void MoveAlongWorldAxisY(float offset);
		void MoveAlongWorldAxisZ(float offset);

	private:
		//	should not be deleted 
		Camera* m_camera;
	};
}

#endif	//	_H_PUNK_VIRTUAL_CAMERA_CONTROLLER