#include "IAI.h"

IAI::IAI(int level) : m_level(level)
{
}

IAI::~IAI()
{
}

void IAI::setLevel(int level)
{
	m_level = level;
}