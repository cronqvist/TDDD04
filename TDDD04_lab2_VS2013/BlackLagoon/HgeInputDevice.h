#pragma once
#include "iinputdevice.h"

#include <hge.h>

class HgeInputDevice :
	public IInputDevice
{
public:
	HgeInputDevice(HGE* hge);
	~HgeInputDevice();

	virtual bool left();
	virtual bool right();
	virtual bool up();
	virtual bool down();
	virtual bool turnLeft();
	virtual bool turnRight();
	virtual bool fire();
	virtual bool left2();
	virtual bool right2();
	virtual bool up2();
	virtual bool down2();

	virtual bool select();
	virtual bool next();
	virtual bool previously();

	virtual bool pause();
	virtual bool displayInfo();
	virtual bool exit();
private:
	HGE* m_hge;
};
