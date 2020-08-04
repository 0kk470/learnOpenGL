#pragma once
class Mouse
{
public:
	static bool IsFisrtMove();

	static void SetFirstMove(bool bFirst);

	static float GetLastX();

	static float GetLastY();

	static void SetLastXY(float x, float y);

private:
	static bool IsFirst;

	static float LastX, LastY;
};

