
#include "stdafx.h"

hgeVector CreateVectorFromAngle(float angle, float length)
{
	return hgeVector(cos(angle)*length, sin(angle)*length);
}

float NormalizeAngle(float angle)
{
	angle = fmod(angle, (2*M_PI));

	if (angle < 0)
		angle += (2*M_PI);

	return angle;
}

float NormalizeAnglePI(float angle)
{
	angle = fmod(angle, (2*M_PI));
	if (angle > M_PI)
		angle -= (2*M_PI);

	if (angle < (- M_PI))
		angle += (2*M_PI);

	return angle;
}

Rect ConvertBoundingBoxToRect(hgeRect* boundingBox)
{
	Rect result;
	result.topLeft().x = boundingBox->x1;
	result.topLeft().y = boundingBox->y1;
	result.bottomRight().x = boundingBox->x2;
	result.bottomRight().y = boundingBox->y2;
	return result;
}