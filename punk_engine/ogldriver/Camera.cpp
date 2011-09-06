#include <windows.h>
#include <gl\gl.h>
#include <gl\glext.h>

#include "Camera.h"

TCamera::TCamera() : roll(0), pitch(0), heading(0)
{
	memset(position, 0, sizeof(position));
	position[2] = 5;
}

void TCamera::Apply()
{
	glTranslatef(-position[0], -position[1], -position[2]);
	glRotatef(-roll, 0.0f, 0.0f, 1.0f);
	glRotatef(-pitch, 0.0f, 1.0f, 0.0f);
	glRotatef(heading, 1.0f, 0.0f, 0.0f);
	//glTranslatef(-position[0], -position[1], -position[2]);
}

void TCamera::Heading(float step)
{
	heading += step;
}

void TCamera::MoveEast(float step)
{
	position[0] += step;
}

void TCamera::MoveNorth(float step)
{
	position[2] += step;
}

void TCamera::MoveHeaven(float step)
{
	position[1] += step;
}

void TCamera::Pitch(float step)
{
	pitch += step;
}

void TCamera::SetProjection(void *projection)
{
}

void TCamera::Restore()
{
}

void TCamera::SetView(void *view)
{
}

void TCamera::Store()
{
}

void TCamera::Roll(float step)
{
	roll += step;
}

TCamera::~TCamera()
{
}



