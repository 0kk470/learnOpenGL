#include "Mouse.h"

float Mouse::LastX = 0;
float Mouse::LastY = 0;
bool Mouse::IsFirst = true;

bool Mouse::IsFisrtMove()
{
	return IsFirst;
}

void Mouse::SetFirstMove(bool bFirst)
{
	IsFirst = bFirst;
}

float Mouse::GetLastX()
{
	return LastX;
}

float Mouse::GetLastY()
{
	return LastY;
}

void Mouse::SetLastXY(float x, float y)
{
	LastX = x;
	LastY = y;
}
