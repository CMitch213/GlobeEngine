#pragma once
class States
{
private:
	static bool bPaused;

public:
	static bool GetPausedState();
	static void SetPausedStated(bool bPaused);
};

