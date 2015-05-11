#ifndef _STDAFX__H
#define _STDAFX__H

#include <hge.h>
#include <hgesprite.h>
#include <hgefont.h>
#include <hgegui.h>
#include <hgecolor.h>
#include <hgeparticle.h>

#include <ctime>
#include <math.h>
#include <vector>
#include <list>

#include "Coordinate.h"
#include "Rectangle.h"

#include "GameConstants.h"

#define SCREEN_WIDTH		800
#define SCREEN_HEIGHT		600
#define PLAY_AREA_WIDTH		600
#define PLAY_AREA_HEIGHT	600

#define SAFE_DELETE(x) { if(x) { delete x; x = 0; } }
#define SAFE_DESTROY(x) { if(x) { x->destroy(); x = 0; } }

typedef float CoordType;
typedef geometric::Coordinate<CoordType> Coord;
typedef geometric::Rectangle<CoordType> Rect;

hgeVector CreateVectorFromAngle(float angle, float length);
float NormalizeAngle(float angle);
float NormalizeAnglePI(float angle);
Rect ConvertBoundingBoxToRect(hgeRect* boundingBox);

#endif
