#pragma once
#include "../GUI/Button.h"
class ButtonMap
{
public:
	static std::map<std::string, Button*>& GetMap();
};

