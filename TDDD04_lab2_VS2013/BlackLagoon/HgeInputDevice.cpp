#include "HgeInputDevice.h"

HgeInputDevice::HgeInputDevice(HGE* hge)
: m_hge(hge)
{
}

HgeInputDevice::~HgeInputDevice()
{
}

bool HgeInputDevice::left()
{
	return m_hge->Input_GetKeyState(HGEK_LEFT);
}

bool HgeInputDevice::right()
{
	return m_hge->Input_GetKeyState(HGEK_RIGHT);
}

bool HgeInputDevice::up()
{
	return m_hge->Input_GetKeyState(HGEK_UP);
}

bool HgeInputDevice::down()
{
	return m_hge->Input_GetKeyState(HGEK_DOWN);
}

bool HgeInputDevice::turnLeft()
{
	return m_hge->Input_GetKeyState(HGEK_Q);;
}

bool HgeInputDevice::turnRight()
{
	return m_hge->Input_GetKeyState(HGEK_E);;
}

bool HgeInputDevice::fire()
{
	return m_hge->Input_KeyDown(HGEK_SPACE)|| m_hge->Input_KeyDown(HGEK_F);
}

bool HgeInputDevice::left2()
{
	return m_hge->Input_GetKeyState(HGEK_A);
}

bool HgeInputDevice::right2()
{
	return m_hge->Input_GetKeyState(HGEK_D);
}

bool HgeInputDevice::up2()
{
	return m_hge->Input_GetKeyState(HGEK_W);
}

bool HgeInputDevice::down2()
{
	return m_hge->Input_GetKeyState(HGEK_S);
}

bool HgeInputDevice::select()
{
	return m_hge->Input_KeyDown(HGEK_ENTER) || m_hge->Input_KeyDown(HGEK_SPACE);
}

bool HgeInputDevice::next()
{
	return m_hge->Input_KeyDown(HGEK_DOWN) || m_hge->Input_KeyDown(HGEK_RIGHT);
}

bool HgeInputDevice::previously()
{
	return m_hge->Input_KeyDown(HGEK_UP) || m_hge->Input_KeyDown(HGEK_LEFT);
}

bool HgeInputDevice::pause()
{
	return m_hge->Input_KeyDown(HGEK_P);
}

bool HgeInputDevice::displayInfo()
{
	return m_hge->Input_KeyDown(HGEK_I);
}

bool HgeInputDevice::exit()
{
	return m_hge->Input_KeyDown(HGEK_ESCAPE);
}