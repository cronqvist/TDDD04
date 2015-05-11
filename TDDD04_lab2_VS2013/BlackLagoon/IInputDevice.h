#pragma once

class IInputDevice
{
public:
	IInputDevice(){};
	virtual ~IInputDevice(){};
	virtual bool left()=0;
	virtual bool right()=0;
	virtual bool up()=0;
	virtual bool down()=0;
	virtual bool turnLeft()=0;
	virtual bool turnRight()=0;
	virtual bool fire()=0;
	virtual bool left2()=0;
	virtual bool right2()=0;
	virtual bool up2()=0;
	virtual bool down2()=0;

	virtual bool select()=0;
	virtual bool next()=0;
	virtual bool previously()=0;

	virtual bool pause()=0;
	virtual bool displayInfo()=0;
	virtual bool exit()=0;

};
