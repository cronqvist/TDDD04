#pragma once

class IGameWorldEvent
{
public:
	IGameWorldEvent(){};
	virtual ~IGameWorldEvent(){};
	virtual void run() = 0;
};
