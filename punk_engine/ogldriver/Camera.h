#ifndef _CAMERA
#define _CAMERA

#include "../PunkEngine/common/ICamera.h"

class TCamera : public ICamera
{
public:
	virtual ~TCamera();
	virtual void SetProjection(void* projection);
	virtual void SetView(void* view);
	virtual void Store();
	virtual void Restore();
	//virtual void SetType(CameraType type);
	virtual void Apply();
	virtual void MoveNorth(float step);
	virtual void MoveEast(float step);
	virtual void MoveHeaven(float step);
	virtual void Roll(float step);
	virtual void Pitch(float step);
	virtual void Heading(float step);
private:
	friend class Scene;
	TCamera();

//	CameraType type;
	float position[3];
	float roll;				//крен
	float pitch;			//тангаж
	float heading;			//направление

	struct FpsParameters
	{
		float position[3];
		float roll;
		float pitch;
		float heading;
	};

	struct TpsParameters
	{
		float lookAt[3];
		float roll;
		float pitch;
		float heading;
		float distance;
	};

	union
	{
		FpsParameters fps;
		TpsParameters tps;
	}Parameters;
};

#endif